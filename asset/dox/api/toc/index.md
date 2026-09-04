# mulle-frame Library Documentation for AI
<!-- Keywords: frame, framebuffer, rasterization, geometry, bitmap, window, graphics -->

## 1. Introduction & Purpose

**mulle-frame** is a library that forms the conceptual and structural relationship between geometric drawing operations (provided by `mulle-geometry`) and bitmap representations (provided by `mulle-bitmap`). The library introduces the "frame" concept as it relates to the rasterization process—the transformation of drawing code into bitmaps. When drawing changes occur, the bitmap must be updated; this update is called a "frame". The bitmap that is drawn to is conventionally called a "framebuffer".

This library is designed to work within the MulleUI graphics stack but provides an abstract interface—it does not provide direct access to Operating System framebuffers. That responsibility belongs to the window libraries of MulleUI. Instead, **mulle-frame** provides data structures and utilities to manage frame information, window information, and conversions between geometric coordinate systems (floating-point) and pixel coordinate systems (integer).

**mulle-frame** is a component of the `mulle-gfx` library family and depends on both `mulle-geometry` and `mulle-bitmap`.

## 2. Key Concepts & Design Philosophy

### Core Concepts

1. **Frame vs. Framebuffer**: A "frame" represents a single rendering update cycle. The "framebuffer" is the bitmap memory that stores pixel data. The library distinguishes between:
   - **Window Frame**: The logical coordinate space of the window (using floating-point CGRect)
   - **Framebuffer Size**: The actual pixel dimensions of the framebuffer (using integer CGPixelSize)

2. **Coordinate System Bridging**: The library bridges between two coordinate systems:
   - **Geometric coordinates**: Floating-point coordinates from `mulle-geometry` (CGPoint, CGSize, CGRect)
   - **Pixel coordinates**: Integer coordinates from `mulle-bitmap` (CGPixelPoint, CGPixelSize, CGPixelRect)

3. **Window Information**: Encapsulates the relationship between window size, framebuffer size, pixel ratio, and UI scale. This allows proper handling of high-DPI displays where the framebuffer size may be larger than the window size.

4. **Frame Information**: Extends window information with additional rendering context like viewport, alpha, timing information (frame rates, timestamps), and debugging flags.

### Design Philosophy

- **Separation of Concerns**: Provides abstract frame concepts without implementation of actual framebuffer access
- **Type Safety**: Uses distinct types for floating-point geometry vs. integer pixels
- **Inline Efficiency**: Most operations are inline functions for zero-overhead abstractions
- **DPI Awareness**: Built-in support for high-DPI displays through pixel ratio calculations
- **Rendering Context**: Packages all necessary frame-related information into single structures

## 3. Core API & Data Structures

### 3.1. `CGBitmap+CGGeometry.h`

This header provides conversion functions between geometric types (floating-point) and pixel types (integer).

#### Conversion Functions: Point

- **`CGPointMakeWithPixelPoint(struct CGPixelPoint a)`**: Converts a pixel point (integer) to a CGPoint (floating-point). Simply casts integer coordinates to float.

- **`CGPixelPointMakeWithPoint(struct CGPoint a)`**: Converts a CGPoint (floating-point) to a pixel point (integer). Uses `roundf()` to round floating-point coordinates to nearest integer.

#### Conversion Functions: Size

- **`CGSizeMakeWithPixelSize(struct CGPixelSize a)`**: Converts a pixel size (integer) to a CGSize (floating-point).

- **`CGPixelSizeMakeWithSize(CGSize a)`**: Converts a CGSize (floating-point) to a pixel size (integer). Rounds dimensions to nearest integer.

#### Conversion Functions: Rect

- **`CGRectMakeWithPixelRect(struct CGPixelRect a)`**: Converts a pixel rect (integer) to a CGRect (floating-point).

- **`CGRectMakeWithPixelSize(struct CGPixelSize a)`**: Creates a CGRect at origin (0,0) with size from pixel size.

- **`CGPixelRectMakeWithRect(CGRect a)`**: Converts a CGRect (floating-point) to a pixel rect (integer). Rounds all components to nearest integer.

- **`CGPixelRectMakeWithSize(CGSize a)`**: Creates a pixel rect at origin (0,0) with size from CGSize, rounding dimensions.

