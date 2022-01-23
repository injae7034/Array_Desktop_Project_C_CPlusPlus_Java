#include "WordBookForm.h"
#include "WordBook.h"
#include "resource.h"
#include "FindingForm.h"
#include<CommCtrl.h>
#include<stdio.h>
#pragma warning(disable:4996)

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmelLine, int nShowCmd)
{
	int response;
	
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_WORDBOOKFORM), NULL, WordBookFormProc);

	return response;
}

//WordBookFormProc
BOOL CALLBACK WordBookFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;

	switch (message)
	{
	case WM_INITDIALOG: ret = WordBookForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = WordBookForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY: ret = WordBookForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = WordBookForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

// WordBookForm_OnInitDialog
BOOL WordBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//1. 윈도우가 생성될 때
	WordBook* wordBook;
	LVCOLUMN column = { 0, };
	LVITEM item = { 0, };
	TCHAR number[64];
	Long index;
	Long count;
	TCHAR partOfSpeechs[ ][8] = {
		"명사",
		"대명사",
		"동사",
		"형용사",
		"부사",
		"전치사",
		"접속사",
		"감탄사"
	};

	//1.1 단어장을 만든다.(Create)
	wordBook = (WordBook*)malloc(sizeof(WordBook));
	Create(wordBook, 10000);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)wordBook);
	//1.2 단어장에서 적재한다.(Load)
	count = Load(wordBook);
	//1.3 콤보박스에서 항목들을 추가한다.
	index = 0;
	while (index < sizeof(partOfSpeechs) / sizeof(partOfSpeechs[0]))
	{
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PARTOFSPEECH), CB_ADDSTRING, 0, (LPARAM)partOfSpeechs[index]);
		index++;
	}
	//1.4 리스트뷰 컨트롤의 헤더를 만든다.
	column.mask = LVCF_WIDTH | LVCF_TEXT;
	column.cx = 50;
	column.pszText = "번호";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);
	column.cx = 150;
	column.pszText = "철자";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "품사";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);
	column.cx = 150;
	column.pszText = "의미";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);
	column.cx = 400;
	column.pszText = "예시";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);

	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)LVS_EX_FULLROWSELECT);

	//1.5 적재된 개수만큼 리스트뷰 컨트롤에 항목을 추가한다.
	item.mask = LVIF_TEXT;
	index = 0;
	while (index < count)
	{
		item.iItem = index;
		item.iSubItem = 0;
		sprintf(number, "%d", index + 1);
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, 0, (LPARAM)&item);
		item.iSubItem = 1;
		item.pszText = wordBook->words[index].spellings;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2;
		item.pszText = wordBook->words[index].partOfSpeech;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = wordBook->words[index].meanings;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = wordBook->words[index].example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		index++;
	}
	return TRUE;
}

//OnCommand
BOOL WordBookForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_RECORD: ret = WordBookForm_OnRecordButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIND: ret = WordBookForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_CORRECT: ret = WordBookForm_OnCorrectButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ERASE: ret = WordBookForm_OnEraseButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ARRANGE: ret = WordBookForm_OnArrangeButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//OnNotify
BOOL WordBookForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (wParam)
	{
	case IDC_LIST_WORDS: ret = WordBookForm_OnListViewDoubleClicked(hWnd, wParam, lParam); break;
	default: FALSE; break;
	}
	return ret;
}

//OnClose
BOOL WordBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//8. 닫기 버튼을 클릭했을 때
	WordBook* wordBook;

	wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
	if (wordBook != NULL)
	{
		//8.1 단어장에서 저장한다.(Save)
		Save(wordBook);
		//8.2 단어장을 지운다.(Destroy)
		Destroy(wordBook);
		free(wordBook);
	}
	//8.3 윈도우를 닫는다.
	EndDialog(hWnd, 0);
	return TRUE;
}

//OnRecordButtonClicked
BOOL WordBookForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordBook* wordBook;
	LVITEM item = { 0, };
	TCHAR number[64];
	TCHAR spellings[64];
	TCHAR partOfSpeech[8];
	TCHAR meanings[32];
	TCHAR example[128];
	Long index;

	//2. 기재하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 철자, 품사, 의미, 예시를 입력받는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLINGS), WM_GETTEXT, (WPARAM)64, (LPARAM)spellings);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PARTOFSPEECH), WM_GETTEXT, (WPARAM)8, (LPARAM)partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANINGS), WM_GETTEXT, (WPARAM)32, (LPARAM)meanings);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)example);
		//2.2 단어장에서 기재한다.(Record)
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Record(wordBook, spellings, partOfSpeech, meanings, example);
		//2.3 리스트뷰 컨트롤에 항목을 추가한다,
		item.mask = LVIF_TEXT;
		item.iItem = index;
		item.iSubItem = 0;
		sprintf(number, "%d", index + 1);
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, 0, (LPARAM)&item);
		item.iSubItem = 1;
		item.pszText = wordBook->words[index].spellings;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2;
		item.pszText = wordBook->words[index].partOfSpeech;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = wordBook->words[index].meanings;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = wordBook->words[index].example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}

