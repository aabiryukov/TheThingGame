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

//---------------------------------------------------------------------------
#ifndef World_h_
#define World_h_
//---------------------------------------------------------------------------
#include "const.h"
#include "Labirint.h"

class Cell;
class Man;

typedef enum{ prDone, prReplay, prComplete, prNextLevel, prDead } TProcResult;
typedef enum{ gsNONE, gsPLAYING, gsPAUSE, gsOVER, gsFINAL} GAMESTATE;
typedef enum{ dEASY, dHARD, dVERYHARD, dCUSTOM1} DIFFICULTY;

class TWorld
{
private:
   HWND WndHandle;
   
public:
   CSize SetSize(CSize w);
   DIFFICULTY GetDif(void) const	{return Difficulty;}
   void SetDifficulty(DIFFICULTY Dif);
   GAMESTATE State;
   Cell* cells[ROWS][COLS];
   BYTE Level;
   BYTE Life;
   WORD Score;
   WORD NumFruits;
   UINT KeyDown;
   BOOL GlobStep, ManIsLive, IsSound;
   Man* atMan;
   
   TWorld( HWND hWnd );
   ~TWorld( void );
   
   TProcResult Process( void );
   void Init( void );
   void Paint( HDC aDC );
   void Start( void );
   void Sound( WORD NameID );

protected:
   LEVELSTYPE* pLevels;
   DIFFICULTY Difficulty;
   WORD wCellWidth, wCellHeight;
};

#endif
