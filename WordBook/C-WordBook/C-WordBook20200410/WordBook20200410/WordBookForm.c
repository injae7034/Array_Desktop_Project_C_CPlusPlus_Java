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
	//1. �����찡 ������ ��
	WordBook* wordBook;
	LVCOLUMN column = { 0, };
	LVITEM item = { 0, };
	TCHAR number[64];
	Long index;
	Long count;
	TCHAR partOfSpeechs[ ][8] = {
		"���",
		"����",
		"����",
		"�����",
		"�λ�",
		"��ġ��",
		"���ӻ�",
		"��ź��"
	};

	//1.1 �ܾ����� �����.(Create)
	wordBook = (WordBook*)malloc(sizeof(WordBook));
	Create(wordBook, 10000);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)wordBook);
	//1.2 �ܾ��忡�� �����Ѵ�.(Load)
	count = Load(wordBook);
	//1.3 �޺��ڽ����� �׸���� �߰��Ѵ�.
	index = 0;
	while (index < sizeof(partOfSpeechs) / sizeof(partOfSpeechs[0]))
	{
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PARTOFSPEECH), CB_ADDSTRING, 0, (LPARAM)partOfSpeechs[index]);
		index++;
	}
	//1.4 ����Ʈ�� ��Ʈ���� ����� �����.
	column.mask = LVCF_WIDTH | LVCF_TEXT;
	column.cx = 50;
	column.pszText = "��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);
	column.cx = 150;
	column.pszText = "ö��";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "ǰ��";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);
	column.cx = 150;
	column.pszText = "�ǹ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);
	column.cx = 400;
	column.pszText = "����";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);

	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)LVS_EX_FULLROWSELECT);

	//1.5 ����� ������ŭ ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
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
	//8. �ݱ� ��ư�� Ŭ������ ��
	WordBook* wordBook;

	wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
	if (wordBook != NULL)
	{
		//8.1 �ܾ��忡�� �����Ѵ�.(Save)
		Save(wordBook);
		//8.2 �ܾ����� �����.(Destroy)
		Destroy(wordBook);
		free(wordBook);
	}
	//8.3 �����츦 �ݴ´�.
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

	//2. �����ϱ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 ö��, ǰ��, �ǹ�, ���ø� �Է¹޴´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLINGS), WM_GETTEXT, (WPARAM)64, (LPARAM)spellings);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PARTOFSPEECH), WM_GETTEXT, (WPARAM)8, (LPARAM)partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANINGS), WM_GETTEXT, (WPARAM)32, (LPARAM)meanings);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)example);
		//2.2 �ܾ��忡�� �����Ѵ�.(Record)
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Record(wordBook, spellings, partOfSpeech, meanings, example);
		//2.3 ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�,
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

	//4. ��ġ�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//4.1 ����Ʈ�� ��Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, 0, 0);
		//4.2 ���ø� �Է¹޴´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)example);
		//4.3 �ܾ��忡�� ��ģ��.(Correct)
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Correct(wordBook, index, example);
		//4.4 ����Ʈ�� ��Ʈ�ѿ��� �׸��� ��ģ��.
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

	//5. ����� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//5.1 ����Ʈ�� ��Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, 0, 0);
		//5.2 �ܾ��忡�� �����.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Erase(wordBook, index);
		//5.3 ����Ʈ�� ��Ʈ�ѿ� �ִ� �׸��� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEITEM, (WPARAM)index, 0);
		//5.4 ����Ʈ�� ��Ʈ�ѿ��� ��ġ�� ��ȣ�� �ٽ� �ű��.
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

	//6. �����ϱ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//6.1 �ܾ��忡�� �����Ѵ�.(Arrange)
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Arrange(wordBook);
		//6.2 ����Ʈ�� ��Ʈ�ѿ� �ִ� ��� �׸���� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEALLITEMS, 0, 0);
		//6.3 ����Ʈ�� ��Ʈ�ѿ� �ܾ��忡 ����� �׸���� �߰��Ѵ�.
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

	//7. ����Ʈ�� ��Ʈ�ѿ��� �׸��� ����Ŭ������ ��
	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		//7.1 ����Ʈ�� ��Ʈ�ѿ��� ������ ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, 0, 0);
		//7.2 ������ �׸��� ö��, ǰ��, �ǹ�, ���ø� �д´�.
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
		//7.3 ����Ʈ�� ��Ʈ�ѿ��� ���� ö��, ǰ��, �ǹ�, ���ø� �ܾ ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLINGS), WM_SETTEXT, 0, (LPARAM)spellings);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PARTOFSPEECH), WM_SETTEXT, 0, (LPARAM)partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANINGS), WM_SETTEXT, 0, (LPARAM)meanings);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_SETTEXT, 0, (LPARAM)example);
	}
	return TRUE;
}
