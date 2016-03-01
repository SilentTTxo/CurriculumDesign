// m3.h : main header file for the M3 application
//

#if !defined(AFX_M3_H__2D0C96DF_A2DD_49F8_B693_3900A9367B27__INCLUDED_)
#define AFX_M3_H__2D0C96DF_A2DD_49F8_B693_3900A9367B27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CM3App:
// See m3.cpp for the implementation of this class
//

class CM3App : public CWinApp
{
public:
	CM3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CM3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CM3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_M3_H__2D0C96DF_A2DD_49F8_B693_3900A9367B27__INCLUDED_)
