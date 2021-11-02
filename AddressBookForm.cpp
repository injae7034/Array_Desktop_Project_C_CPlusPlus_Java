#include "AddressBookForm.h"
#include "FindingForm.h"
#include "AddressBook.h"
#include "resource.h"
#include<afxwin.h>//CDialog �������
#include<afxcmn.h>//CListCtrl�������
#include<afxdb.h>//ODBC class

BEGIN_MESSAGE_MAP(AddressBookForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClikced)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

AddressBookForm::AddressBookForm(CWnd* parent)
	:CDialog(AddressBookForm::IDD, parent)//IDD=IDD_ADDRESSBOOKFORM
{
	this->addressBook = NULL;//MFC������ C++�� 0��� NULL�� �ʱ�ȭ��Ŵ. 
}


//�����ͺ��̽��������α׷��� ����
void AddressBookForm::Load()
{
	CDatabase db;//Connection, INSERT, DELETE, UPDATE, Disconnection
	CRecordset rs(&db);//SELECT
	CString sql = "SELECT Personal.name, Personal.address, Personal.telephoneNumber, personal.emailAddress FROM Personal;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=1q2w3e");//Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//Request, Response
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	while (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0, name);
		rs.GetFieldValue((short)1, address);
		rs.GetFieldValue((short)2, telephoneNumber);
		rs.GetFieldValue((short)3, emailAddress);
		this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);
		rs.MoveNext();
	}
	//DisConnection
	rs.Close();
	db.Close();
}

void AddressBookForm::Save()
{
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=1q2w3e");//Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//Request, Response ��������� �ڵ���� ������
	CString sql2 = "DELETE FROM Personal;";//���ο� �����͸� �����ͺ��̽��� �����ϱ� ���� ������ �����͸� �� ����.
	db.ExecuteSQL(sql2);
	CString code;
	CString sql3;
	Personal personal;
	Long i = 0;
	while (i < this->addressBook->GetLength())
	{
		rs.GetFieldValue((short)0, code);
		personal = this->addressBook->AddressBook_GetAt(i);
		sql3.Format("INSERT INTO Personal(code, name, address, telephoneNumber, emailAddress) "
			"VALUES('%s', '%s', '%s', '%s', '%s');", (LPCTSTR)code, personal.GetName().c_str(),
			personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str());
		db.ExecuteSQL(sql3);
		rs.MoveNext();
		i++;
	}
	rs.Close();
	db.Close();
}
void AddressBookForm::Insert(Long index)
{
	CDatabase db;
	Personal personal = this->addressBook->AddressBook_GetAt(index);
	CString sql;
	CString code = this->GetCode();
	sql.Format("INSERT INTO Personal(code, name, address, telephoneNumber, emailAddress) "
		"VALUES('%s', '%s', '%s', '%s', '%s');", (LPCTSTR)code, personal.GetName().c_str(),
		personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str());
	db.OpenEx("DSN=AddressBook;UID=root;PWD=1q2w3e");//Connection
	db.ExecuteSQL(sql);//Request
	db.Close();//Disconnection
}

CString AddressBookForm::GetCode()
{
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal ORDER BY code DESC;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=1q2w3e");//Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString code = "P0000"; 
	int number;
	if (!rs.IsEOF())//�����ͺ��̽��� ����� �����Ͱ� ������
	{
		rs.GetFieldValue((short)0, code);
	}
	number = _ttoi(code.Right(4));
	number++;
	code.Format("P%04d", number);
	rs.Close();
	db.Close();

	return code;
}

