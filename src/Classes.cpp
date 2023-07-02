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

#include "classes.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//---------------------------------------------------------------------------
LPCTSTR charObjects = _T("-TFORMGB");
CCellQueue Cell::qPerform;

BOOL Cell::bLastDead = FALSE;

HDC Cell::hDC = 0;
HDC MoveCell::hMemDC = 0;

#define ROCK_IMAGE_COUNT 4
BYTE RockResID[ROCK_IMAGE_COUNT] = { 3, 19, 20, 21 };

#define FRUIT_IMAGE_COUNT 1
BYTE FruitResID[FRUIT_IMAGE_COUNT] = { 2 };

#define MAN_IMAGE_COUNT 12//8
BYTE ManResID[MAN_IMAGE_COUNT] = { 11, 10, 11, 12,  14, 13, 14, 15,  17, 16, 17, 18 };

#define MONSTER_IMAGE_COUNT 4
BYTE MonsterResID[MONSTER_IMAGE_COUNT] = { 4, 6, 5, 6 };

#define BALL_IMAGE_COUNT 4
BYTE BallResID[BALL_IMAGE_COUNT] = { 8, 7, 9, 7 };

TWorld* Cell::World = NULL;
HIMAGELIST Cell::hImageList = NULL;

//---------------------------------------------------------------------------
void Cell::show(void)
{
	Paint();
}

void Cell::hide(void)
{
	ImageList_Draw(hImageList, ID - 2, hDC, LEFTBORDER + pixOffs.x, pixOffs.y, ILD_MASK);
}

void Cell::Paint(void)
{
	if (ID == EMPTY_ID) return;
	ImageList_Draw(hImageList, ID - 2, hDC, LEFTBORDER + pixOffs.x, pixOffs.y, ILD_NORMAL);
}

inline Cell* Cell::north(void)
{
	return (offset.y > 0) ? (World->cells[offset.y - 1][offset.x]) : this;
}

Cell* Cell::south(void)
{
	return (offset.y < ROWS - 1) ? (World->cells[offset.y + 1][offset.x]) : this;
}

Cell* Cell::west(void)
{
	return (offset.x > 0) ? (World->cells[offset.y][offset.x - 1]) : this;
}

Cell* Cell::east(void)
{
	return (offset.x < COLS - 1) ? (World->cells[offset.y][offset.x + 1]) : this;
}

Cell& Cell::WhatIn(BYTE aTrand)
{
	switch (aTrand)
	{
	case NORTH: return (offset.y > 0) ? *(World->cells[offset.y - 1][offset.x]) : *this;
	case SOUTH: return (offset.y < ROWS - 1) ? *(World->cells[offset.y + 1][offset.x]) : *this;
	case WEST: return (offset.x > 0) ? *(World->cells[offset.y][offset.x - 1]) : *this;
	case EAST: return (offset.x < COLS - 1) ? *(World->cells[offset.y][offset.x + 1]) : *this;
	default: return *this;
	}
}

BOOL Cell::TestAttr(WORD attr) const
{
	switch (ID)
	{
	case EMPTY_ID:
	case GROUND_ID:   return attr & (objMAIL);
	case OBSTACLE_ID: return attr & (objSTATIC);
	case FRUIT_ID:	   return attr & (objMAIL | objMOVABLE | objDANGER);
	case ROCK_ID:	   return attr & (objMOVABLE | objDANGER);
	case MONSTER_ID:  return attr & (objLIVING);
	case MAN_ID:	   return attr & (objLIVING);
	case BALL_ID:	   return attr & (objMOVABLE);
	}
	return FALSE;
}

//------------------- MoveCell Class (abstract) -------------------------

MoveCell::MoveCell(const CPoint& aCoord) : Cell(aCoord), curStep(TRUE),
image(0), trend(STOP), bMoving(FALSE)
{
	qPerform.Add(this);
	TimeForNext = 0;
}

MoveCell::~MoveCell(void)
{
	qPerform.Remove(this);
}

void MoveCell::Paint(void)
{
	ImageList_Draw(hImageList, (*ResID)[image], hDC, LEFTBORDER + pixOffs.x, pixOffs.y, ILD_NORMAL);
}

