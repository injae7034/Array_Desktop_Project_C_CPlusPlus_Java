#ifndef _ADDRESSBOOKFORM_H
#define _ADDRESSBOOKFORM_H
#include<afxwin.h>//CDialog 헤더파일
#include "resource.h"

typedef signed long int Long;

class AddressBook;//전방선언 AddressBookForm class에서 AddressBook *addressBook을 선언하기 위해 전방선언함
class AddressBookForm :public CDialog
{
public:
	enum{IDD=IDD_ADDRESSBOOKFORM};//IDD_ADDRESSBOOKFORM이 길어서 IDD로 축약해서 쓰기로 약속
public://연산기능
	AddressBookForm(CWnd* parent = NULL);//생성자, NULL이 디폴트값
	void Load();
	void Save();
	void Insert(Long index);
	void Delete(Long index);
	void Update(Long index);
	CString GetCode();
	virtual BOOL OnInitDialog();//윈도우 프레임 생성자 생성 제대로 됬는지 체크한 후에 작성하기
public:
	AddressBook* addressBook;//주소
protected://#
	afx_msg void OnRecordButtonClikced();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnEraseButtonClicked();
	afx_msg void OnArrangeButtonClicked();
	afx_msg void OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()//단 한개의 afx_msg가 있더라도 적어야함.
};
#endif // !_ADDRESSBOOKFORM_H

