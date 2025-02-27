# SoftwareRasterizer

## Overview
**SoftwareRasterizer** is a lightweight, header-only C++ template library that implements a software rasterization pipeline. It allows you to define custom vertex and pixel shaders to render 3D primitives entirely in software. The repository includes multiple demos that showcase its features.

## Dependencies

**SoftwareRasterizer** itself is a **header-only library with no external dependencies**.  
However, the demo applications require the following dependencies:

- **SDL2:**  
  SDL2 must be installed manually for running the demos. You can install it via your system's package manager (e.g., apt, Homebrew, vcpkg) or download it from the [SDL official website](https://www.libsdl.org/).

- **GLM:**  
  GLM is used in some demos for matrix and vector operations. It is automatically fetched by CMake using FetchContent, so no manual installation is required.

## Build Instructions

Each demo is an independent CMake project with its own CMakeLists.txt. To build a demo, follow these steps:

1. Open a terminal and navigate to the desired demo directory (e.g., the rotating cube demo):
   ```bash
   cd demos/rotating_cube
   ```
2. Create a build directory and run CMake:
	```bash
	cmake -B build
	```
3. Build the demo:
	```bash
	cmake --build build
	```
4. Run the demo:
	+ Linux/macOS:
		```bash
		./build/rotating_cube
		```
	+ Windows:
		Run build\rotating_cube.exe.


## Features

- **Header-Only Library:**  
  Integrate easily into your projects by including the header files; no separate compilation is needed.
  
- **Modern C++17:**  
  Built with C++17, leveraging powerful language features such as lambdas and constexpr for a clean and efficient design.
  
- **Customizable Rendering Pipeline:**  
  Plug in your own vertex and pixel shader functions using `std::function` for complete control over the rendering process.

- **Cross-Platform Compatibility:**  
  Works on Windows, Linux, and macOS with standard C++ and no dependencies (only SDL2 for demos).

## Images
### Demo: hello_triangle
![Image](https://github.com/user-attachments/assets/e09d6bee-0ccb-415e-b450-e8db2903be70)
### Demo: rotating_cube
![Image](https://github.com/user-attachments/assets/b04c3daf-5858-47b2-9799-0d682c62ad63)

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
