// carbideDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "carbide.h"
#include "carbideDlg.h"
#include "InputDlg.h"
#include "controltype.h"
#include <vector>

using namespace std;



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const CLSID CLSID_CUIAutomation = {
	0xff48dba4, 0x60ef, 0x4201, {0xaa, 0x87, 0x54, 0x10, 0x3e, 0xef, 0x59, 0x4e}
};

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCarbideDlg 对话框




CCarbideDlg::CCarbideDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCarbideDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCarbideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INSTRUCTION, m_instruction);
}

BEGIN_MESSAGE_MAP(CCarbideDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_PMENU_INPUT, &CCarbideDlg::OnPmenuInput)
	ON_COMMAND(ID_PMENU_ACTIVE, &CCarbideDlg::OnPmenuActive)
	ON_COMMAND(ID_PMENU_CLICK, &CCarbideDlg::OnPmenuClick)
	ON_COMMAND(ID_PMENU_STROKE, &CCarbideDlg::OnPmenuStroke)
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CCarbideDlg 消息处理程序

CPen HighlightPen(PS_SOLID, 2, RGB(0,0,0));

long HighlightFoundWindow (HWND hwnd)
{
	HDC     hWindowDC = NULL;
	HGDIOBJ hPrevPen = NULL;
	HGDIOBJ hPrevBrush = NULL;
	RECT        rect;
	long        lRet = 0;

	GetWindowRect (hwnd, &rect);
	hWindowDC = GetWindowDC (hwnd);

	if (hWindowDC)
	{
		hPrevPen = SelectObject (hWindowDC, (HPEN)HighlightPen);
		hPrevBrush = SelectObject (hWindowDC, GetStockObject(HOLLOW_BRUSH));
		Rectangle (hWindowDC, 1, 1, rect.right - rect.left, rect.bottom - rect.top);
		SelectObject (hWindowDC, hPrevBrush);
		SelectObject (hWindowDC, hPrevPen);
		ReleaseDC (hwnd, hWindowDC);
	}
	return lRet;
}

void RefreshWindow(HWND hwnd)
{
	if( hwnd == NULL )
	{
		return ;
	}

	RedrawWindow(hwnd, NULL, NULL,
		RDW_ERASE|RDW_FRAME|RDW_INTERNALPAINT|RDW_INVALIDATE|
		RDW_ERASENOW|RDW_UPDATENOW);
}



BOOL CCarbideDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_worker = NULL;
	m_instruction.SetImage(IDB_BITMAP2);

	// 注册热键
	m_pressed_control = FALSE;
	RegisterHotKey(GetSafeHwnd(), HOTKEY_ID, MOD_CONTROL, 0);


	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	HRESULT hr = m_auto.CoCreateInstance(CLSID_CUIAutomation, NULL, CLSCTX_INPROC_SERVER);
	if( FAILED(hr) )
	{
		LPSTR szMsg; 
		BOOL bOk = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM  | FORMAT_MESSAGE_IGNORE_INSERTS  | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			NULL, GetLastError(),  MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
			(LPSTR)&szMsg, 0, NULL);

		MessageBoxA(NULL, szMsg, szMsg, MB_OK);

		LocalFree(szMsg);

		return FALSE;
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCarbideDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCarbideDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCarbideDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCarbideDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_worker = dynamic_cast<CTargetWndCtl *>(ChildWindowFromPoint(point));
	if( m_worker == NULL || m_worker->GetTarget() != NULL )
	{
		CDialog::OnLButtonDown(nFlags, point);
		return ;
	}

	m_elements.clear();
	m_worker->SetImage(IDB_BITMAP1);
	SetCapture();

	CDialog::OnLButtonDown(nFlags, point);
}

void CCarbideDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if( m_worker != NULL )
	{
		ReleaseCapture();

		// 将这个点的UI automation获取出来
		POINT curpos;
		GetCursorPos(&curpos);

		CComPtr<IUIAutomationElement> element;
		HRESULT hr = m_auto->ElementFromPoint(curpos, &element);
		if(SUCCEEDED(hr)){
// 			CComBSTR bstrName;
// 			element->get_CurrentName(&bstrName);
// 			CString strName = bstrName;

			CComPtr<IUIAutomationTreeWalker> spControlWalker;
			hr = m_auto->get_ControlViewWalker(&spControlWalker);

			while ( !!element )
			{
				m_elements.push_back(element);
				CComPtr<IUIAutomationElement> parent;
				spControlWalker->GetParentElement(element, &parent);
				element = parent;
			}

			// 移出桌面
			if( !m_elements.empty() )
			{
				m_elements.pop_back();
			}

			// 弹出菜单，依据选择设置当前操作
			CMenu menu;
			menu.LoadMenu(IDR_MENU_POP);

			CMenu* popmenu = menu.GetSubMenu(0);
			popmenu->TrackPopupMenu(TPM_BOTTOMALIGN, curpos.x, curpos.y, this, NULL);

// 
// 			CString strTemp;
// 			strTemp.Format(_T("(%d, %d), name: %s\n"), curpos.x, curpos.y, strName);
// 
// 			m_element_content = strTemp;

			// 添加到行尾
// 			CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CODE);
// 			pEdit->SetSel(-1, -1, FALSE);
// 			pEdit->ReplaceSel(strTemp, TRUE);

		}

		m_worker->SetImage(IDB_BITMAP2);
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CCarbideDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if( nFlags & MK_LBUTTON )
	{
		POINT curpos;
		GetCursorPos(&curpos);

				

	}

	CDialog::OnMouseMove(nFlags, point);
}

void CCarbideDlg::OnDestroy()
{
	CDialog::OnDestroy();

	UnregisterHotKey(GetSafeHwnd(), HOTKEY_ID);

	m_auto = NULL;
	CoUninitialize();

}

void CCarbideDlg::AddText( const CString& strContent )
{
	// 添加到行尾
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CODE);
	pEdit->SetSel(-1, -1, FALSE);
	pEdit->ReplaceSel(strContent, TRUE);
}

void CCarbideDlg::OnPmenuInput()
{
	// 弹出一个对话框，用来输入内容
	m_menu = MENU_INPUT;

	CInputDlg dlg;
	INT nOk = dlg.DoModal();
	if ( nOk == IDOK )
	{
		m_input = dlg.m_input;
		

		CString strCode = ElementCode();
		CString strInput;
		strInput.Format(_T("Set(\"%s\")\n"), m_input);

		strCode += strInput;

		AddText(strCode);	
	}
}



void CCarbideDlg::OnPmenuActive()
{
	CString strCode = ElementCode();
	strCode += _T("Activate()\n");
	AddText(strCode);
}

void CCarbideDlg::OnPmenuClick()
{
	CString strCode = ElementCode();
	strCode += _T("Click()\n");
	AddText(strCode);
}


void CCarbideDlg::OnPmenuStroke()
{
	CString strCode = ElementCode();
	strCode += _T("SendEx()\n");
	AddText(strCode);
}

CString CCarbideDlg::ProduceCode( CComPtr<IUIAutomationElement> pElement )
{
	CString strCode;

	CONTROLTYPEID controltype;
	pElement->get_CurrentControlType(&controltype);
	CString strControlType = FindControlType(controltype);
	if ( strControlType.IsEmpty() )
	{
		return strCode;
	}

	CComBSTR bstrName;
	HRESULT hr = pElement->get_CurrentName(&bstrName);
	CString strName = bstrName;
	if( !strName.IsEmpty() )
	{
		if( strName == _T("Window") )
		{
			strCode = strName;
		}
		else
		{
			strCode.Format(_T("Win%s(\"%s\")"), strControlType, strName);
		}

		return strCode;
	}

	CComBSTR bstrAutomationId;
	pElement->get_CurrentAutomationId(&bstrAutomationId);
	CString strId = bstrAutomationId;
	if ( !strId.IsEmpty() )
	{
		strCode.Format(_T("Win%s({id=\"%s\"})"), strControlType, strId);
		return strCode;
	}

	CComBSTR bstrClassName;
	pElement->get_CurrentClassName(&bstrClassName);
	CString strClassName = bstrClassName;
	if ( !strClassName.IsEmpty() )
	{
		strCode.Format(_T("Win%s({class=\"%s\"})"), strControlType, strClassName);
		return strCode;
	}

	return strCode;
}

CString CCarbideDlg::ElementCode()
{
	CString strCode;

	for (int index=m_elements.size()-1; index>=0; index-- )
	{
		CComPtr<IUIAutomationElement> element = m_elements[index];

		strCode += ProduceCode(element);
		strCode += _T(".");
	}

	return strCode;
}

void CCarbideDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	if( nHotKeyId == HOTKEY_ID )
	{
		// 表明按下Ctrl键了
		if( nKey1 == MOD_CONTROL )
		{
			m_pressed_control = TRUE;
		}
		else
		{
			m_pressed_control = FALSE;
		}
	}

	CDialog::OnHotKey(nHotKeyId, nKey1, nKey2);
}
