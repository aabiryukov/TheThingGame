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

// LevelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Thing.h"
#include "ThingForm.h"
#include "LevelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLevelDlg dialog


CLevelDlg::CLevelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLevelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLevelDlg)
	//}}AFX_DATA_INIT
}


void CLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLevelDlg)
	DDX_Control(pDX, IDC_NUMER, m_numImg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLevelDlg, CDialog)
	//{{AFX_MSG_MAP(CLevelDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLevelDlg message handlers

BOOL CLevelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	if(gameForm == NULL) return FALSE;
	HBITMAP hBitmap = ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(FIRST_RES_NUM+gameForm->World->Level));
//	DWORD dw = ::GetLastError();
	m_numImg.SetBitmap(hBitmap);
//	if(hBitmap != NULL) CloseHandle(hBitmap);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
