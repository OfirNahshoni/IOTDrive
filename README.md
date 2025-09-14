# IOTDrive – Distributed IoT File System

### 📦 A Modular C++ Distributed File System Built for IoT Devices

[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue)](https://en.cppreference.com/w/cpp/20)
[![Platform](https://img.shields.io/badge/Platform-Raspberry%20Pi%20%2B%20Linux-brightgreen)](https://www.raspberrypi.com/)
[![Status](https://img.shields.io/badge/Status-In%20Development-yellow)]()
[![License](https://img.shields.io/badge/License-MIT-green)](./LICENSE)

---

## 🧠 Overview

**IOTDrive** is a distributed file system designed for real-time storage across multiple Raspberry Pi devices (Minions) using modern C++ and modular design principles.  
It monitors a local directory and dispatches file read/write tasks to remote minions over UDP.  
The system is composed of reusable, decoupled components: Master, Minions, a plugin-based `Framework`, and message serialization tools.

> It is fully asynchronous, event-driven, and built with scalability and testability in mind.

---

## 🏗️ Architecture

### 🔴 Master Node

- Interacts with the Linux Kernel via `/dev/nbdX`
- Implements:
    - `NBDProxy`
    - `MinionManager` (Minion registration & tracking)
    - `ResponseManager`
    - `Framework` (Reactor + ThreadPool)

### 🟢 Minion Nodes

- Each Minion listens on a unique UDP port
- Handles:
    - File access via `FileManager`
    - Read/Write command execution
    - Returning responses to the Master

### 🧩 Core Components

#### **Framework**:
- `Reactor`: event demultiplexer
- `ThreadPool`: background processing
- `Handleton`, `Factory`, `Callback`: modular interfaces

#### **Messaging Protocol**:
- `AMessage`: abstract message base
- `ReadSendMessage`, `WriteSendMessage`, `ResponseMessage`
- Serialization/Deserialization for cross-node transport

---

## 📁 Folder Structure

```
IOTDrive/
├── concrete/
│   ├── include/    # Header-only APIs for Master/Minion logic
│   ├── src/        # Source files for logic
│   └── test/       # Test and demo executables (master, minion1, minion2)
│
├── framework/
│   ├── include/    # Core modular framework components (Reactor, TP, etc.)
│   ├── src/
│   └── cmake/
│
├── CMakeLists.txt
└── README.md
```

---

## 🛠️ Build Instructions

### ✅ Prerequisites

- Linux (Ubuntu 22.04+)
- GCC 12+ / Clang 15+
- CMake 3.20+
- Boost (optional, depending on test setup)

### 🧱 Build with CMake

```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)
```

🔧 Example Executables Built:

- `master`
- `minion1`, `minion2`
- `create_demo_file` (for test image creation)
- `test_amessage`, `test_logger`, etc.

---

## 🔬 Testing & Debugging

The `test/` folder contains demo executables and unit tests for:

- Master ↔ Minion UDP communication
- Framework components (ThreadPool, Reactor, etc.)
- Serialization/Deserialization logic
- End-to-end simulation of Read/Write flows

> Use `create_demo_file` to generate test files and simulate client requests.

---

## 🧑‍💻 Author & Notes

This project is built as part of a final engineering project, targeting **Raspberry Pi IoT applications** with modern C++20 design.  
It demonstrates mastery of low-level system programming, distributed design patterns, modular architecture, and real-time network communication.