void MoveCell::show(void)
{
#ifdef SOFT_DRAW

	int x = LEFTBORDER + pixOffs.x - PICCOLS / 2,
		y = pixOffs.y - PICROWS / 2,
		dX = 0, dY = 0;

	BitBlt(hMemDC, 0, 0, PICCOLS * 2, PICROWS * 2, hDC, x, y, SRCCOPY);

	ImageList_Draw(hImageList, (*ResID)[image], hMemDC, PICCOLS / 2, PICROWS / 2, ILD_MASK);

	switch (trend)
	{
	case UP: pixOffs.y += dY = -speed; break;
	case DOWN: pixOffs.y += dY = speed; break;
	case LEFT: pixOffs.x += dX = -speed; break;
	case RIGHT: pixOffs.x += dX = speed;
	}

	if (TimeForNext == 0) ChangeImage();
	else TimeForNext--;
	ImageList_Draw(hImageList, (*ResID)[image], hMemDC, PICCOLS / 2 + dX, PICROWS / 2 + dY, ILD_TRANSPARENT);

	BitBlt(hDC, x, y, PICCOLS * 2, PICROWS * 2, hMemDC, 0, 0, SRCCOPY);

#else

	hide();

	switch (trend)
	{
	case UP: pixOffs.y -= speed; break;
	case DOWN: pixOffs.y += speed; break;
	case LEFT: pixOffs.x -= speed; break;
	case RIGHT: pixOffs.x += speed;
	}
	if (TimeForNext == 0) ChangeImage();
	else TimeForNext--;
	ImageList_Draw(hImageList, (*ResID)[image], hDC, LEFTBORDER + pixOffs.x, pixOffs.y, ILD_TRANSPARENT);

#endif
}

void MoveCell::hide(void)
{
	ImageList_Draw(hImageList, (*ResID)[image], hDC, LEFTBORDER + pixOffs.x, pixOffs.y, ILD_MASK);
}

void MoveCell::moveTo(CPoint aTo)
{
	if (CanMoveTo(aTo))
	{
		if (World->cells[aTo.y][aTo.x]->TestAttr(objMOVABLE | objLIVING) &&
			((MoveCell*)(World->cells[aTo.y][aTo.x]))->bMoving)
			World->cells[aTo.y][aTo.x]->WhatIn(trend).Reserved = NULL;
		World->cells[aTo.y][aTo.x]->Destroy();
		delete World->cells[aTo.y][aTo.x];
		World->cells[aTo.y][aTo.x] = World->cells[offset.y][offset.x];
		World->cells[offset.y][offset.x] = new Cell(offset);
		World->cells[offset.y][offset.x]->Reserved = Reserved;
		offset.x = aTo.x;
		offset.y = aTo.y;
		Reserved = NULL;
		bMoving = FALSE;
	}
	else bLastDead = TRUE;//trend = BYTE((trend+2<4) ? trend+2 : trend-2);
}

void MoveCell::move(void)
{
	switch (trend)
	{
	case NORTH:
		if (pixOffs.y % PICROWS == PICROWS / 2)
			moveTo(World->cells[offset.y - 1][offset.x]->offset);
		break;
	case SOUTH:
		if (pixOffs.y % PICROWS == PICROWS / 2)
			moveTo(World->cells[offset.y + 1][offset.x]->offset);
		break;
	case WEST:
		if (pixOffs.x % PICCOLS == PICCOLS / 2)
			moveTo(World->cells[offset.y][offset.x - 1]->offset);
		break;
	case EAST:
		if (pixOffs.x % PICCOLS == PICCOLS / 2)
			moveTo(World->cells[offset.y][offset.x + 1]->offset);
	}
	show();
}

//------------------- Rock Class ----------------------------------------

Rock::Rock(const CPoint& aCoord) : Fruit(aCoord)
{
	ID = ROCK_ID;
	ResID = (RESID)&RockResID;
	World->NumFruits--;
	wDownSnd = IDW_ROC1;
	image = (BYTE)random(ROCK_IMAGE_COUNT);
}

BOOL Rock::CanMoveTo(CPoint /*aTo*/)
{
	//  if( &POINT(aTo) != &POINT(offset) ) 
	return TRUE;
	//else return FALSE;
}

void Rock::ChangeImage(void)
{
	//  static bool isLeft = FALSE;
	TimeForNext = 2;
	switch (trend)
	{
	case LEFT:
		if (++image >= BALL_IMAGE_COUNT) image = 0;
		break;
	case RIGHT:
		if (image == 0) image = BALL_IMAGE_COUNT - 1;
		else image--;
	default:;
	}
}

