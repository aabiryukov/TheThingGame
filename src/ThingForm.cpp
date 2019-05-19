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

// ThingForm.cpp : implementation of the CThingForm class
//

#include "stdafx.h"
#include "mmsystem.h"
#include "Thing.h"
#include "MainFram.h"

#include "ThingDoc.h"
#include "ThingForm.h"
#include "LevelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CThingForm *gameForm = NULL;

/////////////////////////////////////////////////////////////////////////////
// CThingForm

IMPLEMENT_DYNCREATE(CThingForm, CFormView)

BEGIN_MESSAGE_MAP(CThingForm, CFormView)
	//{{AFX_MSG_MAP(CThingForm)
	ON_COMMAND(IDM_START, OnStart)
	ON_UPDATE_COMMAND_UI(IDM_START, OnUpdateStart)
	ON_UPDATE_COMMAND_UI(IDM_SOUND, OnUpdateSound)
	ON_COMMAND(IDM_SOUND, OnSound)
	ON_COMMAND(IDM_PAUSE, OnPause)
	ON_UPDATE_COMMAND_UI(IDM_PAUSE, OnUpdatePause)
	ON_COMMAND(IDM_REPLAY, OnReplay)
	ON_UPDATE_COMMAND_UI(IDM_DIF_EASY, OnUpdateDifEasy)
	ON_UPDATE_COMMAND_UI(IDM_DIF_HARD, OnUpdateDifHard)
	ON_COMMAND(IDM_DIF_EASY, OnDifEasy)
	ON_COMMAND(IDM_DIF_HARD, OnDifHard)
	ON_UPDATE_COMMAND_UI(IDM_REPLAY, OnUpdateReplay)
	ON_COMMAND(IDM_DIF_VHARD, OnDifVeryHard)
	ON_UPDATE_COMMAND_UI(IDM_DIF_VHARD, OnUpdateDifVHard)
	ON_UPDATE_COMMAND_UI(IDM_STOP, OnUpdateStop)
	ON_COMMAND(IDM_STOP, OnStop)
	ON_UPDATE_COMMAND_UI(IDM_CUSTOM_LEVEL1, OnUpdateCustomLevel1)
	ON_COMMAND(IDM_START_RUS, OnStart)
	ON_UPDATE_COMMAND_UI(IDM_START_RUS, OnUpdateStart)
	ON_COMMAND(IDM_SOUND_RUS, OnSound)
	ON_UPDATE_COMMAND_UI(IDM_SOUND_RUS, OnUpdateSound)
	ON_COMMAND(IDM_PAUSE_RUS, OnPause)
	ON_UPDATE_COMMAND_UI(IDM_PAUSE_RUS, OnUpdatePause)
	ON_COMMAND(IDM_REPLAY_RUS, OnReplay)
	ON_UPDATE_COMMAND_UI(IDM_DIF_EASY_RUS, OnUpdateDifEasy)
	ON_UPDATE_COMMAND_UI(IDM_REPLAY_RUS, OnUpdateReplay)
	ON_COMMAND(IDM_DIF_EASY_RUS, OnDifEasy)
	ON_COMMAND(IDM_DIF_HARD_RUS, OnDifHard)
	ON_UPDATE_COMMAND_UI(IDM_DIF_HARD_RUS, OnUpdateDifHard)
	ON_COMMAND(IDM_DIF_VHARD_RUS, OnDifVeryHard)
	ON_UPDATE_COMMAND_UI(IDM_DIF_VHARD_RUS, OnUpdateDifVHard)
	ON_COMMAND(IDM_STOP_RUS, OnStop)
	ON_UPDATE_COMMAND_UI(IDM_STOP_RUS, OnUpdateStop)
	ON_COMMAND(IDM_CUSTOM_LEVEL1, OnCustomLevel1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThingForm construction/destruction

CThingForm::CThingForm()
	: CFormView(CThingForm::IDD), 
	  World(NULL)
{
   //{{AFX_DATA_INIT(CThingForm)
	   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
   // TODO: add construction code here
   TimeInterval = DEFTIMEINTERVAL;
   Counter = OldCounter = 0;
}

CThingForm::~CThingForm()
{
	if(World != NULL) delete World;
}

void CThingForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThingForm)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CThingForm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	gameForm = this;
	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CThingForm diagnostics

#ifdef _DEBUG
void CThingForm::AssertValid() const
{
   CFormView::AssertValid();
}

void CThingForm::Dump(CDumpContext& dc) const
{
   CFormView::Dump(dc);
}

CThingDoc* CThingForm::GetDocument() // non-debug version is inline
{
   ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CThingDoc)));
   return (CThingDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThingForm message handlers

BOOL CThingForm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
   BOOL result;
   // TODO: Add your specialized code here and/or call the base class
   
   result = CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
   
   World = new TWorld(m_hWnd);
   return result;
}

