# nostalgia — ImGui standalone demo

A standalone ImGui demo replicating the nostalgia CS2 skin/loadout menu UI. Built with SDL2 + OpenGL3 + Dear ImGui.

## Features

- **Skins** — browse weapons by category, search, click any skin to open the detail modal with float slider, StatTrak toggle, sticker/charm slots
- **Loadout** — view all applied skins with a rarity-color list and inline preview panel (float bar, sticker slots, metadata)
- **Visuals** — full ESP / effects / chams checkbox panels
- **Misc** — movement, match, region forcer, appearance settings
- **Configs** — config list with save / load / delete / create new

## Requirements

- Windows 10/11
- [CMake](https://cmake.org/) 3.20+
- [vcpkg](https://vcpkg.io/) with SDL2 installed
- Visual Studio 2022 (MSVC) or any CMake-compatible toolchain

## Build

### 1. Install vcpkg & SDL2

```bat
git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
C:\vcpkg\bootstrap-vcpkg.bat
C:\vcpkg\vcpkg install sdl2:x64-windows
```

### 2. Configure & build

```bat
git clone https://github.com/calamitygamer/imgui-nos.git
cd imgui-nos

cmake -B build -S . ^
  -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake ^
  -DVCPKG_TARGET_TRIPLET=x64-windows ^
  -DCMAKE_BUILD_TYPE=Release

cmake --build build --config Release
```

### 3. Run

```bat
build\Release\nostalgia.exe
```

> ImGui is fetched automatically via CMake FetchContent — no submodule init needed.

## Controls

| Key | Action |
|-----|--------|
| `Esc` | Close window |
| Mouse | Navigate tabs, click items |
