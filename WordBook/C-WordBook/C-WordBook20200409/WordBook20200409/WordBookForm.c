#include "WordBookForm.h"
#include "WordBook.h"
#include "resource.h"
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
	case WM_INITDIALOG: ret = WordBookForm_OnInitDialog(hWnd, wParam, lParam);
	case WM_CLOSE: ret = WordBookForm_OnClose(hWnd, wParam, lParam);
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
	column.cx = 200;
	column.pszText = "철자";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);
	column.cx = 50;
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
