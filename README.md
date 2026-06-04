<p align="center">
*This project has been created as part of the 42 curriculum by cwenhaj and vnaoussi..*
</p>

# <h1 align="center">*miniRT*</h1>

### Description

**miniRT** is a ray tracer written in C using the MiniLibX graphical library. The goal of the project is to **implement the fundamental concepts behind physically-based image generation and to understand how modern rendering engines simulate light interactions in a three-dimensional scene.**

Unlike traditional Rasterization techniques used in most real-time graphics engines (no simulation of light rays. Triangles instead), Raytracing simulates the physical behavior of light. It computes the path of light rays from the camera through each pixel and determines how they interact with objects in the scene. This approach produces realistic lighting effects such as shadows, reflections, and accurate visibility calculations.

The project supports parsing scene description files (.rt) and rendering them in real time inside a graphical window.

### Mandatory Features

- Scene file parser (.rt) 
# Light and camera
- Ambient lighting
- Point light source
- Diffuse lighting (Lambert model)
- Hard shadows
- Camera with configurable FOV
# Geometric Objects
- Sphere primitive
- Plane primitive
- Cylinder primitive
# Mathematics
- Object transformations
-   * Translation
-   * Rotation (when applicable)
- Proper handling of object intersections
# Miscellenous
- Error management and scene validation
- Window management with MiniLibX

### Bonus Features

The project includes all requested bonus features:

# Phong Reflection Model

Implementation of specular highlights using the Phong illumination model, allowing shiny surfaces to realistically reflect light sources.

# Checkerboard Pattern

Procedural checkerboard texture generation without image files.

# Multiple Colored Lights

Support for multiple light sources with independent colors and intensities.

# Cone Primitive

Implementation of a second-degree geometric primitive: Cone.

Supported features:

Finite cone intersections
Cone caps
Surface normal computation
Shadow casting
Lighting support
Rotation and translation

# Bump Mapping

Support for bump-mapped surfaces to simulate small geometric details without increasing mesh complexity.

### Ray Tracing Pipeline

For each pixel:

Generate a ray from the camera.
Find the closest intersection with scene objects.
Compute the surface normal.
Evaluate lighting:
Ambient component
Diffuse component
Specular component (bonus)
Cast shadow rays toward light sources.
Compute the final pixel color.
Display the rendered image.

Instructions
### Instructions

1. <u>**Compilation:**</u>

The program must compile with 42 mandatory flags: -Wall -Werror -Wextra

```bash
make        # Compiles
make clean  # Deletes objs
make fclean # Deletes objs and executable
make re     # Cleans and recompiles
```
Requirements
GCC / Clang
Make
MiniLibX
X11 libraries (Linux)

2. <u>**Execution**</u> 

./miniRT scenes/example.rt

3. <u>Controls</u>

**ESC:**	Exit program
**Window Cross:**	Exit program

### Technical Challenges

During development, several mathematical problems had to be solved:

Ray / sphere intersections
Ray / plane intersections
Ray / cylinder intersections
Ray / cone intersections
Surface normal computation
Coordinate transformations
Shadow ray casting
Phong illumination model
Procedural texturing
Bump mapping

# Resources

