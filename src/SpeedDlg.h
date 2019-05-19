/*========================================================================*
 * TITLE: "The Thing" game
 *  
 * Copyright (c) 1997-2006 Alexander Biryukov
 * All rights reserved.
 * Email : aabiryukov@gmail.com
 * Home page : http://alexbirk.narod.ru
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *========================================================================*/

#if !defined(AFX_SPEEDDLG_H__31783381_57F9_11D2_B084_444553540000__INCLUDED_)
#define AFX_SPEEDDLG_H__31783381_57F9_11D2_B084_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SpeedDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpeedDlg dialog

class CSpeedDlg : public CDialog
{
// Construction
public:
	CSpeedDlg(UINT nIDTemplate, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSpeedDlg)
	enum { IDD = IDD_SPEED};
	CSliderCtrl	m_Slider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpeedDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDefButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEEDDLG_H__31783381_57F9_11D2_B084_444553540000__INCLUDED_)
