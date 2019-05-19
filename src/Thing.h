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

// Thing.h : main header file for the THING application
//

#if !defined(AFX_THING_H__AD759F01_5225_11D2_B084_444553540000__INCLUDED_)
#define AFX_THING_H__AD759F01_5225_11D2_B084_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#define WM_LIFES_CHANGED (WM_USER+1)

#include "resource.h"       // main symbols
#include "ThingForm.h"	// Added by ClassView


/////////////////////////////////////////////////////////////////////////////
// CThingApp:
// See Thing.cpp for the implementation of this class
//

class CThingApp : public CWinApp
{
public:
	CThingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThingApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CThingApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

// Status bar Indicator numbers
#define LEVEL_INDICATOR	  1
#define LIFE_INDICATOR	  2
#define SCORE_INDICATOR	  3


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THING_H__AD759F01_5225_11D2_B084_444553540000__INCLUDED_)
