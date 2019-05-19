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

// ThingForm.h : interface of the CThingForm class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THINGFORM_H__AD759F09_5225_11D2_B084_444553540000__INCLUDED_)
#define AFX_THINGFORM_H__AD759F09_5225_11D2_B084_444553540000__INCLUDED_

#include "World.h"	// Added by ClassView
#include "ThingDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

const LPCTSTR sRegSettings = "Settings";
const LPCTSTR sRegSound = "Sound";
const LPCTSTR sRegSpeed = "Speed";
const LPCTSTR sRegLanguage = "Language";
const LPCTSTR sRegToolBar = "ToolBar";
const LPCTSTR sRegStatusBar = "StatusBar";
const LPCTSTR sRegDifficulty = "Difficulty";

class CThingForm : public CFormView
{
protected: // create from serialization only
	CThingForm();
	DECLARE_DYNCREATE(CThingForm)

public:
	//{{AFX_DATA(CThingForm)
	enum{ IDD = IDD_THING_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CThingDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThingForm)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
private:
//   __int64/*LARGE_INTEGER*/ OldCounter, Counter;
   DWORD OldCounter, Counter;

public:
	DWORD TimeInterval;
	static void DrawTextRect(CDC*pDC, LPCTSTR Str, RECT *R, COLORREF Col);
	void SetKey(UINT nChar, UINT nFlags, BOOL bSet);
	void Idle(void);
	TWorld *World;
	virtual ~CThingForm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void ChangeDifficulty(DIFFICULTY Dif);
	virtual void DrawBackground(CDC *pDC, RECT& R);
	virtual void TheEnd(BOOL bOk);
	//{{AFX_MSG(CThingForm)
	afx_msg void OnStart();
	afx_msg void OnUpdateStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSound(CCmdUI* pCmdUI);
	afx_msg void OnSound();
	afx_msg void OnPause();
	afx_msg void OnUpdatePause(CCmdUI* pCmdUI);
	afx_msg void OnReplay();
	afx_msg void OnUpdateDifEasy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDifHard(CCmdUI* pCmdUI);
	afx_msg void OnDifEasy();
	afx_msg void OnDifHard();
	afx_msg void OnUpdateReplay(CCmdUI* pCmdUI);
	afx_msg void OnDifVeryHard();
	afx_msg void OnUpdateDifVHard(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnStop();
	afx_msg void OnUpdateCustomLevel1(CCmdUI* pCmdUI);
	afx_msg void OnCustomLevel1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//extern CThingForm *ThingForm;
extern CThingForm *gameForm;

#ifndef _DEBUG  // debug version in ThingForm.cpp
inline CThingDoc* CThingForm::GetDocument()
   { return (CThingDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THINGFORM_H__AD759F09_5225_11D2_B084_444553540000__INCLUDED_)
