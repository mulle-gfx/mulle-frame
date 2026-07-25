<!-- Keywords: rounding, null-safety, pixel-ratio, equality, breaking-change, nvidia -->
# Quirks & invariants

## Coordinate conversion

- **All float-to-integer conversions use `roundf()`**, not truncation. Both origin and size components are rounded (see `src/CGBitmap+CGGeometry.h:18-19`). The source code has a TODO noting this may differ from Apple's convention (truncate origin, round size).
- **Conversions are lossy**. `CGRect → CGPixelRect → CGRect` can change values by up to 0.5 due to rounding. Do not round-trip for identity comparison.

## CGWindowInfo

- **`pixelRatio` is automatically derived** as `framebufferSize.width / frame.size.width` in the `SFMake` constructors. If the framebuffer is not exactly `frameSize × pixelRatio`, this ratio is wrong — provide explicit `pixelRatio` via `FBMake` instead.
- **`FBMake` inverts the relationship**: it derives the window frame from `framebufferSize × pixelRatio`, not the other way around. Use only when you have no window.

## CGFrameInfo

- **Timing fields start at zero**. `CGFrameInfoMake` and convenience constructors set `now`, `refreshRate`, `frameRate`, and `debuggingFlags` to 0. You must set them manually each frame.
- **`debuggingFlags` was added in 0.7.56** — this is a **breaking ABI change** (see RELEASENOTES.md). Struct layout changed. Ensure all linked code is compiled against the same version.
- **viewportFrame is not auto-derived from framebufferSize** — you must supply it explicitly in `CGFrameInfoMake`. Convenience constructors set it to `(0, 0, framebufferSize)`.

## Equality functions

- **Both pointers are asserted non-NULL** via `assert()`. Passing NULL triggers undefined behavior in debug builds. Use accessor functions if the pointer may be null.
- **`memcmp` compares padding bytes** — structs must be zero-initialized or fully assigned for reliable equality. Use `memset(&info, 0, sizeof(info))` before field assignment (as the constructors do, see `src/CGFrame.h:78`).

## Framebuffer bitmap types

- **Byte-based stencil and depth types are commented out** (`CGFramebufferStencilBytes`, `CGFramebufferDepthBytes`) due to Nvidia/OpenGL driver crashes (see `src/CGFrame.h:46-49`). Prefer the `Floats` variants.

## Thread safety

- **Structures contain no synchronization.** They are safe for concurrent read access when immutable. Do not mutate a `CGWindowInfo` or `CGFrameInfo` shared between threads without external locking.
