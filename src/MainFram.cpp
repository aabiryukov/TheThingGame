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

// MainFram.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Thing.h"
#include "Const.h"

#include "MainFram.h"
#include "SpeedDlg.h"
//#include "RegDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_LANGUAGE_RUS, OnLanguageRus)
	ON_COMMAND(IDM_LANGUAGE_ENG, OnLanguageEng)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR_RUS, OnUpdateViewStatusBarRus)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_RUS, OnUpdateViewToolbarRus)
	ON_COMMAND(ID_VIEW_STATUS_BAR_RUS, OnViewStatusBarRus)
	ON_COMMAND(ID_VIEW_TOOLBAR_RUS, OnViewToolbarRus)
	ON_WM_CLOSE()
	ON_COMMAND(IDM_SPEED, OnSpeed)
	ON_COMMAND(ID_TOGGLE_LANGUAGE, OnToggleLanguage)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDM_SPEED_RUS, OnSpeed)
	ON_COMMAND(ID_APP_ABOUT_RUS, OnAppAbout)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_LIFES_CHANGED, OnLifesChange)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,
//	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg(UINT nIDTemplate, CWnd* pParentWnd);

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg(UINT nIDTemplate, CWnd* pParentWnd) : CDialog(nIDTemplate, pParentWnd)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
	: CFrameWnd(), Language(lENGLISH)
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
//	m_wndStatusBar.SetBarStyle(m_wndToolBar.GetBarStyle() && ~WS_VISIBLE);

	m_wndStatusBar.SetPaneInfo( LEVEL_INDICATOR, ID_SEPARATOR, 0, 60 );
	m_wndStatusBar.SetPaneInfo( LIFE_INDICATOR,  ID_SEPARATOR, 0, 70 );
	m_wndStatusBar.SetPaneInfo( SCORE_INDICATOR, ID_SEPARATOR, 0, 70 );

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle((m_wndToolBar.GetBarStyle() & ~WS_VISIBLE) |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	LoadSettings();
	UpdateClientRect();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION /*| FWS_ADDTOTITLE*/
		     | WS_SYSMENU | WS_MINIMIZEBOX | DS_CENTER;
/*
   cs.lpszClass = AfxRegisterWndClass(
      CS_VREDRAW | CS_HREDRAW,
      ::LoadCursor(NULL, IDC_ARROW),
      (HBRUSH) ::GetStockObject(WHITE_BRUSH),
	  ::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME))
	  );
*/
	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
   CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
   CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

LRESULT CMainFrame::OnLifesChange(WPARAM wParam, LPARAM lParam)
{
   static LPCTSTR InfoItems[2][3] = { 
	{_T("Level #%u"), _T("Lifes : %u"), _T("Score : %u")}, 
	{_T("Этап #%u"), _T("Жизни : %u"), _T("Очки : %u")}
   };
   CString S;
/*   
   switch(wParam)
   {
   case LIFE_INDICATOR : 
	S.Format("Lifes : %u", lParam);
	break;
   case SCORE_INDICATOR : 
	S.Format("Score : %u", lParam);
	break;
   }
*/
   S.Format(InfoItems[Language][wParam-1], lParam);
   m_wndStatusBar.SetPaneText( wParam, S );

   return 0;
}

void CMainFrame::OnLanguageRus() 
{
   SetLanguage(lRUSSIAN);
}

void CMainFrame::OnLanguageEng() 
{
   SetLanguage(lENGLISH);
}

void CMainFrame::SetLanguage(GAME_LANGUAGE Lang)
{   
   if(Lang == Language) return;

   m_Menu.DestroyMenu();

   switch(Lang)
   {
   case lENGLISH :
	   m_Menu.LoadMenu(IDR_MAINFRAME_ENG);
	   SetMenu(&m_Menu);		
	break;
   case lRUSSIAN :
         m_Menu.LoadMenu(IDR_MAINFRAME_RUS);
	   SetMenu(&m_Menu);		
	   break;
   default : 
	TRACE0("ERROR My: Invalid Language (CMainFrame::SetLanguage(...))");
	return;
   }

   Language = Lang;
   if(gameForm->World->State != gsNONE)
   {
	OnLifesChange(LEVEL_INDICATOR, gameForm->World->Level);
	OnLifesChange(LIFE_INDICATOR,  gameForm->World->Life);
	OnLifesChange(SCORE_INDICATOR, gameForm->World->Score);
   }
}

void CMainFrame::OnUpdateViewStatusBarRus(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_wndStatusBar.GetStyle() & WS_VISIBLE);
}

void CMainFrame::OnUpdateViewToolbarRus(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_wndToolBar.GetStyle() & WS_VISIBLE);	
}

void CMainFrame::OnViewStatusBarRus() 
{
   ShowControlBar(&m_wndStatusBar, (m_wndStatusBar.GetStyle()&WS_VISIBLE) == 0, FALSE);
   UpdateClientRect();
}

