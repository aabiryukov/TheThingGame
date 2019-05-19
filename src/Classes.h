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

#ifndef classes_h_
#define classes_h_
//---------------------------------------------------------------------------
// #include <vcl\Classes.hpp>

#include "const.h"
#include "World.h"
#include "gTools.h"
#include "resource.h"
//---------------------------------------------------------------------------

extern BYTE RockResID[];
extern BYTE FruitResID[];
extern BYTE ManResID[];
extern BYTE MonsterResID[];
extern BYTE BallResID[];

typedef BYTE (*RESID)[];

class Cell
{
   // protected:   // Protected Methods
   //  void   assignCellAt(const CPoint& aCoord, Cell* aCell);
public:
   BYTE ID;
   Cell *Reserved;
   CPoint pixOffs;
   static  HDC hDC;
   static TWorld* World;
   static HIMAGELIST hImageList;
   static CCellQueue qPerform;
   static BOOL bLastDead;
   
   CPoint offset;
   
   Cell(const CPoint& aCoord)
   {
	offset = aCoord;
	ID = EMPTY_ID;
	pixOffs.x = offset.x*PICCOLS;
	pixOffs.y = offset.y*PICROWS;
	Reserved = NULL;
	// show();
   }
   virtual void Destroy(void){}
   virtual ~Cell(void){}
   
   // Public Methods
   Cell* north( void );
   Cell* south( void );
   Cell* east( void );
   Cell* west( void );
   
   BOOL TestAttr(WORD attr) const;
   
   Cell& WhatIn( BYTE aTrend );
   virtual BOOL ShiftTo( BYTE /*aTrend*/){return FALSE;}
   
   // Display methods
   virtual void show(void);  // Show Cell
   virtual void Paint( void );
   virtual void hide(void);  // Hide Cell
   virtual void process(void){} // Process of Cell
};

//---------------------------------------------------------------------------
class MoveCell: public Cell // abstract class
{
protected:
   BOOL curStep,
	  bMoving;
   BYTE speed,
	image;   // current cell image
   RESID ResID;
   signed char TimeForNext;
   //  TResID (*ResID)[];
   
   void moveTo( CPoint to ); // Move this object to the "to" coord of Labirinth
   void move( void );		// Move Cell Image
   virtual BOOL CanMoveTo( CPoint /*aTo*/ ) { return TRUE; }  // Return true if Cell can move to "aTo"
   
public:
   static  HDC hMemDC;
   BYTE trend;
   
   MoveCell( const CPoint& aCoord );
   virtual ~MoveCell(void);
   
   virtual void show( void );
   virtual void Paint( void );
   virtual void hide( void );
   virtual void ChangeImage( void ){}
};

//---------------------------------------------------------------------------

class Monster: public MoveCell
{
private:
   BYTE getWay(void);   // Return Monster way trend
   virtual BOOL CanMoveTo( CPoint aTo );
   
public:
   Monster(const CPoint& aCoord): MoveCell(aCoord)
   {
	ID = MONSTER_ID;
	//   image = 0;// MONSTER_ID;
	trend = NORTH;
	speed = MANSPEED;
	ResID = &MonsterResID;
   }
   
   //  virtual ~Monster(void);
   virtual void Destroy(void);
   virtual void process(void);
   virtual void ChangeImage( void );
};

class Man: public MoveCell
{
private:
   virtual BOOL CanMoveTo( CPoint aTo );
   
public:
   Man(const CPoint& aCoord): MoveCell(aCoord)
   {
	ID = MAN_ID;
	//   image = 0; // MAN_ID;
	World->atMan = this;
	World->ManIsLive = true;
	speed = MANSPEED;
	ResID = &ManResID;
	TimeForNext = MAN_IMAGE_TIME;
   }
   //  virtual ~Man(void);
   virtual void Destroy(void);
   virtual void process(void);
   virtual void ChangeImage( void );
};

class Fruit: public MoveCell
{
protected:
   bool fly;     // true if Fruit moving
   WORD wDownSnd;
   
public:
   //  static WORD NumFruits;
   
   Fruit(const CPoint& aCoord): MoveCell(aCoord), fly(FALSE)
   {
	ID = FRUIT_ID;
	World->NumFruits++;
	ResID = &FruitResID;
	speed = ROCKSPEED;
	wDownSnd = IDW_FRUDOWN;
   }
   virtual void Destroy(void);
   //  virtual ~Fruit(void){}
   virtual BOOL ShiftTo( BYTE aTrend );
   virtual void process( void );
};

//---------------------------------------------------------------------------

class Rock: public Fruit
{
protected:
   virtual BOOL CanMoveTo( CPoint /*aTo*/ );  // Return true if Cell can move to "aTo"
   
public:
   Rock( const CPoint& aCoord );
   
   //  virtual ~Rock(void){}
   //  virtual __fastcall void Paint( HDC hDC, HDC hMemDC );
   virtual void process( void );
   virtual void ChangeImage( void );
};

//---------------------------------------------------------------------------

class Obstacle: public Cell
{
public:
   
   Obstacle(const CPoint& aCoord): Cell(aCoord)
   {
	ID = OBSTACLE_ID;
	//   show();
   }
   //  virtual ~Obstacle(void){}
};

class Ground: public Cell
{
public:
   Ground(const CPoint& aCoord): Cell(aCoord)
   {
	ID = GROUND_ID;
   }
   //  virtual ~Ground(void)
   virtual void Destroy(void)
   { if(World->State == gsPLAYING) hide(); }
};

//---------------------------------------------------------------------------

class Ball: public Rock
{
protected:
   virtual BOOL CanMoveTo( CPoint aTo );  // Return true if Cell can move to "aTo"
   
public:
   Ball( const CPoint& aCoord );
   
   //	virtual ~Ball(void);
   virtual void Destroy(void);
   virtual void process( void );
   virtual void ChangeImage( void );
   //  bool ShiftTo( BYTE aTrend );
};

//---------------------------------------------------------------------------

#endif
