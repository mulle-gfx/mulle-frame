#ifndef cg_bitmap_cg_geometry_h__
#define cg_bitmap_cg_geometry_h__

#include "include.h"

#include <math.h>


static inline CGPoint   CGPointMakeWithPixelPoint( struct CGPixelPoint a)
{
   return( CGPointMake( a.x, a.y));
}


static inline struct CGPixelPoint    CGPixelPointMakeWithPoint( struct CGPoint a)
{
   // TODO: check this: usually we truncate orgin and round size
   return( CGPixelPointMake( (NSInteger) roundf( a.x),
                             (NSInteger) roundf( a.y)));
}


static inline struct CGSize    CGSizeMakeWithPixelSize( struct CGPixelSize a)
{
   return( CGSizeMake( a.width, a.height));
}


static inline struct CGPixelSize    CGPixelSizeMakeWithSize(CGSize a)
{
   return( CGPixelSizeMake( (NSInteger) roundf( a.width),
                            (NSInteger) roundf( a.height)));  // round or floor ?
}


static inline CGRect   CGRectMakeWithPixelRect( struct CGPixelRect a)
{
   return( CGRectMake( a.origin.x, a.origin.y, a.size.width, a.size.height));
}


static inline CGRect   CGRectMakeWithPixelSize( struct CGPixelSize a)
{
   return( CGRectMake( 0, 0, a.width, a.height));
}


static inline struct CGPixelRect   CGPixelRectMakeWithRect( CGRect a)
{
   // TODO: check this: usually we truncate orgin and round size
   return( CGPixelRectMake( roundf( a.origin.x),
                            roundf( a.origin.y), 
                            roundf( a.size.width), 
                            roundf( a.size.height)));
}


static inline struct CGPixelRect   CGPixelRectMakeWithSize( CGSize a)
{
   return( CGPixelRectMake( 0,
                            0, 
                            roundf( a.width), 
                            roundf( a.height)));
}

static inline struct CGPixelRect   CGPixelRectMakeWithPixelSize( struct CGPixelSize a)
{
   return( CGPixelRectMake( 0,
                            0, 
                            a.width, 
                            a.height));
}


#endif

