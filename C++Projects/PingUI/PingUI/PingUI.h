
// PingUI.h : main header file for the PingUI application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPingUIApp:
// See PingUI.cpp for the implementation of this class
//

class CPingUIApp : public CWinApp
{
public:
	CPingUIApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPingUIApp theApp;
