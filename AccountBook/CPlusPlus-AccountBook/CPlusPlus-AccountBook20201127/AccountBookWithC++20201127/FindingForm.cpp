#include "FindingForm.h"
#include "AccountBook.h"//Account�� �ּҷ� ������ ���漱�� �Ǿ� ����
#include "Account.h"//Account�� ������ �������� ������� �ʿ�
#include "Income.h"
#include "Outgo.h"
#include "resource.h"
#include "AccountBookForm.h"
#include<afxwin.h>//CDialog �������
#include<afxcmn.h>//CListCtrl�������
#include<afxdtctl.h>//CDateTimeCrtl�������

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

//1. ã�������� �����찡 ������ ��
BOOL FindingForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 ����Ʈ�� ��Ʈ���� ����׸���� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(0, "����", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(1, "����", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(2, "�ݾ�", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(3, "�ܾ�", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(4, "���", LVCFMT_CENTER, 150);
	//1.2 ����Ʈ�� ��Ʈ���� � �κ��� Ŭ���ص� ������ �ǰ� �ϱ� ���� ����
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.3 ����â�� �����.
	GetDlgItem(IDC_STATIC_CALCULATION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALINCOME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT_TOTALINCOME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALOUTGO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT_TOTALOUTGO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALBALANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT_TOTALBALANCE)->ShowWindow(SW_HIDE);
	//1.3 ������.
	return FALSE;
}

//2. ã���ư�� Ŭ������ ��
void FindingForm::OnFindButtonClicked()
{
	//2.1 ����üũ�ڽ���ư�� �д´�.
	int dateChecked = ((CButton*)GetDlgItem(IDC_CHECK_DATE))->GetCheck();
	//2.2 ����Ʈ��Ŀ�� ���ڸ� �д´�.
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
	//2.3 ����üũ�ڽ���ư�� �д´�.
	int briefsChecked = ((CButton*)GetDlgItem(IDC_CHECK_BRIEFS))->GetCheck();
	//2.4 ���信��Ʈ�� �д´�.
	CString briefs;
	GetDlgItem(IDC_EDIT_BRIEFS)->GetWindowText(briefs);
	//2.5 ����� ������ �����츦 ã�´�.
	AccountBookForm *accountBookForm = (AccountBookForm*)CWnd::FindWindow("#32770", "�����");
	//2.6 ����üũ�ڽ���ư�� ���õǾ� ������
	//ã�������������츦 �����ʰ� ����ؼ� ã�⸦ ������츦 ���� �Ź� ã���ư�� ����������
	//������ indexes�迭�� �Ҵ������ϰ� ���� indexes�迭�� �Ҵ������ �޸𸮴����� ����.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	if (dateChecked == BST_CHECKED && briefsChecked == BST_UNCHECKED)
	{
		//2.6.1 ����� ������ �������� ����ο��� ã�´�.
		accountBookForm->accountBook->Find(Date(charOne), Date(charOther), &this->indexes, &this->count);
	}
	//2.7 ����üũ�ڽ���ư�� ���õǾ� ������
	if (dateChecked == BST_UNCHECKED && briefsChecked == BST_CHECKED)
	{
		//2.7.1 ����� ������ �������� ����ο��� ã�´�.
		accountBookForm->accountBook->Find((LPCTSTR)briefs, &this->indexes, &this->count);
	}
	//2.8 ����üũ�ڽ���ư�� ����üũ�ڽ���ư �Ѵ� ���õǾ� ������
	if (dateChecked == BST_CHECKED && briefsChecked == BST_CHECKED)
	{
		//2.8.1 ����� ������ �������� ����ο��� ã�´�.
		accountBookForm->accountBook->Find(Date(charOne), Date(charOther), (LPCTSTR)briefs, &this->indexes, &this->count);
	}
	//2.9 ����Ʈ����Ʈ�ѿ� �ִ� ����׸���� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->DeleteAllItems();
	//2.10 ����Ʈ����Ʈ�ѿ��� ã�� ������ŭ �׸���� �߰��Ѵ�.
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
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 2, cstringAmount);
		Currency accountBalance = account->GetBalance();
		CString cstringBalance;
		cstringBalance.Format("%d", (int)accountBalance);
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 3, cstringBalance);
		CString accountRemarks = account->GetRemarks().c_str();
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 4, accountRemarks);
		i++;
	}
	//1.3 ����â�� �����.
	GetDlgItem(IDC_STATIC_CALCULATION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALINCOME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT_TOTALINCOME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALOUTGO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT_TOTALOUTGO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALBALANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT_TOTALBALANCE)->ShowWindow(SW_HIDE);
}