- **`CGPixelRectMakeWithPixelSize(struct CGPixelSize a)`**: Creates a pixel rect at origin (0,0) with pixel size (no conversion needed).

### 3.2. `CGFrame.h`

This header defines the core frame and window information structures and their associated functions.

#### `enum CGFramebufferBitmapType`

Defines the types of framebuffer bitmaps that can be read:
- **`CGFramebufferRGBABytes`**: RGBA color data as bytes (8-bit per channel)
- **`CGFramebufferRGBAFloats`**: RGBA color data as floats (32-bit per channel)
- **`CGFramebufferStencilFloats`**: Stencil buffer data as floats
- **`CGFramebufferDepthFloats`**: Depth buffer data as floats

Note: Byte versions of stencil and depth buffers are commented out due to Nvidia/OpenGL compatibility issues.

#### `struct CGWindowInfo`

Encapsulates window and framebuffer relationship information.

- **Purpose**: Describes the window framebuffer currently being rendered/rasterized.
- **Key Fields**:
  - `CGRect frame`: Window coordinates frame (logical coordinate space)
  - `struct CGPixelSize framebufferSize`: Actual pixel dimensions (frame size × pixel ratio)
  - `CGVector UIScale`: UI scaling factor (separate x/y scale)
  - `CGFloat pixelRatio`: Ratio of framebuffer pixels to window coordinates (for high-DPI)

**Lifecycle Functions**:

- **`CGWindowInfoSFMakeVector(CGRect frame, struct CGPixelSize framebufferSize, CGVector scale)`**: Creates window info with separate x/y UI scale. Calculates pixel ratio automatically as framebufferSize.width / frame.size.width.

- **`CGWindowInfoSFMake(CGRect frame, struct CGPixelSize framebufferSize, CGFloat scale)`**: Creates window info with uniform scale (same for x and y).

- **`CGWindowInfoFBMake(struct CGPixelSize framebufferSize, CGFloat pixelRatio, CGFloat scale)`**: Creates window info when you only have framebuffer information. Calculates the window frame from framebuffer size and pixel ratio.

**Accessor Functions**:

- **`CGWindowInfoGetFrame(struct CGWindowInfo *info)`**: Returns the window frame rectangle. Returns CGRectZero if info is NULL.

- **`CGWindowInfoGetContentRect(struct CGWindowInfo *info)`**: Returns the content rectangle (frame at origin 0,0). Returns CGRectZero if info is NULL.

- **`CGWindowInfoGetFramebufferSize(struct CGWindowInfo *info)`**: Returns the framebuffer pixel size. Returns CGPixelSizeZero if info is NULL.

- **`CGWindowInfoGetUIScale(struct CGWindowInfo *info)`**: Returns the UI scale vector. Returns (1.0, 1.0) if info is NULL.

- **`CGWindowInfoGetPixelRatio(struct CGWindowInfo *info)`**: Returns the pixel ratio. Returns 1.0 if info is NULL.

- **`CGWindowInfoGetFrameOrigin(struct CGWindowInfo *info)`**: Returns the frame origin point.

- **`CGWindowInfoGetFrameSize(struct CGWindowInfo *info)`**: Returns the frame size.

**Comparison Functions**:

- **`CGWindowInfoEqualToWindowInfo(struct CGWindowInfo *a, struct CGWindowInfo *b)`**: Compares two CGWindowInfo structures for equality using memcmp. Both parameters must not be NULL.

#### `struct CGFrameInfo`

Extended frame information that includes window info plus rendering context.

- **Purpose**: Contains all information needed for a rendering frame.
- **Key Fields**:
  - `struct CGWindowInfo window`: The window information (see above)
  - `struct CGPixelRect viewportFrame`: Viewport rectangle in pixels (typically 0, 0, framebufferSize)
  - `float alpha`: Global alpha/transparency value (typically 1.0 for opaque)
  - `mulle_absolutetime_t now`: Current timestamp for the frame
  - `mulle_relativetime_t refreshRate`: Screen refresh rate (not the target frame rate)
  - `mulle_relativetime_t frameRate`: Target frame rate to achieve
  - `uintptr_t debuggingFlags`: Debugging flags (e.g., for nvgTrace in NanoVG)

**Lifecycle Functions**:

