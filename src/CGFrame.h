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

typedef struct CGFrameInfo
{
   CGSize                 size;             // window coordinates size
   struct CGBitmapSize    framebufferSize;  // actual pixels (frameSize * pixelRatio)
   struct CGBitmapRect    viewportFrame;    // used for the viewport (use: 0, 0, frameSize)
   CGVector               UIScale;
   CGFloat                pixelRatio;
   mulle_timeinterval_t   now;              // CAAbsoluteTime
} CGFrameInfo;


// this is a convenience constructor, it's not fully flexible
// use if you have a window with a framebuffer
static inline struct CGFrameInfo
   CGFrameInfoSFMake( CGSize size, struct CGBitmapSize framebufferSize, CGFloat scale)
{
   struct CGFrameInfo   info;

   memset( &info, 0, sizeof( info));

   info.size               = size;
   info.framebufferSize    = framebufferSize;
   info.viewportFrame.size = framebufferSize;
   info.UIScale            = CGVectorMake( scale, scale);
   // see: https://github.com/memononen/nanovg/blob/master/src/nanovg.h#L155
   info.pixelRatio         = framebufferSize.width / size.width;

   return( info);
}

// use if you have only a framebuffer
static inline struct CGFrameInfo
   CGFrameInfoFBMake( struct CGBitmapSize framebufferSize, CGFloat pixelRatio, CGFloat scale)
{
   struct CGFrameInfo   info;

   memset( &info, 0, sizeof( info));
   info.size               = CGSizeMake( framebufferSize.width * pixelRatio,
                                         framebufferSize.height * pixelRatio);
   info.framebufferSize    = framebufferSize;
   info.viewportFrame.size = framebufferSize;
   info.UIScale            = CGVectorMake( scale, scale);
   info.pixelRatio         = pixelRatio;

   return( info);
}

#endif
