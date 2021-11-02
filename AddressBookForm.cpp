#include "AddressBookForm.h"
#include "FindingForm.h"
#include "AddressBook.h"
#include "resource.h"
#include<afxwin.h>//CDialog 헤더파일
#include<afxcmn.h>//CListCtrl헤더파일
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
	this->addressBook = NULL;//MFC에서는 C++의 0대신 NULL로 초기화시킴. 
}


//데이터베이스응용프로그래밍 시작
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
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//Request, Response 지우기전에 코드들을 저장함
	CString sql2 = "DELETE FROM Personal;";//새로운 데이터를 데이터베이스에 저장하기 전에 기존의 데이터를 다 지움.
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
	if (!rs.IsEOF())//데이터베이스에 저장된 데이터가 있으면
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
//데이터베이스응용프로그래밍 끝


BOOL AddressBookForm::OnInitDialog()
{
	//1. 윈도우가 생성될 때
	CDialog::OnInitDialog();
	//1.1 주소록을 만든다.
	this->addressBook = new AddressBook;//배열이 아니라 주소를 저장할 일반 포인터변수임.
	//1.2 리스트뷰 컨트를의 헤더항목들을 만든다.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, "번호", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, "성명", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, "주소", LVCFMT_CENTER, 300);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, "전화번호", LVCFMT_CENTER, 200);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, "이메일주소", LVCFMT_CENTER, 300);
	//1.3 리스트뷰 컨트롤의 어떤 부분을 클랙해도 선택이 되게 하기 위한 수단
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.4 데이터베이스에 있는 데이터들을 주소록에 적재한다.
	this->Load();
	//1.5 주소록에 적재된 개수만큼 리스트뷰 컨트롤에 항목들을 추가한다.
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
	//1.6 끝내다.
	return FALSE;
}

//2. 기재하기 버튼을 클릭했을 때
void AddressBookForm::OnRecordButtonClikced()
{
	//2.1 성명을 읽는다.
	CString name;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	//2.2 주소를 읽는다.
	CString address;
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	//2.3 전화번호를 읽는다.
	CString telephoneNumber;
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	//2.4 이메일주소를 읽는다.
	CString emailAddress;
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	//2.5 읽은 내용을 주소록에 기재한다.
	Long index;
	index = this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber,
		(LPCTSTR)emailAddress);
	//2.6 데이터베이스에 저장한다.
	this->Insert(index);
	//2.7 personal을 구한다.
	Personal personal;
	personal = this->addressBook->AddressBook_GetAt(index);
	//2.8 리스트뷰컨트롤에 번호를 삽입한다.
	CString number;
	number.Format("%d", index + 1);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(index, number);
	//2.9 리스트뷰 컨트롤에 성명을 삽입한다.
	name = CString(personal.GetName().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 1, name);
	//2.10 리스트뷰컨트롤에 주소를 삽입한다.
	address = CString(personal.GetAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);
	//2.11 리스트뷰컨트롤에 전화번호를 삽입한다.
	telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);
	//2.12 리스트뷰컨트롤에 이메일주소를 삽입한다.
	emailAddress = CString(personal.GetEmailAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, emailAddress);
}

//3. 찾기버튼을 클릭했을 때
void AddressBookForm::OnFindButtonClicked()
{
	FindingForm findingForm;//객체생성, 내용
	//3.1 찾기 프레임 윈도우를 띄운다.
	findingForm.DoModal();// 내용이므로 .으로 멤버접근함.
}

//4. 고치기버튼을 클릭했을 때
void AddressBookForm::OnCorrectButtonClicked()
{
	//4.1 리스트뷰컨트롤에서 선택된 항목의 위치를 읽는다.
	Long index;
	index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	//4.2 주소를 읽는다.
	CString address;
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	//4.3 전화번호를 읽는다.
	CString telephoneNumber;
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	//4.4 이메일주소를 읽는다.
	CString emailAddress;
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	//4.5 주소록에서 고친다.
	index = this->addressBook->Correct(index, (LPCTSTR)address, (LPCTSTR)telephoneNumber,
		(LPCTSTR)emailAddress);
	//4.6 데이터베이스에서 고친다.
	this->Update(index);
	//4.7 Personal을 구한다.
	Personal personal;
	personal = this->addressBook->AddressBook_GetAt(index);
	//4.8 리스트뷰컨트롤에서 주소를 고친다.
	address = CString(personal.GetAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);
	//4.9 리스트뷰컨트롤에서 전화번호를 고친다.
	telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);
	//4.10 리스트뷰컨트롤에서 이메일주소를 고친다.
	emailAddress = CString(personal.GetEmailAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, emailAddress);
}

