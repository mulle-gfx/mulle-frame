//
//  CGFrame.c
//  mulle_framebuffer
//
//  Copyright (c) 2021 Nat! - Mulle kybernetiK.
//  Copyright (c) 2021 Codeon GmbH.
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
#ifndef cgframe_h__
#define cgframe_h__

#include "include.h"



// A frame describes the "frame" that is currently being rendered/rasterized.
// The render destination is a framebuffer of "framebufferSize".
// The size is the size of the drawing into the frameBuffer, this can be
// a floating point value. So the drawing could have a different scale.

typedef struct CGWindowInfo
{
   CGRect                 frame;            // window coordinates frame
   struct CGBitmapSize    framebufferSize;  // actual pixels (frameSize * pixelRatio)
   CGVector               UIScale;
   CGFloat                pixelRatio;
} CGWindowInfo;



static inline struct CGWindowInfo
   CGWindowInfoSFMakeVector( CGRect frame, struct CGBitmapSize framebufferSize, CGVector scale)
{
   struct CGWindowInfo   info;

   memset( &info, 0, sizeof( info));

   info.frame             = frame;
   info.framebufferSize   = framebufferSize;
   info.UIScale           = scale;
   // see: https://github.com/memononen/nanovg/blob/master/src/nanovg.h#L155
   info.pixelRatio        = framebufferSize.width / frame.size.width;

   return( info);
}

static inline struct CGWindowInfo
   CGWindowInfoSFMake( CGRect frame, struct CGBitmapSize framebufferSize, CGFloat scale)
{
   return( CGWindowInfoSFMakeVector( frame, framebufferSize, CGVectorMake( scale, scale)));
}


static inline struct CGWindowInfo
   CGWindowInfoFBMake( struct CGBitmapSize framebufferSize, CGFloat pixelRatio, CGFloat scale)
{
   struct CGWindowInfo   info;

   memset( &info, 0, sizeof( info));

   info.frame.size         = CGSizeMake( framebufferSize.width * pixelRatio,
                                         framebufferSize.height * pixelRatio);
   info.framebufferSize    = framebufferSize;
   info.UIScale            = CGVectorMake( scale, scale);
   info.pixelRatio         = pixelRatio;

   return( info);
}


static inline CGRect   CGWindowInfoGetFrame( struct CGWindowInfo *info)
{
   return( info ? info->frame : CGRectZero);
}


static inline struct CGBitmapSize   CGWindowInfoGetFramebufferSize( struct CGWindowInfo *info)
{
   return( info ? info->framebufferSize : CGBitmapSizeZero);
}


static inline struct CGVector   CGWindowInfoGetUIScale( struct CGWindowInfo *info)
{
   return( info ? info->UIScale : CGVectorMake( 1.0f, 1.0f));
}


static inline CGFloat   CGWindowInfoGetPixelRatio( struct CGWindowInfo *info)
{
   return( info ? info->pixelRatio : 1.0f);
}


static inline CGPoint   CGWindowInfoGetFrameOrigin( struct CGWindowInfo *info)
{
   return( CGWindowInfoGetFrame( info).origin);
}


static inline CGSize   CGWindowInfoGetFrameSize( struct CGWindowInfo *info)
{
   return( CGWindowInfoGetFrame( info).size);
}


static inline int   CGWindowInfoEqualToWindowInfo( struct CGWindowInfo *a, struct CGWindowInfo *b)
{
   assert( a);
   assert( b);

   return( ! memcmp( a, b, sizeof( struct CGWindowInfo)));
}


typedef struct CGFrameInfo
{
   struct CGWindowInfo    window;
   struct CGBitmapRect    viewportFrame;    // used for the viewport (use: 0, 0, frameSize)
   CGFloat                alpha;            // set to 1.0
   mulle_absolutetime_t   now;              // mulle_absolutetime_t
} CGFrameInfo;


static inline struct CGFrameInfo
   CGFrameInfoMake( CGWindowInfo windowInfo, struct CGBitmapRect viewportFrame, CGFloat alpha)
{
   struct CGFrameInfo   info;

   memset( &info, 0, sizeof( info));

   info.window        = windowInfo;
   info.viewportFrame = viewportFrame;
   info.alpha         = alpha;

   return( info);
}


// this is a convenience constructor, it's not fully flexible
// use if you have a window with a framebuffer
static inline struct CGFrameInfo
   CGFrameInfoSFMake( CGRect frame, struct CGBitmapSize framebufferSize, CGFloat scale)
{
   return( CGFrameInfoMake( CGWindowInfoSFMake( frame, framebufferSize, scale),
                            CGBitmapRectMake( 0, 0, framebufferSize.width, framebufferSize.height),
                            1.0));
}
// use if you have only a framebuffer
static inline struct CGFrameInfo
   CGFrameInfoFBMake( struct CGBitmapSize framebufferSize, CGFloat pixelRatio, CGFloat scale)
{
   return( CGFrameInfoMake( CGWindowInfoFBMake( framebufferSize, pixelRatio, scale),
                            CGBitmapRectMake( 0, 0, framebufferSize.width, framebufferSize.height),
                            1.0));
}


static inline CGRect   CGFrameInfoGetFrame( struct CGFrameInfo *info)
{
   if( ! info)
     return( CGRectZero);
   return( CGWindowInfoGetFrame( &info->window));
}


static inline CGSize   CGFrameInfoGetFrameSize( struct CGFrameInfo *info)
{
   if( ! info)
     return( CGSizeZero);
   return( CGWindowInfoGetFrameSize( &info->window));
}



static inline int   CGFrameInfoEqualToFrameInfoInfo( struct CGFrameInfo *a, struct CGFrameInfo *b)
{
   assert( a);
   assert( b);

   return( ! memcmp( a, b, sizeof( struct CGFrameInfo)));
}

#endif
