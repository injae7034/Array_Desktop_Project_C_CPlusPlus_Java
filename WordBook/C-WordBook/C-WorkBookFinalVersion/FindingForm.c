#include "FindingForm.h"
#include "WordBook.h"
#include "resource.h"
#include<CommCtrl.h>
#include<stdio.h>
#pragma warning(disable:4996)

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG: ret = FindingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = FindingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY: ret = FindingForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = FindingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//OnInitDialog
BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//1. ã�� ������ �����찡 ������ ��
	LVCOLUMN column = { 0, };
	//1.1 ����Ʈ�� ��Ʈ���� ����� �����.
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

	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
		(LPARAM)LVS_EX_FULLROWSELECT);

	return TRUE;
}

//OnCommand
BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_FIND: ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_RADIO_SPELLINGS: ret=FindingForm_OnRadioButtonSpellingsClicked(hWnd, wParam, lParam); break;
	case IDC_RADIO_MEANINGS: ret=FindingForm_OnRadioButtonMeainingsClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//OnNotify
BOOL FindingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (wParam)
	{
	case IDC_LIST_WORDS: ret = FindingForm_OnListViewDoubleClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//Onclose
BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//4. �ݱ� ��ư�� Ŭ������ ��
	Long(*indexes);

	indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
	if (indexes != NULL)
	{
		free(indexes);
	}
	//4.1 �����츦 �ݴ�.
	EndDialog(hWnd, 0);

	return TRUE;
}

//OnFindButtonClicked
BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordBook* wordBook;
	LVITEM item = { 0, };
	TCHAR spellings[64];
	TCHAR meanings[32];
	Long(*indexes)=NULL;
	Long count;
	Long index;
	TCHAR number[64];
	HWND wordBookForm;
	int spellingsChecked;
	int meaningsChecked;
	Word word;
	

	//2. ã�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 �ܾ��忡�� ������ �����츦 ã�´�.
		wordBookForm = FindWindow("#32770", "�ܾ���");
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL)
		{
			free(indexes);
		}
		wordBook = (WordBook*)GetWindowLong(wordBookForm, GWL_USERDATA);
		spellingsChecked = (int)SendMessage(GetDlgItem(hWnd, IDC_RADIO_SPELLINGS), BM_GETCHECK, 0, 0);
		meaningsChecked=(int)SendMessage(GetDlgItem(hWnd, IDC_RADIO_MEANINGS), BM_GETCHECK, 0, 0);
		//2.2 ö�� ���� ��ư�� ���õǾ� ������
		if (spellingsChecked == BST_CHECKED)
		{
			//2.2.1 ö�ڸ� �Է¹޴´�.
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLINGS), WM_GETTEXT, (WPARAM)64, (LPARAM)spellings);
			//2.2.2 �ܾ��� ������ �������� �ܾ��忡�� ã�´�.(FindBySpellings)
			FindBySpellings(wordBook, spellings, &indexes, &count);
		}
		//2.3 �ǹ� ���� ��ư�� ���õǾ� ������
		if (meaningsChecked == BST_CHECKED)
		{
			//2.3.1 �ǹ̸� �Է¹޴´�.
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANINGS), WM_GETTEXT, (WPARAM)32, (LPARAM)meanings);
			//2.3.2 �ܾ��� ������ �������� �ܾ��忡�� ã�´�.(FindByMeanings)
			FindByMeanings(wordBook, meanings, &indexes, &count);
		}
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)indexes);
		//2.4 ����Ʈ�� ��Ʈ�ѿ� �ִ� ��� �׸���� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEALLITEMS, 0, 0);
		//2.5 ����Ʈ�� ��Ʈ�ѿ� ã�� ������ŭ �׸���� �߰��Ѵ�.
		item.mask = LVIF_TEXT;
		index = 0;
		while (index < count)
		{
			item.iItem = index;
			word = WordBook_GetAt(wordBook, indexes[index]);
			item.iSubItem = 0;
			sprintf(number, "%d", index + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, 0, (LPARAM)&item);
			item.iSubItem = 1;
			item.pszText = word.spellings;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 2;
			item.pszText = word.partOfSpeech;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 3;
			item.pszText = word.meanings;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 4;
			item.pszText = word.example;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			index++;
		}
	}
	return TRUE;
}

//OnRadioButtonSpellingsClicked
BOOL FindingForm_OnRadioButtonSpellingsClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	
	if (HIWORD(wParam) == BN_CLICKED)
	{
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANINGS), WM_SETTEXT, 0, (LPARAM)"");
	}
	return TRUE;
}

//OnRadioButtonMeainingsClicked
BOOL FindingForm_OnRadioButtonMeainingsClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	
	if (HIWORD(wParam) == BN_CLICKED)
	{
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLINGS), WM_SETTEXT, 0, (LPARAM)"");
	}
	return TRUE;
}

//OnListViewDoubleClicked
BOOL FindingForm_OnListViewDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordBook* wordBook;
	LVITEM item = { 0, };
	TCHAR spellings[64];
	TCHAR partOfSpeech[8];
	TCHAR meanings[32];
	TCHAR example[128];
	Long index;
	Long(*indexes);
	HWND wordBookForm;

	//3. ����Ʈ�� ��Ʈ�ѿ� �ִ� �׸��� ����Ŭ������ ��
	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		//3.1 ����Ʈ�� ��Ʈ�ѿ��� ������ ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, 0, 0);
		//3.2 ������ �׸��� ö��, ǰ��, �ǹ�, ���ø� �д´�.
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
		//3.3 �ܾ��� ������ �����츦  ã�´�.
		wordBookForm = FindWindow("#32770", "�ܾ���");
		//3.4 �ܾ��� ������ �������� �ܾ ������ ö��, ǰ��, �ǹ�, ���ø� ����Ѵ�.
		SendMessage(GetDlgItem(wordBookForm, IDC_EDIT_SPELLINGS), WM_SETTEXT, 0, (LPARAM)spellings);
		SendMessage(GetDlgItem(wordBookForm, IDC_COMBO_PARTOFSPEECH), WM_SETTEXT, 0, (LPARAM)partOfSpeech);
		SendMessage(GetDlgItem(wordBookForm, IDC_EDIT_MEANINGS), WM_SETTEXT, 0, (LPARAM)meanings);
		SendMessage(GetDlgItem(wordBookForm, IDC_EDIT_EXAMPLE), WM_SETTEXT, 0, (LPARAM)example);
		//3.5 �ܾ��� ������ �������� ����Ʈ�� ��Ʈ�ѿ��� �׸���  �����Ѵ�.
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		SendMessage(GetDlgItem(wordBookForm, IDC_LIST_WORDS), LVM_SETSELECTIONMARK, 0, (LPARAM)indexes[index]);
		//3.6 �����츦 �ݴ´�.
		if (indexes != NULL)
		{
			free(indexes);
		}
		EndDialog(hWnd, 0);
	}
	return TRUE;
}
