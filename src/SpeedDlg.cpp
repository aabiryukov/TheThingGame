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

// SpeedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Thing.h"
#include "SpeedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define QTICS  100
/////////////////////////////////////////////////////////////////////////////
// CSpeedDlg dialog


CSpeedDlg::CSpeedDlg(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CSpeedDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSpeedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpeedDlg)
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpeedDlg, CDialog)
	//{{AFX_MSG_MAP(CSpeedDlg)
	ON_BN_CLICKED(IDC_DEF_BUTTON, OnDefButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpeedDlg message handlers

BOOL CSpeedDlg::OnInitDialog() 
{
   CDialog::OnInitDialog();
   
   m_Slider.SetRange(0, QTICS);
   m_Slider.SetPos((gameForm->TimeInterval-MINTIMEINTERVAL)*QTICS/(MAXTIMEINTERVAL-MINTIMEINTERVAL));
//   m_Slider.SetTicFreq(10);
   
   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CSpeedDlg::OnOK() 
{
	// TODO: Add extra validation here
	gameForm->TimeInterval = MINTIMEINTERVAL + (MAXTIMEINTERVAL-MINTIMEINTERVAL)*m_Slider.GetPos()/QTICS;
	CDialog::OnOK();
}

void CSpeedDlg::OnDefButton() 
{
   m_Slider.SetPos((DEFTIMEINTERVAL-MINTIMEINTERVAL)*QTICS/(MAXTIMEINTERVAL-MINTIMEINTERVAL));	
}
