#include "AddressBookForm.h"
#include "AddressBook.h"
#include "resource.h"
#include <commctrl.h>
#include <stdio.h>
#pragma warning(disable:4996)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
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
	case WM_CLOSE: ret = AddressBookForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//OnInitDialog
BOOL AddressBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//1. 윈도우가 생성될 때
	AddressBook* addressBook;
	LVCOLUMN column = { 0, };
	LVITEM item = { 0, };
	TCHAR number[64];
	Long index;
	Long count;
	
	//1.1 주소록을 만든다.(Create)
	addressBook = (AddressBook*)malloc(sizeof(AddressBook));
	Create(addressBook, 10000);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)addressBook);
	//1.2 주소록에서 적재한다(Load)
	count = Load(addressBook);
	//1.3 리스트뷰 컨드롤의 헤더를 만든다.(LVM_INSERTCOLUMN)
	column.mask = LVCF_WIDTH | LVCF_TEXT;
	column.cx = 50;
	column.pszText = "번호";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "성명";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);
	column.cx = 300;
	column.pszText = "주소";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);
	column.cx = 200;
	column.pszText = "전화번호";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);
	column.cx = 300;
	column.pszText = "이메일주소";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);
	//1.4  적재된 개수만큼 리스트뷰 컨트롤에 항목을 추가한다.(LVM_INSERTITEM)(LVM_SETITEMTEXT)
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

//OnClose
BOOL AddressBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//8. 닫기 버튼을 클릭했을 때
	AddressBook* addressBook;

	addressBook = (AddressBook*)GetWindowLong(hWnd, GWL_USERDATA);
	if (addressBook != NULL)
	{
		//8.1 주소록에서 저장한다(Save)
		Save(addressBook);
		//8.2 주소록을 지운다.(Destroy)
		Destroy(addressBook);
		free(addressBook);
	}
	//8.3 윈도우를 닫는다.
	return TRUE;
}