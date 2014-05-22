// TargetWndCtl.cpp : 实现文件
//

#include "stdafx.h"
#include "carbide.h"
#include "TargetWndCtl.h"


// CTargetWndCtl

IMPLEMENT_DYNAMIC(CTargetWndCtl, CStatic)

CTargetWndCtl::CTargetWndCtl()
: m_hwnd( NULL )
{

}

CTargetWndCtl::~CTargetWndCtl()
{
}


BEGIN_MESSAGE_MAP(CTargetWndCtl, CStatic)
END_MESSAGE_MAP()



// CTargetWndCtl 消息处理程序

void CTargetWndCtl::SetImage( INT nID )
{
	CWinApp *pApp = AfxGetApp();
	SetBitmap(LoadBitmap(pApp->m_hInstance, MAKEINTRESOURCE(nID)));
}

HWND CTargetWndCtl::GetTarget()
{
	return m_hwnd;
}

void CTargetWndCtl::SetTarget( HWND hWnd )
{
	m_hwnd = hWnd;
}