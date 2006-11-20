//
//  DarkBox.m
//  OsiriX
//
//  Created by Lance Pysher on 11/20/06.

/*=========================================================================
  Program:   OsiriX

  Copyright (c) OsiriX Team
  All rights reserved.
  Distributed under GNU - GPL
  
  See http://homepage.mac.com/rossetantoine/osirix/copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.
=========================================================================*/

#import "DarkBox.h"


@implementation DarkBox

- (void)drawRect:(NSRect)rect{
	NSColor *backgroundColor = [NSColor  colorWithCalibratedRed:0.5 green:0.5 blue:0.5 alpha:0.25];
	[backgroundColor setFill];	
	[NSBezierPath fillRect:rect];
	[super drawRect:rect];

}

@end
