// m3Dlg.h : header file
//

#if !defined(AFX_M3DLG_H__C1F6979A_ABF5_485F_832A_C12674C9D9C4__INCLUDED_)
#define AFX_M3DLG_H__C1F6979A_ABF5_485F_832A_C12674C9D9C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CM3Dlg dialog

class CM3Dlg : public CDialog
{
// Construction
public:
	CM3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CM3Dlg)
	enum { IDD = IDD_M3_DIALOG };
	CString	m_content;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CM3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CM3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void Onsend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_M3DLG_H__C1F6979A_ABF5_485F_832A_C12674C9D9C4__INCLUDED_)
