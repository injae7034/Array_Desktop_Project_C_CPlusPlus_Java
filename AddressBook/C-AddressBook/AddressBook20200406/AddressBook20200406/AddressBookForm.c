#include "AddressBookForm.h"
#include "AddressBook.h"
#include "FindingForm.h"
#include "resource.h"
#include <commctrl.h>
#include <stdio.h>
#pragma warning(disable:4996)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nShowCmd)
{
	int response;
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_ADDRESSBOOKFORM), NULL, AddressBookFormProc);

	return response;
}

BOOL CALLBACK AddressBookFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG: ret = AddressBookForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = AddressBookForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY: ret = AddressBookForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = AddressBookForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//OnInitDialog
BOOL AddressBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//1. �����찡 ������ ��
	AddressBook* addressBook;
	LVCOLUMN column = { 0, };
	LVITEM item = { 0, };
	TCHAR number[64];
	Long index;
	Long count;
	
	//1.1 �ּҷ��� �����.(Create)
	addressBook = (AddressBook*)malloc(sizeof(AddressBook));
	Create(addressBook, 10000);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)addressBook);
	//1.2 �ּҷϿ��� �����Ѵ�(Load)
	count = Load(addressBook);
	//1.3 ����Ʈ�� ������� ����� �����.(LVM_INSERTCOLUMN)
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

	// ����Ʈ�� ��Ʈ�ѿ��� ��ȣ���� ��� �׸��� �����ϴ��� ���� �� �ֵ��� �ϱ� ���� ��ġ
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)LVS_EX_FULLROWSELECT);

	//1.4  ����� ������ŭ ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.(LVM_INSERTITEM)(LVM_SETITEMTEXT)
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
		item.pszText = addressBook->personals[index].name;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2;
		item.pszText = addressBook->personals[index].address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = addressBook->personals[index].telephoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = addressBook->personals[index].emailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		index++;
	}
	return TRUE;
}

//OnCommand
BOOL AddressBookForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_RECORD: ret = AddressBookForm_OnRecordButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_CORRECT: ret = AddressBookForm_OnCorrectButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIND: ret = AddressBookForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ERASE: ret = AddressBookForm_OnEraseButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ARRANGE: ret = AddressBookForm_OnArrangeButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//OnNotify
BOOL AddressBookForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (wParam)
	{
	case IDC_LIST_PERSONALS: ret = AddressBookForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//OnRecordButtonClicked
BOOL AddressBookForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook* addressBook;
	LVITEM item = { 0, };
	TCHAR number[64];
	TCHAR name[11];
	TCHAR address[64];
	TCHAR telephoneNumber[12];
	TCHAR emailAddress[32];
	Long index;

	//2. �����ϱ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �Է¹޴´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_GETTEXT, (WPARAM)11, (LPARAM)emailAddress);
		//2.2 �ּҷϿ��� �����ϴ�.(Record)
		addressBook = (AddressBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Record(addressBook, name, address, telephoneNumber, emailAddress);
		//2.3 ����Ʈ�� ��Ʈ�ѿ� �׸���  �߰��Ѵ�.
		item.mask = LVIF_TEXT;
		item.iItem = index;
		item.iSubItem = 0;
		sprintf(number, "%d", index + 1);
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, 0, (LPARAM)&item);
		item.iSubItem = 1;
		item.pszText = addressBook->personals[index].name;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2;
		item.pszText = addressBook->personals[index].address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = addressBook->personals[index].telephoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = addressBook->personals[index].emailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}

//OnFindButtonClicked
BOOL AddressBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM),
			NULL, FindingFormProc);
	}
	return TRUE;
}

