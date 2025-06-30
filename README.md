# 🌀 MiniEngine — Lightweight OpenGL Game Engine

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey)
![OpenGL](https://img.shields.io/badge/OpenGL-3.3+-blue)

**MiniEngine** is a minimal yet modular OpenGL-based game engine sandbox, written in modern C++.  
Its purpose is to provide a clean, extensible foundation for learning real-time rendering, camera control, input systems, and general 3D engine architecture.

---

## 🧩 Dependencies

- C++17 or later  
- OpenGL 3.3+  
- [GLFW](https://www.glfw.org/) (window/input handling)  
- [GLAD](https://github.com/Dav1dde/glad) (OpenGL function loader)  
- [GLM](https://github.com/g-truc/glm) (math)  
- [CMake](https://cmake.org/) 3.14+

---

## ⚙️ Build Instructions

```bash
git clone --recurse-submodules https://github.com/ParsaFaghani/Game-Engine.git
cd MiniEngine
mkdir build && cd build
cmake ..
make -j$(nproc)
./MiniEngine
```