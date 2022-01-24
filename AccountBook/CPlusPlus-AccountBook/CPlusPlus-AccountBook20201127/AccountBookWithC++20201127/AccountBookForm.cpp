#include "AccountBookForm.h"
#include "FindingForm.h"
#include "AccountBook.h"
#include "Account.h"//AccountBook헤더파일에서는 Account가 전방선언만 되어 있기때문에 
//AccountBook의 연산을 사용하기 위해서는 따로 헤더파일 선언을 해줘야함.
#include "Income.h"
#include "Outgo.h"
#include "resource.h"
#include<afxwin.h>//CDialog헤더파일
#include<afxcmn.h>//CListCtrl헤더파일
#include<afxdtctl.h>//CDateTimeCrtl헤더파일

BEGIN_MESSAGE_MAP(AccountBookForm, CDialog)
	ON_BN_CLICKED(IDC_RADIO_INCOME, OnIncomeRadioButtonClicked)
	ON_BN_CLICKED(IDC_RADIO_OUTGO, OnOutgoRadioButtonClicked)
	ON_EN_KILLFOCUS(IDC_EDIT_AMOUNT, OnAmountEditKillFocus)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACCOUNTS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

AccountBookForm::AccountBookForm(CWnd* parent)
	:CDialog(AccountBookForm::IDD, parent)
{
	this->accountBook = NULL;//NULL로 초기화시킴.
}