void CThingForm::OnStart() 
{
   World->Init();
   {
	CLevelDlg LevelDlg;
	LevelDlg.DoModal();
   }
   World->Start();
   AfxGetApp()->m_pMainWnd->PostMessage(WM_LIFES_CHANGED, LEVEL_INDICATOR, 1);
   AfxGetApp()->m_pMainWnd->PostMessage(WM_LIFES_CHANGED, LIFE_INDICATOR, World->Life);
   AfxGetApp()->m_pMainWnd->PostMessage(WM_LIFES_CHANGED, SCORE_INDICATOR, World->Score);
   Invalidate(TRUE);
}

void CThingForm::OnDraw(CDC* pDC) 
{
	static LPCTSTR Words[2][2] ={
	   {_T("Victory"), _T("Game Over")},
	   {_T("Победа"), _T("Конец")}};
	RECT R;

	GetClientRect(&R);
//		GetUpdateRect(&R, TRUE);
	switch(World->State)
	{
	case gsNONE:
	   DrawBackground(pDC, R);
	   break;

	case gsPLAYING:
	case gsPAUSE: 
	   pDC->FillSolidRect(&R, Black);
	   World->Paint(pDC->m_hDC);
	   break;

	case gsOVER:	
	   DrawBackground(pDC, R);
	   DrawTextRect(pDC, Words[((CMainFrame*)AfxGetMainWnd())->GetLanguage()][1], &R, Blue);
	   break;

	case gsFINAL: 
	   DrawBackground(pDC, R);
   	   DrawTextRect(pDC, Words[((CMainFrame*)AfxGetMainWnd())->GetLanguage()][0], &R, Green);
	   break;

	default:;
	}
}

void CThingForm::Idle()
{
  //static __int64/*LARGE_INTEGER*/ OldCounter = 0, Counter;

  if(World->State != gsPLAYING) 
  {
	  ::Sleep(10);
	  return;
  }
//  QueryPerformanceCounter( (LARGE_INTEGER *) &Counter );
  Counter = ::GetTickCount();

  if( Counter - OldCounter >= TimeInterval ) //Speed )
  {
     WORD OldScore = World->Score;
     switch( World->Process() )
     {
     case prDone      : 
	  break;

     case prNextLevel :
	  //m_gameState = gsPAUSE;
	  {
	     CLevelDlg LevelDlg;
	     LevelDlg.DoModal();
	  }
	  World->Start();
	  AfxGetApp()->m_pMainWnd->PostMessage(WM_LIFES_CHANGED, LEVEL_INDICATOR, World->Level+1);
	  Invalidate(TRUE);
	  //m_gameState = gsPLAYING;
	  break;
     
     case prDead	:
	  if(World->Life > 0)
	  {
	     CLevelDlg LevelDlg;
	     LevelDlg.DoModal();
	     World->Start();
	     Invalidate(TRUE);
	  }
	  else TheEnd(FALSE);
	  AfxGetApp()->m_pMainWnd->PostMessage(WM_LIFES_CHANGED, LIFE_INDICATOR, World->Life);
	  break;

     case prComplete  : 
	  TheEnd(TRUE);
	  break;

     default : ;
     }
     if(OldScore != World->Score) AfxGetApp()->m_pMainWnd->PostMessage(WM_LIFES_CHANGED, SCORE_INDICATOR, World->Score);
     OldCounter = Counter;
  }
  else
	  ::Sleep(4);
}

void CThingForm::SetKey(UINT nChar, UINT /*nFlags*/, BOOL bSet)
{
/*  if( Key == VK_RETURN &&  Shift.Contains(ssCtrl) && Shift.Contains(ssAlt) && World->IsGame )
  {
    Timer = false;
    PasswEdit->Text = "";
    PasswPanel->Show();
    PasswEdit->SetFocus();
  }
  else
*/
	if(World->State != gsPLAYING) return;

	switch(nChar)
	{
	case 'N':
		if(GetKeyState(VK_CONTROL)<0)  World->NumFruits = 0;
		break;
	case 'L':
		if(GetKeyState(VK_CONTROL)<0)  World->Life = 100;
		break;
	default:
			if(bSet) World->KeyDown = nChar;
			else if(nChar == World->KeyDown) World->KeyDown = 0;
	}
}

BOOL CThingForm::PreTranslateMessage(MSG* pMsg) 
{
   if(World->State == gsPLAYING)
	switch(pMsg->message)
   {
		case WM_KEYDOWN: SetKey(pMsg->wParam, pMsg->lParam, TRUE);
		   break;
		case WM_KEYUP: SetKey(pMsg->wParam, pMsg->lParam, FALSE);
   }
   
   return CFormView::PreTranslateMessage(pMsg);
}

void CThingForm::TheEnd(BOOL bOk)
{
   if(World->IsSound)
	if(bOk) PlaySound( MAKEINTRESOURCE(IDW_FINAL), NULL, SND_RESOURCE|SND_ASYNC ); //gsFINAL;
	else  PlaySound( MAKEINTRESOURCE(IDW_HAHA), NULL, SND_RESOURCE|SND_ASYNC );//gsOVER;
   Invalidate(TRUE);
}

