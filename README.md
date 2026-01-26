# N-Body Sim (C++/SFML)

> **Building a custom 2d physics engine that can simulate n body gravity for thousands of particles**
> **Using Barnes-Hut Algortithm and Quadtree data structures for optimization**

---
### ✅✅✅ Successfully managed to simulate 8000 particles at 60 fps in 10 days of learning c++ and simulation engineering
---

### Goals
- ✅ **Logic Prototype:** Functional 1D console sim with gravity classes.
- ✅ **2D Rendering:** Migrating to SFML for real-time visualization.
- ✅ **Optimization:** Optimizing to handle a reasonably large number of particles.

---
### Tech Stack
* **Language:** C++20 (Core Logic)
* **Graphics:** SFML (Rendering & Windowing)
* **Physics:** Numerical Integration (Euler/Verlet)

---
### The Math
* Simulating a relatively low number of particles can be done by using a brute-force approach, by doing pair-wise calculation for every object against every other object. However, this approach is not optimal when scaled as it has a time complexity of **O(n^2)**.
* The alternate approach is to use an algorithm like **Barnes-Hut** by using **QuadTree** data structures to recursively keep objects in nodes relative to their position in space, and then approximating distant particles into one body (or a center of mass) and then applying required forces.
* This approach significanly increases performance as it has a time complexity of **O(n log n)** , n for each body, and log n for rebuilding the quadtree.

### The Vision
I am moving away from high-level engines like **Godot** to understand the "essence" of physics simulations at the hardware level. This project focuses on building a custom engine from scratch, handling everything from vector math to memory-efficient rendering.

---
# Milestones

### 3 body simulation
![0116(1)](https://github.com/user-attachments/assets/1ae697a3-1459-448f-8aa7-862446f820e0)

### Randomized n body Simulation
![0118(1)](https://github.com/user-attachments/assets/90681d78-ca19-4fab-b106-0897138090f8)

### Solar System Simulation with Elastic Collisions
![0118](https://github.com/user-attachments/assets/bba48145-292d-40de-ae25-71e46dac87ac)

### 5000 particles at 60 FPS (using Barnes-Hut Algorithm)
![5000system](https://github.com/user-attachments/assets/e4ec0988-67af-4f4c-9232-bc58d2e5e75b)

### 8000 particles at 60 FPS 
![0118(2)](https://github.com/user-attachments/assets/3fa3c565-1b3b-45b8-bed2-d89b666f9bc6)
