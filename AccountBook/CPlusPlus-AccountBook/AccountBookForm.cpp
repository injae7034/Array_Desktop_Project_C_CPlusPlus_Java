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
#include<afxdb.h>//ODBC class �������
#include<string>

BEGIN_MESSAGE_MAP(AccountBookForm, CDialog)
	ON_EN_CHANGE(IDC_DATETIMEPICKER_ONE, OnDateTimePickerCliked)
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

//�����ͺ��̽��������α׷��� ����

//Load
void AccountBookForm::Load()
{
	CDatabase db;//Connection, INSERT, DELETE, UPDATE, Disconnection
	CRecordset rs(&db);//SELECT
	CString sql = "SELECT Account.date, Account.briefs, Account.amount, Account.remarks FROM Account;";
	db.OpenEx("DSN=AccountBook;UID=root;PWD=1q2w3e");//Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//Request, Response

	CDBVariant date;
	CString briefs;
	CDBVariant amount;
	CString remarks;
	while (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0, date, SQL_C_TIMESTAMP);
		rs.GetFieldValue((short)1, briefs);
		rs.GetFieldValue((short)2, amount, SQL_C_DOUBLE);
		rs.GetFieldValue((short)3, remarks);
		this->accountBook->Record(Date(date.m_pdate->year, (Month)date.m_pdate->month, date.m_pdate->day), 
			(LPCTSTR)briefs, amount.m_dblVal, (LPCTSTR)remarks);
		rs.MoveNext();
	}
	//Disconnection
	rs.Close();
	db.Close();
}

//Save
void AccountBookForm::Save()
{
	CDatabase db;//Connection, INSERT, DELETE, UPDATE, Disconnection
	CRecordset rs(&db);//SELECT
	CString sql = "SELECT Account.code FROM Account;";
	db.OpenEx("DSN=AccountBook;UID=root;PWD=1q2w3e");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//�����ͺ��̽��� �ִ� ���� �����͵��� ����� ���� code���� Recordset�� ������.
	CString sql2 = "DELETE FROM Account;";//�����ͺ��̽��� ���ο� �����͵��� �����ϱ� ���� ������ �����͵��� ��� ����.
	db.ExecuteSQL(sql2);//�����ͺ��̽����� ������ �����͵��� ����� ����� ������.

	CString code;
	CString sql3;
	Long i = 0;
	while (i < this->accountBook->GetLength())
	{
		rs.GetFieldValue((short)0, code);
		Account *account = this->accountBook->GetAt(i);
		//�������� �Ǵ��Ѵ�.
		//�����̸�
		Currency amount = account->GetAmount();
		if (dynamic_cast<Outgo*>(account))
		{
			//�ݾ��� ������ �ٲ۴�.
			amount *= -1;
		}
		sql3.Format("INSERT INTO Account(code, date, briefs, amount, remarks) "
			"VALUES('%s', '%04d%02d%02d', '%s', '%.0lf', '%s');", (LPCTSTR)code, 
			account->GetDate().GetYear(), (int)account->GetDate().GetMonth(), account->GetDate().GetDay(),
			account->GetBriefs().c_str(), amount, account->GetRemarks().c_str());
		db.ExecuteSQL(sql3);
		rs.MoveNext();
		i++;
	}
	rs.Close();
	db.Close();
}

//Insert
void AccountBookForm::Insert(Long index)
{
	CDatabase db;
	Account *account = this->accountBook->GetAt(index);
	//�������� �Ǵ��Ѵ�.
	//�����̸�
	Currency amount = account->GetAmount();
	if (dynamic_cast<Outgo*>(account))
	{
		//�ݾ��� ������ �ٲ۴�.
		amount *= -1;
	}
	CString sql;
	CString code = this->GetCode();
	sql.Format("INSERT INTO Account(code, date, briefs, amount, remarks) "
		"VALUES('%s', '%04d%02d%02d', '%s', '%.0lf', '%s');", (LPCTSTR)code,
		account->GetDate().GetYear(), (int)account->GetDate().GetMonth(), account->GetDate().GetDay(),
		account->GetBriefs().c_str(), amount, account->GetRemarks().c_str());
	db.OpenEx("DSN=AccountBook;UID=root;PWD=1q2w3e");
	db.ExecuteSQL(sql);//Request
	db.Close();//Disconnection
}

//GetCode
CString AccountBookForm::GetCode()
{
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Account.code FROM Account ORDER BY code DESC;";
	db.OpenEx("DSN=AccountBook;UID=root;PWD=1q2w3e");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	Date today = Date::Today();
	CString code;
	code.Format("%04d%02d000", today.GetYear(), (int)today.GetMonth());
	int number;
	if (!rs.IsEOF())//�����ͺ��̽��� ����� �����Ͱ� ������
	{
		rs.GetFieldValue((short)0, code);
	}
	number = _ttoi(code.Right(3));
	number++;
	code.Format("%04d%02d%03d", today.GetYear(), (int)today.GetMonth(), number);
	rs.Close();
	db.Close();

	return code;
}