- **`CGFrameInfoMake(CGWindowInfo windowInfo, struct CGPixelRect viewportFrame, float alpha)`**: Creates frame info from window info, viewport, and alpha. Sets other fields to zero.

- **`CGFrameInfoSFMake(CGRect frame, struct CGPixelSize framebufferSize, CGFloat scale)`**: Convenience constructor when you have a window with a framebuffer. Creates viewport as (0, 0, framebufferSize), alpha as 1.0.

- **`CGFrameInfoFBMake(struct CGPixelSize framebufferSize, CGFloat pixelRatio, CGFloat scale)`**: Convenience constructor when you only have a framebuffer (no window). Creates viewport as (0, 0, framebufferSize), alpha as 1.0.

**Accessor Functions**:

- **`CGFrameInfoGetFrame(struct CGFrameInfo *info)`**: Returns the window frame. Returns CGRectZero if info is NULL.

- **`CGFrameInfoGetContentRect(struct CGFrameInfo *info)`**: Returns the window content rectangle. Returns CGRectZero if info is NULL.

- **`CGFrameInfoGetFrameSize(struct CGFrameInfo *info)`**: Returns the window frame size. Returns CGSizeZero if info is NULL.

- **`CGFrameInfoGetFramebufferSize(struct CGFrameInfo *info)`**: Returns the framebuffer pixel size. Returns CGPixelSizeZero if info is NULL.

**Comparison Functions**:

- **`CGFrameInfoEqualToFrameInfoInfo(struct CGFrameInfo *a, struct CGFrameInfo *b)`**: Compares two CGFrameInfo structures for equality using memcmp. Both parameters must not be NULL.

### 3.3. `mulle-frame.h`

Main library header that includes all public headers and provides version information.

#### Version Functions

- **`mulle_frame_get_version_major(void)`**: Returns the major version number (inline).

- **`mulle_frame_get_version_minor(void)`**: Returns the minor version number (inline).

- **`mulle_frame_get_version_patch(void)`**: Returns the patch version number (inline).

- **`mulle_frame_get_version(void)`**: Returns the full version as a packed uint32_t value.

**Version Constant**:
- **`MULLE__FRAME_VERSION`**: Packed version number as ((major << 20) | (minor << 8) | patch).

## 4. Performance Characteristics

### Conversion Functions
- **Time Complexity**: O(1) for all conversion functions
- **Space Complexity**: O(1), all operations are value-based with no allocation
- **Implementation**: All conversion functions are inline, resulting in zero function call overhead
- **Rounding**: Uses `roundf()` for float-to-integer conversions, which may have platform-dependent performance

### Structure Operations
- **Construction**: O(1), all constructors are inline and perform simple field assignments
- **Access**: O(1), all accessor functions are inline and perform direct field access
- **Comparison**: O(1), uses `memcmp()` for structure equality checks

### Memory Characteristics
- **`struct CGWindowInfo`**: Fixed size, contains 4 fields (2 structs, 1 vector, 1 float)
- **`struct CGFrameInfo`**: Fixed size, contains CGWindowInfo plus 5 additional fields
- **No Dynamic Allocation**: All structures are value types with no internal pointers or dynamic memory

### Thread Safety
- **Not Thread-Safe**: Structures contain no synchronization primitives
- **Immutable Pattern**: Structures are typically created and passed by value, supporting concurrent read access
- **External Synchronization**: If shared between threads, users must provide their own synchronization

## 5. AI Usage Recommendations & Patterns

### Best Practices

1. **Use Convenience Constructors**: Prefer `CGFrameInfoSFMake()` or `CGFrameInfoFBMake()` over `CGFrameInfoMake()` when possible. They set sensible defaults and reduce boilerplate.

2. **NULL Safety**: All accessor functions check for NULL and return zero/identity values. However, comparison functions require non-NULL arguments, so always validate before calling them.

3. **Rounding Convention**: The library uses `roundf()` for float-to-integer conversions. Be aware that this may differ from truncation or flooring in edge cases.

4. **DPI Awareness**: Always use `pixelRatio` when converting between window coordinates and framebuffer pixels. High-DPI displays have pixelRatio > 1.0.

5. **Pass by Value**: These structures are designed to be passed by value (copying is cheap). Only use pointers for accessor functions.

6. **Initialize Timing Fields**: If you need frame timing information, manually set the `now`, `refreshRate`, and `frameRate` fields after creating a CGFrameInfo structure.

