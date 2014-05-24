// carbideDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "TargetWndCtl.h"
#include "automation/include/UIAutomationCore.h"

#include <vector>


enum MENU_SELECT 
{
	MENU_INPUT,
	MENU_CLICK,
	MENU_ACTIVE,
	MENU_STROKE,
};

#define HOTKEY_ID		0x1000

// CCarbideDlg �Ի���
class CCarbideDlg : public CDialog
{
// ����
public:
	CCarbideDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CARBIDE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��




// ʵ��
protected:
	HICON m_hIcon;
	CTargetWndCtl m_instruction;
	CTargetWndCtl* m_worker;
	CComPtr<IUIAutomation> m_auto;
	std::vector<CComPtr<IUIAutomationElement> > m_elements;

	int m_menu;
	CString m_input;
	CString m_element_content;
	BOOL m_pressed_control;


	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


private:
	void AddText(const CString& strContent);
	CString ProduceCode(CComPtr<IUIAutomationElement> pElement);
	CString ElementCode();
	
public:
	
	afx_msg void OnDestroy();
	afx_msg void OnPmenuInput();
	afx_msg void OnPmenuActive();
	afx_msg void OnPmenuClick();
	afx_msg void OnPmenuStroke();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
};