void CThingForm::OnUpdateStart(CCmdUI* pCmdUI) 
{
   switch(World->State)
   {
   case gsNONE :
   case gsFINAL :
   case gsOVER :	
			pCmdUI->Enable(TRUE);
			break;
   default :	pCmdUI->Enable(FALSE);
   }
}

void CThingForm::OnUpdateSound(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(World->IsSound);	
}

void CThingForm::OnSound() 
{
   World->IsSound = !gameForm->World->IsSound;	
}

void CThingForm::OnPause() 
{
   World->State = (World->State == gsPAUSE) ? gsPLAYING : gsPAUSE;	
}

void CThingForm::OnUpdatePause(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(World->State == gsPAUSE || World->State == gsPLAYING);
   pCmdUI->SetCheck(World->State == gsPAUSE);
}

void CThingForm::OnReplay() 
{
   World->ManIsLive = FALSE;
}

#define  BX	   211
#define  BY	   203

void CThingForm::DrawBackground(CDC * pDC, RECT& R)
{
   CDC hDC;
   CBitmap b;
   
   hDC.CreateCompatibleDC(pDC);
   b.LoadBitmap(IDB_BACK);
   hDC.SelectObject(b);
   
   for(int y = 0; y<R.bottom; y+=BY)
	for(int x = 0; x<R.right; x+=BX)
	   pDC->BitBlt(x, y, BX, BY, &hDC, 0,0, SRCCOPY);
	
/*
   HDC hMemDC;
   HBITMAP bmpBack;
   // CSize c = bmpBack.GetBitmapDimension();
   bmpBack = ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BACK));
  
     hMemDC = ::CreateCompatibleDC( NULL );
     ::SelectObject( hMemDC, bmpBack );
     
	 ::BitBlt( pDC->m_hDC, 1, 1, 100,100, hMemDC, 0,0, SRCPAINT  );
	 
	   ::DeleteDC( hMemDC );
*/
}

void CThingForm::DrawTextRect(CDC * pDC, LPCTSTR Str, RECT *R, COLORREF Col)
{
   static LOGFONT fs =
   {
	500, //Height
	   50,  // Width
	   10,  // Escape
	   0,	// Orientation
	   700, // Weight
	   FALSE,// Italic
	   FALSE,// UnderLine
	   FALSE,//StrikeOut
	   ANSI_CHARSET,//
	   OUT_CHARACTER_PRECIS,
	   CLIP_CHARACTER_PRECIS,
	   DEFAULT_QUALITY,
	   FIXED_PITCH,
	   _T("Courier New Cyr")
   };
   CFont Font;

   Font.CreateFontIndirect(&fs);
   pDC->SelectObject(&Font);
   pDC->SetBkMode(TRANSPARENT);
   pDC->SetTextColor(Col);
//	   pDC->TextOut(60,0, Str, strlen(Str));
   pDC->DrawText(Str, strlen(Str), R, DT_CENTER|DT_VCENTER|DT_NOCLIP|DT_SINGLELINE);
}

void CThingForm::OnUpdateDifEasy(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(World->GetDif()==dEASY);
}

void CThingForm::OnUpdateDifHard(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(World->GetDif()==dHARD);	
}

void CThingForm::OnDifEasy() 
{
   if(World->GetDif()!=dEASY)   ChangeDifficulty(dEASY);
}

void CThingForm::OnDifHard() 
{
   if(World->GetDif() != dHARD)  ChangeDifficulty(dHARD);
}

void CThingForm::ChangeDifficulty(DIFFICULTY Dif)
{
   World->SetDifficulty(Dif);

   if(World->State == gsPLAYING || World->State == gsPAUSE)
   {
	CLevelDlg LevelDlg;
	LevelDlg.DoModal();
	
	AfxGetApp()->m_pMainWnd->PostMessage(WM_LIFES_CHANGED, LIFE_INDICATOR, World->Life);
	AfxGetApp()->m_pMainWnd->PostMessage(WM_LIFES_CHANGED, SCORE_INDICATOR, World->Score);
	World->Start();
	Invalidate(TRUE);   
   }
}

void CThingForm::OnUpdateReplay(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(World->State == gsPLAYING || World->State == gsPAUSE);
}

void CThingForm::OnDifVeryHard() 
{
   if(World->GetDif() != dVERYHARD)
	   ChangeDifficulty(dVERYHARD);
}

void CThingForm::OnUpdateDifVHard(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(World->GetDif()==dVERYHARD);	
}

void CThingForm::OnUpdateStop(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(World->State != gsNONE);
}

void CThingForm::OnStop() 
{
   World->State = gsNONE;
   AfxGetApp()->m_pMainWnd->PostMessage(WM_LIFES_CHANGED, LIFE_INDICATOR, 0);
   AfxGetApp()->m_pMainWnd->PostMessage(WM_LIFES_CHANGED, SCORE_INDICATOR, 0);
   Invalidate(TRUE);
}

void CThingForm::OnUpdateCustomLevel1(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(World->GetDif()==dCUSTOM1);
}

void CThingForm::OnCustomLevel1() 
{
   if(World->GetDif() != dCUSTOM1)  ChangeDifficulty(dCUSTOM1);
}