### Common Pitfalls

1. **Don't Confuse Coordinate Systems**: CGRect uses floating-point coordinates; CGPixelRect uses integer coordinates. Always use conversion functions.

2. **Don't Ignore Pixel Ratio**: On Retina/high-DPI displays, framebufferSize will be larger than frame.size. The pixelRatio captures this relationship.

3. **Don't Manually Calculate Pixel Ratio**: Let the constructors calculate pixelRatio automatically from frame size and framebuffer size.

4. **Don't Assume Square Pixels**: While rare, UIScale allows for non-uniform x/y scaling. Use `CGWindowInfoSFMakeVector()` if you need this.

5. **Don't Use memcmp for Partial Comparisons**: The equality functions compare entire structures. If you need to compare specific fields, access them individually.

### Idiomatic Usage

1. **Frame Creation Pattern**: Create frame info at the start of a render cycle:
   ```c
   struct CGFrameInfo   frameInfo;
   
   frameInfo = CGFrameInfoSFMake( windowFrame, framebufferSize, 1.0);
   frameInfo.now         = mulle_absolutetime_now();
   frameInfo.frameRate   = 60.0; // target 60 FPS
   frameInfo.refreshRate = 60.0; // screen refresh rate
   ```

2. **Coordinate Conversion Pattern**: When converting user input (in window coordinates) to pixel coordinates:
   ```c
   CGPoint         mousePos;      // from window system
   CGPixelPoint    pixelPos;
   
   pixelPos = CGPixelPointMakeWithPoint( mousePos);
   ```

3. **DPI Handling Pattern**: When working with high-DPI displays:
   ```c
   struct CGPixelSize   framebufferSize;
   CGRect               windowFrame;
   CGFloat              pixelRatio;
   
   // framebufferSize and windowFrame from window system
   pixelRatio = framebufferSize.width / windowFrame.size.width;
   ```

## 6. Integration Examples

### Example 1: Creating Frame Info for Standard Display

```c
#include <mulle-frame/mulle-frame.h>

void   render_frame( void)
{
   CGRect                  windowFrame;
   struct CGPixelSize      framebufferSize;
   struct CGFrameInfo      frameInfo;
   
   // Get window dimensions (e.g., from windowing system)
   windowFrame       = CGRectMake( 100.0, 100.0, 800.0, 600.0);
   framebufferSize   = CGPixelSizeMake( 800, 600);
   
   // Create frame info with 1:1 pixel ratio (standard display)
   frameInfo = CGFrameInfoSFMake( windowFrame, framebufferSize, 1.0);
   
   // Set timing information
   frameInfo.now         = mulle_absolutetime_now();
   frameInfo.frameRate   = 60.0;
   frameInfo.refreshRate = 60.0;
   
   // Use frameInfo for rendering...
   printf( "Rendering frame at size %.0fx%.0f\n", 
           frameInfo.window.frame.size.width,
           frameInfo.window.frame.size.height);
}
```

### Example 2: Creating Frame Info for High-DPI Display

```c
#include <mulle-frame/mulle-frame.h>

void   render_retina_frame( void)
{
   CGRect                  windowFrame;
   struct CGPixelSize      framebufferSize;
   struct CGFrameInfo      frameInfo;
   CGFloat                 pixelRatio;
   
   // Window is 800x600 logical points
   windowFrame = CGRectMake( 0.0, 0.0, 800.0, 600.0);
   
   // Framebuffer is 1600x1200 pixels (2x Retina)
   framebufferSize = CGPixelSizeMake( 1600, 1200);
   
   // Create frame info - pixel ratio calculated automatically
   frameInfo = CGFrameInfoSFMake( windowFrame, framebufferSize, 1.0);
   
   // Verify pixel ratio
   pixelRatio = CGWindowInfoGetPixelRatio( &frameInfo.window);
   printf( "Pixel ratio: %.1f\n", pixelRatio); // Should print "2.0"
   
   // Use frameInfo for rendering...
}
```

### Example 3: Converting Mouse Coordinates to Pixel Coordinates

