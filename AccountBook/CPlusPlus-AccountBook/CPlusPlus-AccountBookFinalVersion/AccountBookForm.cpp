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
#include<afxdb.h>//ODBC class 헤더파일
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
	this->accountBook = NULL;//NULL로 초기화시킴.
}

//데이터베이스응용프로그래밍 시작

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
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//데이터베이스에 있는 기존 데이터들을 지우기 전에 code들을 Recordset에 저장함.
	CString sql2 = "DELETE FROM Account;";//데이터베이스에 새로운 데이터들을 저장하기 전에 기존에 데이터들을 모두 지움.
	db.ExecuteSQL(sql2);//데이터베이스에서 기존의 데이터들을 지우는 명령을 실행함.

	CString code;
	CString sql3;
	Long i = 0;
	while (i < this->accountBook->GetLength())
	{
		rs.GetFieldValue((short)0, code);
		Account *account = this->accountBook->GetAt(i);
		//지출인지 판단한다.
		//지출이면
		Currency amount = account->GetAmount();
		if (dynamic_cast<Outgo*>(account))
		{
			//금액을 음수로 바꾼다.
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
	//지출인지 판단한다.
	//지출이면
	Currency amount = account->GetAmount();
	if (dynamic_cast<Outgo*>(account))
	{
		//금액을 음수로 바꾼다.
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
	if (!rs.IsEOF())//데이터베이스에 저장된 데이터가 있으면
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
	//지출인지 판단한다.
	//지출이면
	Currency amount = account->GetAmount();
	if (dynamic_cast<Outgo*>(account))
	{
		//금액을 음수로 바꾼다.
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

//데이터베이스응용프로그래밍 끝

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
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(0, "일자", LVCFMT_LEFT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(1, "적요", LVCFMT_CENTER, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(2, "금액", LVCFMT_RIGHT, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(3, "잔액", LVCFMT_RIGHT, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(4, "비고", LVCFMT_CENTER, 150);
	//1.6 리스트뷰 컨트롤의 어떤 부분을 클랙해도 선택이 되게 하기 위한 수단
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.7 데이터베이스에 있는 데이터들을 가계부에 적재한다.
	this->Load();


	//리스트뷰컨트롤에 이지미삽입
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
	//1.8 가계부에 적재된 개수만큼 리스트뷰컨트롤에 항목들을 추가한다.
	Date accountDate;//자료형 선언은 반복구조 밖에서 하는게 좋음.
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
		//수입이면
		if (dynamic_cast<Income*>(account))
		{
			item.iImage = 1;
		}
		//지출이면
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

//데이트피커를 클릭했을 때
void AccountBookForm::OnDateTimePickerCliked()
{
	//리스트뷰컨트롤에서 항목 선택을 없앤다.
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetSelectionMark(-1);
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
	if (outgoChecked == BST_CHECKED && amount != "" && currencyAmount != 0)
	{
		//4.4.1 금액을 음수로 바꾼다.
		currencyAmount *= (-1);
		amount.Format("%.0lf", currencyAmount);
	}
	//4.5 리스트뷰컨트롤에서 선택된 항목의 위치를 읽는다.
	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	//4.6 리스트뷰 컨트롤에서 선택된 위치가 없는 경우에
	BOOL IsMinusRemoved = FALSE;
	Long m;
	Long k;
	Long j;
	int remainder;
	if (index == -1)
	{
		//4.6.1 가계부에 account가 처음이면
		if (this->accountBook->GetLength() == 0)
		{
			//4.6.1.1 잔액스태틱에 금액을 출력한다.
			//amount가 음수이면
			if (amount.Find('-') != -1)
			{
				//minus 부호를 없앤다.
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

			//minus부호를 없앴으면
			if (IsMinusRemoved == TRUE)
			{
				//minus부호를 다시 넣어준다.
				amount.Insert(0, "-");
			}
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
			//cstringBalance가 음수이면
			if (cstringBalance.Left(1) == "-")
			{
				//minus 부호를 없앤다.
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

			//minus부호를 없앴으면
			if (IsMinusRemoved == TRUE)
			{
				//minus를 다시 넣어준다.
				cstringBalance.Insert(0, "-");
			}
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
			//amount가 음수이면
			if (amount.Find('-') != -1)
			{
				//minus 부호를 없앤다.
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
			//minus부호를 없앴으면
			if (IsMinusRemoved == TRUE)
			{
				//minus부호를 다시 넣어준다.
				amount.Insert(0, "-");
			}
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
			//cstringBalance가 음수이면
			if (cstringBalance.Find('-') != -1)
			{
				//minus 부호를 없앤다.
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
			//minus부호를 없앴으면
			if (IsMinusRemoved == TRUE)
			{
				//minus를 다시 넣어준다.
				cstringBalance.Insert(0, "-");
			}
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
	//5.7 데이터베이스에 저장한다.
	this->Insert(index);
	//5.8 account를 구한다.
	Account* account = this->accountBook->GetAt(index);

	//리스트뷰컨트롤에 이지미삽입
	CImageList* imageList = new CImageList;
	imageList->Create(16, 16, ILC_COLOR32, 2, 0);
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	imageList->Add(hIcon);
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	imageList->Add(hIcon);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetImageList(imageList, LVSIL_SMALL);

	LVITEM item = { 0, };
	item.mask = LVIF_TEXT | LVIF_IMAGE;

	//수입이면
	if (dynamic_cast<Income*>(account))
	{
		item.iImage = 1;
	}
	//지출이면
	else if (dynamic_cast<Outgo*>(account))
	{
		item.iImage = 0;
	}
	item.iItem = index;

	//5.9 리스트뷰 컨트롤에 항목을 추가한다.
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
	//7.8 데이터베이스에서 고친다.
	this->Update(index);
	//7.9 account를 구한다.
	Account* account = this->accountBook->GetAt(index);
	//7.10 account의 금액을 구하고 구한 금액으로 리스트뷰 컨트롤에서 고친다.
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
	//7.11 account의 잔액을 구하고 구한 잔액으로 리스트뷰 컨트롤에서 고친다.
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
	//7.12 비고를 구하고 구한 비고로 리스트뷰 컨트롤에서 고친다.
	CString accountRemarks = account->GetRemarks().c_str();
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 4, accountRemarks);
	//7.13 index가 length보다 작은동안에 반복한다.
	index++;
	while (index < this->accountBook->GetLength())
	{
		//7.13.1 account를 구한다.
		account = this->accountBook->GetAt(index);
		//7.13.2 잔액을 구한다.
		balance = account->GetBalance();
		cstringBalance;
		cstringBalance.Format("%d", (int)balance);
		//7.13.3 리스트뷰컨트롤에서 고친 항목 이후의 항목들의 잔액을 고친다.
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
	//7.14 리스트뷰컨트롤에서 항목 선택을 없앤다.
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
	amount.Remove(',');
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
	//9.1 데이터베이스에 가계부를 저장한다.
	this->Save();
	//9.2 가계부를 지운다.
	if (this->accountBook != NULL)
	{
		delete this->accountBook;
	}
	//9.3 윈도우를 닫는다.
	EndDialog(0);// this->EndDialog(0); 가 원래 문장이지만 this를 안써도 MFC에서 알아서 처리해줌.
}