void CMainFrame::OnViewToolbarRus() 
{
   ShowControlBar(&m_wndToolBar, (m_wndToolBar.GetStyle()&WS_VISIBLE) == 0, FALSE);	
   UpdateClientRect();
}

void CMainFrame::OnClose() 
{
   SaveSettings();

   m_hMenuDefault = NULL;
   CFrameWnd::OnClose();
}

void CMainFrame::SaveSettings()
{
   CWinApp *app = AfxGetApp();

   app->WriteProfileInt( sRegSettings, sRegSound, gameForm->World->IsSound );
   app->WriteProfileInt( sRegSettings, sRegSpeed, (int)(gameForm->TimeInterval) );
   app->WriteProfileInt( sRegSettings, sRegDifficulty, (int)(gameForm->World->GetDif()) );
   app->WriteProfileInt( sRegSettings, sRegLanguage, (int)Language );
   app->WriteProfileInt( sRegSettings, sRegToolBar, int((m_wndToolBar.GetStyle()&WS_VISIBLE) != 0) );
   app->WriteProfileInt( sRegSettings, sRegStatusBar, int((m_wndStatusBar.GetStyle()&WS_VISIBLE) != 0) );
}

void CMainFrame::LoadSettings()
{
   CWinApp *app = AfxGetApp();

   gameForm->World->IsSound = app->GetProfileInt( sRegSettings, sRegSound, 1 );
   gameForm->TimeInterval = (DWORD) app->GetProfileInt( sRegSettings, sRegSpeed, (int)DEFTIMEINTERVAL );
   gameForm->World->SetDifficulty( (DIFFICULTY) app->GetProfileInt( sRegSettings, sRegDifficulty, 0 ) );
   SetLanguage( (GAME_LANGUAGE)app->GetProfileInt( sRegSettings, sRegLanguage, (int)lENGLISH ) );
   ShowControlBar( &m_wndToolBar,   app->GetProfileInt( sRegSettings, sRegToolBar,   1 ), FALSE );
   ShowControlBar( &m_wndStatusBar, app->GetProfileInt( sRegSettings, sRegStatusBar, 1 ), FALSE );
}

void CMainFrame::OnSpeed() 
{
   UINT tem;

   switch(Language)
   {
   case lENGLISH : 
	tem = IDD_SPEED;
	break;
   case lRUSSIAN : 
	tem = IDD_SPEED_RUS;
	break;
   default : 
	TRACE0("ERROR My: Invalid Language (CMainFrame::OnSpeed())");
	return;
   }
   CSpeedDlg SpeedDlg(tem, this);

   SpeedDlg.DoModal();	
}

void CMainFrame::OnToggleLanguage() 
{
   switch(Language)
   {
   case lENGLISH : 
	SetLanguage(lRUSSIAN);
	break;
   case lRUSSIAN : 
	SetLanguage(lENGLISH);
	break;
   default :;
   }
}

void CMainFrame::OnAppAbout() 
{
   UINT tem;
   switch(Language)
   {
   case lENGLISH : 
	tem = IDD_ABOUTBOX;
	break;
   case lRUSSIAN : 
	tem = IDD_ABOUTBOX_RUS;
	break;
   default : return;
   }
   CAboutDlg aboutDlg(tem, this);
   aboutDlg.DoModal();	
}

void CMainFrame::UpdateClientRect()
{
#define _B  5 // window borter width

   RECT wR, cR, R;
   
   int height = 0;//-R.top;

   ::GetWindowRect(m_hWnd, &wR);
   ::GetClientRect(m_hWnd, &cR);

   if((m_wndToolBar.GetStyle()&WS_VISIBLE) != 0)
   {
      m_wndToolBar.GetWindowRect(&R);
	height += R.bottom-R.top+1;// /2;
   }

   if((m_wndStatusBar.GetStyle()&WS_VISIBLE) != 0)
   {
	m_wndStatusBar.GetWindowRect(&R);
	height += R.bottom-R.top+1;// /2;
   }

//   wR.top = 100;


   SetWindowPos( &wndNoTopMost, wR.left, wR.top, 
	(wR.right-wR.left+1)-cR.right+WORLDWIDTH+_B, 
	(wR.bottom-wR.top+1)-cR.bottom+WORLDHEIGHT+height,
	SWP_NOMOVE );

#ifdef USE_REGION
   HRGN Rgn1, Rgn2;

   Rgn1 = ::CreateRectRgn(LEFTBORDER-1, 0, wR.right-wR.left-RIGHTBORDER+1, wR.bottom-wR.top);
   Rgn2 = ::CreateRectRgn(0, 0, WORLDWIDTH+2*_B+1, height+_B);
   ::CombineRgn(Rgn1, Rgn1, Rgn2, RGN_OR);
   Rgn2 = ::CreateEllipticRgn(_B-1, height, WORLDWIDTH+_B+1, WORLDHEIGHT*2/3);
   ::CombineRgn(Rgn1, Rgn1, Rgn2, RGN_OR);


  ::SetWindowRgn(m_hWnd, Rgn1, TRUE);
#endif
}