//3. ����Ʈ����Ʈ�ѿ��� �׸��� ����Ŭ�� ���� ��
void FindingForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//3.1 ����Ʈ�� ��Ʈ�ѿ��� ������ ��ġ�� �д´�.
	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	//3.2 ����Ʈ����Ʈ�ѿ��� ������ �׸��� ����, ����, �ݾ�, �ܾ�, ��� �д´�.
	CString date = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 0);
	CString briefs = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 1);
	CString amount = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 2);
	CString balance = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 3);
	CString remarks = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetItemText(index, 4);
	//3.3 ����������� �����츦  ã�´�.
	AccountBookForm* accountBookForm = (AccountBookForm*)CWnd::FindWindow("#32770", "�����");
	//3.4 ����������� �������� ����Ʈ�� ��Ʈ�ѿ��� ���� ����, ����, �ݾ�, �ܾ�, ��� ����Ѵ�.
	int year = _ttoi(date.Left(4));
	int month = _ttoi(date.Mid(4, 2));
	int day = _ttoi(date.Mid(6, 2));
	COleDateTime choosedDate;
	choosedDate.SetDate(year, month, day);
	((CDateTimeCtrl*)accountBookForm->GetDlgItem(IDC_DATETIMEPICKER_ONE))->SetTime(choosedDate);
	accountBookForm->GetDlgItem(IDC_EDIT_BRIEFS)->SetWindowText(briefs);
	accountBookForm->GetDlgItem(IDC_EDIT_AMOUNT)->SetWindowText(amount);
	accountBookForm->GetDlgItem(IDC_STATIC_EDIT_BALANCE)->SetWindowText(balance);
	accountBookForm->GetDlgItem(IDC_EDIT_REMARKS)->SetWindowText(remarks);
	//3.5 account�� ���Ѵ�.
	Account* account = accountBookForm->accountBook->GetAt(this->indexes[index]);
	//3.6 �����̸�
	if (dynamic_cast<Income*>(account))
	{
		//3.6.1 ����������� �������� ���Զ�����ư�� �����Ѵ�.
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_CHECKED);
		//3.6.2 ����������� �������� ���������ư�� UNCHKECK�Ѵ�.
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_UNCHECKED);
	}
	//3.7 �����̸�
	else if (dynamic_cast<Outgo*>(account))
	{
		//3.7.1 ����������� �������� ���������ư�� �����Ѵ�.
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);
		//3.7.2 ����������� �������� ���Զ�����ư�� UNCHKECK�Ѵ�.
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	}
	//3.8 ����������� �������� ����Ʈ�� ��Ʈ�ѿ��� �׸��� �����Ѵ�.
	((CListCtrl*)accountBookForm->GetDlgItem(IDC_LIST_ACCOUNTS))->SetSelectionMark(this->indexes[index]);
	//3.9 �����츦 �ݴ´�.
	EndDialog(0);
}

//4. �����ϱ� ��ư�� Ŭ������ ��
void FindingForm::OnCalculateButtonClicked()
{
	//4.1 ����â�� ���̰� �Ѵ�.
	GetDlgItem(IDC_STATIC_CALCULATION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TOTALINCOME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_EDIT_TOTALINCOME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TOTALOUTGO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_EDIT_TOTALOUTGO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TOTALBALANCE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_EDIT_TOTALBALANCE)->ShowWindow(SW_SHOW);
	//4.2 ����Ʈ��Ŀ���� ���ڵ��� �д´�.
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
	//4.3 ����������� �����츦  ã�´�.
	AccountBookForm* accountBookForm = (AccountBookForm*)CWnd::FindWindow("#32770", "�����");
	//4.4 ����� ������ �����쿡�� ã�´�.
	accountBookForm->accountBook->Find(Date(charOne), Date(charOther), &this->indexes, &this->count);
	//4.5 ����Ʈ����Ʈ�ѿ��� �ִ� ��� �׸���� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->DeleteAllItems();
	//4.6 ����Ʈ����Ʈ�ѿ��� ã�� ������ŭ �׸���� �߰��Ѵ�.
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
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 2, cstringAmount);
		Currency accountBalance = account->GetBalance();
		CString cstringBalance;
		cstringBalance.Format("%d", (int)accountBalance);
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 3, cstringBalance);
		CString accountRemarks = account->GetRemarks().c_str();
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 4, accountRemarks);
		i++;
	}
	//4.7 ����� ������ �����쿡�� ����Ѵ�.
	Currency totalIncome;
	Currency totalOutgo;
	Currency totalBalance;
	accountBookForm->accountBook->Calculate(Date(charOne), Date(charOther), &totalIncome, &totalOutgo, &totalBalance);
	//4.8 ����â�� �Ѽ���, ������, ���ܾ��� ����Ѵ�.
	CString cstringTotalIncome;
	cstringTotalIncome.Format("%0.lf", totalIncome);
	GetDlgItem(IDC_STATIC_EDIT_TOTALINCOME)->SetWindowText(cstringTotalIncome);
	CString cstringTotalOutgo;
	cstringTotalOutgo.Format("%0.lf", totalOutgo);
	GetDlgItem(IDC_STATIC_EDIT_TOTALOUTGO)->SetWindowText(cstringTotalOutgo);
	CString cstringTotalBalance;
	cstringTotalBalance.Format("%0.lf", totalBalance);
	GetDlgItem(IDC_STATIC_EDIT_TOTALBALANCE)->SetWindowText(cstringTotalBalance);
}

//5. �ݱ��ư�� Ŭ������ ��
void FindingForm::OnClose()
{
	//5.1 ���ι迭�� ���ش�.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	//5.2 �����츦 �ݴ´�.
	EndDialog(0);
}