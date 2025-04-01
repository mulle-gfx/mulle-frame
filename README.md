# mulle-frame

#### 💺 mulle-frame combines mulle-geometry with mulle-bitmap


# mulle-frame

#### 💺 mulle-frame combines mulle-geometry with mulle-bitmap

The process of transforming drawing code into bitmaps is called "rasterization".
Whenever the drawing changes, the bitmap has to be updated. This update is
called a "frame". The bitmap is conventionally called "framebuffer".

In MulleUI you don't have direct access to the framebuffer, as its on the
GPU (usually), but you can read pixels from it.

This library forms the relationship between mulle-geometry and mulle-bitmap.





| Release Version                                       | Release Notes
|-------------------------------------------------------|--------------
| ![Mulle kybernetiK tag](https://img.shields.io/github/tag/mulle-gfx/mulle-frame.svg?branch=release) [![Build Status](https://github.com/mulle-gfx/mulle-frame/workflows/CI/badge.svg?branch=release)](//github.com/mulle-gfx/mulle-frame/actions) | [RELEASENOTES](RELEASENOTES.md) |






### You are here

![Overview](overview.dot.svg)





## Add

**This project is a component of the [mulle-core](//github.com/mulle-core/mulle-core) library. As such you usually will *not* add or install it
individually, unless you specifically do not want to link against
`mulle-core`.**


### Add as an individual component

Use [mulle-sde](//github.com/mulle-sde) to add mulle-frame to your project:

``` sh
mulle-sde add github:mulle-gfx/mulle-frame
```

To only add the sources of mulle-frame with dependency
sources use [clib](https://github.com/clibs/clib):


``` sh
clib install --out src/mulle-gfx mulle-gfx/mulle-frame
```

Add `-isystem src/mulle-gfx` to your `CFLAGS` and compile all the sources that were downloaded with your project.


## Install

### Install with mulle-sde

Use [mulle-sde](//github.com/mulle-sde) to build and install mulle-frame and all dependencies:

``` sh
mulle-sde install --prefix /usr/local \
   https://github.com/mulle-gfx/mulle-frame/archive/latest.tar.gz
```

### Manual Installation

Install the requirements:

| Requirements                                 | Description
|----------------------------------------------|-----------------------
| [mulle-geometry](https://github.com/MulleUI/mulle-geometry)             | 
| [mulle-bitmap](https://github.com/MulleUI/mulle-bitmap)             | 

Install **mulle-frame** into `/usr/local` with [cmake](https://cmake.org):

``` sh
cmake -B build \
      -DCMAKE_INSTALL_PREFIX=/usr/local \
      -DCMAKE_PREFIX_PATH=/usr/local \
      -DCMAKE_BUILD_TYPE=Release &&
cmake --build build --config Release &&
cmake --install build --config Release
```


## Author

[Nat!](https://mulle-kybernetik.com/weblog) for Mulle kybernetiK  



