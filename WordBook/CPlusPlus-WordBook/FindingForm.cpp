#include "FindingForm.h"
#include "WordBookForm.h"
#include "WordBook.h"
#include"resource.h"
#include<afxwin.h>//CDialog�������
#include<afxcmn.h>//CListCtrl�������

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

//1. ã�� ������ �����찡 ������ ��
BOOL FindingForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 ����Ʈ����Ʈ���� ����׸��� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(0, "��ȣ", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(1, "ö��", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(2, "ǰ��", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(3, "�ǹ�", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(4, "����", LVCFMT_CENTER, 400);
	//1.2 ����Ʈ����Ʈ���� � �κ��� Ŭ���ص� ���õǵ��� �ϱ� ���� ��ġ
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.3 ö�� ������ư�� �����Ѵ�.
	((CButton*)GetDlgItem(IDC_RADIO_SPELLINGS))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_MEANINGS))->SetCheck(BST_UNCHECKED);
	//1.4 ������.
	return FALSE;
}

//2. ã�� ��ư�� Ŭ������ ��
void FindingForm::OnFindButtonClicked()
{
	//2.1 �ܾ��� ������ �����츦 ã�´�.
	WordBookForm* wordBookForm;
	wordBookForm = (WordBookForm*)CWnd::FindWindow("#32770", "�ܾ���");
	//2.2 ö�� ���� ��ư�� �д´�.
	int spellingsChecked;
	spellingsChecked = ((CButton*)GetDlgItem(IDC_RADIO_SPELLINGS))->GetCheck();
	//2.3 �ǹ� ���� ��ư�� �д´�.
	int meaningsChecked;
	meaningsChecked = ((CButton*)GetDlgItem(IDC_RADIO_MEANINGS))->GetCheck();
	//�Ҵ�����(FindingForm �����츦 ���� �ʰ� ã�� ��ư�� �ߺ��ؼ� ���� ��� �ʿ���.)
	if (this->indexes != NULL)
	{
		delete[]this->indexes;
	}
	CString spellings;
	CString meanings;
	//2.4 ö�ڶ�����ư�� ���õǾ� ������
	if (spellingsChecked == BST_CHECKED)
	{
		//2.4.1 ö�ڸ� �д´�.
		GetDlgItem(IDC_EDIT_SPELLINGS)->GetWindowText(spellings);
		//2.4.2 �ܾ��� ������ �������� �ܾ��忡�� ö�ڸ� ã�´�.
		wordBookForm->wordBook->FindBySpellings((LPCTSTR)spellings, &this->indexes, &this->count);
	}
	//2.5 �ǹ̶��� ��ư�� ���õǾ� ������
	else if (meaningsChecked == BST_CHECKED)
	{
		//2.5.1 �ǹ̸� �д´�.
		GetDlgItem(IDC_EDIT_MEANINGS)->GetWindowText(meanings);
		//2.5.2 �ܾ��� ������ �������� �ܾ��忡�� �ǹ̸� ã�´�.
		wordBookForm->wordBook->FindByMeanings((LPCTSTR)meanings, &this->indexes, &this->count);
	}
	//2.6 ����Ʈ�� ��Ʈ�ѿ� �ִ� ��� �׸���� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteAllItems();
	//2.7 ����Ʈ�� ��Ʈ�ѿ��� ã�� ������ŭ �׸���� �߰��Ѵ�.
	Word word;
	CString number;
	CString partOfSpeech;
	CString example;
	Long index = 0;
	while (index < this->count)
	{
		word = wordBookForm->wordBook->GetAt(this->indexes[index]);
		//2.7.1 ����Ʈ����Ʈ�ѿ� ��ȣ�� �߰��Ѵ�.
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(index, number);
		//2.7.2 ����Ʈ����Ʈ�ѿ� ö��, ǰ��, �ǹ�, ���ø� �߰��Ѵ�.
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

//3. ö�� ���� ��ư�� Ŭ������ ��
void FindingForm::OnRadioButtonSpellingsClicked()
{
	//3.1 �ǹ� ����Ʈ�� �������� �����.
	GetDlgItem(IDC_EDIT_MEANINGS)->SetWindowText("");
}

//4. �ǹ� ���� ��ư�� Ŭ������ ��
void FindingForm::OnRadioButtonMeaningsClicked()
{
	//4.1 ö�� ����Ʈ�� �������� �����.
	GetDlgItem(IDC_EDIT_SPELLINGS)->SetWindowText("");
}

//5. ����Ʈ�� ��Ʈ�ѿ� �ִ� �׸��� ����Ŭ������ ��
void FindingForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//5.1  ����Ʈ�� ��Ʈ���� ���õ� �׸��� ��ġ�� �д´�.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//5.2 ����Ʈ�� ��Ʈ�ѿ��� ���õ� �׸��� ö��, ǰ��, �ǹ�, ���ø� �д´�.
	CString spellings;
	spellings = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 1);
	CString partOfSpeech;
	partOfSpeech = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 2);
	CString meanings;
	meanings = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 3);
	CString example;
	example = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 4);
	//5.3 �ܾ��� ������ �����츦 ã�´�.
	WordBookForm* wordBookForm;
	wordBookForm = (WordBookForm*)CWnd::FindWindow("#32770", "�ܾ���");
	//5.4 �ܾ��� ������ �����쿡 ö��, ǰ��, �ǹ�, ���ø� ����Ѵ�.
	wordBookForm->GetDlgItem(IDC_EDIT_SPELLINGS)->SetWindowText(spellings);
	wordBookForm->GetDlgItem(IDC_COMBO_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	wordBookForm->GetDlgItem(IDC_EDIT_MEANINGS)->SetWindowText(meanings);
	wordBookForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
	//5.5 �ܾ��� ������ �������� ����Ʈ�� ��Ʈ�ѿ��� �׸��� �����Ѵ�.
	((CListCtrl*)wordBookForm->GetDlgItem(IDC_LIST_WORDS))->SetSelectionMark(this->indexes[index]);
	//5.6 �����츦 �ݴ´�.
	if (this->indexes != NULL)
	{
		delete[]this->indexes;
	}
	EndDialog(0);
}

//6.�ݱ��ư�� Ŭ������ ��
void FindingForm::OnClose()
{
	//6.1 ���� �迭�� ���ش�.
	if (this->indexes != NULL)
	{
		delete[]this->indexes;
	}
	//6.2 �����츦 �ݴ´�.
	EndDialog(0);
}