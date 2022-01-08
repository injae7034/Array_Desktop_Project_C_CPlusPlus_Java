#include"WordBookForm.h"
#include"WordBook.h"
#include"FindingForm.h"
#include"resource.h"
#include<afxwin.h>//CDialog �������
#include<afxcmn.h>//CListCtrl�������
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
	this->wordBook = NULL;//NULL�� �ʱ�ȭ��Ŵ
}

//�����ͺ��̽��������α׷��� ����

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
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//�����ͺ��̽��� �ִ� ���� �����͵��� ����� ���� code���� Recordset�� ������.
	CString sql2 = "DELETE FROM Word;";//�����ͺ��̽��� ���ο� �����͵��� �����ϱ� ���� ������ �����͵��� ��� ����.
	db.ExecuteSQL(sql2);//�����ͺ��̽����� ������ �����͵��� ����� ����� ������.

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
	if (!rs.IsEOF())//�����ͺ��̽��� ����� �����Ͱ� ������
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
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//�����ͺ��̽��� �ִ� ���� �����͵��� ����� ���� code���� Recordset�� ������.
	CString sql2 = "DELETE FROM Word;";//�����ͺ��̽��� ���ο� �����͵��� �����ϱ� ���� ������ �����͵��� ��� ����.
	db.ExecuteSQL(sql2);//�����ͺ��̽����� ������ �����͵��� ����� ����� ������.

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

//�����ͺ��̽� �������α׷��� ��


//1.�����찡 ������ ��
BOOL WordBookForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	TCHAR partOfSpeechs[][8] = {
		"���",
		"����",
		"����",
		"�����",
		"�λ�",
		"��ġ��",
		"���ӻ�",
		"��ź��"
	};
	//1.1 �ܾ����� �����.
	this->wordBook = new WordBook;
	//1.2 �޺��ڽ��� �׸���� �߰��Ѵ�.
	Long index = 0;
	while (index < sizeof(partOfSpeechs) / sizeof(partOfSpeechs[0]))
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_PARTOFSPEECH))->AddString(partOfSpeechs[index]);
		index++;
	}
	//1.3 ����Ʈ����Ʈ���� ����׸��� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(0, "��ȣ", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(1, "ö��", LVCFMT_LEFT, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(2, "ǰ��", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(3, "�ǹ�", LVCFMT_LEFT, 150);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertColumn(4, "����", LVCFMT_LEFT, 400);
	//1.4 ����Ʈ����Ʈ���� � �κ��� Ŭ���ص� ���õǵ��� �ϱ� ���� ��ġ
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//1.5 �����ͺ��̽��� �ִ� �����͵��� �ܾ��忡 �����Ѵ�.
	this->Load();
	//1.6 �ܾ��忡 ����� ������ŭ ����Ʈ����Ʈ�ѿ� �׸���� �߰��Ѵ�.
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
		//���ð� �ʹ� �� ��� ��ũ�ѹٸ� ���ؼ��� ����Ʈ����Ʈ�ѿ� ...���� ǥ���Ǳ⶧����
		//���� �ڵ带 ���ؼ� ���� column�� ũ�⸦ �ڵ����� ������ ���̿� �°� ũ�� ���ش�.
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetColumnWidth(4, LVSCW_AUTOSIZE);
		i++;
	}
	//1.7 ������.
	return FALSE;
}

//2. �����ϱ� ��ư�� Ŭ������ ��
void WordBookForm::OnRecordButtonClicked()
{
	//2.1 ö��, ǰ��, �ǹ�, ���ø� �Է¹޴´�.
	CString spellings;
	GetDlgItem(IDC_EDIT_SPELLINGS)->GetWindowText(spellings);
	CString partOfSpeech;
	GetDlgItem(IDC_COMBO_PARTOFSPEECH)->GetWindowText(partOfSpeech);
	CString meanings;
	GetDlgItem(IDC_EDIT_MEANINGS)->GetWindowText(meanings);
	CString example;
	GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);
	//2.2 �ܾ��忡�� �����Ѵ�.
	Long index;
	index = this->wordBook->Record((LPCTSTR)spellings, (LPCTSTR)partOfSpeech, (LPCTSTR)meanings,
		(LPCTSTR)example);
	//2.3 �����ͺ��̽��� �����Ѵ�.
	this->Insert(index);
	//2.4 ����Ʈ����Ʈ�ѿ� �׸��� �߰��Ѵ�.
	Word word;
	word = this->wordBook->GetAt(index);
	//2.4.1 ����Ʈ����Ʈ�ѿ� ��ȣ�� �߰��Ѵ�.
	CString number;
	number.Format("%d", index + 1);
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(index, number);
	//2.4.2 ����Ʈ����Ʈ�ѿ� ö��, ǰ��, �ǹ�, ���ø� �߰��Ѵ�.
	spellings = CString(word.GetSpellings().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 1, spellings);
	partOfSpeech = CString(word.GetPartOfSpeech().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 2, partOfSpeech);
	meanings = CString(word.GetMeanings().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 3, meanings);
	example = CString(word.GetExample().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, example);
	//���ð� �ʹ� �� ��� ��ũ�ѹٸ� ���ؼ��� ����Ʈ����Ʈ�ѿ� ...���� ǥ���Ǳ⶧����
	//���� �ڵ带 ���ؼ� ���� column�� ũ�⸦ �ڵ����� ������ ���̿� �°� ũ�� ���ش�.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetColumnWidth(4, LVSCW_AUTOSIZE);
}

