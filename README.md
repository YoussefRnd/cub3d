# cub3D

A simple raycasting engine, inspired by Wolfenstein 3D, created as a project for 1337 school. The program takes a `.cub` file as input, which describes a map, and renders it in a window using the MLX42 graphics library.

## How to Compile

To compile the project, simply run `make`:

```bash
make
```

This will create a `cub3D` executable.

### Dependencies

The project uses the MLX42 graphics library. The `Makefile` is configured for macOS and expects MLX42 to be installed. It also uses a custom `libft` library which is included as a submodule.

## How to Run

To run the program, pass a `.cub` map file as an argument:

```bash
./cub3D map.cub
```

## Map Format

The `.cub` file has a specific format:

1.  **Texture Paths**: Four lines specifying the paths to the wall textures for North, South, West, and East.
    ```
    NO path/to/north_texture.png
    SO path/to/south_texture.png
    WE path/to/west_texture.png
    EA path/to/east_texture.png
    ```

2.  **Floor and Ceiling Colors**: Two lines specifying the RGB colors for the floor and ceiling.
    ```
    F R,G,B  (e.g., F 220,100,0)
    C R,G,B  (e.g., C 225,30,0)
    ```

3.  **Map Grid**: The rest of the file is the map, represented by a grid of characters:
    -   `1`: Wall
    -   `0`: Empty space
    -   `N`, `S`, `E`, `W`: Player's starting position and orientation.

The map must be enclosed by walls (`1`s).

Example:
```
NO textures/north.png
SO textures/south.png
WE textures/west.png
EA textures/east.png

F 220,100,0
C 225,30,0

11111111
10010001
10N00001
11111111
```

## Controls

The following controls are available:

| Key         | Action          |
| ----------- | --------------- |
| **W**       | Move forward    |
| **S**       | Move backward   |
| **A**       | Strafe left     |
| **D**       | Strafe right    |
| **← Left**  | Turn left       |
| **→ Right** | Turn right      |
| **Mouse**   | Look left/right |
| **ESC**     | Exit the game   |
