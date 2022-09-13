#ifndef cg_bitmap_cg_geometry_h__
#define cg_bitmap_cg_geometry_h__

#include "include.h"

#include <math.h>


static inline struct CGSize    MulleIntegerSizeGetSize( struct MulleIntegerSize a)
{
   return( CGSizeMake( a.width, a.height));
}

static inline struct MulleIntegerSize    CGSizeGetIntegerSize(CGSize a)
{
   return( MulleIntegerSizeMake( roundf( a.width), roundf( a.height)));  // round or floor ?
}

static inline CGPoint   MulleIntegerPointGetPoint( struct MulleIntegerPoint a)
{
   return( CGPointMake( a.x, a.y));
}


static inline struct MulleIntegerPoint    CGPointGetIntegerPoint( struct CGPoint a)
{
   return( MulleIntegerPointMake( (NSInteger) a.x, (NSInteger) a.y));
}

static inline CGRect   MulleIntegerRectGetRect( struct MulleIntegerRect a)
{
   return( CGRectMake( a.origin.x, a.origin.y, a.size.width, a.size.height));
}


#endif

