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

// MainFram.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRAM_H__AD759F05_5225_11D2_B084_444553540000__INCLUDED_)
#define AFX_MAINFRAM_H__AD759F05_5225_11D2_B084_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

typedef enum{lENGLISH, lRUSSIAN} GAME_LANGUAGE;

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void RegDialog(void);
	void UpdateClientRect(void);
	void SetLanguage(GAME_LANGUAGE Lang);
	GAME_LANGUAGE GetLanguage(void) const {return Language;}
	void SaveSettings(void);
	void LoadSettings(void);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	GAME_LANGUAGE Language;
	CMenu m_Menu;
	LRESULT OnLifesChange(WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLanguageRus();
	afx_msg void OnLanguageEng();
	afx_msg void OnUpdateViewStatusBarRus(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewToolbarRus(CCmdUI* pCmdUI);
	afx_msg void OnViewStatusBarRus();
	afx_msg void OnViewToolbarRus();
	afx_msg void OnClose();
	afx_msg void OnSpeed();
	afx_msg void OnToggleLanguage();
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAM_H__AD759F05_5225_11D2_B084_444553540000__INCLUDED_)