//OnFindButtonClicked
BOOL WordBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL,
			FindingFormProc);
	}
	return TRUE;
}

//OnCorrectButtonClicked
BOOL WordBookForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordBook* wordBook;
	LVITEM item = { 0, };
	TCHAR example[128];
	Long index;

	//4. 고치기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//4.1 리스트뷰 컨트롤에서 선택된 항목의 위치를 읽는다.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, 0, 0);
		//4.2 예시를 입력받는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)example);
		//4.3 단어장에서 고친다.(Correct)
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Correct(wordBook, index, example);
		//4.4 리스트뷰 컨트롤에서 항목을 고친다.
		item.mask = LVIF_TEXT;
		item.iItem = index;
		item.iSubItem = 4;
		item.pszText = wordBook->words[index].example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}

//OnEraseButtonClicked
BOOL WordBookForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordBook* wordBook;
	LVITEM item = { 0, };
	TCHAR number[64];
	Long index;

	//5. 지우기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//5.1 리스트뷰 컨트롤에서 선택된 항목의 위치를 읽는다.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, 0, 0);
		//5.2 단어장에서 지운다.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Erase(wordBook, index);
		//5.3 리스트뷰 컨트롤에 있는 항목을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEITEM, (WPARAM)index, 0);
		//5.4 리스트뷰 컨트롤에서 위치의 번호를 다시 매긴다.
		item.mask = LVIF_TEXT;
		while (index < wordBook->length)
		{
			item.iItem = index;
			item.iSubItem = 0;
			sprintf(number, "%d", index + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			index++;
		}
	}
	return TRUE;
}

//OnArrangeButtonClicked
BOOL WordBookForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordBook* wordBook;
	LVITEM item = { 0, };
	TCHAR number[64];
	Long index;

	//6. 정리하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//6.1 단어장에서 정렬한다.(Arrange)
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Arrange(wordBook);
		//6.2 리스트뷰 컨트롤에 있는 모든 항목들을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEALLITEMS, 0, 0);
		//6.3 리스트뷰 컨트롤에 단어장에 기재된 항목들을 추가한다.
		item.mask = LVIF_TEXT;
		index = 0;
		while (index < wordBook->length)
		{
			item.iItem = index;
			item.iSubItem = 0;
			sprintf(number, "%d", index + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, 0, (LPARAM)&item);
			item.iSubItem = 1;
			item.pszText = wordBook->words[index].spellings;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 2;
			item.pszText = wordBook->words[index].partOfSpeech;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 3;
			item.pszText = wordBook->words[index].meanings;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 4;
			item.pszText = wordBook->words[index].example;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			index++;
		}
	}
	return TRUE;
}

//OnListViewDoubleClicked
BOOL WordBookForm_OnListViewDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordBook* wordBook;
	LVITEM item = { 0, };
	TCHAR spellings[64];
	TCHAR partOfSpeech[8];
	TCHAR meanings[32];
	TCHAR example[128];
	Long index;

	//7. 리스트뷰 컨트롤에서 항목을 더블클릭했을 때
	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		//7.1 리스트뷰 컨트롤에서 선택한 위치를 읽는다.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, 0, 0);
		//7.2 선택한 항목의 철자, 품사, 의미, 예시를 읽는다.
		item.iItem = index;
		item.iSubItem = 1;
		item.pszText = spellings;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2;
		item.pszText = partOfSpeech;
		item.cchTextMax = 8;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = meanings;
		item.cchTextMax = 32;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = example;
		item.cchTextMax = 128;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		//7.3 리스트뷰 컨트롤에서 읽은 철자, 품사, 의미, 예시를 단어에 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLINGS), WM_SETTEXT, 0, (LPARAM)spellings);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PARTOFSPEECH), WM_SETTEXT, 0, (LPARAM)partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANINGS), WM_SETTEXT, 0, (LPARAM)meanings);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_SETTEXT, 0, (LPARAM)example);
	}
	return TRUE;
}
