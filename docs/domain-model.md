# Domain model

The concepts of the client's domain and how the code represents them. The words below are the ones we use in the code, the tests and the conversations with the client.

## Vocabulary

| Term | Meaning | In the code |
|---|---|---|
| Vector | A point or a direction in 3D space | `Vector` (`math/`) |
| Colour | A red, green and blue value between 0 and 1 | `Colour` (`colour/`) |
| Ray | A half-line with an origin and a direction | `Ray` (`geometry/`) |
| Material | How a surface takes and reflects light | `Material` (`material/`) |
| Hit | A ray's point and surface normal at a shape intersection | `Hit` (`geometry/`) |
| Shape | A surface that can answer with its nearest ray hit | `Shape` (`geometry/`) |
| Sphere | A round `Shape` with a centre and radius | `Sphere` (`geometry/`) |
| Plane | A flat `Shape` with a point and normal | `Plane` (`geometry/`) |
| Scene | The shapes and the sun in the world | `Scene` (`scene/`) |
| Camera | The eye and the screen it looks through | `Camera` (`render/`) |
| Image | A grid of coloured pixels | `Image` (`image/`) |
| Trace | Find the colour seen along one ray | `trace` (`render/`) |
| Render | Trace one ray per pixel to fill an image | `Camera::render` |
| Saver | Writes an image to a file | `ImageSaver`, `PngSaver` (`image/`, `io/`) |

## Relationships

```mermaid
classDiagram
    class Vector
    class Colour
    class Ray
    class Material {
        colour() Colour
        shade(normal, toLight) Colour
    }
    class Hit {
        t
        point
        normal
        material
    }
    class Shape {
        <<interface>>
        hit(Ray) Hit?
    }
    class Sphere
    class Plane
    class Scene {
        add(Shape)
        nearestHit(Ray) Hit?
        toLight() Vector
    }
    class Camera {
        rayThroughPixel(column, row, width, height) Ray
        render(Scene, width, height) Image
    }
    class Image {
        pixel(column, row) Colour
        setPixel(column, row, Colour)
    }
    class ImageSaver {
        <<interface>>
        save(Image, path)
    }
    class PngSaver

    Ray *-- Vector : origin, direction
    Sphere *-- Vector : centre
    Sphere *-- Material
    Plane *-- Vector : point, normal
    Plane *-- Material
    Shape <|.. Sphere
    Shape <|.. Plane
    Scene o-- Shape
    Scene *-- Vector : toLight
    Hit *-- Vector : point, normal
    Hit *-- Material
    Camera *-- Vector : position
    Image o-- Colour : one per pixel
    Camera ..> Ray : creates
    Camera ..> Scene : renders
    Camera ..> Image : returns
    ImageSaver <|.. PngSaver
    ImageSaver ..> Image : saves
```

`trace(Ray, Scene)` returns the shaded colour of the nearest hit, or black when the scene is missed.

## Conventions

See ADR 0006 for the world axes and the pixel grid.