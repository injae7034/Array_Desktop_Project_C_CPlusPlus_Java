#include "FindingForm.h"
#include "AccountBook.h"//Account가 주소로 쓰여서 전방선언만 되어 있음
#include "Account.h"//Account의 연산을 쓰기위해 헤더파일 필요
#include "Income.h"
#include "Outgo.h"
#include "resource.h"
#include "AccountBookForm.h"
#include<afxwin.h>//CDialog 헤더파일
#include<afxcmn.h>//CListCtrl헤더파일
#include<afxdtctl.h>//CDateTimeCrtl헤더파일

BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACCOUNTS, OnListViewItemDoubleClicked)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE, OnCalculateButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

FindingForm::FindingForm(CWnd* parent)
	: CDialog(FindingForm::IDD, parent)
{
	this->indexes = NULL;
	this->count = 0;
}

//1. 찾기프레임 윈도우가 생성될 때
BOOL FindingForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 리스트뷰 컨트를의 헤더항목들을 만든다.
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(0, "일자", LVCFMT_LEFT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(1, "적요", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(2, "금액", LVCFMT_RIGHT, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(3, "잔액", LVCFMT_RIGHT, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(4, "비고", LVCFMT_CENTER, 150);
	//1.2 리스트뷰 컨트롤의 어떤 부분을 클랙해도 선택이 되게 하기 위한 수단
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.3 정산창을 숨긴다.
	GetDlgItem(IDC_STATIC_CALCULATION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALINCOME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT_TOTALINCOME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALOUTGO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT_TOTALOUTGO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALBALANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT_TOTALBALANCE)->ShowWindow(SW_HIDE);
	//1.3 끝내다.
	return FALSE;
}

//2. 찾기버튼을 클릭했을 때
void FindingForm::OnFindButtonClicked()
{
	//2.1 일자체크박스버튼을 읽는다.
	int dateChecked = ((CButton*)GetDlgItem(IDC_CHECK_DATE))->GetCheck();
	//2.2 데이트피커의 일자를 읽는다.
	CTime choosedOne;
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_ONE))->GetTime(choosedOne);
	int year = choosedOne.GetYear();
	int month = choosedOne.GetMonth();
	int day = choosedOne.GetDay();
	char charOne[9];
	sprintf_s(charOne, "%d%d%d", year, month, day);
	CTime choosedOther;
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_OTHER))->GetTime(choosedOther);
	year = choosedOther.GetYear();
	month = choosedOther.GetMonth();
	day = choosedOther.GetDay();
	char charOther[9];
	sprintf_s(charOther, "%d%d%d", year, month, day);
	//2.3 적요체크박스버튼을 읽는다.
	int briefsChecked = ((CButton*)GetDlgItem(IDC_CHECK_BRIEFS))->GetCheck();
	//2.4 적요에디트를 읽는다.
	CString briefs;
	GetDlgItem(IDC_EDIT_BRIEFS)->GetWindowText(briefs);
	//2.5 가계부 프레임 윈도우를 찾는다.
	AccountBookForm *accountBookForm = (AccountBookForm*)CWnd::FindWindow("#32770", "가계부");
	//찾기프레임윈도우를 끄지않고 계속해서 찾기를 누를경우를 위해 매번 찾기버튼을 누를때마다
	//기존의 indexes배열은 할당해제하고 새로 indexes배열을 할당해줘야 메모리누수가 없음.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	//2.6 일자체크박스버튼만 선택되어 있으면
	if (dateChecked == BST_CHECKED && briefsChecked == BST_UNCHECKED)
	{
		//2.6.1 가계부 프레임 윈도우의 가계부에서 찾는다.
		accountBookForm->accountBook->Find(Date(charOne), Date(charOther), &this->indexes, &this->count);
	}
	//2.7 적요체크박스버튼만 선택되어 있으면
	if (dateChecked == BST_UNCHECKED && briefsChecked == BST_CHECKED)
	{
		//2.7.1 가계부 프레임 윈도우의 가계부에서 찾는다.
		accountBookForm->accountBook->Find((LPCTSTR)briefs, &this->indexes, &this->count);
	}
	//2.8 일자체크박스버튼와 적요체크박스버튼 둘다 선택되어 있으면
	if (dateChecked == BST_CHECKED && briefsChecked == BST_CHECKED)
	{
		//2.8.1 가계부 프레임 윈도우의 가계부에서 찾는다.
		accountBookForm->accountBook->Find(Date(charOne), Date(charOther), (LPCTSTR)briefs,
			&this->indexes, &this->count);
	}
	//2.9 리스트뷰컨트롤에 있는 모든항목들을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->DeleteAllItems();
	//2.10 리스트뷰컨트롤에서 찾은 개수만큼 항목들을 추가한다.
	Long i = 0;
	while (i < this->count)
	{
		Account* account = accountBookForm->accountBook->GetAt(this->indexes[i]);
		Date accountDate = account->GetDate();
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertItem(i, accountDate);
		CString accountBriefs = account->GetBriefs().c_str();
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 1, accountBriefs);
		Currency accountAmount = account->GetAmount();
		CString cstringAmount;
		cstringAmount.Format("%d", (int)accountAmount);
		Long k = 0;
		int remainder = cstringAmount.GetLength() % 3;
		if (remainder == 0)
		{
			k = 3;
		}
		else if (remainder == 1)
		{
			k = 1;
		}
		else if (remainder == 2)
		{
			k = 2;
		}
		Long j = 3;
		while (j < cstringAmount.GetLength())
		{
			cstringAmount.Insert(k, ",");
			k += 4;
			j += 3;
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 2, cstringAmount);
		Currency accountBalance = account->GetBalance();
		CString cstringBalance;
		cstringBalance.Format("%d", (int)accountBalance);
		k = 0;
		remainder = cstringBalance.GetLength() % 3;
		if (remainder == 0)
		{
			k = 3;
		}
		else if (remainder == 1)
		{
			k = 1;
		}
		else if (remainder == 2)
		{
			k = 2;
		}
		j = 3;
		while (j < cstringBalance.GetLength())
		{
			cstringBalance.Insert(k, ",");
			k += 4;
			j += 3;
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 3, cstringBalance);
		CString accountRemarks = account->GetRemarks().c_str();
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 4, accountRemarks);
		i++;
	}
	//1.3 정산창을 숨긴다.
	GetDlgItem(IDC_STATIC_CALCULATION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALINCOME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT_TOTALINCOME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALOUTGO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT_TOTALOUTGO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALBALANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT_TOTALBALANCE)->ShowWindow(SW_HIDE);
}