//5. 지우기버튼을 클릭했을 때
void AddressBookForm::OnEraseButtonClicked()
{
	//5.1 리스트뷰컨트롤에서 선택된 항목의 위치를 읽는다.
	Long index;
	index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	//5.2 주소록에서 지운다.
	this->addressBook->Erase(index);
	//5.3 데이터베이스에서 지운다.
	this->Delete(index);
	//5.4 리스트뷰컨트롤에서 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteItem(index);
	//5.5 리스트뷰컨트롤에서 번호를 다시 매긴다.
	CString number;
	while (index < this->addressBook->GetLength())
	{
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 0, number);
		index++;
	}
}

//6. 정리하기 버튼을 클릭했을 때
void AddressBookForm::OnArrangeButtonClicked()
{
	//6.1 주소록에서 정리한다.
	this->addressBook->Arrange();
	//6.2 리스트뷰컨트롤에 있는 모든항목들을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();
	//6.3 리스트뷰 컨트롤에 주소록의 내용을 추가한다.
	CString number;
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Personal personal;
	Long index = 0;
	while (index < this->addressBook->GetLength())
	{
		//6.3.1 personal을 구한다.
		personal = this->addressBook->AddressBook_GetAt(index);
		//6.3.2 리스트뷰 컨트롤에 번호를 삽입한다.
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(index, number);
		//6.3.3 리스트뷰 컨트롤에 성명을 삽입한다.
		name = CString(personal.GetName().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 1, name);
		//6.3.4 리스트뷰컨트롤에 주소를 삽입한다.
		address = CString(personal.GetAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);
		//6.3.5 리스트뷰컨트롤에 전화번호를 삽입한다.
		telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);
		//6.3.6 리스트뷰컨트롤에 이메일주소를 삽입한다.
		emailAddress = CString(personal.GetEmailAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, emailAddress);
		index++;
	}
}

//7. 리스트뷰 컨트롤의 항목을 더블 클릭했을 때
void AddressBookForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//7.1 리스트뷰컨트롤에서 선택된 항목의 위치를 읽는다.
	Long index;
	index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	//7.2 리스트뷰컨트롤에서 선택된 항목의 성명을 읽는다.
	CString name;
	name = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	//7.3 리스트뷰컨트롤에서 선택된 항목의 주소를 읽는다.
	CString address;
	address = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	//7.4 리스트뷰컨트롤에서 선택된 항목의 전화번호를 읽는다.
	CString telephoneNumber;
	telephoneNumber = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	//7.5 리스트뷰컨트롤에서 선택된 항목의 이메일주소를 읽는다.
	CString emailAddress;
	emailAddress = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);
	//7.6 에디트컨트롤에 성명을 출력한다.
	GetDlgItem(IDC_EDIT_NAME)->SetWindowText(name);
	//7.7 에디트컨트롤에 주소를 출력한다.
	GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
	//7.8 에디트컨트롤에 전화번호를 출력한다.
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	//7.9 에디트컨트롤에 이메일주소를 출력한다.
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
}

void AddressBookForm::OnClose()//AddressBookForm::->준비를 의미함 this임.
{
	//8.닫기버튼을 클릭했을 때
	if (this->addressBook != NULL)
	{
		//8.1 주소록의 내용을 데이터베이스에 저장한다.
		this->Save();
		//8.2 주소록을 지운다.
		delete this->addressBook;
	}
	//8.3 윈도우를 닫는다.
	EndDialog(0);// this->EndDialog(0); 가 원래 문장이지만 this를 안써도 MFC에서 알아서 처리해줌.
}