//1. 윈도우가 생성될 때
BOOL AccountBookForm::OnInitDialog()
{
	//1.1 가계부를 만든다.
	CDialog::OnInitDialog();
	this->accountBook = new AccountBook;//배열이 아니라 주소를 저장할 일반 포인터변수임.
	//1.2 수입라디오 버튼을 UNCHECKED한다.
	((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	//1.3 지출라디오버튼을 CHECKED한다.
	((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);
	//1.4 잔액에 0원을 출력한다.
	GetDlgItem(IDC_STATIC_EDIT_BALANCE)->SetWindowText(0);
	//1.5 리스트뷰 컨트롤의 헤더를 만든다.
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(0, "일자", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(1, "적요", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(2, "금액", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(3, "잔액", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(4, "비고", LVCFMT_CENTER, 150);
	//1.6 리스트뷰 컨트롤의 어떤 부분을 클랙해도 선택이 되게 하기 위한 수단
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	return FALSE;
}

//2. 수입라디오 버튼을 클릭했을 때
void AccountBookForm::OnIncomeRadioButtonClicked()
{
	//2.1 지출라디오 버튼을 uncheck한다.
	((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_UNCHECKED);
}

//3. 지출라디오 버튼을 클릭했을 때
void AccountBookForm::OnOutgoRadioButtonClicked()
{
	//3.1 수입라디오버튼을 uncheck한다.
	((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
}

//4. 금액에디트가 포커스를 잃을 때
void AccountBookForm::OnAmountEditKillFocus()
{
	//4.1 수입라디오 버튼을 읽는다.
	int incomeChecked = ((CButton*)GetDlgItem(IDC_RADIO_INCOME))->GetCheck();
	//4.2 지출라디오 버튼을 읽는다.
	int outgoChecked = ((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->GetCheck();
	//4.3 금액 에디트에서 금액을 읽는다.
	CString amount;
	GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowText(amount);
	//4.4 금액의 자료형을 Currency로 바꾼다.
	Currency currencyAmount = _ttoi(amount);
	//4.4 선택된 라디오버튼이 지출이면
	if (outgoChecked == BST_CHECKED)
	{
		//4.4.1 금액을 음수로 바꾼다.
		currencyAmount *= (-1);
		amount.Format("%.0lf", currencyAmount);
	}
	//4.5 리스트뷰컨트롤에서 선택된 항목의 위치를 읽는다.
	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	//4.6 리스트뷰 컨트롤에서 선택된 위치가 없는 경우에
	if (index == -1)
	{
		//4.6.1 가계부에 account가 처음이면
		if (this->accountBook->GetLength() == 0)
		{
			//4.6.1.1 잔액스태틱에 금액을 출력한다.
			GetDlgItem(IDC_STATIC_EDIT_BALANCE)->SetWindowText(amount);
		}
		//4.6.2 가계부에 account가 처음이 아니면
		else if (this->accountBook->GetLength() > 0)
		{
			//4.6.2.1 가계부의 마지막항을 구한다.
			Account* account = this->accountBook->GetAt(this->accountBook->GetLength() - 1);
			//4.6.2.2 마지막항의 잔액을 구한다.
			Currency balance = account->GetBalance();
			//4.6.2. 최신잔액을 구한다.
			Currency currentBalance = balance + currencyAmount;
			CString cstringBalance;
			cstringBalance.Format("%.0lf", currentBalance);
			//4.6.2.4 잔액스태틱에 최신잔액을 출력한다.
			GetDlgItem(IDC_STATIC_EDIT_BALANCE)->SetWindowText(cstringBalance);
		}
	}
	//4.7 고치기버튼을 누를 경우
	else
	{
		//4.7.1 리스트뷰컨트롤에서 선택한 항목이 처음이면
		if (index == 0)
		{
			//4.6.1.1 잔액스태틱에 금액을 출력한다.
			GetDlgItem(IDC_STATIC_EDIT_BALANCE)->SetWindowText(amount);
		}
		//4.7.2 처음이 아니면
		else
		{
			//4.7.1 account를 구한다.
			Account* account = this->accountBook->GetAt(index - 1);
			//4.7.2 account의 잔액을 구한다.
			Currency balance = account->GetBalance();
			//4.7.3 최신잔액을 구한다.
			Currency currentBalance = balance + currencyAmount;
			CString cstringBalance;
			cstringBalance.Format("%.0lf", currentBalance);
			//4.7.4 잔액스태틱에 최신잔액을 출력한다.
			GetDlgItem(IDC_STATIC_EDIT_BALANCE)->SetWindowText(cstringBalance);
		}
	}
}

//5. 기재하기버튼을 클릭했을 때
void AccountBookForm::OnRecordButtonClicked()
{
	//5.1 수입라디오버튼을 읽는다.
	int incomeChecked = ((CButton*)GetDlgItem(IDC_RADIO_INCOME))->GetCheck();
	//5.2 지출라디오버튼을 읽는다.
	int outgoChecked = ((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->GetCheck();
	//5.3 일자, 적요, 금액, 비고를 읽는다.
	CTime choosedDate;
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_ONE))->GetTime(choosedDate);
	int year = choosedDate.GetYear();
	int month = choosedDate.GetMonth();
	int day = choosedDate.GetDay();
	char charDate[9];
	sprintf_s(charDate, "%d%d%d", year, month, day);
	CString briefs;
	GetDlgItem(IDC_EDIT_BRIEFS)->GetWindowText(briefs);
	CString amount;
	GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowText(amount);
	CString remarks;
	GetDlgItem(IDC_EDIT_REMARKS)->GetWindowText(remarks);
	//5.4 금액의 자료형을 Currency로 바꾼다.
	Currency currencyAmount = _ttoi(amount);
	//5.5 선택된 라디오버튼이 지출이면
	if (outgoChecked == BST_CHECKED)
	{
		//5.5.1 금액을 음수로 바꾼다.
		currencyAmount *= (-1);
	}
	//5.6 가계부에서 기재한다.
	Long index = this->accountBook->Record(charDate, (LPCTSTR)briefs, currencyAmount, (LPCTSTR)remarks);
	//5.7 account를 구한다.
	Account* account = this->accountBook->GetAt(index);
	//5.8 리스트뷰 컨트롤에 항목을 추가한다.
	Date accountDate = account->GetDate();
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertItem(index, accountDate);
	CString accountBriefs = account->GetBriefs().c_str();
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 1, accountBriefs);
	Currency accountAmount = account->GetAmount();
	CString cstringAmount;
	cstringAmount.Format("%d", (int)accountAmount);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 2, cstringAmount);
	Currency accountBalance = account->GetBalance();
	CString cstringBalance;
	cstringBalance.Format("%d", (int)accountBalance);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 3, cstringBalance);
	CString accountRemarks = account->GetRemarks().c_str();
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 4, accountRemarks);
}

//6. 찾기 버튼을 클릭했을 때
void AccountBookForm::OnFindButtonClicked()
{
	FindingForm findingForm;//객체생성, 내용
	//3.1 찾기 프레임 윈도우를 띄운다.
	findingForm.DoModal();// 내용이므로 .으로 멤버접근함.
}

//7. 고치기버튼을 클릭했을 때
void AccountBookForm::OnCorrectButtonClicked()
{
	//7.1 수입라디오버튼을 읽는다.
	int incomeChecked = ((CButton*)GetDlgItem(IDC_RADIO_INCOME))->GetCheck();
	//7.2 지출라디오버튼을 읽는다.
	int outgoChecked = ((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->GetCheck();
	//7.3 금액, 비고를 읽는다.
	CString amount;
	GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowText(amount);
	CString remarks;
	GetDlgItem(IDC_EDIT_REMARKS)->GetWindowText(remarks);
	//7.4 리스트뷰컨트롤에서 선택된 항목의 위치를 읽는다.
	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	//7.5 금액의 자료형을 Currency로 바꾼다.
	Currency currencyAmount = _ttoi(amount);
	//7.6 선택된 라디오버튼이 지출이면
	if (outgoChecked == BST_CHECKED)
	{
		//7.6.1 금액을 음수로 바꾼다.
		currencyAmount *= (-1);
	}
	//7.7 가계부에서 고친다.
	index = this->accountBook->Correct(index, currencyAmount, (LPCTSTR)remarks);
	//7.8 account를 구한다.
	Account* account = this->accountBook->GetAt(index);
	//7.9 account의 금액을 구하고 구한 금액으로 리스트뷰 컨트롤에서 고친다.
	currencyAmount = account->GetAmount();
	amount.Format("%d", (int)currencyAmount);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 2, amount);
	//7.9 account의 잔액을 구하고 구한 잔액으로 리스트뷰 컨트롤에서 고친다.
	Currency balance = account->GetBalance();
	CString cstringBalance;
	cstringBalance.Format("%d", (int)balance);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 3, cstringBalance);
	//7.10 비고를 구하고 구한 비고로 리스트뷰 컨트롤에서 고친다.
	CString accountRemarks = account->GetRemarks().c_str();
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 4, accountRemarks);
	//7.8 index가 length보다 작은동안에 반복한다.
	index++;
	while (index < this->accountBook->GetLength())
	{
		//5.7.1 account를 구한다.
		account = this->accountBook->GetAt(index);
		//5.7.2 잔액을 구한다.
		balance = account->GetBalance();
		cstringBalance;
		cstringBalance.Format("%d", (int)balance);
		//5.7.3 리스트뷰컨트롤에서 고친 항목 이후의 항목들의 잔액을 고친다.
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 3, cstringBalance);
		index++;
	}
	//7.9 리스트뷰컨트롤에서 항목 선택을 없앤다.
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetSelectionMark(-1);
}

//8. 리스트뷰 컨트롤에서 항목을 더블클릭했을 때
void AccountBookForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//8.1 리스트뷰컨트롤에서 선택된 항목의 위치를 읽는다.
	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	//8.2 리스트뷰컨트롤에서 선택한 항목의 일자, 적요, 금액, 잔액, 비고를 읽는다.
	CString date = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 0);
	CString briefs = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 1);
	CString amount = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 2);
	CString balance = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 3);
	CString remarks = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 4);
	//
#if 0
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_ONE))->GetTime(choosedDate);
	int year = choosedDate.GetYear();
	int month = choosedDate.GetMonth();
	int day = choosedDate.GetDay();
	char charDate[9];
	sprintf_s(charDate, "%d%d%d", year, month, day);
	CString code = "P0000";
	int number;
	number = _ttoi(code.Right(4));
