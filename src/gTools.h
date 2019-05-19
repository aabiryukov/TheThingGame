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

#ifndef gTools_h_
#define gTools_h_
//---------------------------------------------------------------------------

class Cell;

struct QITEM
{
	Cell *data;
	QITEM *next;
};

class CCellQueue : public CObject
{
private:
	int FCount;
protected:
	QITEM  *Head, *Tail, *Current;

public:
	CCellQueue(void);
	~CCellQueue(void);

	void Add(Cell* cItem, BOOL toTail = TRUE);
	void Remove(Cell* cItem);
	void RemoveAt(int Index);

	int IndexOf(Cell* cItem);
	int GetCount(void) const;
	Cell* GetCellAt(int Index);
	
	void ToHead(void);
	Cell* GetNext(void);

	void MoveIntoHead(Cell* cItem);
	void MoveIntoTail(Cell* cItem);
};

#define random(_I) (rand()*_I/ RAND_MAX)

#endif
