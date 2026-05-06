# CG-LAB-2026
This Repo consists of my Computer Graphics Lab Project Based on 3D Grhaphical Representaion of Evolution of Earth From Prehistoric to Modern Times

# ☄️ K-Pg Asteroid Impact Simulation (OpenGL)

A 3D interactive historical and astronomical simulation built from scratch using C++ and legacy OpenGL (`freeglut`). 

Originally developed as a final Computer Graphics Lab project (Lab 10), this application demonstrates advanced 3D rendering techniques, hierarchical transformations, and a dynamic 2D Heads-Up Display (HUD) overlay. It visualizes the Earth's history from the Late Cretaceous period, through the Chicxulub asteroid impact, all the way to the modern Information Age.

![Simulation Screenshot](https://via.placeholder.com/800x450.png?text=Add+a+Screenshot+of+your+simulation+here!)

## ✨ Features
* **Hierarchical Solar System:** Real-time orbits of the Earth around the Sun, and the Moon around the Earth.
* **The Extinction Event:** A dynamic asteroid trajectory that impacts Earth, triggering a visual shockwave (expanding torus) and altering the planet's atmospheric colors.
* **Historical Timeline HUD:** A 2D orthographic text overlay that dynamically updates to narrate the current historical era.
* **Epoch Visualizations:** 3D rendered markers for different eras, including:
  * The Great Pyramids (Tetrahedron)
  * The Birth of Christ (Cross)
  * The Industrial Revolution (Smog Particle Spheres)
  * The Modern Age (Satellite Network Torus)

## 🖥️ Computer Graphics Concepts Implemented
This project was designed to showcase fundamental low-level computer graphics principles:
1. **The Matrix Stack (`glPushMatrix` / `glPopMatrix`):** Used extensively to isolate local coordinate systems (e.g., ensuring the Moon orbits the Earth without being affected by the Earth's axial spin).
2. **Double Buffering (`GLUT_DOUBLE`):** Prevents screen tearing and flickering during high-speed animation loops.
3. **Lighting & Materials (`GL_LIGHTING`):** Implemented a central Point Light at the Sun's origin. Uses `GL_EMISSION` to make the Sun glow, while utilizing diffuse and ambient lighting to cast realistic shadows on the planetary bodies.
4. **Depth Testing (`GL_DEPTH_TEST`):** Utilizes the Z-buffer to accurately occlude objects (e.g., the Moon passing behind the Earth).
5. **Projection Switching:** Combines 3D Perspective Projection (`gluPerspective`) for the celestial bodies with 2D Orthographic Projection (`gluOrtho2D`) to render flat UI text that is immune to camera movement.

## 🎮 Controls
* **`Spacebar`**: Hold down to advance time, progress the story, and orbit the planets.
* **`ESC`**: Exit the simulation.

## 🚀 Installation and Compilation (Windows)

This project requires a C++ compiler (`g++`) and the FreeGLUT development libraries. The recommended setup is via MSYS2.

### 1. Prerequisites
If you don't have FreeGLUT installed, open your **MSYS2 MinGW 64-bit** terminal and run:
```bash
pacman -S mingw-w64-x86_64-freeglut