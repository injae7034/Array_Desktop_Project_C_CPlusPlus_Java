#ifndef _WORDBOOKFORM_H
#define _WORDBOOKFORM_H
#include<afxwin.h>//CDialog �������
#include"resource.h"

class WordBook;//���漱��


class WordBookForm :public CDialog
{
public:
	enum{IDD=IDD_WORDBOOKFORM};
public:
	WordBookForm(CWnd* parent = NULL);//������, NULL�� ����Ʈ��
	virtual BOOL OnInitDialog();
public:
	WordBook* wordBook;//�ּ�, ���漱���� �ʿ���.
protected://#
	afx_msg void OnRecordButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnEraseButtonClicked();
	afx_msg void OnArrangeButtonClicked();
	afx_msg void OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif//_WORDBOOKFORM_H

