# Vulkan Course

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![C++](https://img.shields.io/badge/language-C++-blue.svg)]()
[![Vulkan](https://img.shields.io/badge/API-Vulkan-red.svg)]()

A learning project for **Vulkan** graphics API, with examples, notes, and utilities.

---

## Contents

- `project/` — example/demo code implementing Vulkan concepts  
- `vulkaninfo.html` — generated Vulkan capabilities and device info snapshot  
- `.gitignore` — files and directories to ignore

---

## What’s Here

This repository is organized to help you follow along and experiment with Vulkan-based graphics programming. You’ll find:

- Basic Vulkan setup (instance, device, swapchain, etc.)  
- Sample shaders and rendering pipelines  
- Platform-specific setup (window creation, surface, etc.)  
- Utility functions for Vulkan info and debugging

---

## Requirements

To build and run the examples, you’ll need:

- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home) installed
- Visual Studio
- [Ninja](https://ninja-build.org/)
- [CMake](https://cmake.org/)

## How to run

 - Install `Vulkan SDK` (currently using 1.4.321).
 - Download `ninja`. Create a folder in `C:` named `ninja` and place the downloaded instance here.
 - As admin, Open `Start`->`Edit environment variables for your account`->`Path`->`Edit`. Create a new entry called `C:\ninja` and press `OK`
 - Install `CMake` (currently 4.1.0).
