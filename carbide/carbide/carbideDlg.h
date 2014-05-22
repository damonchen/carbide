// carbideDlg.h : 头文件
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


// CCarbideDlg 对话框
class CCarbideDlg : public CDialog
{
// 构造
public:
	CCarbideDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CARBIDE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持




// 实现
protected:
	HICON m_hIcon;
	CTargetWndCtl m_instruction;
	CTargetWndCtl* m_worker;
	CComPtr<IUIAutomation> m_auto;
	std::vector<CComPtr<IUIAutomationElement> > m_elements;

	int m_menu;
	CString m_input;
	CString m_element_content;


	// 生成的消息映射函数
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
};
