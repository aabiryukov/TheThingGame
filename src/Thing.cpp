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

// Thing.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Thing.h"

#include "MainFram.h"
#include "ThingDoc.h"
#include "ThingForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThingApp

BEGIN_MESSAGE_MAP(CThingApp, CWinApp)
	//{{AFX_MSG_MAP(CThingApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDM_APP_EXIT_RUS, OnAppExit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThingApp construction

CThingApp::CThingApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CThingApp object

CThingApp theApp;
extern CThingForm *gameForm;

/////////////////////////////////////////////////////////////////////////////
// CThingApp initialization

BOOL CThingApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MFC_VER < 7

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

#endif // _MFC_VER < 7

	SetRegistryKey(_T("Master Software"));

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)
	WriteProfileString( "", "", "Copiryght (c) 1996-1998 by Alexander Biryukov.  tel. (24) 12-87-29" );

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CThingDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CThingForm));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

//	if (!static_cast<CMainFrame*>(m_pMainWnd)->LoadFrame(IDR_MAINFRAME))
//		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
	m_pMainWnd->UpdateWindow();

	//OnAppAbout();
	m_pMainWnd->PostMessage(WM_COMMAND, ID_APP_ABOUT, NULL);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CThingApp commands


BOOL CThingApp::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(lCount == 0) 
		CWinApp::OnIdle(lCount);

	gameForm->Idle();

	return TRUE;
}
