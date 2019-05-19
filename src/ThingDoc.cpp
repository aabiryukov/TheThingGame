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

// ThingDoc.cpp : implementation of the CThingDoc class
//

#include "stdafx.h"
#include "Thing.h"

#include "ThingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThingDoc

IMPLEMENT_DYNCREATE(CThingDoc, CDocument)

BEGIN_MESSAGE_MAP(CThingDoc, CDocument)
	//{{AFX_MSG_MAP(CThingDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThingDoc construction/destruction

CThingDoc::CThingDoc()
{
	// TODO: add one-time construction code here

}

CThingDoc::~CThingDoc()
{
}

BOOL CThingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	SetTitle("");

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CThingDoc serialization

void CThingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CThingDoc diagnostics

#ifdef _DEBUG
void CThingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CThingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThingDoc commands
