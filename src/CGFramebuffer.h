#ifndef cg_framebuffer_h__
#define cg_framebuffer_h__

#include "include.h"


enum CGFramebufferBitmapType
{
   CGFramebufferRGBABytes,
   CGFramebufferRGBAFloats,
//   CGFramebufferStencilBytes,   // Nvidia/GL crashes when you try GL_UNSIGNED as return type
   CGFramebufferStencilFloats,
   // CGFramebufferDepthBytes,  // Nvidia/GL crashes when you try GL_UNSIGNED as return type
   CGFramebufferDepthFloats
};



struct CGFramebufferBitmap
{
   void                     *bytes;
   struct mulle_allocator   *allocator;
   struct CGBitmapInfo      info;
};


static inline  void   CGFramebufferBitmapInit( struct CGFramebufferBitmap *p,
                                               void *bytes,
                                               struct CGBitmapInfo info,
                                               struct mulle_allocator *allocator)
{
   if( ! p)
      return;

   p->bytes     = bytes;
   p->info      = info;
   p->allocator = allocator; // if NULL no free
}


static inline void   CGFramebufferBitmapDone( struct CGFramebufferBitmap *p)
{
   if( p && p->allocator)
      mulle_allocator_free( p->allocator, p->bytes);
}


#endif
