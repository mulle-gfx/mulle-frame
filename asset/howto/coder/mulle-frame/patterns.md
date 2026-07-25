<!-- Keywords: coordinate-conversion, constructor, framebuffer, timing, viewport -->
# Patterns

## Coordinate conversion (CGBitmap+CGGeometry)

Convert user input or drawing output between coordinate systems:

```c
CGPoint         mousePos = CGPointMake(10.5, 20.3);
CGPixelPoint    pixelPos = CGPixelPointMakeWithPoint(mousePos);
// (NSInteger) roundf(10.5) = 11, roundf(20.3) = 20
```

Round-trip a rect:

```c
CGRect              logical = CGRectMake(10.5, 20.7, 100.3, 50.9);
CGPixelRect         pixels  = CGPixelRectMakeWithRect(logical);
CGRect              back    = CGRectMakeWithPixelRect(pixels);
```

`CGPixelRectMakeWithSize` and `CGRectMakeWithPixelSize` create zero-origin rects from a size — useful for viewport setup.

All conversions use `roundf()` — both origin and size are rounded (see `src/CGBitmap+CGGeometry.h:18-19`).

## Window info construction (CGWindowInfo)

Three constructors handle the common cases (see `src/CGFrame.h:73-110`):

| Constructor | When to use |
|-------------|-------------|
| `CGWindowInfoSFMake(frame, fbSize, scale)` | You have a window frame and framebuffer. Uniform scale. |
| `CGWindowInfoSFMakeVector(frame, fbSize, scaleVector)` | Non-uniform x/y UI scale. |
| `CGWindowInfoFBMake(fbSize, pixelRatio, scale)` | Only a framebuffer (offscreen rendering). Frame is derived from `fbSize × pixelRatio`. |

`pixelRatio` is auto-calculated as `framebufferSize.width / frame.size.width` in the SF variants. Do not set it manually.

## Frame info construction (CGFrameInfo)

Extend window info with rendering context (see `src/CGFrame.h:167-216`):

```c
// From window + framebuffer
CGFrameInfo   info = CGFrameInfoSFMake(windowFrame, framebufferSize, 1.0);

// Offscreen: framebuffer only
CGFrameInfo   info = CGFrameInfoFBMake(bufferSize, 1.0, 1.0);

// Manual: full control
CGFrameInfo   info = CGFrameInfoMake(windowInfo, viewportRect, alpha);
```

After construction, set per-frame fields:

```c
info.now         = mulle_absolutetime_now();
info.frameRate   = 60.0;   // target frame rate
info.refreshRate = 60.0;   // screen refresh rate
info.alpha       = 1.0f;   // global alpha
```

## Accessor safety

All `CGWindowInfoGet*` and `CGFrameInfoGet*` accessors accept NULL and return zero/identity values. Use them instead of direct field access when the pointer might be null (see `src/CGFrame.h:113-124`).

## Framebuffer bitmap types

```c
enum CGFramebufferBitmapType type = CGFramebufferRGBABytes;
```

Available types: `CGFramebufferRGBABytes`, `CGFramebufferRGBAFloats`, `CGFramebufferStencilFloats`, `CGFramebufferDepthFloats`. Byte variants of stencil and depth are excluded due to Nvidia/OpenGL crashes (see `src/CGFrame.h:46-49`).

## Equality comparison

```c
if (CGWindowInfoEqualToWindowInfo(&old, &new))
   // framebuffer or frame unchanged
```

Both pointers are asserted non-NULL. Use individual field access for partial comparison.