void AddressBookForm::Delete(Long index)
{
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=1q2w3e");//Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString code;
	Long i = 0;
	while (!rs.IsEOF() && i <= index)
	{
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}
	sql.Format("DELETE FROM Personal WHERE code = '%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);
	rs.Close();
	db.Close();
}

void AddressBookForm::Update(Long index)
{
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=1q2w3e");//Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString code;
	Personal personal = this->addressBook->AddressBook_GetAt(index);
	Long i = 0;
	while (!rs.IsEOF() && i <= index)
	{
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}
	sql.Format("UPDATE Personal SET address='%s', telephoneNumber='%s', emailAddress='%s' WHERE code='%s';",
		personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str(),
		(LPCTSTR)code);
	db.ExecuteSQL(sql);
	rs.Close();
	db.Close();
}
//�����ͺ��̽��������α׷��� ��


BOOL AddressBookForm::OnInitDialog()
{
	//1. �����찡 ������ ��
	CDialog::OnInitDialog();
	//1.1 �ּҷ��� �����.
	this->addressBook = new AddressBook;//�迭�� �ƴ϶� �ּҸ� ������ �Ϲ� �����ͺ�����.
	//1.2 ����Ʈ�� ��Ʈ���� ����׸���� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, "��ȣ", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, "����", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, "�ּ�", LVCFMT_CENTER, 300);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, "��ȭ��ȣ", LVCFMT_CENTER, 200);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, "�̸����ּ�", LVCFMT_CENTER, 300);
	//1.3 ����Ʈ�� ��Ʈ���� � �κ��� Ŭ���ص� ������ �ǰ� �ϱ� ���� ����
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.4 �����ͺ��̽��� �ִ� �����͵��� �ּҷϿ� �����Ѵ�.
	this->Load();
	//1.5 �ּҷϿ� ����� ������ŭ ����Ʈ�� ��Ʈ�ѿ� �׸���� �߰��Ѵ�.
	Personal personal;
	CString number;
	Long i = 0;
	while (i < this->addressBook->GetLength())
	{
		personal = this->addressBook->AddressBook_GetAt(i);
		number.Format("%d", i + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(i, number);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 1, personal.GetName().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 2, personal.GetAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 3, personal.GetTelephoneNumber().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 4, personal.GetEmailAddress().c_str());
		i++;
	}
	//1.6 ������.
	return FALSE;
}

//2. �����ϱ� ��ư�� Ŭ������ ��
void AddressBookForm::OnRecordButtonClikced()
{
	//2.1 ������ �д´�.
	CString name;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	//2.2 �ּҸ� �д´�.
	CString address;
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	//2.3 ��ȭ��ȣ�� �д´�.
	CString telephoneNumber;
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	//2.4 �̸����ּҸ� �д´�.
	CString emailAddress;
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	//2.5 ���� ������ �ּҷϿ� �����Ѵ�.
	Long index;
	index = this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber,
		(LPCTSTR)emailAddress);
	//2.6 �����ͺ��̽��� �����Ѵ�.
	this->Insert(index);
	//2.7 personal�� ���Ѵ�.
	Personal personal;
	personal = this->addressBook->AddressBook_GetAt(index);
	//2.8 ����Ʈ����Ʈ�ѿ� ��ȣ�� �����Ѵ�.
	CString number;
	number.Format("%d", index + 1);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(index, number);
	//2.9 ����Ʈ�� ��Ʈ�ѿ� ������ �����Ѵ�.
	name = CString(personal.GetName().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 1, name);
	//2.10 ����Ʈ����Ʈ�ѿ� �ּҸ� �����Ѵ�.
	address = CString(personal.GetAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);
	//2.11 ����Ʈ����Ʈ�ѿ� ��ȭ��ȣ�� �����Ѵ�.
	telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);
	//2.12 ����Ʈ����Ʈ�ѿ� �̸����ּҸ� �����Ѵ�.
	emailAddress = CString(personal.GetEmailAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, emailAddress);
}

//3. ã���ư�� Ŭ������ ��
void AddressBookForm::OnFindButtonClicked()
{
	FindingForm findingForm;//��ü����, ����
	//3.1 ã�� ������ �����츦 ����.
	findingForm.DoModal();// �����̹Ƿ� .���� ���������.
}

//4. ��ġ���ư�� Ŭ������ ��
void AddressBookForm::OnCorrectButtonClicked()
{
	//4.1 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
	Long index;
	index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	//4.2 �ּҸ� �д´�.
	CString address;
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	//4.3 ��ȭ��ȣ�� �д´�.
	CString telephoneNumber;
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	//4.4 �̸����ּҸ� �д´�.
	CString emailAddress;
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	//4.5 �ּҷϿ��� ��ģ��.
	index = this->addressBook->Correct(index, (LPCTSTR)address, (LPCTSTR)telephoneNumber,
		(LPCTSTR)emailAddress);
	//4.6 �����ͺ��̽����� ��ģ��.
	this->Update(index);
	//4.7 Personal�� ���Ѵ�.
	Personal personal;
	personal = this->addressBook->AddressBook_GetAt(index);
	//4.8 ����Ʈ����Ʈ�ѿ��� �ּҸ� ��ģ��.
	address = CString(personal.GetAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);
	//4.9 ����Ʈ����Ʈ�ѿ��� ��ȭ��ȣ�� ��ģ��.
	telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);
	//4.10 ����Ʈ����Ʈ�ѿ��� �̸����ּҸ� ��ģ��.
	emailAddress = CString(personal.GetEmailAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, emailAddress);
}

