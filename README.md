# Usurper's Retribution

This is my attempt at a simple tile-based overhead-view RPG game engine as a
side-project back in my high school days.  The timestamps date back to March
2003, although I think I did the bulk of the work in 2002.

Licensed GPLv2 for now until I get around to relicensing it to 3-clause BSD or
something.

The first git commit contains no changes after the initial 2002/2003 work.

## Build

This project has a pretty standard CMake build system.

A vcpkg manifest is included for convenience (particularly for Windows and CI
builds), but is not required.

### Linux/macOS

You'll need your standard GNU or Clang toolchain, and cmake.

Install the development packages for SDL2, SDL2_image, and libmodplug from your
distro (homebrew on Mac).

Then:

    $ cmake .
    $ make
    $ ./ur

### Windows (Visual Studio)

Ensure you have Visual Studio 2022 with the Desktop Development set of features
(C++ toolchain, cmake integration, Windows SDK, etc.) installed.

Then open this repo's directory directly in Visual Studio 2022. VS' cmake
integration and vcpkg package manager should automatically do the rest.

### VS Code IDE (all platforms)

Ensure you have the C/C++ extension and CMake Tools extension. Open the project
in VS Code.  The dependencies discussed in the above sections apply.

Note that you may need to set `"configurationProvider": "ms-vscode.cmake-tools"`
in your C++ extension workspace settings (c-cpp-properties.json) to get
intellisense working.
