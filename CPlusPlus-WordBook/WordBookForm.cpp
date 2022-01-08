#include"WordBookForm.h"
#include"WordBook.h"
#include"FindingForm.h"
#include"resource.h"
#include<afxwin.h>//CDialog 헤더파일
#include<afxcmn.h>//CListCtrl헤더파일
#include<afxdb.h>//ODBC class


BEGIN_MESSAGE_MAP(WordBookForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_WORDS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


WordBookForm::WordBookForm(CWnd* parent)
	:CDialog(WordBookForm::IDD, parent)
{
	this->wordBook = NULL;//NULL로 초기화시킴
}

//데이터베이스응용프로그래밍 시작

//Load
void WordBookForm::Load()
{
	CDatabase db;//Connection, INSERT, DELETE, UPDATE, Disconnection
	CRecordset rs(&db);//SELECT
	CString sql = "SELECT Word.spellings, Word.partOfSpeech, Word.meanings, Word.example FROM Word;";
	db.OpenEx("DSN=WordBook;UID=root;PWD=1q2w3e");//Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//Request, Response

	CString spellings;
	CString partOfSpeech;
	CString meanings;
	CString example;
	while (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0, spellings);
		rs.GetFieldValue((short)1, partOfSpeech);
		rs.GetFieldValue((short)2, meanings);
		rs.GetFieldValue((short)3, example);
		this->wordBook->Record((LPCTSTR)spellings, (LPCTSTR)partOfSpeech, (LPCTSTR)meanings,
			(LPCTSTR)example);
		rs.MoveNext();
	}
	//Disconnection
	rs.Close();
	db.Close();
}

//Save
void WordBookForm::Save()
{
	CDatabase db;//Connection, INSERT, DELETE, UPDATE, Disconnection
	CRecordset rs(&db);//SELECT
	CString sql = "SELECT Word.code FROM Word;";
	db.OpenEx("DSN=WordBook;UID=root;PWD=1q2w3e");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//데이터베이스에 있는 기존 데이터들을 지우기 전에 code들을 Recordset에 저장함.
	CString sql2 = "DELETE FROM Word;";//데이터베이스에 새로운 데이터들을 저장하기 전에 기존에 데이터들을 모두 지움.
	db.ExecuteSQL(sql2);//데이터베이스에서 기존의 데이터들을 지우는 명령을 실행함.

	CString code;
	CString sql3;
	Word word;
	Long i = 0;
	while(i < this->wordBook->GetLength())
	{
		rs.GetFieldValue((short)0, code);
		word = this->wordBook->GetAt(i);
		sql3.Format("INSERT INTO Word(code, spellings, partOfSpeech, meanings, example) "
			"VALUES('%s', '%s', '%s', '%s', '%s');", (LPCTSTR)code, word.GetSpellings().c_str(),
			word.GetPartOfSpeech().c_str(), word.GetMeanings().c_str(), word.GetExample().c_str());
		db.ExecuteSQL(sql3);
		rs.MoveNext();
		i++;
	}
	rs.Close();
	db.Close();
}

//GetCode
CString WordBookForm::GetCode()
{
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Word.code FROM Word ORDER BY code DESC;";
	db.OpenEx("DSN=WordBook;UID=root;PWD=1q2w3e");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString code = "W0000";
	int number;
	if (!rs.IsEOF())//데이터베이스에 저장된 데이터가 있으면
	{
		rs.GetFieldValue((short)0, code);
	}
	number = _ttoi(code.Right(4));
	number++;
	code.Format("W%04d", number);
	rs.Close();
	db.Close();

	return code;
}

//Insert
void WordBookForm::Insert(Long index)
{
	CDatabase db;
	Word word = this->wordBook->GetAt(index);
	CString sql;
	CString code = this->GetCode();
	sql.Format("INSERT INTO Word(code, spellings, partOfSpeech, meanings, example) "
		"VALUES('%s', '%s', '%s', '%s', '%s');", (LPCTSTR)code, word.GetSpellings().c_str(),
		word.GetPartOfSpeech().c_str(), word.GetMeanings().c_str(), word.GetExample().c_str());
	db.OpenEx("DSN=WordBook;UID=root;PWD=1q2w3e");
	db.ExecuteSQL(sql);//Request
	db.Close();//Disconnection
}