//OnCorrectButtonClicked
BOOL AddressBookForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook* addressBook;
	LVITEM item = { 0, };
	TCHAR address[64];
	TCHAR telephoneNumber[12];
	TCHAR emailAddress[32];
	Long index;

	//4. ��ġ���ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//4.1 ����Ʈ�� ��Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, 0, 0);
		//4.2  �ּ�, ��ȭ��ȣ, �̸����ּҸ� �Է¹޴´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_GETTEXT, (WPARAM)32, (LPARAM)emailAddress);
		//4.3 �ּҷϿ��� ��ģ��.(Correct)
		addressBook = (AddressBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Correct(addressBook, index, address, telephoneNumber, emailAddress);
		//4.4 ����Ʈ�� ��Ʈ�ѿ��� �׸��� ��ģ��.
		item.mask = LVIF_TEXT;
		item.iItem = index;
		item.iSubItem = 2;
		item.pszText = addressBook->personals[index].address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = addressBook->personals[index].telephoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = addressBook->personals[index].emailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}

//OnEraseButtonClicked
BOOL AddressBookForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook* addressBook;
	LVITEM item = { 0, };
	TCHAR number[64];
	Long index;

	//5. ����� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//5.1 ����Ʈ�� ��Ʈ�ѿ��� ���õ� �׸��� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, 0, 0);
		//5.2 �ּҷϿ��� �����.(Erase)
		addressBook = (AddressBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Erase(addressBook, index);
		//5.3 ����Ʈ�� ��Ʈ�ѿ� �ִ� �׸��� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEITEM, (WPARAM)index, 0);
		//5.4 ����Ʈ�� ��Ʈ�ѿ��� ��ġ�� ��ȣ�� �ٽ� �ű��.
		item.mask = LVIF_TEXT;
		while (index < addressBook->length)
		{
			item.iItem = index;
			item.iSubItem = 0;
			sprintf(number, "%d", index + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			index++;
		}
	}
	return TRUE;
}

//OnArrangeButtonClicked
BOOL AddressBookForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook* addressBook;
	LVITEM item = { 0, };
	TCHAR number[64];
	Long index;

	//6. �����ϱ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//6.1 �ּҷϿ��� �����Ѵ�.(Arrange)
		addressBook = (AddressBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Arrange(addressBook);
		//6.2 ����Ʈ�� ��Ʈ�ѿ� �մ� ��� �׸���� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEALLITEMS, 0, 0);
		//6.3 ����Ʈ�� ��Ʈ�ѿ� �ּҷϿ� ����� �׸���� �߰��Ѵ�.
		item.mask = LVIF_TEXT;
		index = 0;
		while (index < addressBook->length)
		{
			item.iItem = index;
			item.iSubItem = 0;
			sprintf(number, "%d", index + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, 0, (LPARAM)&item);
			item.iSubItem = 1;
			item.pszText = addressBook->personals[index].name;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 2;
			item.pszText = addressBook->personals[index].address;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 3;
			item.pszText = addressBook->personals[index].telephoneNumber;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 4;
			item.pszText = addressBook->personals[index].emailAddress;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			index++;
		}
	}
	return TRUE;
}

//ListViewDoubleClicked
BOOL AddressBookForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook* addressBook;
	LVITEM item = { 0, };
	TCHAR name[11];
	TCHAR address[64];
	TCHAR telephoneNumber[12];
	TCHAR emailAddress[32];
	Long index;

	//7. ����Ʈ�� ��Ʈ�Ѿּ� �׸��� ���� Ŭ������ ��
	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		//7.1 ����Ʈ�� ��Ʈ�ѿ��� ������ ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, 0, 0);
		//7.2 ������ �׸��� ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �д´�.
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
		//7.3 ����Ʈ�� ��Ʈ�ѿ��� ���� ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� ���ο� ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_SETTEXT, 0, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_SETTEXT, 0, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_SETTEXT, 0, (LPARAM)emailAddress);
	}
	return TRUE;
}

//OnClose
BOOL AddressBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//8. �ݱ� ��ư�� Ŭ������ ��
	AddressBook* addressBook;

	addressBook = (AddressBook*)GetWindowLong(hWnd, GWL_USERDATA);
	if (addressBook != NULL)
	{
		//8.1 �ּҷϿ��� �����Ѵ�(Save)
		Save(addressBook);
		//8.2 �ּҷ��� �����.(Destroy)
		Destroy(addressBook);
		free(addressBook);
	}
	//8.3 �����츦 �ݴ´�.
	EndDialog(hWnd, 0);
	return TRUE;
}