//3. 리스트뷰컨트롤에서 항목을 더블클릭 했을 때
void FindingForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//3.1 리스트뷰 컨트롤에서 선택한 위치를 읽는다.
	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	//3.2 리스트뷰컨트롤에서 선택한 항목의 일자, 적요, 금액, 잔액, 비고를 읽는다.
	CString date = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 0);
	CString briefs = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 1);
	CString amount = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 2);
	CString balance = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 3);
	CString remarks = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 4);
	//3.3 가계부프레임 윈도우를  찾는다.
	AccountBookForm* accountBookForm = (AccountBookForm*)CWnd::FindWindow("#32770", "가계부");
	//3.4 가계부프레임 윈도우의 리스트뷰 컨트롤에서 읽은 일자, 적요, 금액, 잔액, 비고를 출력한다.
	int year = _ttoi(date.Left(4));
	int month = _ttoi(date.Mid(4, 2));
	int day = _ttoi(date.Mid(6, 2));
	COleDateTime choosedDate;
	choosedDate.SetDate(year, month, day);
	((CDateTimeCtrl*)accountBookForm->GetDlgItem(IDC_DATETIMEPICKER_ONE))->SetTime(choosedDate);
	accountBookForm->GetDlgItem(IDC_EDIT_BRIEFS)->SetWindowText(briefs);
	amount.Remove(',');
	accountBookForm->GetDlgItem(IDC_EDIT_AMOUNT)->SetWindowText(amount);
	accountBookForm->GetDlgItem(IDC_STATIC_EDIT_BALANCE)->SetWindowText(balance);
	accountBookForm->GetDlgItem(IDC_EDIT_REMARKS)->SetWindowText(remarks);
	//3.5 account를 구한다.
	Account* account = accountBookForm->accountBook->GetAt(this->indexes[index]);
	//3.6 수입이면
	if (dynamic_cast<Income*>(account))
	{
		//3.6.1 가계부프레임 윈도우의 수입라디오버튼을 선택한다.
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_CHECKED);
		//3.6.2 가계부프레임 윈도우의 지출라디오버튼을 UNCHKECK한다.
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_UNCHECKED);
	}
	//3.7 지출이면
	else if (dynamic_cast<Outgo*>(account))
	{
		//3.7.1 가계부프레임 윈도우의 지출라디오버튼을 선택한다.
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);
		//3.7.2 가계부프레임 윈도우의 수입라디오버튼을 UNCHKECK한다.
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	}
	//3.8 가계부프레임 윈도우의 리스트뷰 컨트롤에서 항목을 선택한다.
	((CListCtrl*)accountBookForm->GetDlgItem(IDC_LIST_ACCOUNTS))->SetSelectionMark(this->indexes[index]);
	//3.9 윈도우를 닫는다.
	EndDialog(0);
}