//5. ������ư�� Ŭ������ ��
void AddressBookForm::OnEraseButtonClicked()
{
	//5.1 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
	Long index;
	index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	//5.2 �ּҷϿ��� �����.
	this->addressBook->Erase(index);
	//5.3 �����ͺ��̽����� �����.
	this->Delete(index);
	//5.4 ����Ʈ����Ʈ�ѿ��� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteItem(index);
	//5.5 ����Ʈ����Ʈ�ѿ��� ��ȣ�� �ٽ� �ű��.
	CString number;
	while (index < this->addressBook->GetLength())
	{
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 0, number);
		index++;
	}
}

//6. �����ϱ� ��ư�� Ŭ������ ��
void AddressBookForm::OnArrangeButtonClicked()
{
	//6.1 �ּҷϿ��� �����Ѵ�.
	this->addressBook->Arrange();
	//6.2 ����Ʈ����Ʈ�ѿ� �ִ� ����׸���� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();
	//6.3 ����Ʈ�� ��Ʈ�ѿ� �ּҷ��� ������ �߰��Ѵ�.
	CString number;
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Personal personal;
	Long index = 0;
	while (index < this->addressBook->GetLength())
	{
		//6.3.1 personal�� ���Ѵ�.
		personal = this->addressBook->AddressBook_GetAt(index);
		//6.3.2 ����Ʈ�� ��Ʈ�ѿ� ��ȣ�� �����Ѵ�.
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(index, number);
		//6.3.3 ����Ʈ�� ��Ʈ�ѿ� ������ �����Ѵ�.
		name = CString(personal.GetName().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 1, name);
		//6.3.4 ����Ʈ����Ʈ�ѿ� �ּҸ� �����Ѵ�.
		address = CString(personal.GetAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);
		//6.3.5 ����Ʈ����Ʈ�ѿ� ��ȭ��ȣ�� �����Ѵ�.
		telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);
		//6.3.6 ����Ʈ����Ʈ�ѿ� �̸����ּҸ� �����Ѵ�.
		emailAddress = CString(personal.GetEmailAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, emailAddress);
		index++;
	}
}

//7. ����Ʈ�� ��Ʈ���� �׸��� ���� Ŭ������ ��
void AddressBookForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//7.1 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
	Long index;
	index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	//7.2 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ������ �д´�.
	CString name;
	name = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	//7.3 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� �ּҸ� �д´�.
	CString address;
	address = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	//7.4 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ȭ��ȣ�� �д´�.
	CString telephoneNumber;
	telephoneNumber = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	//7.5 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� �̸����ּҸ� �д´�.
	CString emailAddress;
	emailAddress = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);
	//7.6 ����Ʈ��Ʈ�ѿ� ������ ����Ѵ�.
	GetDlgItem(IDC_EDIT_NAME)->SetWindowText(name);
	//7.7 ����Ʈ��Ʈ�ѿ� �ּҸ� ����Ѵ�.
	GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
	//7.8 ����Ʈ��Ʈ�ѿ� ��ȭ��ȣ�� ����Ѵ�.
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	//7.9 ����Ʈ��Ʈ�ѿ� �̸����ּҸ� ����Ѵ�.
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
}

void AddressBookForm::OnClose()//AddressBookForm::->�غ� �ǹ��� this��.
{
	//8.�ݱ��ư�� Ŭ������ ��
	if (this->addressBook != NULL)
	{
		//8.1 �ּҷ��� ������ �����ͺ��̽��� �����Ѵ�.
		this->Save();
		//8.2 �ּҷ��� �����.
		delete this->addressBook;
	}
	//8.3 �����츦 �ݴ´�.
	EndDialog(0);// this->EndDialog(0); �� ���� ���������� this�� �Ƚᵵ MFC���� �˾Ƽ� ó������.
}
