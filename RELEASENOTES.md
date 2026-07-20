### 0.7.56


feature: add central include headers and frame debugging flags

* introduce central public and private include headers (src/generic/include.h, src/generic/include-private.h) to simplify and standardize project includes
* extend CGFrameInfo with a debuggingFlags field to carry per-frame debug flags (**BREAKING**: changes struct layout/ABI)
* add comprehensive library documentation (asset/dox/TOC.md) and register it in clib.json




* add refreshRate und frameRate to CGFrameInfo
