#include"WordBookForm.h"
#include"WordBook.h"
#include"FindingForm.h"
#include"resource.h"
#include<afxwin.h>//CDialog �������
#include<afxcmn.h>//CListCtrl�������


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
	this->wordBook = NULL;//NULL�� �ʱ�ȭ��Ŵ
}

//1.�����찡 ������ ��
BOOL WordBookForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	TCHAR partOfSpeechs[][8] = {
		"���",
		"����",
		"����",
		"�����",
		"�λ�",
		"��ġ��",
		"���ӻ�",
		"��ź��"
	};
	//1.1 �ܾ����� �����.
	this->wordBook = new WordBook;
	//1.2 �޺��ڽ��� �׸���� �߰��Ѵ�.
	Long index = 0;
	while (index < sizeof(partOfSpeechs) / sizeof(partOfSpeechs[0]))
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_PARTOFSPEECH))->AddString(partOfSpeechs[index]);
		index++;
	}
	//1.3 ����Ʈ����Ʈ���� ����׸��� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(0, "��ȣ", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(1, "ö��", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(2, "ǰ��", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(3, "�ǹ�", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(4, "����", LVCFMT_CENTER, 400);
	//1.4 ����Ʈ����Ʈ���� � �κ��� Ŭ���ص� ���õǵ��� �ϱ� ���� ��ġ
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.5 ������.
	return FALSE;
}

//2. �����ϱ� ��ư�� Ŭ������ ��
void WordBookForm::OnRecordButtonClicked()
{
	//2.1 ö��, ǰ��, �ǹ�, ���ø� �Է¹޴´�.
	CString spellings;
	GetDlgItem(IDC_EDIT_SPELLINGS)->GetWindowText(spellings);
	CString partOfSpeech;
	GetDlgItem(IDC_COMBO_PARTOFSPEECH)->GetWindowText(partOfSpeech);
	CString meanings;
	GetDlgItem(IDC_EDIT_MEANINGS)->GetWindowText(meanings);
	CString example;
	GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);
	//2.2 �ܾ��忡�� �����Ѵ�.
	Long index;
	index = this->wordBook->Record((LPCTSTR)spellings, (LPCTSTR)partOfSpeech, (LPCTSTR)meanings,
		(LPCTSTR)example);
	//2.3 ����Ʈ����Ʈ�ѿ� �׸��� �߰��Ѵ�.
	Word word;
	word = this->wordBook->GetAt(index);
	//2.3.1 ����Ʈ����Ʈ�ѿ� ��ȣ�� �߰��Ѵ�.
	CString number;
	number.Format("%d", index + 1);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(index, number);
	//2.3.2 ����Ʈ����Ʈ�ѿ� ö��, ǰ��, �ǹ�, ���ø� �߰��Ѵ�.
	spellings = CString(word.GetSpellings().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 1, spellings);
	partOfSpeech = CString(word.GetPartOfSpeech().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 2, partOfSpeech);
	meanings = CString(word.GetMeanings().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 3, meanings);
	example = CString(word.GetExample().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, example);
}

//3.ã���ư�� Ŭ������ ��
void WordBookForm::OnFindButtonClicked()
{
	FindingForm findingForm;//��ü����, ����O, �ּ�X
	//3.1 ã�� ������ �����츦 ����.
	findingForm.DoModal();
}


//4. ��ġ���ư�� Ŭ������ ��
void WordBookForm::OnCorrectButtonClicked()
{
	//4.1 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//4.2 ���ø� �д´�.
	CString example;
	GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);
	//4.3 �ܾ��忡�� ��ģ��.
	index = this->wordBook->Correct(index, (LPCTSTR)example);
	//4.4 ����Ʈ�� ��Ʈ�ѿ��� �׸��� ��ģ��.
	Word word;
	word = this->wordBook->GetAt(index);
	example = CString(word.GetExample().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, example);
}

//5. ������ư�� Ŭ������ ��
void WordBookForm::OnEraseButtonClicked()
{
	//5.1 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//5.2 �ܾ��忡�� �����.
	this->wordBook->Erase(index);
	//5.3 ����Ʈ�信 �ִ� �׸��� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteItem(index);
	//5.4 ����Ʈ����Ʈ�ѿ��� ��ȣ�� �ٽøű��.
	CString number;
	while (index < this->wordBook->GetLength())
	{
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 0, number);
		index++;
	}
}

//6. �����ϱ� ��ư�� Ŭ������ ��
void WordBookForm::OnArrangeButtonClicked()
{
	//6.1 �ܾ��忡�� �����Ѵ�.
	this->wordBook->Arrange();
	//6.2 ����Ʈ�� ��Ʈ�ѿ� �ִ� ��� �׸���� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteAllItems();
	//6.3 ����Ʈ�� ��Ʈ�ѿ� �ܾ����� ������ �߰��Ѵ�.
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
		//6.3.1 ����Ʈ����Ʈ�ѿ� ��ȣ�� �߰��Ѵ�.
		CString number;
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(index, number);
		//6.3.2 ����Ʈ����Ʈ�ѿ� ö��, ǰ��, �ǹ�, ���ø� �߰��Ѵ�.
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

//7. ����Ʈ�� ��Ʈ���� �׸��� ����Ŭ������ ��
void WordBookForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//7.1 ����Ʈ�� ��Ʈ���� ���õ� �׸��� ��ġ�� �д´�.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//7.2 ����Ʈ�� ��Ʈ�ѿ��� ���õ� �׸��� ö��, ǰ��, �ǹ�, ���ø� �д´�.
	CString spellings;
	spellings = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 1);
	CString partOfSpeech;
	partOfSpeech = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 2);
	CString meanings;
	meanings = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 3);
	CString example;
	example = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 4);
	//7.3 ����Ʈ�� ��Ʈ�ѿ��� ���� ö��, ǰ��, �ǹ�, ���ø� ����Ѵ�.
	GetDlgItem(IDC_EDIT_SPELLINGS)->SetWindowText(spellings);
	GetDlgItem(IDC_COMBO_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	GetDlgItem(IDC_EDIT_MEANINGS)->SetWindowText(meanings);
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}

//8.�ݱ� ��ư�� Ŭ������ ��
void WordBookForm::OnClose()
{
	//8.1 �ܾ����� �����.
	if (this->wordBook != NULL)
	{
		delete this->wordBook;
	}
	//8.2 �����츦 �ݴ´�.
	EndDialog(0);
}

