<!-- Keywords: coordinate-conversion, framebuffer, rasterization, window-info, frame-info, viewport, pixel-ratio -->
# mulle-frame: Frame management and coordinate conversion for rasterization

Use this topic when writing code that bridges geometric drawing coordinates (floating-point) with pixel framebuffer coordinates (integer), or when managing per-frame rendering context (viewport, alpha, timing).

## Understand first

```bash
mulle-sde api cat CGFrame.h
mulle-sde api cat CGBitmap+CGGeometry.h
mulle-sde api apropos CGFrame
mulle-sde api apropos CGWindowInfo
```

## Local references

| Path | Purpose |
|------|---------|
| `src/CGBitmap+CGGeometry.h` | Coordinate conversion between CG* (float) and CGPixel* (integer) types |
| `src/CGFrame.h` | `CGWindowInfo`, `CGFrameInfo` structs and `CGFramebufferBitmapType` enum |
| `src/mulle-frame.h` | Umbrella header, version macros |
| `asset/dox/TOC.md` | Full API reference with examples |

## API families

| Family | Header | Role |
|--------|--------|------|
| Coordinate conversion | `CGBitmap+CGGeometry.h` | Convert between `CGPoint`/`CGSize`/`CGRect` (float) and `CGPixelPoint`/`CGPixelSize`/`CGPixelRect` (integer) |
| Window info | `CGFrame.h` | `CGWindowInfo` — describes window ↔ framebuffer relationship with `pixelRatio` and `UIScale` |
| Frame info | `CGFrame.h` | `CGFrameInfo` — extends window info with viewport, alpha, timing, debugging flags |
| Framebuffer types | `CGFrame.h` | `CGFramebufferBitmapType` — enum for reading back pixel data (RGBA, stencil, depth) |

## Primary workflow

1. Obtain window frame (`CGRect`) and framebuffer size (`CGPixelSize`) from the windowing system.
2. Create `CGWindowInfo` with one of the `CGWindowInfo*Make` constructors.
3. Optionally promote to `CGFrameInfo` with `CGFrameInfoMake` or convenience constructors.
4. Use coordinate conversion functions from `CGBitmap+CGGeometry.h` to convert user input / drawing coordinates.
5. Set timing fields (`now`, `frameRate`, `refreshRate`) on `CGFrameInfo` each frame.

## Verify

```bash
mulle-sde test      # run library tests
```