void Rock::process(void)
{
	Cell* what;
	BYTE oldTrend;

	if (curStep != World->GlobStep) return;

	oldTrend = trend;
	Fruit::process();

	if (trend == oldTrend && trend == STOP)
	{
		static BYTE flag;

		if (offset.y >= ROWS - 2) return;
		flag = 0;

		what = west();
		if (what->ID == EMPTY_ID && what->Reserved == NULL)
		{
			what = what->south();
			if (what->ID == EMPTY_ID && what->Reserved == NULL)
				flag |= 1;
		}

		what = east();
		if (what->ID == EMPTY_ID && what->Reserved == NULL)
		{
			what = what->south();
			if (what->ID == EMPTY_ID && what->Reserved == NULL)
				flag |= 2;
		}

		switch (flag)
		{
		case 1: trend = WEST;
			break;
		case 2: trend = EAST;
			break;
		case 3: if (random(2)) trend = WEST;
			  else trend = EAST;
			break;
		default: return;
		}

		if (trend != STOP)
		{
			WhatIn(trend).Reserved = this;
			bMoving = TRUE;
			show();
		}
	}
}

//--------------------------------- Monster Class ------------------------------------------

BOOL Monster::CanMoveTo(CPoint aTo)
{
	if (!World->cells[aTo.y][aTo.x]->TestAttr(objDANGER)) return TRUE;
	else return FALSE;
}

inline BYTE inc4(BYTE aTrend, BYTE i)
{
	return (BYTE)(aTrend + i < 4 ? aTrend + i : aTrend + i - 4);
}

inline BYTE dec4(BYTE aTrend, BYTE i)
{
	return (BYTE)(aTrend - i >= 0 ? aTrend - i : aTrend - i + 4);
}

BYTE Monster::getWay(void)
{
	int manX = offset.x - World->atMan->offset.x, manY = offset.y - World->atMan->offset.y;
	BYTE flag = 0, best[4];

	if (abs(manX) + abs(manY) > 1)
	{
		if (WhatIn(trend).ID == EMPTY_ID) flag |= 0x1;
		if (WhatIn(inc4(trend, 1)).ID == EMPTY_ID) flag |= 0x2;
		if (WhatIn(dec4(trend, 1)).ID == EMPTY_ID) flag |= 0x4;
		if (WhatIn(inc4(trend, 2)).ID == EMPTY_ID) flag |= 0x8;
		BYTE resWay = STOP;
		switch (flag)
		{
		case 0x0: return STOP;
		case 0x1: resWay = trend;
			break;
		case 0x2: resWay = inc4(trend, 1);
			break;
		case 0x4: resWay = dec4(trend, 1);
			break;
		case 0x8: resWay = inc4(trend, 2);
		}
		if (resWay != STOP && (WhatIn(resWay).Reserved == NULL ||
			WhatIn(resWay).Reserved->ID == MAN_ID)) return resWay;
	}
	if (abs(manX) > abs(manY))
	{
		if (manX > 0) { best[0] = WEST; best[3] = EAST; }
		else { best[0] = EAST; best[3] = WEST; }

		if (manY > 0) { best[1] = NORTH; best[2] = SOUTH; }
		else { best[1] = SOUTH; best[2] = NORTH; }
	}
	else
	{
		if (manY > 0) { best[0] = NORTH; best[3] = SOUTH; }
		else { best[0] = SOUTH; best[3] = NORTH; }

		if (manX > 0) { best[1] = WEST; best[2] = EAST; }
		else { best[1] = EAST; best[2] = WEST; }
	}

	BYTE i = NORTH;
	while (i <= WEST)
	{
		Cell& what = WhatIn(best[i]);

		if (!(what.ID == MAN_ID && World->atMan->trend == best[i] &&
			what.north()->TestAttr(objMOVABLE)))
			if (what.ID == EMPTY_ID || what.ID == MAN_ID)
				if (best[i] != inc4(trend, 2))
					if (what.Reserved == NULL ||
						what.Reserved->ID == MAN_ID) break;
		i++;
	}
	if (i < 4) return best[i];
	else return STOP; // return inc4(trend,2);
}

void Monster::process(void)
{
	if (curStep != World->GlobStep) return;
	else curStep = !curStep;

	if (random(501) == 0)
		if (random(2) == 0) World->Sound(IDW_MON2);
		else  World->Sound(IDW_MON3);

	if (pixOffs.x % PICCOLS || pixOffs.y % PICROWS) move();
	else
	{
		bool IsWay = TRUE;
		switch (getWay())
		{
		case NORTH:
			trend = NORTH;
			show();
			break;
		case SOUTH:
			trend = SOUTH;
			show();
			break;
		case WEST:
			trend = WEST;
			show();
			break;
		case EAST:
			trend = EAST;
			show();
			break;
		default:
			IsWay = FALSE;
		}
		if (IsWay)
		{
			WhatIn(trend).Reserved = this;
			bMoving = TRUE;
		}
	}
}

