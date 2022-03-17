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


#endif
