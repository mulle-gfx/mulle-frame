//
//  CGBitmap+CGGeometry.h
//  mulle-frame
//
//  Copyright (c) 2021 Nat! - Mulle kybernetiK.
//  All rights reserved.
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.
//
//  Neither the name of Mulle kybernetiK nor the names of its contributors
//  may be used to endorse or promote products derived from this software
//  without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
//
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