void Monster::ChangeImage(void)
{
	if (random(20) == 0)
		if (++image >= MONSTER_IMAGE_COUNT) image = 0;
}

//Monster::~Monster(void)
void Monster::Destroy(void)
{
	if (World->State == gsPLAYING)
	{
		World->Sound(IDW_MON1);
		World->Score += 2;
		//-   GameBox->DisplayStatus();
		WhatIn(trend).Reserved = NULL;
		bMoving = TRUE;
		hide();
	}
}

// ------------------ Man Class -----------------------------------------

void Man::ChangeImage(void)
{
	TimeForNext = MAN_IMAGE_TIME;
	image++;
	switch (trend)
	{
	case WEST: if (image == 4) image = 0;
			 else if (image > 4) image = 1;
		break;
	case EAST: if (image == 8) image = 4;
			 else if (image > 8 || image < 4) image = 5;
		break;
	default: if (image <= MAN_IMAGE_COUNT - 4) image = MAN_IMAGE_COUNT - 3;
		   else if (image >= MAN_IMAGE_COUNT) image = MAN_IMAGE_COUNT - 4;
	}
}

BOOL Man::CanMoveTo(CPoint aTo)
{
	if (World->cells[aTo.y][aTo.x]->TestAttr(objMAIL)) return TRUE;
	else return FALSE;
}

void Man::process(void)
{
	if (curStep != World->GlobStep) return;
	else curStep = !curStep;

	Cell* what;

	if (trend == STOP)
	{
		if (!World->KeyDown) return;
		switch (World->KeyDown)
		{
		case VK_UP:     // UP
			what = north();
			if (what->TestAttr(objMAIL) ||
				what->ShiftTo(NORTH))
			{
				trend = NORTH;
				show();
			}
			break;
		case VK_DOWN:     // DOWN
			what = south();
			if (what->TestAttr(objMAIL) ||
				what->ShiftTo(SOUTH))
			{
				trend = SOUTH;
				show();
			}
			break;
		case VK_LEFT:     // LEFT
			what = west();
			if (what->TestAttr(objMAIL) ||
				what->ShiftTo(WEST))
			{
				trend = WEST;
				show();
			}
			break;
		case VK_RIGHT:     // RIGHT
			what = east();
			if (what->TestAttr(objMAIL) ||
				what->ShiftTo(EAST))
			{
				trend = EAST;
				show();
			}
		} // end of switch(keyDown)
		if (trend != STOP)
		{
			WhatIn(trend).Reserved = this;
			bMoving = TRUE;
		}
	}
	else
	{
		move();
		if (!(pixOffs.x % PICCOLS || pixOffs.y % PICROWS)) trend = STOP;
	}
}

// Man::~Man(void)
void Man::Destroy(void)
{
	if (World->State == gsPLAYING)
	{
		World->ManIsLive = FALSE;
		//    PlaySound( "MAN1", NULL, SND_RESOURCE|SND_ASYNC );
		World->Sound(IDW_MAN1);
	}
}

//-------------  Fruit Class --------------------------------------------

// Fruit::~Fruit(void)
void Fruit::Destroy(void)
{
	if (World->State == gsPLAYING)
	{
		//	PlaySound( "FRU1", NULL, SND_RESOURCE|SND_ASYNC );
		World->Sound(IDW_FRU1);
		hide();
		World->NumFruits--;
		World->Score++;
		//-    GameBox->DisplayStatus();
	}
	//  QueueRemove();
}

BOOL Fruit::ShiftTo(BYTE aTrend)
{
	Cell& target = WhatIn(aTrend);

	if (&target == this || trend != STOP) return FALSE;

	if (target.ID == EMPTY_ID)
		if (target.Reserved == NULL)
		{
			qPerform.MoveIntoHead(this);
			target.Reserved = this;
			bMoving = TRUE;
		}
		else return FALSE;
	else
	{
		qPerform.MoveIntoHead(this);
		if (!target.ShiftTo(aTrend)) return FALSE;
	}
	trend = aTrend;
	speed = MANSPEED;
	move();

	curStep = !World->GlobStep;

	return TRUE;
}

