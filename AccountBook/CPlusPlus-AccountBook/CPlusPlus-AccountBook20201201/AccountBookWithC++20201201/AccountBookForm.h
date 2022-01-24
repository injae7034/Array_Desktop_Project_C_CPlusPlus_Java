#ifndef _ACCOUNTBOOKFORM_H
#define _ACCOUNTBOOKFORM_H

#include<afxwin.h>//CDialog 헤더파일
#include "resource.h"

typedef signed long int Long;

class AccountBook;//전방선언 AccountBook이 전방선언으로 사용됨.
class AccountBookForm :public CDialog
{
public:
	enum{IDD=IDD_ACCOUNTBOOKFORM};
public:
	AccountBookForm(CWnd* parent = NULL);//생성자, NULL이 디폴트값
	void Load();
	void Insert(Long index);
	void Update(Long index);
	CString GetCode();
	void Save();
	virtual BOOL OnInitDialog();
public:
	AccountBook* accountBook;//주소이므로 전방선언이 필요함.
protected://#
	afx_msg void OnIncomeRadioButtonClicked();
	afx_msg void OnOutgoRadioButtonClicked();
	afx_msg void OnAmountEditKillFocus();
	afx_msg void OnRecordButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

};

#endif // !_ACCOUNTBOOKFORM_H