//3.ã���ư�� Ŭ������ ��
void WordBookForm::OnFindButtonClicked()
{
	FindingForm findingForm(this);//��ü����, ����O, �ּ�X
	//3.1 ã�� ������ �����츦 ����.
	findingForm.DoModal();
}


//4. ��ġ���ư�� Ŭ������ ��
void WordBookForm::OnCorrectButtonClicked()
{
	//4.1 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//4.2 ���ø� �д´�.
	CString example;
	GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);
	//4.3 �ܾ��忡�� ��ģ��.
	index = this->wordBook->Correct(index, (LPCTSTR)example);
	//4.4 �����ͺ��̽����� ��ģ��.
	this->Update(index);
	//4.4 ����Ʈ�� ��Ʈ�ѿ��� �׸��� ��ģ��.
	Word word;
	word = this->wordBook->GetAt(index);
	example = CString(word.GetExample().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, example);
}

//5. ������ư�� Ŭ������ ��
void WordBookForm::OnEraseButtonClicked()
{
	//5.1 ����Ʈ����Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//5.2 �ܾ��忡�� �����.
	this->wordBook->Erase(index);
	//5.3 �����ͺ��̽����� �����.
	this->Delete(index);
	//5.4 ����Ʈ�信 �ִ� �׸��� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteItem(index);
	//5.5 ����Ʈ����Ʈ�ѿ��� ��ȣ�� �ٽøű��.
	CString number;
	while (index < this->wordBook->GetLength())
	{
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 0, number);
		index++;
	}
}

//6. �����ϱ� ��ư�� Ŭ������ ��
void WordBookForm::OnArrangeButtonClicked()
{
	//6.1 �ܾ��忡�� �����Ѵ�.
	this->wordBook->Arrange();
	//6.2 �����ͺ��̽����� �����Ѵ�.
	this->Replace();
	//6.3 ����Ʈ�� ��Ʈ�ѿ� �ִ� ��� �׸���� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->DeleteAllItems();
	//6.4 ����Ʈ�� ��Ʈ�ѿ� �ܾ����� ������ �߰��Ѵ�.
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
		//6.4.1 ����Ʈ����Ʈ�ѿ� ��ȣ�� �߰��Ѵ�.
		CString number;
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->InsertItem(index, number);
		//6.4.2 ����Ʈ����Ʈ�ѿ� ö��, ǰ��, �ǹ�, ���ø� �߰��Ѵ�.
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

//7. ����Ʈ�� ��Ʈ���� �׸��� ����Ŭ������ ��
void WordBookForm::OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//7.1 ����Ʈ�� ��Ʈ���� ���õ� �׸��� ��ġ�� �д´�.
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	//7.2 ����Ʈ�� ��Ʈ�ѿ��� ���õ� �׸��� ö��, ǰ��, �ǹ�, ���ø� �д´�.
	CString spellings;
	spellings = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 1);
	CString partOfSpeech;
	partOfSpeech = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 2);
	CString meanings;
	meanings = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 3);
	CString example;
	example = ((CListCtrl*)GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 4);
	//7.3 ����Ʈ�� ��Ʈ�ѿ��� ���� ö��, ǰ��, �ǹ�, ���ø� ����Ѵ�.
	GetDlgItem(IDC_EDIT_SPELLINGS)->SetWindowText(spellings);
	GetDlgItem(IDC_COMBO_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	GetDlgItem(IDC_EDIT_MEANINGS)->SetWindowText(meanings);
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}

//8.�ݱ� ��ư�� Ŭ������ ��
void WordBookForm::OnClose()
{
	//8.1 �ܾ����� ������
	if (this->wordBook != NULL)
	{
		//8.1.1 �ܾ����� ������ �����ͺ��̽��� �����Ѵ�.
		this->Save();
		//8.1.2 �ܾ����� �����.
		delete this->wordBook;
	}
	//8.2 �����츦 �ݴ´�.
	EndDialog(0);
}

