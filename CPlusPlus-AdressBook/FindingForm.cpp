#include "FindingForm.h"
#include "AddressBook.h"
#include "resource.h"
#include "AddressBookForm.h"
#include<afxwin.h>//CDialog 헤더파일
#include<afxcmn.h>//CListCtrl헤더파일

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
	//1. 찾기프레임 윈도우가 생성될 때
	CDialog::OnInitDialog();
	//1.1 리스트뷰 컨트를의 헤더항목들을 만든다.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, "번호", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, "성명", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, "주소", LVCFMT_CENTER, 300);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, "전화번호", LVCFMT_CENTER, 200);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, "이메일주소", LVCFMT_CENTER, 300);
	//1.2 리스트뷰 컨트롤의 어떤 부분을 클랙해도 선택이 되게 하기 위한 수단
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.3 끝내다.
	return FALSE;
}

//2. 찾기버튼을 클릭했을 때
void FindingForm::OnFindButtonClicked()
{
	//2.1 성명을 입력받는다.
	CString name;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	//2.2 주소록 프레임윈도우를 찾는다.
	AddressBookForm* addressBookForm;
	addressBookForm = (AddressBookForm*)CWnd::FindWindow("#32770", "주소록");
	//2.3 주소록 프레임 윈도우의 주소록에서 찾는다.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	addressBookForm->addressBook->Find((LPCTSTR)name, &this->indexes, &this->count);
	//2.4 리스트뷰컨트롤에 있는 모든항목들을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();
	//2.5 리스트뷰컨트롤에서 찾은 개수만큼 항목들을 추가한다.
	CString number;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Personal personal;
	Long index = 0;
	while (index < this->count)
	{
		//2.5.1 personal을 구한다.
		personal = addressBookForm->addressBook->AddressBook_GetAt(this->indexes[index]);
		//2.5.2 리스트뷰 컨트롤에 번호를 삽입한다.
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(index, number);
		//2.5.3 리스트뷰 컨트롤에 성명을 삽입한다.
		name = CString(personal.GetName().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 1, name);
		//2.5.4 리스트뷰컨트롤에 주소를 삽입한다.
		address = CString(personal.GetAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);
		//2.5.5 리스트뷰컨트롤에 전화번호를 삽입한다.
		telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);
		//2.5.6 리스트뷰컨트롤에 이메일주소를 삽입한다.
		emailAddress = CString(personal.GetEmailAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, emailAddress);
		index++;
	}
}

//3. 리스트뷰 컨트롤의 항목을 더블클릭했을 때
void FindingForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//3.1 리스트뷰컨트롤에서 선택된 항목의 위치를 읽는다.
	Long index;
	index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	//3.2 리스트뷰컨트롤에서 선택된 항목의 성명을 읽는다.
	CString name;
	name = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	//3.3 리스트뷰컨트롤에서 선택된 항목의 주소를 읽는다.
	CString address;
	address = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	//3.4 리스트뷰컨트롤에서 선택된 항목의 전화번호를 읽는다.
	CString telephoneNumber;
	telephoneNumber = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	//3.5 리스트뷰컨트롤에서 선택된 항목의 이메일주소를 읽는다.
	CString emailAddress;
	emailAddress = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);
	//3.6 주소록 프레임윈도우를 찾는다.
	AddressBookForm* addressBookForm;
	addressBookForm = (AddressBookForm*)CWnd::FindWindow("#32770", "주소록");
	//3.7 주소록 프레임 윈도우의 에디트컨트롤에 성명을 출력한다.
	addressBookForm->GetDlgItem(IDC_EDIT_NAME)->SetWindowText(name);
	//3.8 주소록 프레임 윈도우의 에디트컨트롤에 주소를 출력한다.
	addressBookForm->GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
	//3.9 주소록 프레임 윈도우의 에디트컨트롤에 전화번호를 출력한다.
	addressBookForm->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	//3.10 주소록 프레임 윈도우의 에디트컨트롤에 이메일주소를 출력한다.
	addressBookForm->GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
	//3.11 주소록 프레임 윈도우의 리스트뷰 컨트롤에서 항목을 선택한다.
	((CListCtrl*)addressBookForm->GetDlgItem(IDC_LIST_PERSONALS))->SetSelectionMark(this->indexes[index]);
	//3.12 윈도우를 닫는다.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	EndDialog(0);
}

//4. 닫기버튼을 클릭했을 때
void FindingForm::OnClose()
{
	//4.1 색인배열을 없앤다.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	//4.2 윈도우를 닫는다.
	EndDialog(0);
}