//Delete
void WordBookForm::Delete(Long index)
{
	CDatabase db;//Connection, INSERT, DELETE, UPDATE, Disconnection
	CRecordset rs(&db);//SELECT
	CString sql = "SELECT Word.code FROM Word;";
	db.OpenEx("DSN=WordBook;UID=root;PWD=1q2w3e");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	CString code;
	Long i = 0;
	while (!rs.IsEOF() && i <= index)
	{
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}
	sql.Format("DELETE FROM Word WHERE code='%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);
	rs.Close();
	db.Close();
}

//Update
void WordBookForm::Update(Long index)
{
	CDatabase db;//Connection, INSERT, DELETE, UPDATE, Disconnection
	CRecordset rs(&db);//SELECT
	CString sql = "SELECT Word.code FROM Word;";
	db.OpenEx("DSN=WordBook;UID=root;PWD=1q2w3e");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	CString code;
	Word word = this->wordBook->GetAt(index);
	Long i = 0;
	while (!rs.IsEOF() && i <= index)
	{
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}
	sql.Format("UPDATE Word SET example='%s' WHERE code='%s';", word.GetExample().c_str(),
		(LPCTSTR)code);
	db.ExecuteSQL(sql);
	rs.Close();
	db.Close();
}

//Replace
void WordBookForm::Replace()
{
	CDatabase db;//Connection, INSERT, DELETE, UPDATE, Disconnection
	CRecordset rs(&db);//SELECT
	CString sql = "SELECT Word.code FROM Word;";
	db.OpenEx("DSN=WordBook;UID=root;PWD=1q2w3e");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//데이터베이스에 있는 기존 데이터들을 지우기 전에 code들을 Recordset에 저장함.
	CString sql2 = "DELETE FROM Word;";//데이터베이스에 새로운 데이터들을 저장하기 전에 기존에 데이터들을 모두 지움.
	db.ExecuteSQL(sql2);//데이터베이스에서 기존의 데이터들을 지우는 명령을 실행함.

	CString code;
	CString sql3;
	Word word;
	Long i = 0;
	while (i < this->wordBook->GetLength())
	{
		rs.GetFieldValue((short)0, code);
		word = this->wordBook->GetAt(i);
		sql3.Format("INSERT INTO Word(code, spellings, partOfSpeech, meanings, example) "
			"VALUES('%s', '%s', '%s', '%s', '%s');", (LPCTSTR)code, word.GetSpellings().c_str(),
			word.GetPartOfSpeech().c_str(), word.GetMeanings().c_str(), word.GetExample().c_str());
		db.ExecuteSQL(sql3);
		rs.MoveNext();
		i++;
	}
	rs.Close();
	db.Close();
}

//데이터베이스 응용프로그래밍 끝


//1.윈도우가 생성될 때
BOOL WordBookForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	TCHAR partOfSpeechs[][8] = {
		"명사",
		"대명사",
		"동사",
		"형용사",
		"부사",
		"전치사",
		"접속사",
		"감탄사"
	};
	//1.1 단어장을 만든다.
	this->wordBook = new WordBook;
	//1.2 콤보박스에 항목들을 추가한다.
	Long index = 0;
	while (index < sizeof(partOfSpeechs) / sizeof(partOfSpeechs[0]))
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_PARTOFSPEECH))->AddString(partOfSpeechs[index]);
		index++;
	}
	//1.3 리스트뷰컨트롤의 헤더항목을 만든다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(0, "번호", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(1, "철자", LVCFMT_LEFT, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(2, "품사", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(3, "의미", LVCFMT_LEFT, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(4, "예시", LVCFMT_LEFT, 400);
	//1.4 리스트뷰컨트롤의 어떤 부분을 클릭해도 선택되도록 하기 위한 조치
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.5 데이터베이스에 있는 데이터들을 단어장에 적재한다.
	this->Load();
	//1.6 단어장에 적재된 개수만큼 리스트뷰컨트롤에 항목들을 추가한다.
	Word word;
	CString number;
	Long i = 0;
	while (i < this->wordBook->GetLength())
	{
		word = this->wordBook->GetAt(i);
		number.Format("%d", i + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(i, number);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 1, word.GetSpellings().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 2, word.GetPartOfSpeech().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 3, word.GetMeanings().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 4, word.GetExample().c_str());
		//예시가 너무 길 경우 스크롤바를 통해서도 리스트뷰컨트롤에 ...으로 표현되기때문에
		//다음 코드를 통해서 예시 column의 크기를 자동으로 예시의 길이에 맞게 크게 해준다.
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetColumnWidth(4, LVSCW_AUTOSIZE);
		i++;
	}
	//1.7 끝내다.
	return FALSE;
}

//2. 기재하기 버튼을 클릭했을 때
void WordBookForm::OnRecordButtonClicked()
{
	//2.1 철자, 품사, 의미, 예시를 입력받는다.
	CString spellings;
	GetDlgItem(IDC_EDIT_SPELLINGS)->GetWindowText(spellings);
	CString partOfSpeech;
	GetDlgItem(IDC_COMBO_PARTOFSPEECH)->GetWindowText(partOfSpeech);
	CString meanings;
	GetDlgItem(IDC_EDIT_MEANINGS)->GetWindowText(meanings);
	CString example;
	GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);
	//2.2 단어장에서 기재한다.
	Long index;
	index = this->wordBook->Record((LPCTSTR)spellings, (LPCTSTR)partOfSpeech, (LPCTSTR)meanings,
		(LPCTSTR)example);
	//2.3 데이터베이스에 저장한다.
	this->Insert(index);
	//2.4 리스트뷰컨트롤에 항목을 추가한다.
	Word word;
	word = this->wordBook->GetAt(index);
	//2.4.1 리스트뷰컨트롤에 번호를 추가한다.
	CString number;
	number.Format("%d", index + 1);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(index, number);
	//2.4.2 리스트뷰컨트롤에 철자, 품사, 의미, 예시를 추가한다.
	spellings = CString(word.GetSpellings().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 1, spellings);
	partOfSpeech = CString(word.GetPartOfSpeech().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 2, partOfSpeech);
	meanings = CString(word.GetMeanings().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 3, meanings);
	example = CString(word.GetExample().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, example);
	//예시가 너무 길 경우 스크롤바를 통해서도 리스트뷰컨트롤에 ...으로 표현되기때문에
	//다음 코드를 통해서 예시 column의 크기를 자동으로 예시의 길이에 맞게 크게 해준다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetColumnWidth(4, LVSCW_AUTOSIZE);
}