//Update
void AccountBookForm::Update(Long index)
{
	CDatabase db;//Connection, INSERT, DELETE, UPDATE, Disconnection
	CRecordset rs(&db);//SELECT
	CString sql = "SELECT Account.code FROM Account;";
	db.OpenEx("DSN=AccountBook;UID=root;PWD=1q2w3e");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	CString code;
	Account *account = this->accountBook->GetAt(index);
	//�������� �Ǵ��Ѵ�.
	//�����̸�
	Currency amount = account->GetAmount();
	if (dynamic_cast<Outgo*>(account))
	{
		//�ݾ��� ������ �ٲ۴�.
		amount *= -1;
	}
	Long i = 0;
	while (!rs.IsEOF() && i <= index)
	{
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}
	sql.Format("UPDATE Account SET amount='%0.lf', remarks='%s' WHERE code='%s';",
		amount, account->GetRemarks().c_str(), (LPCTSTR)code);
	db.ExecuteSQL(sql);
	rs.Close();
	db.Close();
}

//�����ͺ��̽��������α׷��� ��

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
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(0, "����", LVCFMT_LEFT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(1, "����", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(2, "�ݾ�", LVCFMT_RIGHT, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(3, "�ܾ�", LVCFMT_RIGHT, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(4, "���", LVCFMT_CENTER, 150);
	//1.6 ����Ʈ�� ��Ʈ���� � �κ��� Ŭ���ص� ������ �ǰ� �ϱ� ���� ����
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.7 �����ͺ��̽��� �ִ� �����͵��� ����ο� �����Ѵ�.
	this->Load();


	//����Ʈ����Ʈ�ѿ� �����̻���
	CImageList* imageList = new CImageList;

	imageList->Create(16, 16, ILC_COLOR32, 2, 0);
	
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	imageList->Add(hIcon);
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	imageList->Add(hIcon);
	//CImageList* imageIndex = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetImageList(imageList, LVSIL_SMALL | LVSIL_STATE);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetImageList(imageList, LVSIL_SMALL); //| LVSIL_STATE);

	LVITEM item = { 0, };
	item.mask = LVIF_TEXT | LVIF_IMAGE; //| LVIF_STATE;
	//item.iImage = 0;
	//item.stateMask = LVIS_STATEIMAGEMASK;
	//item.state = INDEXTOSTATEIMAGEMASK(0);

	

	//CListCtrl list;
	//list.Create(LVS_ICON, CRect(16, 16, 16, 16), this, IDC_LIST_ACCOUNTS);

	//CImageList* bigSmile = new CImageList;
	//CImageList smallSmile;
	//CImageList bigSad;
	//CImageList smallSad;
	//CImageList *imageList = new CImageList;
	//imageList->Create(16, 16, ILC_COLOR32, 2, 0);
	//smallSmile.Create(16, 16, ILC_COLOR4, 1, 1);
	//bigSad.Create(32, 32, ILC_COLOR4, 1, 1);
	//smallSad.Create(32, 32, ILC_COLOR4, 1, 1);

	//imageList->Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	//this->imageList->Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	//((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetImageList(imageList, LVSIL_NORMAL);
	//imageList->Detach();
	//LVITEM item = { 0, };
	//item.mask =  LVIF_IMAGE;
	//item.iSubItem = 0;
	//item.iImage = 0;
	//item.stateMask = LVIS_STATEIMAGEMASK;
	//GetDlgItem(IDC_LIST_ACCOUNTS)->ModifyStyle(LVS_TYPEMASK, LVS_ICON);
	//GetDlgItem(IDC_LIST_ACCOUNTS)->SetExtendedListViewStyleEx(m_ListCtrl.m_hwnd, LVS_EX_SUBITEMIMAGES)
	//LVITEM item = { 0, };
	//item.mask = LVIF_TEXT;
	//item.iImage = -1;
	//1.8 ����ο� ����� ������ŭ ����Ʈ����Ʈ�ѿ� �׸���� �߰��Ѵ�.
	Date accountDate;//�ڷ��� ������ �ݺ����� �ۿ��� �ϴ°� ����.
	Currency accountAmount;
	CString cstringAmount;
	Currency accountBalance;
	CString cstringBalance;
	CString accountRemarks;
	Long i = 0;
	while (i < this->accountBook->GetLength())
	{
		item.iItem = i;
		Account* account = this->accountBook->GetAt(i);
		//�����̸�
		if (dynamic_cast<Income*>(account))
		{
			item.iImage = 1;
		}
		//�����̸�
		else if (dynamic_cast<Outgo*>(account))
		{
			item.iImage = 0;
		}
		accountDate = account->GetDate();
		item.iSubItem = 0;
		item.pszText = accountDate;
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertItem(&item);
		item.iSubItem = 1;
		item.pszText = (LPSTR)account->GetBriefs().c_str();
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItem(&item);
		accountAmount = account->GetAmount();
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
		Long m = 0;
		Long j = 3;
		while (j < cstringAmount.GetLength() - m)
		{
			cstringAmount.Insert(k, ",");
			m++;
			k += 4;
			j += 3;
		}

		item.iSubItem = 2;
		item.pszText = (LPSTR)(LPCTSTR)cstringAmount;
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItem(&item);
		accountBalance = account->GetBalance();
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
		m = 0;
		j = 3;
		while (j < cstringBalance.GetLength() - m)
		{
			cstringBalance.Insert(k, ",");
			m++;
			k += 4;
			j += 3;
		}

		item.iSubItem = 3;
		item.pszText = (LPSTR)(LPCTSTR)cstringBalance;
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItem(&item);
		accountRemarks = account->GetRemarks().c_str();
		item.iSubItem = 4;
		item.pszText = (LPSTR)account->GetRemarks().c_str();
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItem(&item);
		i++;
	}
	return FALSE;
}

//����Ʈ��Ŀ�� Ŭ������ ��
void AccountBookForm::OnDateTimePickerCliked()
{
	//����Ʈ����Ʈ�ѿ��� �׸� ������ ���ش�.
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetSelectionMark(-1);
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
	if (outgoChecked == BST_CHECKED && amount != "" && currencyAmount != 0)
	{
		//4.4.1 �ݾ��� ������ �ٲ۴�.
		currencyAmount *= (-1);
		amount.Format("%.0lf", currencyAmount);
	}
	//4.5 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	//4.6 ����Ʈ�� ��Ʈ�ѿ��� ���õ� ��ġ�� ���� ��쿡
	BOOL IsMinusRemoved = FALSE;
	Long m;
	Long k;
	Long j;
	int remainder;
	if (index == -1)
	{
		//4.6.1 ����ο� account�� ó���̸�
		if (this->accountBook->GetLength() == 0)
		{
			//4.6.1.1 �ܾ׽���ƽ�� �ݾ��� ����Ѵ�.
			//amount�� �����̸�
			if (amount.Find('-') != -1)
			{
				//minus ��ȣ�� ���ش�.
				amount.Remove('-');
				IsMinusRemoved = TRUE;
			}

			k = 0;
			remainder = amount.GetLength() % 3;
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
			while (j < amount.GetLength() - m)
			{
				amount.Insert(k, ",");
				m++;
				k += 4;
				j += 3;
			}

			//minus��ȣ�� ��������
			if (IsMinusRemoved == TRUE)
			{
				//minus��ȣ�� �ٽ� �־��ش�.
				amount.Insert(0, "-");
			}
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
			//cstringBalance�� �����̸�
			if (cstringBalance.Left(1) == "-")
			{
				//minus ��ȣ�� ���ش�.
				cstringBalance.Remove('-');
				IsMinusRemoved = TRUE;
			}

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
			m = 0;
			j = 3;
			while (j < cstringBalance.GetLength() - m)
			{
				cstringBalance.Insert(k, ",");
				m++;
				k += 4;
				j += 3;
			}

			//minus��ȣ�� ��������
			if (IsMinusRemoved == TRUE)
			{
				//minus�� �ٽ� �־��ش�.
				cstringBalance.Insert(0, "-");
			}
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
			//amount�� �����̸�
			if (amount.Find('-') != -1)
			{
				//minus ��ȣ�� ���ش�.
				amount.Remove('-');
				IsMinusRemoved = TRUE;
			}
			k = 0;
			remainder = amount.GetLength() % 3;
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
			while (j < amount.GetLength() - m)
			{
				amount.Insert(k, ",");
				m++;
				k += 4;
				j += 3;
			}
			//minus��ȣ�� ��������
			if (IsMinusRemoved == TRUE)
			{
				//minus��ȣ�� �ٽ� �־��ش�.
				amount.Insert(0, "-");
			}
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
			//cstringBalance�� �����̸�
			if (cstringBalance.Find('-') != -1)
			{
				//minus ��ȣ�� ���ش�.
				cstringBalance.Remove('-');
				IsMinusRemoved = TRUE;
			}
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
			m = 0;
			j = 3;
			while (j < cstringBalance.GetLength() - m)
			{
				cstringBalance.Insert(k, ",");
				m++;
				k += 4;
				j += 3;
			}
			//minus��ȣ�� ��������
			if (IsMinusRemoved == TRUE)
			{
				//minus�� �ٽ� �־��ش�.
				cstringBalance.Insert(0, "-");
			}
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
	//5.7 �����ͺ��̽��� �����Ѵ�.
	this->Insert(index);
	//5.8 account�� ���Ѵ�.
	Account* account = this->accountBook->GetAt(index);

	//����Ʈ����Ʈ�ѿ� �����̻���
	CImageList* imageList = new CImageList;
	imageList->Create(16, 16, ILC_COLOR32, 2, 0);
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	imageList->Add(hIcon);
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	imageList->Add(hIcon);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetImageList(imageList, LVSIL_SMALL);

	LVITEM item = { 0, };
	item.mask = LVIF_TEXT | LVIF_IMAGE;

	//�����̸�
	if (dynamic_cast<Income*>(account))
	{
		item.iImage = 1;
	}
	//�����̸�
	else if (dynamic_cast<Outgo*>(account))
	{
		item.iImage = 0;
	}
	item.iItem = index;

	//5.9 ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
	Date accountDate = account->GetDate();
	item.iSubItem = 0;
	item.pszText = accountDate;
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertItem(&item);
	item.iSubItem = 1;
	item.pszText = (LPSTR)account->GetBriefs().c_str();
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItem(&item);
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
	Long m = 0;
	Long j = 3;
	while (j < cstringAmount.GetLength() - m)
	{
		cstringAmount.Insert(k, ",");
		m++;
		k += 4;
		j += 3;
	}
	item.iSubItem = 2;
	item.pszText = (LPSTR)(LPCTSTR)cstringAmount;
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItem(&item);
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
	m = 0;
	j = 3;
	while (j < cstringBalance.GetLength() - m)
	{
		cstringBalance.Insert(k, ",");
		m++;
		k += 4;
		j += 3;
	}
	item.iSubItem = 3;
	item.pszText = (LPSTR)(LPCTSTR)cstringBalance;
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItem(&item);
	item.iSubItem = 4;
	item.pszText = (LPSTR)account->GetRemarks().c_str();
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItem(&item);
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
	//7.8 �����ͺ��̽����� ��ģ��.
	this->Update(index);
	//7.9 account�� ���Ѵ�.
	Account* account = this->accountBook->GetAt(index);
	//7.10 account�� �ݾ��� ���ϰ� ���� �ݾ����� ����Ʈ�� ��Ʈ�ѿ��� ��ģ��.
	currencyAmount = account->GetAmount();
	amount.Format("%d", (int)currencyAmount);
	Long k = 0;
	int remainder = amount.GetLength() % 3;
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
	Long m = 0;
	Long j = 3;
	while (j < amount.GetLength() - m)
	{
		amount.Insert(k, ",");
		m++;
		k += 4;
		j += 3;
	}
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 2, amount);
	//7.11 account�� �ܾ��� ���ϰ� ���� �ܾ����� ����Ʈ�� ��Ʈ�ѿ��� ��ģ��.
	Currency balance = account->GetBalance();
	CString cstringBalance;
	cstringBalance.Format("%d", (int)balance);
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
	m = 0;
	j = 3;
	while (j < cstringBalance.GetLength() - m)
	{
		cstringBalance.Insert(k, ",");
		m++;
		k += 4;
		j += 3;
	}
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 3, cstringBalance);
	//7.12 ��� ���ϰ� ���� ���� ����Ʈ�� ��Ʈ�ѿ��� ��ģ��.
	CString accountRemarks = account->GetRemarks().c_str();
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 4, accountRemarks);
	//7.13 index�� length���� �������ȿ� �ݺ��Ѵ�.
	index++;
	while (index < this->accountBook->GetLength())
	{
		//7.13.1 account�� ���Ѵ�.
		account = this->accountBook->GetAt(index);
		//7.13.2 �ܾ��� ���Ѵ�.
		balance = account->GetBalance();
		cstringBalance;
		cstringBalance.Format("%d", (int)balance);
		//7.13.3 ����Ʈ����Ʈ�ѿ��� ��ģ �׸� ������ �׸���� �ܾ��� ��ģ��.
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
		m = 0;
		j = 3;
		while (j < cstringBalance.GetLength() - m)
		{
			cstringBalance.Insert(k, ",");
			m++;
			k += 4;
			j += 3;
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 3, cstringBalance);
		index++;
	}
	//7.14 ����Ʈ����Ʈ�ѿ��� �׸� ������ ���ش�.
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
	amount.Remove(',');
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
	//9.1 �����ͺ��̽��� ����θ� �����Ѵ�.
	this->Save();
	//9.2 ����θ� �����.
	if (this->accountBook != NULL)
	{
		delete this->accountBook;
	}
	//9.3 �����츦 �ݴ´�.
	EndDialog(0);// this->EndDialog(0); �� ���� ���������� this�� �Ƚᵵ MFC���� �˾Ƽ� ó������.
}