### Raytracing
1. [Ray Tracing in One Weekend](https://raytracing.github.io/)
2. [Scratchapixel](https://www.scratchapixel.com/)
3. [The Ray Tracer Challenge](https://raytracerchallenge.com/)
4. [Physically Based Rendering (PBR)](https://www.pbr-book.org/)

###  MiniLibX 
1. [42 Docs - MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx.html)
2. [Aurelien Brabant - MLX Tutorial](https://aurelienbrabant.fr/blog/pixel-drawing-with-minilibx)
3. [MiniLibX: 42 MiniLibX Documentation](https://github.com/42paris/minilibx-linux)

###  Mathematics and Bonus 
1. [Intersection Ray-Cone (PDF)](https://www.geometrictools.com/Documentation/IntersectionLineCone.pdf)
2. [Phong's Model](https://fr.wikipedia.org/wiki/Ombrage_de_Phong)
3. [Texture Mapping (UV)](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/texture-mapping)
4. [Color Disruption](https://medium.com/@Ksatese/advanced-ray-tracer-part-4-87d1c98eecff)
5. [Texture Mapping](http://raytracerchallenge.com/bonus/texture-mapping.html)

<u>AI Usage</u>
Artificial Intelligence tools were used as assistants during development for:
- Understanding ray tracing concepts
- Verifying mathematical derivations
- Reviewing algorithms

All implementation, debugging, architecture decisions, and final code were written and validated by the project authors.

# Lighting Models Overview

## 1. Introduction

In a ray tracer, lighting models simulate how light interacts with surfaces. To correctly compute the final color of a pixel, it is important to distinguish three fundamental concepts: **intensity**, **color**, and **light contribution**.

---

## 2. Fundamental Concepts

### A. Intensity ("How Much Light")

Intensity is a **scalar value** (a single number, typically between 0.0 and 1.0).

- **Definition:** It represents the pure quantity of light reaching a point on a surface.
- **Dependencies:** Intensity depends on the light source power (**brightness ratio**) and the angle at which the light strikes the surface.
- **Analogy:** Think of it as the brightness control of a spotlight.

---

### B. Color ("What Color Is the Light")

Color is a three-component **RGB vector**.

- **Definition:** It represents the spectral composition of the light.
- **Usage:** For lighting calculations, colors are usually normalized to the range [0.0, 1.0].
- **Analogy:** It is equivalent to placing a colored filter in front of a spotlight.

---

### C. Light Contribution ("The Actual Illuminating Result")

A contribution is an RGB vector resulting from the combination of intensity and light color.

- **Formula:** **Contribution = Intensity × LightColor**
- **Definition:** It represents the actual colored light reaching a specific point on a surface.

For example, an intensity of 0.5 combined with a red light produces a dark red contribution.

---

## 3. Lambert Diffuse Reflection Model

The Lambert model simulates matte surfaces that scatter light equally in all directions.

### Diffuse Intensity Calculation

The diffuse intensity depends on the angle between the surface normal **N** and the light direction **L**.

[I_{diffuse} = \max(0, N \cdot L) \times LightBrightness] Where:

* **N** = normalized surface normal
* **L** = normalized light direction
* **N · L** = cosine of the angle between them

The closer the light direction is to the normal, the brighter the surface appears.

---

## 4. Phong Specular Reflection Model

The Phong model adds shiny highlights that depend on the observer's position.

### Reflection Vector

[R = 2(N \cdot L)N - L] Where:

* **R** = reflection vector
* **N** = surface normal
* **L** = light direction

### Specular Intensity

[I_{specular} = (R \cdot V)^n] Where:

* **V** = view direction (toward the camera)
* **n** = shininess coefficient

Typical values:

* n ≈ 10 → plastic-like materials
* n ≈ 100 → polished metal surfaces

Higher values produce smaller and sharper highlights.

---

## 5. Multiple Colored Lights

When multiple lights are present, the final pixel color results from the interaction between the object's color and the sum of all light contributions.

### Accumulated Lighting

For a given color channel (e.g. Red):
[R_{pixel} = R_{object} \times \sum_i Contribution_{red,i}]
The same computation is performed independently for the Green and Blue channels.

## Why Multiplication?
Multiplying the object's color by the incoming light contribution simulates physical reflection. An object can only reflect wavelengths it already contains.

For example:
* Blue object → (0, 0, 1)
* Red light → (1, 0, 0)
Result: [(0,0,1) \times (1,0,0) = (0,0,0)]. The object appears black because blue surfaces absorb red light rather than reflecting it.

---

## 6. Visual Summary

* **Intensity:** Determines the amount of light reaching a surface. **Effect:** Bright versus dark regions.
* **Color:** Determines the tint of the light source. **Effect:** Overall atmosphere and mood of the scene.
* **Light Contribution:** Represents the final colored light reaching a point. **Effect:** The actual illumination used for shading calculations.
* **Object Color:** Defines how a surface reacts to incoming light. **Effect:** Determines which wavelengths are reflected and which are absorbed.

---

**The final color of a pixel is obtained by combining the object's material properties with the accumulated contributions of all light sources visible from that point**.