//3.찾기버튼을 클릭했을 때
void WordBookForm::OnFindButtonClicked()
{
	FindingForm findingForm(this);//객체생성, 내용O, 주소X
	//3.1 찾기 츠레임 윈도우를 띄운다.
	findingForm.DoModal();
}


//4. 고치기버튼을 클릭했을 때
void WordBookForm::OnCorrectButtonClicked()
{
	//4.1 리스트뷰컨트롤에서 선택된 항목의 위치를 읽는다.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//4.2 예시를 읽는다.
	CString example;
	GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);
	//4.3 단어장에서 고친다.
	index = this->wordBook->Correct(index, (LPCTSTR)example);
	//4.4 데이터베이스에서 고친다.
	this->Update(index);
	//4.4 리스트뷰 컨트롤에서 항목을 고친다.
	Word word;
	word = this->wordBook->GetAt(index);
	example = CString(word.GetExample().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, example);
}

//5. 지우기버튼을 클릭했을 때
void WordBookForm::OnEraseButtonClicked()
{
	//5.1 리스트뷰컨트롤에서 선택된 항목의 위치를 읽는다.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//5.2 단어장에서 지운다.
	this->wordBook->Erase(index);
	//5.3 데이터베이스에서 지운다.
	this->Delete(index);
	//5.4 리스트뷰에 있는 항목을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteItem(index);
	//5.5 리스트뷰컨트롤에서 번호를 다시매긴다.
	CString number;
	while (index < this->wordBook->GetLength())
	{
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 0, number);
		index++;
	}
}

//6. 정리하기 버튼을 클릭했을 떄
void WordBookForm::OnArrangeButtonClicked()
{
	//6.1 단어장에서 정렬한다.
	this->wordBook->Arrange();
	//6.2 데이터베이스에서 정렬한다.
	this->Replace();
	//6.3 리스트뷰 컨트롤에 있는 모든 항목들을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteAllItems();
	//6.4 리스트뷰 컨트롤에 단어장의 내용을 추가한다.
	Word word;
	CString number;
	CString spellings;
	CString partOfSpeech;
	CString meanings;
	CString example;
	Long index = 0;
	while (index < this->wordBook->GetLength())
	{
		Word word;
		word = this->wordBook->GetAt(index);
		//6.4.1 리스트뷰컨트롤에 번호를 추가한다.
		CString number;
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(index, number);
		//6.4.2 리스트뷰컨트롤에 철자, 품사, 의미, 예시를 추가한다.
		spellings = CString(word.GetSpellings().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 1, spellings);
		partOfSpeech = CString(word.GetPartOfSpeech().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 2, partOfSpeech);
		meanings = CString(word.GetMeanings().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 3, meanings);
		example = CString(word.GetExample().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, example);
		index++;
	}
}

//7. 리스트뷰 컨트롤의 항목을 더블클릭했을 때
void WordBookForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//7.1 리스트뷰 컨트롤의 선택된 항목의 위치를 읽는다.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//7.2 리스트뷰 컨트롤에서 선택된 항목의 철자, 품사, 의미, 예시를 읽는다.
	CString spellings;
	spellings = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 1);
	CString partOfSpeech;
	partOfSpeech = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 2);
	CString meanings;
	meanings = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 3);
	CString example;
	example = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 4);
	//7.3 리스트뷰 컨트롤에서 읽은 철자, 품사, 의미, 예시를 출력한다.
	GetDlgItem(IDC_EDIT_SPELLINGS)->SetWindowText(spellings);
	GetDlgItem(IDC_COMBO_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	GetDlgItem(IDC_EDIT_MEANINGS)->SetWindowText(meanings);
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}

//8.닫기 버튼을 클릭했을 때
void WordBookForm::OnClose()
{
	//8.1 단어장이 있으면
	if (this->wordBook != NULL)
	{
		//8.1.1 단어장의 내용을 데이터베이스에 저장한다.
		this->Save();
		//8.1.2 단어장을 지운다.
		delete this->wordBook;
	}
	//8.2 윈도우를 닫는다.
	EndDialog(0);
}

