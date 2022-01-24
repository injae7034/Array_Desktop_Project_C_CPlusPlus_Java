#include "AccountBookForm.h"
#include "FindingForm.h"
#include "AccountBook.h"
#include "Account.h"//AccountBook������Ͽ����� Account�� ���漱�� �Ǿ� �ֱ⶧���� 
//AccountBook�� ������ ����ϱ� ���ؼ��� ���� ������� ������ �������.
#include "Income.h"
#include "Outgo.h"
#include "resource.h"
#include<afxwin.h>//CDialog�������
#include<afxcmn.h>//CListCtrl�������
#include<afxdtctl.h>//CDateTimeCrtl�������

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
	this->accountBook = NULL;//NULL�� �ʱ�ȭ��Ŵ.
}

//1. �����찡 ������ ��
BOOL AccountBookForm::OnInitDialog()
{
	//1.1 ����θ� �����.
	CDialog::OnInitDialog();
	this->accountBook = new AccountBook;//�迭�� �ƴ϶� �ּҸ� ������ �Ϲ� �����ͺ�����.
	//1.2 ���Զ��� ��ư�� UNCHECKED�Ѵ�.
	((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	//1.3 ���������ư�� CHECKED�Ѵ�.
	((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);
	//1.4 �ܾ׿� 0���� ����Ѵ�.
	GetDlgItem(IDC_STATIC_EDIT_BALANCE)->SetWindowText(0);
	//1.5 ����Ʈ�� ��Ʈ���� ����� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(0, "����", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(1, "����", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(2, "�ݾ�", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(3, "�ܾ�", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(4, "���", LVCFMT_CENTER, 150);
	//1.6 ����Ʈ�� ��Ʈ���� � �κ��� Ŭ���ص� ������ �ǰ� �ϱ� ���� ����
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	return FALSE;
}

//2. ���Զ��� ��ư�� Ŭ������ ��
void AccountBookForm::OnIncomeRadioButtonClicked()
{
	//2.1 ������� ��ư�� uncheck�Ѵ�.
	((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_UNCHECKED);
}

//3. ������� ��ư�� Ŭ������ ��
void AccountBookForm::OnOutgoRadioButtonClicked()
{
	//3.1 ���Զ�����ư�� uncheck�Ѵ�.
	((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
}

//4. �ݾ׿���Ʈ�� ��Ŀ���� ���� ��
void AccountBookForm::OnAmountEditKillFocus()
{
	//4.1 ���Զ��� ��ư�� �д´�.
	int incomeChecked = ((CButton*)GetDlgItem(IDC_RADIO_INCOME))->GetCheck();
	//4.2 ������� ��ư�� �д´�.
	int outgoChecked = ((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->GetCheck();
	//4.3 �ݾ� ����Ʈ���� �ݾ��� �д´�.
	CString amount;
	GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowText(amount);
	//4.4 �ݾ��� �ڷ����� Currency�� �ٲ۴�.
	Currency currencyAmount = _ttoi(amount);
	//4.4 ���õ� ������ư�� �����̸�
	if (outgoChecked == BST_CHECKED)
	{
		//4.4.1 �ݾ��� ������ �ٲ۴�.
		currencyAmount *= (-1);
		amount.Format("%.0lf", currencyAmount);
	}
	//4.5 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	//4.6 ����Ʈ�� ��Ʈ�ѿ��� ���õ� ��ġ�� ���� ��쿡
	if (index == -1)
	{
		//4.6.1 ����ο� account�� ó���̸�
		if (this->accountBook->GetLength() == 0)
		{
			//4.6.1.1 �ܾ׽���ƽ�� �ݾ��� ����Ѵ�.
			GetDlgItem(IDC_STATIC_EDIT_BALANCE)->SetWindowText(amount);
		}
		//4.6.2 ����ο� account�� ó���� �ƴϸ�
		else if (this->accountBook->GetLength() > 0)
		{
			//4.6.2.1 ������� ���������� ���Ѵ�.
			Account* account = this->accountBook->GetAt(this->accountBook->GetLength() - 1);
			//4.6.2.2 ���������� �ܾ��� ���Ѵ�.
			Currency balance = account->GetBalance();
			//4.6.2. �ֽ��ܾ��� ���Ѵ�.
			Currency currentBalance = balance + currencyAmount;
			CString cstringBalance;
			cstringBalance.Format("%.0lf", currentBalance);
			//4.6.2.4 �ܾ׽���ƽ�� �ֽ��ܾ��� ����Ѵ�.
			GetDlgItem(IDC_STATIC_EDIT_BALANCE)->SetWindowText(cstringBalance);
		}
	}
	//4.7 ��ġ���ư�� ���� ���
	else
	{
		//4.7.1 ����Ʈ����Ʈ�ѿ��� ������ �׸��� ó���̸�
		if (index == 0)
		{
			//4.6.1.1 �ܾ׽���ƽ�� �ݾ��� ����Ѵ�.
			GetDlgItem(IDC_STATIC_EDIT_BALANCE)->SetWindowText(amount);
		}
		//4.7.2 ó���� �ƴϸ�
		else
		{
			//4.7.1 account�� ���Ѵ�.
			Account* account = this->accountBook->GetAt(index - 1);
			//4.7.2 account�� �ܾ��� ���Ѵ�.
			Currency balance = account->GetBalance();
			//4.7.3 �ֽ��ܾ��� ���Ѵ�.
			Currency currentBalance = balance + currencyAmount;
			CString cstringBalance;
			cstringBalance.Format("%.0lf", currentBalance);
			//4.7.4 �ܾ׽���ƽ�� �ֽ��ܾ��� ����Ѵ�.
			GetDlgItem(IDC_STATIC_EDIT_BALANCE)->SetWindowText(cstringBalance);
		}
	}
}

//5. �����ϱ��ư�� Ŭ������ ��
void AccountBookForm::OnRecordButtonClicked()
{
	//5.1 ���Զ�����ư�� �д´�.
	int incomeChecked = ((CButton*)GetDlgItem(IDC_RADIO_INCOME))->GetCheck();
	//5.2 ���������ư�� �д´�.
	int outgoChecked = ((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->GetCheck();
	//5.3 ����, ����, �ݾ�, ��� �д´�.
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
	//5.4 �ݾ��� �ڷ����� Currency�� �ٲ۴�.
	Currency currencyAmount = _ttoi(amount);
	//5.5 ���õ� ������ư�� �����̸�
	if (outgoChecked == BST_CHECKED)
	{
		//5.5.1 �ݾ��� ������ �ٲ۴�.
		currencyAmount *= (-1);
	}
	//5.6 ����ο��� �����Ѵ�.
	Long index = this->accountBook->Record(charDate, (LPCTSTR)briefs, currencyAmount, (LPCTSTR)remarks);
	//5.7 account�� ���Ѵ�.
	Account* account = this->accountBook->GetAt(index);
	//5.8 ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
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

//6. ã�� ��ư�� Ŭ������ ��
void AccountBookForm::OnFindButtonClicked()
{
	FindingForm findingForm;//��ü����, ����
	//3.1 ã�� ������ �����츦 ����.
	findingForm.DoModal();// �����̹Ƿ� .���� ���������.
}

//7. ��ġ���ư�� Ŭ������ ��
void AccountBookForm::OnCorrectButtonClicked()
{
	//7.1 ���Զ�����ư�� �д´�.
	int incomeChecked = ((CButton*)GetDlgItem(IDC_RADIO_INCOME))->GetCheck();
	//7.2 ���������ư�� �д´�.
	int outgoChecked = ((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->GetCheck();
	//7.3 �ݾ�, ��� �д´�.
	CString amount;
	GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowText(amount);
	CString remarks;
	GetDlgItem(IDC_EDIT_REMARKS)->GetWindowText(remarks);
	//7.4 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	//7.5 �ݾ��� �ڷ����� Currency�� �ٲ۴�.
	Currency currencyAmount = _ttoi(amount);
	//7.6 ���õ� ������ư�� �����̸�
	if (outgoChecked == BST_CHECKED)
	{
		//7.6.1 �ݾ��� ������ �ٲ۴�.
		currencyAmount *= (-1);
	}
	//7.7 ����ο��� ��ģ��.
	index = this->accountBook->Correct(index, currencyAmount, (LPCTSTR)remarks);
	//7.8 account�� ���Ѵ�.
	Account* account = this->accountBook->GetAt(index);
	//7.9 account�� �ݾ��� ���ϰ� ���� �ݾ����� ����Ʈ�� ��Ʈ�ѿ��� ��ģ��.
	currencyAmount = account->GetAmount();
	amount.Format("%d", (int)currencyAmount);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 2, amount);
	//7.9 account�� �ܾ��� ���ϰ� ���� �ܾ����� ����Ʈ�� ��Ʈ�ѿ��� ��ģ��.
	Currency balance = account->GetBalance();
	CString cstringBalance;
	cstringBalance.Format("%d", (int)balance);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 3, cstringBalance);
	//7.10 ��� ���ϰ� ���� ���� ����Ʈ�� ��Ʈ�ѿ��� ��ģ��.
	CString accountRemarks = account->GetRemarks().c_str();
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 4, accountRemarks);
	//7.8 index�� length���� �������ȿ� �ݺ��Ѵ�.
	index++;
	while (index < this->accountBook->GetLength())
	{
		//5.7.1 account�� ���Ѵ�.
		account = this->accountBook->GetAt(index);
		//5.7.2 �ܾ��� ���Ѵ�.
		balance = account->GetBalance();
		cstringBalance;
		cstringBalance.Format("%d", (int)balance);
		//5.7.3 ����Ʈ����Ʈ�ѿ��� ��ģ �׸� ������ �׸���� �ܾ��� ��ģ��.
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 3, cstringBalance);
		index++;
	}
	//7.9 ����Ʈ����Ʈ�ѿ��� �׸� ������ ���ش�.
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetSelectionMark(-1);
}

//8. ����Ʈ�� ��Ʈ�ѿ��� �׸��� ����Ŭ������ ��
void AccountBookForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//8.1 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	//8.2 ����Ʈ����Ʈ�ѿ��� ������ �׸��� ����, ����, �ݾ�, �ܾ�, ��� �д´�.
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
	//8.3 ����Ʈ�� ��Ʈ�ѿ��� ���� ����, ����, �ݾ�, �ܾ�, ��� ����Ѵ�.
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
	//8.4 account�� �������� �������� �Ǵ��Ѵ�.
	Account* account = this->accountBook->GetAt(index);
	//8.4.1 �����̸�
	if (dynamic_cast<Income*>(account))
	{
		//8.4.1.1 ���Զ�����ư�� �����Ѵ�.
		((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_CHECKED);
		//8.4.1.2 ���������ư�� UNCHKECK�Ѵ�.
		((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_UNCHECKED);
	}
	//8.4.2 account�� �����̸�
	else if (dynamic_cast<Outgo*>(account))
	{
		//8.4.2.1 ���������ư�� �����Ѵ�.
		((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);
		//8.4.2.2 ���Զ�����ư�� UNCHKECK�Ѵ�.
		((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	}
}

//9. �ݱ��ư�� Ŭ������ ��
void AccountBookForm::OnClose()//AccountBookForm::->�غ� �ǹ��� this��.
{
	//7.1 ����θ� �����.
	if (this->accountBook != NULL)
	{
		delete this->accountBook;
	}
	//7.2 �����츦 �ݴ´�.
	EndDialog(0);// this->EndDialog(0); �� ���� ���������� this�� �Ƚᵵ MFC���� �˾Ƽ� ó������.
}


