#ifndef _ACCOUNTBOOKFORM_H
#define _ACCOUNTBOOKFORM_H

#include<afxwin.h>//CDialog �������
#include "resource.h"

class AccountBook;//���漱�� AccountBook�� ���漱������ ����.
class AccountBookForm :public CDialog
{
public:
	enum{IDD=IDD_ACCOUNTBOOKFORM};
public:
	AccountBookForm(CWnd* parent = NULL);//������, NULL�� ����Ʈ��
	virtual BOOL OnInitDialog();
public:
	AccountBook* accountBook;//�ּ��̹Ƿ� ���漱���� �ʿ���.
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

