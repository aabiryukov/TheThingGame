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

#include <stdafx.h>
#include "gTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CCellQueue::CCellQueue(void): Head(NULL), Tail(NULL), Current(NULL), FCount(0)
{
}

CCellQueue::~CCellQueue(void)
{
	QITEM *p,*p1;

	for(p=Head; p!=NULL;)
	{
		p1 = p;
		p = p->next;
		delete p1;
	}
}

void CCellQueue::Add(Cell* cItem, BOOL toTail)
{
   if(FCount)
   {
	if(toTail)
	{
	   Tail->next = new QITEM;
	   Tail = Tail->next;
	   Tail->next = NULL;
	   Tail->data = cItem;
	}
	else
	{
	   QITEM *p;
	   
	   p = new QITEM;
	   p->next = Head;
	   p->data = cItem;
	   Head = p;
	}
   }
   else
   {
	Head = new QITEM;
	Head->data = cItem;
	Current = Tail = Head;
   }
   FCount++;
}

void CCellQueue::Remove(Cell* cItem)
{
   QITEM *p,*p1 = NULL;
   
   if(!FCount || cItem == NULL) return;
   
   for(p=Head; p->data!=cItem && p!=NULL; p=p->next) p1 = p;

   if(p != NULL)
   {
	if( p == Current && FCount > 1 )
	   if(p == Head) Current = Head->next;
	   else Current = p1;

	if(p == Head)
	   if(FCount == 1)
	   {
		Head = NULL;
		Tail = NULL;
		Current = NULL;
	   }
	   else
	   {
		Head = Head->next;
	   }
	else 
	   if(p == Tail)
	   {
		Tail = p1;
		Tail->next = NULL;
	   }
	   else
	   {
		p1->next = p->next;
	   }

      delete p;
	FCount--;
   }
}

void CCellQueue::RemoveAt(int Index)
{
   Remove(GetCellAt(Index));
}

int CCellQueue::IndexOf(Cell* cItem)
{
   if(cItem == NULL) return -1;

   int i = 0;
   QITEM* p = Head;
   for(; p->data!=cItem && p!=NULL; p=p->next) i++;

   if(p) return i;
   else return -1;
}

int CCellQueue::GetCount(void) const
{
   return FCount;
}

Cell* CCellQueue::GetCellAt(int Index)
{
   if(Index >= FCount) return NULL;

   int i = 0;
   QITEM* p=Head;
   for(; i<Index; i++) p = p->next;

   return p->data;
}

void CCellQueue::ToHead(void)
{
   Current = Head;
}

Cell* CCellQueue::GetNext(void)
{
   if(Current == NULL) return NULL;
   
   Cell *c = Current->data;
   Current = Current->next;

   return c;
}

void CCellQueue::MoveIntoHead(Cell* cItem)
{
   if(Head->data != cItem)
   {
	Remove(cItem);
	Add(cItem, FALSE);
   }
}

void CCellQueue::MoveIntoTail(Cell* cItem)
{
   if(Tail->data != cItem)
   {
	Remove(cItem);
	Add(cItem);
   }
}