#endif
	//
	//8.3 리스트뷰 컨트롤에서 읽은 일자, 적요, 금액, 잔액, 비고를 출력한다.
	int year = _ttoi(date.Left(4));
	int month = _ttoi(date.Mid(4, 2));
	int day = _ttoi(date.Mid(6, 2));
	COleDateTime choosedDate;
	choosedDate.SetDate(year, month, day);
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_ONE))->SetTime(choosedDate);
	GetDlgItem(IDC_DATETIMEPICKER_ONE)->SetWindowText(date);
	GetDlgItem(IDC_EDIT_BRIEFS)->SetWindowText(briefs);
	GetDlgItem(IDC_EDIT_AMOUNT)->SetWindowText(amount);
	GetDlgItem(IDC_STATIC_EDIT_BALANCE)->SetWindowText(balance);
	GetDlgItem(IDC_EDIT_REMARKS)->SetWindowText(remarks);
	//8.4 account가 수입인지 지출인지 판단한다.
	Account* account = this->accountBook->GetAt(index);
	//8.4.1 수입이면
	if (dynamic_cast<Income*>(account))
	{
		//8.4.1.1 수입라디오버튼을 선택한다.
		((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_CHECKED);
		//8.4.1.2 지출라디오버튼을 UNCHKECK한다.
		((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_UNCHECKED);
	}
	//8.4.2 account가 지출이면
	else if (dynamic_cast<Outgo*>(account))
	{
		//8.4.2.1 지출라디오버튼을 선택한다.
		((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);
		//8.4.2.2 수입라디오버튼을 UNCHKECK한다.
		((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	}
}

//9. 닫기버튼을 클릭했을 때
void AccountBookForm::OnClose()//AccountBookForm::->준비를 의미함 this임.
{
	//7.1 가계부를 지운다.
	if (this->accountBook != NULL)
	{
		delete this->accountBook;
	}
	//7.2 윈도우를 닫는다.
	EndDialog(0);// this->EndDialog(0); 가 원래 문장이지만 this를 안써도 MFC에서 알아서 처리해줌.
}


