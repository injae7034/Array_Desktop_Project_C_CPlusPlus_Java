#include"WordBookForm.h"
#include"WordBook.h"
#include"FindingForm.h"
#include"resource.h"
#include<afxwin.h>//CDialog 헤더파일
#include<afxcmn.h>//CListCtrl헤더파일


BEGIN_MESSAGE_MAP(WordBookForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_WORDS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


WordBookForm::WordBookForm(CWnd* parent)
	:CDialog(WordBookForm::IDD, parent)
{
	this->wordBook = NULL;//NULL로 초기화시킴
}

//1.윈도우가 생성될 때
BOOL WordBookForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	TCHAR partOfSpeechs[][8] = {
		"명사",
		"대명사",
		"동사",
		"형용사",
		"부사",
		"전치사",
		"접속사",
		"감탄사"
	};
	//1.1 단어장을 만든다.
	this->wordBook = new WordBook;
	//1.2 콤보박스에 항목들을 추가한다.
	Long index = 0;
	while (index < sizeof(partOfSpeechs) / sizeof(partOfSpeechs[0]))
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_PARTOFSPEECH))->AddString(partOfSpeechs[index]);
		index++;
	}
	//1.3 리스트뷰컨트롤의 헤더항목을 만든다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(0, "번호", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(1, "철자", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(2, "품사", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(3, "의미", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(4, "예시", LVCFMT_CENTER, 400);
	//1.4 리스트뷰컨트롤의 어떤 부분을 클릭해도 선택되도록 하기 위한 조치
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.5 끝내다.
	return FALSE;
}

//2. 기재하기 버튼을 클릭했을 때
void WordBookForm::OnRecordButtonClicked()
{
	//2.1 철자, 품사, 의미, 예시를 입력받는다.
	CString spellings;
	GetDlgItem(IDC_EDIT_SPELLINGS)->GetWindowText(spellings);
	CString partOfSpeech;
	GetDlgItem(IDC_COMBO_PARTOFSPEECH)->GetWindowText(partOfSpeech);
	CString meanings;
	GetDlgItem(IDC_EDIT_MEANINGS)->GetWindowText(meanings);
	CString example;
	GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);
	//2.2 단어장에서 기재한다.
	Long index;
	index = this->wordBook->Record((LPCTSTR)spellings, (LPCTSTR)partOfSpeech, (LPCTSTR)meanings,
		(LPCTSTR)example);
	//2.3 리스트뷰컨트롤에 항목을 추가한다.
	Word word;
	word = this->wordBook->GetAt(index);
	//2.3.1 리스트뷰컨트롤에 번호를 추가한다.
	CString number;
	number.Format("%d", index + 1);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(index, number);
	//2.3.2 리스트뷰컨트롤에 철자, 품사, 의미, 예시를 추가한다.
	spellings = CString(word.GetSpellings().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 1, spellings);
	partOfSpeech = CString(word.GetPartOfSpeech().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 2, partOfSpeech);
	meanings = CString(word.GetMeanings().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 3, meanings);
	example = CString(word.GetExample().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, example);
}

//3.찾기버튼을 클릭했을 때
void WordBookForm::OnFindButtonClicked()
{
	FindingForm findingForm;//객체생성, 내용O, 주소X
	//3.1 찾기 츠레임 윈도우를 띄운다.
	findingForm.DoModal();
}


//4. 고치기버튼을 클릭했을 때
void WordBookForm::OnCorrectButtonClicked()
{
	//4.1 리스트뷰컨트롤에서 선택된 항목의 위치를 읽는다.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//4.2 예시를 읽는다.
	CString example;
	GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);
	//4.3 단어장에서 고친다.
	index = this->wordBook->Correct(index, (LPCTSTR)example);
	//4.4 리스트뷰 컨트롤에서 항목을 고친다.
	Word word;
	word = this->wordBook->GetAt(index);
	example = CString(word.GetExample().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, example);
}

//5. 지우기버튼을 클릭했을 때
void WordBookForm::OnEraseButtonClicked()
{
	//5.1 리스트뷰컨트롤에서 선택된 항목의 위치를 읽는다.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//5.2 단어장에서 지운다.
	this->wordBook->Erase(index);
	//5.3 리스트뷰에 있는 항목을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteItem(index);
	//5.4 리스트뷰컨트롤에서 번호를 다시매긴다.
	CString number;
	while (index < this->wordBook->GetLength())
	{
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 0, number);
		index++;
	}
}

//6. 정리하기 버튼을 클릭했을 떄
void WordBookForm::OnArrangeButtonClicked()
{
	//6.1 단어장에서 정렬한다.
	this->wordBook->Arrange();
	//6.2 리스트뷰 컨트롤에 있는 모든 항목들을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteAllItems();
	//6.3 리스트뷰 컨트롤에 단어장의 내용을 추가한다.
	Word word;
	CString number;
	CString spellings;
	CString partOfSpeech;
	CString meanings;
	CString example;
	Long index = 0;
	while (index < this->wordBook->GetLength())
	{
		Word word;
		word = this->wordBook->GetAt(index);
		//6.3.1 리스트뷰컨트롤에 번호를 추가한다.
		CString number;
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(index, number);
		//6.3.2 리스트뷰컨트롤에 철자, 품사, 의미, 예시를 추가한다.
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

//7. 리스트뷰 컨트롤의 항목을 더블클릭했을 때
void WordBookForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//7.1 리스트뷰 컨트롤의 선택된 항목의 위치를 읽는다.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//7.2 리스트뷰 컨트롤에서 선택된 항목의 철자, 품사, 의미, 예시를 읽는다.
	CString spellings;
	spellings = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 1);
	CString partOfSpeech;
	partOfSpeech = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 2);
	CString meanings;
	meanings = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 3);
	CString example;
	example = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 4);
	//7.3 리스트뷰 컨트롤에서 읽은 철자, 품사, 의미, 예시를 출력한다.
	GetDlgItem(IDC_EDIT_SPELLINGS)->SetWindowText(spellings);
	GetDlgItem(IDC_COMBO_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	GetDlgItem(IDC_EDIT_MEANINGS)->SetWindowText(meanings);
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}

//8.닫기 버튼을 클릭했을 때
void WordBookForm::OnClose()
{
	//8.1 단어장을 지운다.
	if (this->wordBook != NULL)
	{
		delete this->wordBook;
	}
	//8.2 윈도우를 닫는다.
	EndDialog(0);
}

