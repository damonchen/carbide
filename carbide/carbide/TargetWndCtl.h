#pragma once


// CTargetWndCtl

class CTargetWndCtl : public CStatic
{
	DECLARE_DYNAMIC(CTargetWndCtl)

public:
	CTargetWndCtl();
	virtual ~CTargetWndCtl();

public:
	HWND GetTarget();
	void SetTarget(HWND hWnd);

public:
	void SetImage(INT nID);

protected:
	DECLARE_MESSAGE_MAP()

private:
	HWND m_hwnd;
};