```c
#include <mulle-frame/mulle-frame.h>

void   handle_mouse_click( CGPoint mousePos, struct CGFrameInfo *frameInfo)
{
   struct CGPixelPoint   pixelPos;
   struct CGPixelSize    fbSize;
   
   // Convert floating-point mouse position to pixel coordinates
   pixelPos = CGPixelPointMakeWithPoint( mousePos);
   
   // Check if click is within framebuffer bounds
   fbSize = CGFrameInfoGetFramebufferSize( frameInfo);
   
   if( pixelPos.x >= 0 && pixelPos.x < fbSize.width &&
       pixelPos.y >= 0 && pixelPos.y < fbSize.height)
   {
      printf( "Click at pixel (%ld, %ld)\n", 
              (long) pixelPos.x, 
              (long) pixelPos.y);
   }
   else
   {
      printf( "Click outside framebuffer\n");
   }
}
```

### Example 4: Creating Frame Info from Framebuffer Only

```c
#include <mulle-frame/mulle-frame.h>

void   render_offscreen_buffer( void)
{
   struct CGPixelSize      bufferSize;
   struct CGFrameInfo      frameInfo;
   CGFloat                 pixelRatio;
   CGFloat                 scale;
   
   // Creating an offscreen buffer with no associated window
   bufferSize  = CGPixelSizeMake( 1024, 768);
   pixelRatio  = 1.0;  // 1:1 for offscreen buffer
   scale       = 1.0;
   
   // Create frame info from framebuffer dimensions only
   frameInfo = CGFrameInfoFBMake( bufferSize, pixelRatio, scale);
   
   // The window frame is calculated automatically
   printf( "Window frame: %.0fx%.0f\n",
           frameInfo.window.frame.size.width,
           frameInfo.window.frame.size.height); // Should be 1024.0x768.0
}
```

### Example 5: Comparing Frame Info for Changes

```c
#include <mulle-frame/mulle-frame.h>

int   check_if_window_changed( struct CGFrameInfo *oldInfo, 
                                struct CGFrameInfo *newInfo)
{
   struct CGWindowInfo   *oldWindow;
   struct CGWindowInfo   *newWindow;
   
   oldWindow = &oldInfo->window;
   newWindow = &newInfo->window;
   
   // Compare window info to detect resize events
   if( ! CGWindowInfoEqualToWindowInfo( oldWindow, newWindow))
   {
      printf( "Window changed!\n");
      printf( "Old size: %.0fx%.0f\n", 
              oldWindow->frame.size.width,
              oldWindow->frame.size.height);
      printf( "New size: %.0fx%.0f\n",
              newWindow->frame.size.width,
              newWindow->frame.size.height);
      return( 1);
   }
   
   return( 0);
}
```

### Example 6: Converting Between Coordinate Systems

```c
#include <mulle-frame/mulle-frame.h>

void   coordinate_conversion_example( void)
{
   CGRect                  logicalRect;
   struct CGPixelRect      pixelRect;
   CGRect                  backToLogical;
   
   // Start with logical coordinates (floating-point)
   logicalRect = CGRectMake( 10.5, 20.7, 100.3, 50.9);
   
   // Convert to pixel coordinates (rounded to integers)
   pixelRect = CGPixelRectMakeWithRect( logicalRect);
   printf( "Pixel rect: (%ld, %ld, %ld, %ld)\n",
           (long) pixelRect.origin.x,
           (long) pixelRect.origin.y,
           (long) pixelRect.size.width,
           (long) pixelRect.size.height); // (11, 21, 100, 51)
   
   // Convert back to logical coordinates
   backToLogical = CGRectMakeWithPixelRect( pixelRect);
   printf( "Back to logical: (%.0f, %.0f, %.0f, %.0f)\n",
           backToLogical.origin.x,
           backToLogical.origin.y,
           backToLogical.size.width,
           backToLogical.size.height); // (11, 21, 100, 51)
}
```

## 7. Dependencies

**mulle-frame** has the following direct dependencies:

- **mulle-geometry**: Provides geometric types (CGPoint, CGSize, CGRect, CGVector) and operations for coordinate-based calculations. This is the floating-point coordinate system side of the bridge.

- **mulle-bitmap**: Provides bitmap/pixel types (CGPixelPoint, CGPixelSize, CGPixelRect) and bitmap manipulation capabilities. This is the integer pixel coordinate system side of the bridge.

Both dependencies are essential to the library's purpose of bridging geometry and bitmap coordinate systems for frame-based rendering.
