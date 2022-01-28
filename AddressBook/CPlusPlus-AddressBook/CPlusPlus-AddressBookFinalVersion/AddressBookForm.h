#ifndef _ADDRESSBOOKFORM_H
#define _ADDRESSBOOKFORM_H
#include<afxwin.h>//CDialog �������
#include "resource.h"

typedef signed long int Long;

class AddressBook;//���漱�� AddressBookForm class���� AddressBook *addressBook�� �����ϱ� ���� ���漱����
class AddressBookForm :public CDialog
{
public:
	enum{IDD=IDD_ADDRESSBOOKFORM};//IDD_ADDRESSBOOKFORM�� �� IDD�� ����ؼ� ����� ���
public://������
	AddressBookForm(CWnd* parent = NULL);//������, NULL�� ����Ʈ��
	void Load();
	void Save();
	void Insert(Long index);
	void Delete(Long index);
	void Update(Long index);
	CString GetCode();
	virtual BOOL OnInitDialog();//������ ������ ������ ���� ����� ����� üũ�� �Ŀ� �ۼ��ϱ�
public:
	AddressBook* addressBook;//�ּ�
protected://#
	afx_msg void OnRecordButtonClikced();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnEraseButtonClicked();
	afx_msg void OnArrangeButtonClicked();
	afx_msg void OnListViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()//�� �Ѱ��� afx_msg�� �ִ��� �������.
};
#endif // !_ADDRESSBOOKFORM_H

