# 3D Arcade Dodger

A high-performance, real-time 3D arcade game built from scratch to demonstrate the power, ergonomics, and production-readiness of the **ELPL** programming language.

The entire project—including the game logic, rendering loops, and asset pipelines—is written completely in ELPL, compiling down to native machine code via **LLVM** and bytecode via the **JVM**. It features deep, zero-overhead C interop to power its 3D graphics subsystems and is deployed as a fully functional Android application on the Google Play Store.

---

## 🚀 Language Profile: ELPL

**ELPL** is a general-purpose programming language designed for maximum developer control, low latency, and cross-platform flexibility. Key architectural pillars include:

*   **Dual-Backend Architecture:** Native compilation via LLVM for maximum execution performance and a JVM backend for robust, write-once-run-anywhere portability.
*   **Seamless C Interop:** Direct binding and calling conventions to external native C libraries without translation layers or heavy marshalling overhead.
*   **Manual Memory Management:** Complete, deterministic control over allocations and hardware memory lifecycles—eliminating garbage collection pauses in hot rendering paths.
*   **Full Developer Tooling:** Equipped with robust IDE integrations, native syntax diagnostics, and precise compiler-driven static analysis out of the box.

---

## 🛠️ Tech Stack & Architecture

This project leverages ELPL's bare-metal control to handle complex 3D engine mathematics, asset handling, and hardware abstraction interfaces.

*   **Core Engine:** Built fully in ELPL managing 3D vector transformations, matrix operations, and rigid bounding-box collision detection.
*   **Windowing & Audio:** Direct bindings to **SDL3** for hardware initialization, low-level event handling, input polling, and audio channels.
*   **Memory Footprint:** Explicit allocation and deallocation paths for vertex arrays, textures, and runtime game states using ELPL’s manual memory controls.

---

## 📁 Repository Structure

```text
├── src/                      # Source files written entirely in ELPL
├── assets/                   # Fonts, textures, and audio files (ignored via git)
├── .gitattributes            # Custom language definitions for scrapers & IDEs
├── .gitignore                # Optimized build artifact exclusions
└── README.md                 # Project manifesto and technical overview
```

---

## ⚡ Technical Highlights

### Zero-Overhead External C Bindings
ELPL interacts directly with low-level native systems. The language declares foreign function interfaces (FFI) smoothly, allowing raw access to C types and binaries without dynamic glue code:

```elpl
// ELPL Syntax Example: Direct external binding to SDL3
extern function ExampleWindow(Pointer title): Pointer;
extern function Example_DestroyWindow(Void window);

//or

use "OpenGL/gl.h"
use "stdlib.h"
```

### Deterministic Manual Control
In high-frame-rate environments, unpredictable garbage collection cycles break real-time deadlines. ELPL gives developers strict ownership over memory lifecycles, enabling deterministic performance curves directly inside the game loop.

---

## 📲 Deployment

*   **Desktop:** Compiled natively via LLVM for low-level performance testing.
*   **Mobile:** Fully packaged and shipped to the **Google Play Store** via the language's native compilation pipeline.

* **Official Website** [ELPL's Official Website](https://elpl-d8625.web.app/)