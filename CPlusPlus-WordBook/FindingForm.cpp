#include "FindingForm.h"
#include "WordBookForm.h"
#include "WordBook.h"
#include"resource.h"
#include<afxwin.h>//CDialog헤더파일
#include<afxcmn.h>//CListCtrl헤더파일

BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_RADIO_SPELLINGS, OnRadioButtonSpellingsClicked)
	ON_BN_CLICKED(IDC_RADIO_MEANINGS, OnRadioButtonMeaningsClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_WORDS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

FindingForm::FindingForm(CWnd* parent)
	:CDialog(FindingForm::IDD, parent)
{
	this->wordBookForm = (WordBookForm*)parent;
	this->indexes = NULL;
	this->count = 0;
}

//1. 찾기 프레임 윈도우가 생성될 때
BOOL FindingForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 리스트뷰컨트롤의 헤더항목을 만든다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(0, "번호", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(1, "철자", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(2, "품사", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(3, "의미", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(4, "예시", LVCFMT_CENTER, 400);
	//1.2 리스트뷰컨트롤의 어떤 부분을 클릭해도 선택되도록 하기 위한 조치
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.3 철자 라디오버튼을 선택한다.
	((CButton*)GetDlgItem(IDC_RADIO_SPELLINGS))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_MEANINGS))->SetCheck(BST_UNCHECKED);
	//1.4 끝내다.
	return FALSE;
}

//2. 찾기 버튼을 클릭했을 때
void FindingForm::OnFindButtonClicked()
{
	//2.1 단어장 프레임 윈도우를 찾는다.
	WordBookForm* wordBookForm;
	wordBookForm = (WordBookForm*)CWnd::FindWindow("#32770", "단어장");
	//2.2 철자 라디오 버튼을 읽는다.
	int spellingsChecked;
	spellingsChecked = ((CButton*)GetDlgItem(IDC_RADIO_SPELLINGS))->GetCheck();
	//2.3 의미 라디오 버튼을 읽는다.
	int meaningsChecked;
	meaningsChecked = ((CButton*)GetDlgItem(IDC_RADIO_MEANINGS))->GetCheck();
	//할당해제(FindingForm 윈도우를 끄지 않고 찾기 버튼을 중복해서 누를 경우 필요함.)
	if (this->indexes != NULL)
	{
		delete[]this->indexes;
	}
	CString spellings;
	CString meanings;
	//2.4 철자라디오버튼이 선택되어 있으면
	if (spellingsChecked == BST_CHECKED)
	{
		//2.4.1 철자를 읽는다.
		GetDlgItem(IDC_EDIT_SPELLINGS)->GetWindowText(spellings);
		//2.4.2 단어장 프레임 윈도우의 단어장에서 철자를 찾는다.
		wordBookForm->wordBook->FindBySpellings((LPCTSTR)spellings, &this->indexes, &this->count);
	}
	//2.5 의미라디오 버튼이 선택되어 있으면
	else if (meaningsChecked == BST_CHECKED)
	{
		//2.5.1 의미를 읽는다.
		GetDlgItem(IDC_EDIT_MEANINGS)->GetWindowText(meanings);
		//2.5.2 단어장 프레임 윈도우의 단어장에서 의미를 찾는다.
		wordBookForm->wordBook->FindByMeanings((LPCTSTR)meanings, &this->indexes, &this->count);
	}
	//2.6 리스트뷰 컨트롤에 있는 모든 항목들을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteAllItems();
	//2.7 리스트뷰 컨트롤에서 찾은 개수만큼 항목들을 추가한다.
	Word word;
	CString number;
	CString partOfSpeech;
	CString example;
	Long index = 0;
	while (index < this->count)
	{
		word = wordBookForm->wordBook->GetAt(this->indexes[index]);
		//2.7.1 리스트뷰컨트롤에 번호를 추가한다.
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(index, number);
		//2.7.2 리스트뷰컨트롤에 철자, 품사, 의미, 예시를 추가한다.
		spellings = CString(word.GetSpellings().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 1, spellings);
		partOfSpeech = CString(word.GetPartOfSpeech().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 2, partOfSpeech);
		meanings = CString(word.GetMeanings().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 3, meanings);
		example = CString(word.GetExample().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, example);
		index++;
	}
}

//3. 철자 라디오 버튼을 클릭했을 때
void FindingForm::OnRadioButtonSpellingsClicked()
{
	//3.1 의미 에디트를 공란으로 만든다.
	GetDlgItem(IDC_EDIT_MEANINGS)->SetWindowText("");
}

//4. 의미 라디오 버튼을 클릭했을 때
void FindingForm::OnRadioButtonMeaningsClicked()
{
	//4.1 철자 에디트를 공란으로 만든다.
	GetDlgItem(IDC_EDIT_SPELLINGS)->SetWindowText("");
}

//5. 리스트뷰 컨트롤에 있는 항목을 더블클릭했을 때
void FindingForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//5.1  리스트뷰 컨트롤의 선택된 항목의 위치를 읽는다.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//5.2 리스트뷰 컨트롤에서 선택된 항목의 철자, 품사, 의미, 예시를 읽는다.
	CString spellings;
	spellings = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 1);
	CString partOfSpeech;
	partOfSpeech = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 2);
	CString meanings;
	meanings = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 3);
	CString example;
	example = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 4);
	//5.3 단어장 프레임 윈도우를 찾는다.
	WordBookForm* wordBookForm;
	wordBookForm = (WordBookForm*)CWnd::FindWindow("#32770", "단어장");
	//5.4 단어장 프레임 윈도우에 철자, 품사, 의미, 예시를 출력한다.
	wordBookForm->GetDlgItem(IDC_EDIT_SPELLINGS)->SetWindowText(spellings);
	wordBookForm->GetDlgItem(IDC_COMBO_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	wordBookForm->GetDlgItem(IDC_EDIT_MEANINGS)->SetWindowText(meanings);
	wordBookForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
	//5.5 단어장 프레임 윈도우의 리스트뷰 컨트롤에서 항목을 선택한다.
	((CListCtrl*)wordBookForm->GetDlgItem(IDC_LIST_WORDS))->SetSelectionMark(this->indexes[index]);
	//5.6 윈도우를 닫는다.
	if (this->indexes != NULL)
	{
		delete[]this->indexes;
	}
	EndDialog(0);
}

//6.닫기버튼을 클릭했을 때
void FindingForm::OnClose()
{
	//6.1 색인 배열을 없앤다.
	if (this->indexes != NULL)
	{
		delete[]this->indexes;
	}
	//6.2 윈도우를 닫는다.
	EndDialog(0);
}