//4. 정산하기 버튼을 클릭했을 때
void FindingForm::OnCalculateButtonClicked()
{
	//4.1 정산창을 보이게 한다.
	GetDlgItem(IDC_STATIC_CALCULATION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TOTALINCOME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_EDIT_TOTALINCOME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TOTALOUTGO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_EDIT_TOTALOUTGO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TOTALBALANCE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_EDIT_TOTALBALANCE)->ShowWindow(SW_SHOW);
	//4.2 데이트피커들의 일자들을 읽는다.
	CTime choosedOne;
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_ONE))->GetTime(choosedOne);
	int year = choosedOne.GetYear();
	int month = choosedOne.GetMonth();
	int day = choosedOne.GetDay();
	char charOne[9];
	sprintf_s(charOne, "%d%d%d", year, month, day);
	CTime choosedOther;
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_OTHER))->GetTime(choosedOther);
	year = choosedOther.GetYear();
	month = choosedOther.GetMonth();
	day = choosedOther.GetDay();
	char charOther[9];
	sprintf_s(charOther, "%d%d%d", year, month, day);
	//4.3 가계부프레임 윈도우를  찾는다.
	AccountBookForm* accountBookForm = (AccountBookForm*)CWnd::FindWindow("#32770", "가계부");
	//4.4 가계부 프레임 윈도우에서 찾는다.
	accountBookForm->accountBook->Find(Date(charOne), Date(charOther), &this->indexes, &this->count);
	//4.5 리스트뷰컨트롤에서 있는 모든 항목들을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->DeleteAllItems();
	//4.6 리스트뷰컨트롤에서 찾은 개수만큼 항목들을 추가한다.
	Long k;
	int remainder;
	Long j;
	Long m;
	Long i = 0;
	while (i < this->count)
	{
		Account* account = accountBookForm->accountBook->GetAt(this->indexes[i]);
		Date accountDate = account->GetDate();
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertItem(i, accountDate);
		CString accountBriefs = account->GetBriefs().c_str();
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 1, accountBriefs);
		Currency accountAmount = account->GetAmount();
		CString cstringAmount;
		cstringAmount.Format("%d", (int)accountAmount);
		k = 0;
		remainder = cstringAmount.GetLength() % 3;
		if (remainder == 0)
		{
			k = 3;
		}
		else if (remainder == 1)
		{
			k = 1;
		}
		else if (remainder == 2)
		{
			k = 2;
		}
		j = 3;
		while (j < cstringAmount.GetLength())
		{
			cstringAmount.Insert(k, ",");
			k += 4;
			j += 3;
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 2, cstringAmount);
		Currency accountBalance = account->GetBalance();
		CString cstringBalance;
		cstringBalance.Format("%d", (int)accountBalance);
		k = 0;
		remainder = cstringBalance.GetLength() % 3;
		if (remainder == 0)
		{
			k = 3;
		}
		else if (remainder == 1)
		{
			k = 1;
		}
		else if (remainder == 2)
		{
			k = 2;
		}
		j = 3;
		while (j < cstringBalance.GetLength())
		{
			cstringBalance.Insert(k, ",");
			k += 4;
			j += 3;
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 3, cstringBalance);
		CString accountRemarks = account->GetRemarks().c_str();
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 4, accountRemarks);
		i++;
	}
	//4.7 가계부 프레임 윈도우에서 계산한다.
	Currency totalIncome;
	Currency totalOutgo;
	Currency totalBalance;
	accountBookForm->accountBook->Calculate(Date(charOne), Date(charOther), &totalIncome, &totalOutgo, &totalBalance);
	//4.8 정산창에 총수입, 총지출, 총잔액을 출력한다.
	CString cstringTotalIncome;
	cstringTotalIncome.Format("%0.lf", totalIncome);
	k = 0;
	remainder = cstringTotalIncome.GetLength() % 3;
	if (remainder == 0)
	{
		k = 3;
	}
	else if (remainder == 1)
	{
		k = 1;
	}
	else if (remainder == 2)
	{
		k = 2;
	}
	j = 3;
	while (j < cstringTotalIncome.GetLength())
	{
		cstringTotalIncome.Insert(k, ",");
		k += 4;
		j += 3;
	}
	GetDlgItem(IDC_STATIC_EDIT_TOTALINCOME)->SetWindowText(cstringTotalIncome);
	CString cstringTotalOutgo;
	cstringTotalOutgo.Format("%0.lf", totalOutgo);
	k = 0;
	remainder = cstringTotalOutgo.GetLength() % 3;
	if (remainder == 0)
	{
		k = 3;
	}
	else if (remainder == 1)
	{
		k = 1;
	}
	else if (remainder == 2)
	{
		k = 2;
	}
	m = 0;
	j = 3;
	while (j < cstringTotalOutgo.GetLength() - m)
	{
		cstringTotalOutgo.Insert(k, ",");
		m++;
		k += 4;
		j += 3;
	}
	GetDlgItem(IDC_STATIC_EDIT_TOTALOUTGO)->SetWindowText(cstringTotalOutgo);
	CString cstringTotalBalance;
	cstringTotalBalance.Format("%0.lf", totalBalance);
	k = 0;
	remainder = cstringTotalBalance.GetLength() % 3;
	if (remainder == 0)
	{
		k = 3;
	}
	else if (remainder == 1)
	{
		k = 1;
	}
	else if (remainder == 2)
	{
		k = 2;
	}
	j = 3;
	while (j < cstringTotalBalance.GetLength())
	{
		cstringTotalBalance.Insert(k, ",");
		k += 4;
		j += 3;
	}
	GetDlgItem(IDC_STATIC_EDIT_TOTALBALANCE)->SetWindowText(cstringTotalBalance);
}

//5. 닫기버튼을 클릭했을 때
void FindingForm::OnClose()
{
	//5.1 색인배열을 없앤다.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	//5.2 윈도우를 닫는다.
	EndDialog(0);
}

