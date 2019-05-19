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

#include "stdafx.h"
#include "mmsystem.h"

#include "World.h"
#include "Classes.h"
#include "Labirint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Resource.h"

//---------------------------------------------------------------------------
TWorld::TWorld( HWND hWnd ) : State(gsNONE), IsSound(TRUE), WndHandle(hWnd)
{
//   HBITMAP hBitmap;
	
   PlaySound( MAKEINTRESOURCE(IDW_MUS), NULL, SND_RESOURCE|SND_ASYNC );
   Difficulty = dEASY;
   pLevels = &EasyLevels;
   wCellHeight = PICROWS;
   wCellWidth = PICCOLS;

   Cell::World = this;
   Init();

   SetSize(CSize(0,0));

   cells[0][0] = NULL;
}
//---------------------------------------------------------------------------
TWorld::~TWorld( void )
{
//   for( int i=1; i<=LAST_ID; i++) delete Images[i];
   State = gsNONE;
   if( cells[0][0] != NULL )
   {
     Cell::hDC = GetDC( WndHandle );
     for(unsigned row = 0; row<ROWS; row++)
       for(WORD col = 0; col<COLS; col++)
           delete cells[row][col];
     ReleaseDC( WndHandle, Cell::hDC );      
   }
   if( Cell::hImageList ) ImageList_Destroy( Cell::hImageList );
}
//---------------------------------------------------------------------------
void TWorld::Init( void )
{
   Level = 0;
   Life = LIFES_MAX;
   Score = 0;
   NumFruits = 0;
//   State = gsNONE;
   KeyDown = 0;
   GlobStep = TRUE;
}
//---------------------------------------------------------------------------
void TWorld::Start( void )
{
  State = gsPAUSE;
  Cell::hDC = GetDC( WndHandle );

  if( cells[0][0] != NULL )
    for(WORD row = 0; row<ROWS; row++)
      for(WORD col = 0; col<COLS; col++)
          delete cells[row][col];
//  cells[0][0] = NULL;
  NumFruits = 0;
  KeyDown = 0;

  for(WORD row = 0; row<ROWS; row++)
   for(WORD col = 0; col<COLS; col++)
     switch( (*pLevels)[Level][row][col] )
     {
     case  EMPTY    : cells[row][col] = new Cell(CPoint(col,row));
                      break;
     case  MAN      : cells[row][col] = new Man(CPoint(col,row));
                      break;
     case  FRUIT    : cells[row][col] = new Fruit(CPoint(col,row));
                      break;
     case  OBSTACLE : cells[row][col] = new Obstacle(CPoint(col,row));
                      break;
     case  ROCK     : cells[row][col] = new Rock(CPoint(col,row));
                      break;
     case  BALL     : cells[row][col] = new Ball(CPoint(col,row));
                      break;
     case  MONSTER  : cells[row][col] = new Monster(CPoint(col,row));
                      break;
     case  GROUND   : cells[row][col] = new Ground(CPoint(col,row));
			    break;
     default : TRACE("Invalid char '%c' in labirinth (Row=%i,Column=%i)\n", (*pLevels)[Level][row][col], row, col );
     } // end of switch( level[][] )

  State = gsPLAYING;
  ReleaseDC( WndHandle, Cell::hDC );
}
//---------------------------------------------------------------------------
TProcResult TWorld::Process( void )
{
  if( NumFruits == 0 )
    if( Level == QLEVELS-1 )
	{
		State = gsFINAL;
		return prComplete;
	}
    else
    {
	  State = gsPAUSE;
      Level++;
      return prNextLevel;
    }

    Cell::hDC = ::GetDC( WndHandle );

#ifdef SOFT_DRAW
    MoveCell::hMemDC = ::CreateCompatibleDC(Cell::hDC);
    HBITMAP Bmp = ::CreateCompatibleBitmap(Cell::hDC, PICCOLS*2, PICROWS*2);
    SelectObject(MoveCell::hMemDC, Bmp);
#endif
/*
  for( WORD row = 0; row < ROWS; row++ )
    for( WORD col = 0; col < COLS; col++ )
       cells[row][col] -> process();
*/
//  POSITION qPos = Cell::qPerform.GetHeadPosition();


//  while( qPos != NULL)
  Cell::qPerform.ToHead();
  for(Cell* p = Cell::qPerform.GetNext(); p != NULL;  p = Cell::qPerform.GetNext())
  {
     p->process();
     if(Cell::bLastDead)
     {
	  CPoint offs = p->offset;
	  p->Destroy();
	  delete p;
	  cells[offs.y][offs.x] = new Cell(offs);
	  Cell::bLastDead = FALSE;
     }
  };

#ifdef SOFT_DRAW
  ::DeleteDC(MoveCell::hMemDC);
  ::DeleteObject(Bmp);
#endif

  ::ReleaseDC( WndHandle, Cell::hDC );
  GlobStep = !GlobStep;
  if(ManIsLive) return prDone;
  else
  {
	if(--Life <= 0) State = gsOVER;
	return prDead;
  }
}
//---------------------------------------------------------------------------
void TWorld::Paint( HDC aDC )
{
  if( cells[0][0] == NULL ) return;

  Cell::hDC = aDC;//GetDC( WndHandle );

  for(WORD row = 0; row<ROWS; row++)
     for(WORD col = 0; col<COLS; col++) cells[row][col]->Paint();

//-  ReleaseDC( WndHandle, Cell::hDC );
}
//---------------------------------------------------------------------------
void TWorld::Sound( WORD NameID )
{
  if( IsSound && State == gsPLAYING ) 
  {
	  PlaySound( MAKEINTRESOURCE(NameID), NULL, SND_RESOURCE|SND_ASYNC );
  }
}
//---------------------------------------------------------------------------

void TWorld::SetDifficulty(DIFFICULTY Dif)
{
   if(Difficulty == Dif) return;

   //State = gsNONE;
   Difficulty = Dif;
   switch(Difficulty)
   {
   case dEASY : pLevels = &EasyLevels;
		    break;
   case dHARD : pLevels = &HardLevels;
		    break;
   case dVERYHARD : pLevels = &VeryHardLevels;
		    break;
   case dCUSTOM1 : pLevels = &lev_CustomLevels_1;
		    break;
   }
   Init();
}
//---------------------------------------------------------------------------

CSize TWorld::SetSize(CSize w)
{
   HBITMAP hSrcBmp;

   if(Cell::hImageList) ImageList_Destroy(Cell::hImageList);
   Cell::hImageList = ImageList_Create( wCellWidth, wCellHeight, ILC_COLOR8|ILC_MASK, SRCIMAGES, 0);

   for( BYTE i=FIRST_RES_CELL_NUM; i<FIRST_RES_CELL_NUM+SRCIMAGES; i++ )
   {
	hSrcBmp = ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(i));
	ImageList_AddMasked(Cell::hImageList, hSrcBmp, Black );
	::DeleteObject(hSrcBmp);
   }

   return w;
}