void Fruit::process(void)
{
	Cell* what;

	if (curStep != World->GlobStep) return;
	else curStep = !curStep;
	switch (trend)
	{
	case NORTH:
	case WEST:
	case EAST:
		move();
		if (!(pixOffs.x % PICCOLS || pixOffs.y % PICROWS))
		{
			trend = STOP;
			speed = ROCKSPEED;
		}
		break;
	case SOUTH:
		if (!(pixOffs.y % PICROWS))  trend = STOP;
		else
		{
			if (pixOffs.y % PICROWS == PICROWS / 2)
			{
				//                 if( World->cells[offset.y+1][offset.x]->Reserved == MONSTER_ID ||
				//                     World->cells[offset.y+1][offset.x]->Reserved == MAN_ID ) break;
				moveTo(World->cells[offset.y + 1][offset.x]->offset);
			}
			show();
			break;
		}
	case STOP:
		what = south();
		if (what == this) break;

		if (fly)
		{
			if (what->ID == EMPTY_ID || what->TestAttr(objLIVING))
			{
				if (what->Reserved == NULL || what->Reserved->TestAttr(objLIVING))
				{
					trend = DOWN;
					fly = TRUE;
				}
			}
			else
			{
				World->Sound(wDownSnd);
				show();
				fly = FALSE;
			}
		}
		else
			if (what->ID == EMPTY_ID && (what->Reserved == NULL || what->Reserved->ID == MONSTER_ID))
			{
				trend = DOWN;
				fly = TRUE;
			}
		if (trend != STOP)
		{
			WhatIn(trend).Reserved = this;
			bMoving = TRUE;
			show();
		}

	} // End of switch( trend )
}

// ------------ Ball Class ----------------------------------------------
Ball::Ball(const CPoint& aCoord) : Rock(aCoord)
{
	ID = BALL_ID;
	ResID = (RESID)&BallResID;
	speed = BALLSPEED;
	image = (BYTE)random(BALL_IMAGE_COUNT);
	TimeForNext = BALL_IMAGE_TIME;
}

// Ball::~Ball(void)
void Ball::Destroy(void)
{
	if (World->State == gsPLAYING)
	{
		World->Sound(IDW_BALL1);
		hide();
	}
}

BOOL Ball::CanMoveTo(CPoint aTo)
{
	if (World->cells[aTo.y][aTo.x]->ID == EMPTY_ID) return TRUE;
	else return FALSE;
}

void Ball::ChangeImage(void)
{
	TimeForNext = BALL_IMAGE_TIME;
	if (++image >= BALL_IMAGE_COUNT) image = 0;
}

void Ball::process(void)
{
	if (curStep != World->GlobStep) return;
	else curStep = !curStep;

	switch (trend)
	{
	case SOUTH:
	case WEST:
	case EAST:
		move();
		if (!(pixOffs.x % PICCOLS || pixOffs.y % PICROWS))
		{
			trend = STOP;
			//speed = ROCKSPEED;
		}
		break;

	case NORTH:
		if (!(pixOffs.y % PICROWS))  trend = STOP;
		else
		{
			if (pixOffs.y % PICROWS == PICROWS / 2)
			{
				//               if( World->cells[offset.y-1][offset.x]->Reserved != EMPTY_ID ) break;
				moveTo(World->cells[offset.y - 1][offset.x]->offset);
			}
			show();
			break;
		}

	case STOP:
		Cell* what;
		what = north();
		if (what == this)
		{
			bLastDead = TRUE;
			return;
		}

		if (what->ID == EMPTY_ID && what->Reserved == NULL)
		{
			what->Reserved = this;
			fly = TRUE;
			trend = UP;
			show();
		}
		else
			if (fly)
			{
				//                 PlaySound( "ROC1", NULL, SND_RESOURCE|SND_ASYNC );
				show();
				fly = FALSE;
			}
			else
			{
				static BYTE flag;
				//static Cell* what;

				if (offset.y == 0) return;
				flag = 0;

				what = west();
				if (what->ID == EMPTY_ID && what->Reserved == NULL)
				{
					what = what->north();
					if (what->ID == EMPTY_ID && what->Reserved == NULL)
						flag |= 1;
				}

				what = east();
				if (what->ID == EMPTY_ID && what->Reserved == NULL)
				{
					what = what->north();
					if (what->ID == EMPTY_ID && what->Reserved == NULL)
						flag |= 2;
				}

				switch (flag)
				{
				case 1: trend = WEST;
					break;
				case 2: trend = EAST;
					break;
				case 3: if (random(2)) trend = WEST;
					  else trend = EAST;
					break;
				default: return;
				}
				WhatIn(trend).Reserved = this;
				bMoving = TRUE;
				show();
			}
	} // End of switch( trend )
}

