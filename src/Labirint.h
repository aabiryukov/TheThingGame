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

#ifndef labirintH
#define labirintH
//---------------------------------------------------------------------------
#include "const.h"

#define QLEVELS 6

typedef char LEVELSTYPE[QLEVELS][ROWS][COLS];
extern LEVELSTYPE EasyLevels, HardLevels, VeryHardLevels, lev_CustomLevels_1;

#endif
 