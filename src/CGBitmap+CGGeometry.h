#ifndef cg_bitmap_cg_geometry_h__
#define cg_bitmap_cg_geometry_h__

#include "include.h"

#include <math.h>


static inline CGPoint   CGPointMakeWithIntegerPoint( struct MulleIntegerPoint a)
{
   return( CGPointMake( a.x, a.y));
}

static inline struct MulleIntegerPoint    MulleIntegerPointMakeWithPoint( struct CGPoint a)
{
   return( MulleIntegerPointMake( (NSInteger)roundf( a.x), 
                                  (NSInteger) roundf( a.y)));
}


static inline struct CGSize    CGSizeMakeWithIntegerSize( struct MulleIntegerSize a)
{
   return( CGSizeMake( a.width, a.height));
}

static inline struct MulleIntegerSize    MulleIntegerSizeMakeWithSize(CGSize a)
{
   return( MulleIntegerSizeMake( (NSInteger) roundf( a.width), 
                                 (NSInteger) roundf( a.height)));  // round or floor ?
}


static inline CGRect   CGRectMakeWithIntegerRect( struct MulleIntegerRect a)
{
   return( CGRectMake( a.origin.x, a.origin.y, a.size.width, a.size.height));
}


static inline CGRect   CGRectMakeWithIntegerSize( struct MulleIntegerSize a)
{
   return( CGRectMake( 0, 0, a.width, a.height));
}


static inline struct MulleIntegerRect   MulleIntegerRectMakeWithRect( CGRect a)
{
   return( MulleIntegerRectMake( roundf( a.origin.x), 
                                 roundf( a.origin.y), 
                                 roundf( a.size.width), 
                                 roundf( a.size.height)));
}


static inline struct MulleIntegerRect   MulleIntegerRectMakeWithSize( CGSize a)
{
   return( MulleIntegerRectMake( 0, 
                                 0, 
                                 roundf( a.width), 
                                 roundf( a.height)));
}

#endif

