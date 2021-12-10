# mulle-framebuffer

#### 💺 mulle-framebuffer combines mulle-geometry with mulle-bitmap

The process of transforming drawing code into bitmaps is called "rasterization".
Whenever the drawing changes, the bitmap has to be updated. This update is
called a "frame". The bitmap is conventionally called "framebuffer".

This is the relationship between  mulle-geometry and mulle-bitmap.



## mulle-sde

This is a [mulle-sde](//github.com/mulle-sde) project. mulle-sde combines
recursive package management with cross-platform builds via **cmake**:

Action  | Command                               | Description
--------|---------------------------------------|---------------
Build   | `mulle-sde craft [--release|--debug]` | Builds into local `kitchen` folder
Add     | `mulle-sde dependency add --c --github <|GITHUB_USER|> mulle_framebuffer` | Add mulle_framebuffer to another mulle-sde project as a dependency
Install | `mulle-sde install --prefix /usr/local https://github.com/<|GITHUB_USER|>/mulle_framebuffer.git` | Like `make install`


### Manual Installation


Install the requirements:

Requirements                                      | Description
--------------------------------------------------|-----------------------
[some-requirement](//github.com/some/requirement) | Some requirement

Install into `/usr/local`:

```
mkdir build 2> /dev/null
(
   cd build ;
   cmake -DCMAKE_INSTALL_PREFIX=/usr/local \
         -DCMAKE_PREFIX_PATH=/usr/local \
         -DCMAKE_BUILD_TYPE=Release .. ;
   make install
)
```


<!--
extension : mulle-sde/sde
directory : demo/library
template  : .../README.md
Suppress this comment with `export MULLE_SDE_GENERATE_FILE_COMMENTS=NO`
-->
