#include "FindingForm.h"
#include "AddressBook.h"
#include "resource.h"
#include "AddressBookForm.h"
#include<afxwin.h>//CDialog �������
#include<afxcmn.h>//CListCtrl�������

BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

FindingForm::FindingForm(CWnd* parent)
	: CDialog(FindingForm::IDD, parent)
{
	this->indexes = NULL;
	this->count = 0;
}

BOOL FindingForm::OnInitDialog()
{
	//1. ã�������� �����찡 ������ ��
	CDialog::OnInitDialog();
	//1.1 ����Ʈ�� ��Ʈ���� ����׸���� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, "��ȣ", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, "����", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, "�ּ�", LVCFMT_CENTER, 300);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, "��ȭ��ȣ", LVCFMT_CENTER, 200);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, "�̸����ּ�", LVCFMT_CENTER, 300);
	//1.2 ����Ʈ�� ��Ʈ���� � �κ��� Ŭ���ص� ������ �ǰ� �ϱ� ���� ����
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.3 ������.
	return FALSE;
}

//2. ã���ư�� Ŭ������ ��
void FindingForm::OnFindButtonClicked()
{
	//2.1 ������ �Է¹޴´�.
	CString name;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	//2.2 �ּҷ� �����������츦 ã�´�.
	AddressBookForm* addressBookForm;
	addressBookForm = (AddressBookForm*)CWnd::FindWindow("#32770", "�ּҷ�");
	//2.3 �ּҷ� ������ �������� �ּҷϿ��� ã�´�.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	addressBookForm->addressBook->Find((LPCTSTR)name, &this->indexes, &this->count);
	//2.4 ����Ʈ����Ʈ�ѿ� �ִ� ����׸���� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();
	//2.5 ����Ʈ����Ʈ�ѿ��� ã�� ������ŭ �׸���� �߰��Ѵ�.
	CString number;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Personal personal;
	Long index = 0;
	while (index < this->count)
	{
		//2.5.1 personal�� ���Ѵ�.
		personal = addressBookForm->addressBook->AddressBook_GetAt(this->indexes[index]);
		//2.5.2 ����Ʈ�� ��Ʈ�ѿ� ��ȣ�� �����Ѵ�.
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(index, number);
		//2.5.3 ����Ʈ�� ��Ʈ�ѿ� ������ �����Ѵ�.
		name = CString(personal.GetName().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 1, name);
		//2.5.4 ����Ʈ����Ʈ�ѿ� �ּҸ� �����Ѵ�.
		address = CString(personal.GetAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);
		//2.5.5 ����Ʈ����Ʈ�ѿ� ��ȭ��ȣ�� �����Ѵ�.
		telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);
		//2.5.6 ����Ʈ����Ʈ�ѿ� �̸����ּҸ� �����Ѵ�.
		emailAddress = CString(personal.GetEmailAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, emailAddress);
		index++;
	}
}

//3. ����Ʈ�� ��Ʈ���� �׸��� ����Ŭ������ ��
void FindingForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//3.1 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
	Long index;
	index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	//3.2 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ������ �д´�.
	CString name;
	name = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	//3.3 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� �ּҸ� �д´�.
	CString address;
	address = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	//3.4 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ȭ��ȣ�� �д´�.
	CString telephoneNumber;
	telephoneNumber = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	//3.5 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� �̸����ּҸ� �д´�.
	CString emailAddress;
	emailAddress = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);
	//3.6 �ּҷ� �����������츦 ã�´�.
	AddressBookForm* addressBookForm;
	addressBookForm = (AddressBookForm*)CWnd::FindWindow("#32770", "�ּҷ�");
	//3.7 �ּҷ� ������ �������� ����Ʈ��Ʈ�ѿ� ������ ����Ѵ�.
	addressBookForm->GetDlgItem(IDC_EDIT_NAME)->SetWindowText(name);
	//3.8 �ּҷ� ������ �������� ����Ʈ��Ʈ�ѿ� �ּҸ� ����Ѵ�.
	addressBookForm->GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
	//3.9 �ּҷ� ������ �������� ����Ʈ��Ʈ�ѿ� ��ȭ��ȣ�� ����Ѵ�.
	addressBookForm->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	//3.10 �ּҷ� ������ �������� ����Ʈ��Ʈ�ѿ� �̸����ּҸ� ����Ѵ�.
	addressBookForm->GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
	//3.11 �ּҷ� ������ �������� ����Ʈ�� ��Ʈ�ѿ��� �׸��� �����Ѵ�.
	((CListCtrl*)addressBookForm->GetDlgItem(IDC_LIST_PERSONALS))->SetSelectionMark(this->indexes[index]);
	//3.12 �����츦 �ݴ´�.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	EndDialog(0);
}

//4. �ݱ��ư�� Ŭ������ ��
void FindingForm::OnClose()
{
	//4.1 ���ι迭�� ���ش�.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	//4.2 �����츦 �ݴ´�.
	EndDialog(0);
}