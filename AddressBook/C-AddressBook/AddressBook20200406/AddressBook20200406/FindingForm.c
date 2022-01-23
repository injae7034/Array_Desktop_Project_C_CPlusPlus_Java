#include "AddressBook.h"
#include "FindingForm.h"
#include "resource.h"
#include <commctrl.h>
#include <stdio.h>
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
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "����";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);
	column.cx = 300;
	column.pszText = "�ּ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);
	column.cx = 200;
	column.pszText = "��ȭ��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);
	column.cx = 300;
	column.pszText = "�̸����ּ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);

	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
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
	case IDC_LIST_PERSONALS: ret = FindingForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//OnFindButtonClicked
BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook* addressBook;
	LVITEM item = { 0, };
	TCHAR name[11];
	TCHAR number[64];
	Long(*indexes)=NULL;
	Long count;
	Long index;
	HWND addressBookForm;

	//2. ã�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 ������ �Է¹޴´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)name);
		//2.2 �ּҷ� ������ �����츦 ã�´�.
		addressBookForm = FindWindow("#32770", "�ּҷ�");
		//2.3 �ּҷ� ������ �������� �ּҷϿ��� ã�´�.(Find)
		//ã�� �����츦 �������� �ʰ� ã�� ��ư�� �����ؼ� ���� �� �߻��ϴ� �޸� ������ ���� ���� �Ҵ�����
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL)
		{
			free(indexes);
		}
		addressBook = (AddressBook*)GetWindowLong(addressBookForm, GWL_USERDATA);
		Find(addressBook, name, &indexes, &count);
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)indexes);
		//2.4 ����Ʈ�� ��Ʈ�ѿ� �ִ� ��� �׸���� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEALLITEMS, 0, 0);
		//2.5 ����Ʈ�� ��Ʈ�ѿ� ã�� ������ŭ �׸���� �߰��Ѵ�.
		item.mask = LVIF_TEXT;
		index = 0;
		while (index < count)
		{
			item.iItem = index;
			item.iSubItem = 0;
			sprintf(number, "%d", index + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, 0, (LPARAM)&item);
			item.iSubItem = 1;
			item.pszText = addressBook->personals[indexes[index]].name;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 2;
			item.pszText = addressBook->personals[indexes[index]].address;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 3;
			item.pszText = addressBook->personals[indexes[index]].telephoneNumber;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 4;
			item.pszText = addressBook->personals[indexes[index]].emailAddress;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			index++;
		}
	}
	return TRUE;
}

//OnListViewItemDoubleClicked
BOOL FindingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook* addressBook;
	LVITEM item = { 0, };
	TCHAR name[11];
	TCHAR address[64];
	TCHAR telephoneNumber[12];
	TCHAR emailAddress[32];
	Long index;
	HWND addressBookForm;
	Long(*indexes);

	//3. ����Ʈ�� ��Ʈ�ѿ� �ִ� �׸��� ���� Ŭ������ ��
	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		//3.1 ����Ʈ�� ��Ʈ�ѿ��� ������ ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, 0, 0);
		//3.2 ������ �׸��� ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �д´�.
		item.iItem = index;
		item.iSubItem = 1;
		item.pszText = name;
		item.cchTextMax = 11;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2;
		item.pszText = address;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = telephoneNumber;
		item.cchTextMax = 12;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = emailAddress;
		item.cchTextMax = 32;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		//3.3 �ּҷ� ������ �����츦 ã�´�.
		addressBookForm = FindWindow("#32770", "�ּҷ�");
		//3.4 �ּҷ� ������ �������� ���ο� ������ ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� ����Ѵ�.
		SendMessage(GetDlgItem(addressBookForm, IDC_EDIT_NAME), WM_SETTEXT, 0, (LPARAM)name);
		SendMessage(GetDlgItem(addressBookForm, IDC_EDIT_ADDRESS), WM_SETTEXT, 0, (LPARAM)address);
		SendMessage(GetDlgItem(addressBookForm, IDC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(addressBookForm, IDC_EDIT_EMAILADDRESS), WM_SETTEXT, 0, (LPARAM)emailAddress);
		//3.5 �ּҷ� ������ �������� ����Ʈ�� ��Ʈ�ѿ��� �׸��� �����Ѵ�.
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		SendMessage(GetDlgItem(addressBookForm, IDC_LIST_PERSONALS), LVM_SETSELECTIONMARK, 0, (LPARAM)indexes[index]);
		//3.6 �����츦 �ݴ´�.
		if (indexes != NULL)
		{
			free(indexes);
		}
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

//OnClose
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