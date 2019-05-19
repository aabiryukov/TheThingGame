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

#ifndef const_H_
#define const_H_
//---------------------------------------------------------------------------

#define ROWS		14       // Quantity of rows (Y)
#define COLS		20       // Quantity of columns (X)
// #define IMAGES         6

#define PICROWS		32       // Size of row (Y) in pixels
#define PICCOLS		32       // Size of column (X) in pixels
#define PICSIZE		PICROWS*PICCOLS

#define LEFTBORDER     0 //PICCOLS
#define RIGHTBORDER    LEFTBORDER

#define WORLDHEIGHT	ROWS*PICROWS
#define WORLDWIDTH	COLS*PICCOLS + LEFTBORDER + RIGHTBORDER

/*
#define MINTIMEINTERVAL 10000
#define MAXTIMEINTERVAL 70000
#define DEFTIMEINTERVAL 50000
*/

#define MINTIMEINTERVAL 4
#define MAXTIMEINTERVAL 30
#define DEFTIMEINTERVAL 16

#define FIRST_RES_CELL_NUM	20
#define FIRST_RES_NUM	51
#define LIFES_MAX		10

// #define QIMAGES      19  // Number of source images + masks
#define SRCIMAGES		22  // Number of source images

// ID numbers of Objects image
#define EMPTY_ID		1   // ! No Change it !
#define GROUND_ID		2
#define OBSTACLE_ID	3
#define FRUIT_ID		4
#define ROCK_ID		5
#define MONSTER_ID	6
#define MAN_ID		7
#define BALL_ID	      8
#define LAST_ID	      8


// Image symbol in laberinth array
#define EMPTY      	'-'
#define MAN        	'T'
#define FRUIT     	'F'
#define OBSTACLE  	'O'
#define ROCK      	'R'
#define MONSTER   	'M'
#define GROUND    	'G'
#define BALL    		'B'

#define WIN			1
#define DEAD		2

// Trend of object
#define UP			 0   // ! Do not replace THIS !
#define RIGHT		 1
#define DOWN		 2
#define LEFT		 3
#define STOP		 4

#define NORTH		0
#define EAST		1
#define SOUTH		2
#define WEST		3

#define ROCKSPEED		8
#define MANSPEED		4
#define BALLSPEED		2

#define BALL_IMAGE_TIME 10
#define MAN_IMAGE_TIME	3

// Object characteristics (attributes)
#define objSTATIC		0x1   // this object present in one place of all time of the game
#define objMOVABLE	0x2   // this object can be moving
#define objLIVING		0x4   // this object moving by self
#define objMAIL		0x8   // this object is mail for man
#define objDANGER		0x10  // this object is dangerous for all living objects

#define White	0x00FFFFFF
#define Black	0x00000000
#define Gray	0x00808080
#define Red		0x000000FF
#define Yellow	0x0000FFFF
#define Green	0x0000FF00
#define Cyan	0x00FFFF00
#define Blue	0x00FF0000
#define Magenta	0x00FF00FF

//-------- Source definitions -----
//#define USE_REGION  // Use regions in the program
//#define SOFT_DRAW     // Hi quality of image drawing, but it slowly

//---------------------------------------------------------------------------
#endif
