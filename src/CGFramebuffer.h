#ifndef cg_framebuffer_h__
#define cg_framebuffer_h__

#include "include.h"

#include <stdint.h>


enum CGFramebufferBitmapType
{
   CGFramebufferRGBABytes,
   CGFramebufferRGBAFloats,
//   CGFramebufferStencilBytes,   // Nvidia/GL crashes when you try GL_UNSIGNED as return type
   CGFramebufferStencilFloats,
   // CGFramebufferDepthBytes,  // Nvidia/GL crashes when you try GL_UNSIGNED as return type
   CGFramebufferDepthFloats
};

typedef uintptr_t  CGFramebufferBitmapType;


#endif
