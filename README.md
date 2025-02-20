NFSIISE
=======

![Screenshot](https://raw.githubusercontent.com/zaps166/GitHubCommonContents/master/Screenshots/NFSIISE.png)

Cross-platform wrapper for the Need For Speed™ II SE game with 3D acceleration and TCP protocol!

## GIT clone:

Don't forget to update submodules:
```sh
git submodule update --init --recursive
```

## OpenGL

* By default OpenGL 1 is used (except Android - it always uses GLES2).
* To use OpenGL 2, add `gl2` argument to compilation script.
* To use OpenGL|ES 2, add `gles2` argument to compilation script.

## Compile for x86:

* To compile the game, you must have:
  * GCC or Clang compiler which can generate **32-bit** code for x86 (set by `$CC` environment variable),
  * **32-bit** OpenGL devel and drivers,
  * **32-bit** SDL2 devel.
  * Yasm assembler,
* On **Debian** you should add 32-bit architecture and install 32-bit dependencies (run as `root`):
```sh
dpkg --add-architecture i386
apt-get update
apt-get install libsdl2-dev:i386 gcc-multilib yasm
```
* Edit the `compile_nfs` script, modify what do you want. Compile the game by executing the script - it will automatically generate executable file inside `Need For Speed II SE` directory:
  * `./compile_nfs` - native compilation for Unix-like systems (Linux, OS X, ...),
  * `./compile_nfs win32` - cross compilation for Windows.


# Notes About Windows Build:
* One way is to use WSL (Windows Subsystem for Linux) and install `mingw-w64` which cross-compiles to Windows
```sh
sudo apt install mingw-w64
```
also `gcc-multilib` might be needed to be installed using
```sh
sudo apt install gcc-multilib
```

* Don't install SDL using apt-get, instead take it from their [official repo packages page](https://github.com/libsdl-org/SDL/releases/), get the package with **mingw** suffix

* Inside the package folder you should use the one called *`i686-w64-mingw32`*
* Either copy the `include, bin, lib, share` to your system files (not recommended) or you can modify the following lines in the file `compile_nfs`:

  1. On line 30 with:
      ```sh
      C_FLAGS="$COMMON_FLAGS -O2 $CPU_FLAGS"
      ```
      add before the last quotation mark `-I/path/to/include/folder` so that it becomes:
      ```sh
      C_FLAGS="$COMMON_FLAGS -O2 $CPU_FLAGS -I/path/to/include/folder"
      ```
      
  2. On line 30 add the same include directory paramter before the quote

  3. On line 42 which has:
      ```sh
      i686-w64-mingw32-ld --enable-stdcall-fixup -o "../Need For Speed II SE/nfs2se.exe" *.o --stack=0x7D00,0x7D00 --heap=0x2000,0x1000 -lws2_32 -lwinmm -lmingwex -lmsvcrt -lkernel32 -lopengl32 -lSDL2 -lSDL2main -lSDL2_test -subsystem=$WIN_SUBSYSTEM $STRIP -e _start &&
      ```
      After the `-lSDL2_test` add `-L/path/to/lib/folder/`
  4. Now the command `./compile_nfs win32` should work fine
  5. If you try to run the exe, windows will say the dll is missing so you should get it from the `same SDL packages link` but this time the package for `win32-x86`
  6. Copy the dll you get from decompressing the zip file and put it in the same directory as the game's exe file
  7. Now if you follow the other steps (of copying game data and dealing with possible errors explained futher), it should work fine
  
## Compile for non-x86 CPUs:

### Information:
* This game can run on ARM devices, also on Android. Only **32-bit little-endian** CPUs are supported.
* The performance is lower than the original assembly code.
* It can be less stable than assembly code due to possible translation bugs.

### Requirements:
* SDL2 (32-bit) and OpenGL (32-bit),
* target must be 32-bit little-endian,
* GCC 4.9 or higher (currently Clang is not supported).

### Compilation:

#### Linux:
* run `./compile_nfs cpp`

#### Android:
* install NDK and SDK (API levels: 14 and 16),
* set environment variables: `ANDROID_NDK_ROOT` and `ANDROID_HOME`,
* create directory path: `src/Android/jni/SDL/include/SDL2`,
* download SDL2 sources and create symlinks from SDL2 source directory:
  * `android-project/app/src/main/java/org` to `src/Android/src/org`,
  * `src` to `src/Android/jni/SDL`,
  * `include/*.h` to `src/Android/jni/SDL/include/SDL2`,
* run `./compile_nfs android` or `./compile_nfs android install`

## Run:

* Copy `fedata` and `gamedata` directories from the Need For Speed™ II SE original CD-ROM into `Need For Speed II SE` directory.
* This game **needs** data from Need For Speed 2 **Special Edition**, otherwise you'll see a 'MOVIE FILE NOT FOUND' message!
* You can delete unnecessary files, e.g. `fedata/pc/text/text.*`, because TCP version uses new files in root directory.
* All files and directories copied from CD-ROM **must** have *small letters* on Unix-like systems!!!
  * Please use the `Need For Speed II SE/convert_to_lowercase` script if you have UPPERCASE names.
* If you want to change the language, edit `install.win` file and change the first line. Leave `4nn` as is and modify only language name. Possible languages are:
  * english,
  * french,
  * german,
  * italian,
  * spanish,
  * swedish.
* Run the game.
* The game settings files are located in `~/.nfs2se` (`%AppData%\.nfs2se` on Windows). At the first run, the `nfs2se.conf.template` will be copied there. You can modify the file if you want to configure the game. On Windows, you can use `open_config.bat` to open the config file in notepad.
* On Ubuntu 16.04 you can quick start by installing these dependencies:
    `sudo apt install libgl1-mesa-glx:i386 libxinerama1:i386 libxrandr2:i386`

## What works:

* Game controllers (reconnected game controllers should be the same),
* Force Feedback (tested on Linux),
* TCP and UDP connection,
* Serial port connection,
* Brightness,
* Sound.

## What does not work:

* Modem connection (it will never work again, this feature has been removed from assembly code),
* If Force Feedback does not work, you can try to select Force Feedback device in `nfs2se.conf` file (`ForceFeedbackDevice`).

## Function keys in-game

* F1  - toggle rain,
* F2  - car detail,
* F3  - view distance,
* F4  - toggle horizon,
* F5  - toggle HUD (player 1),
* F6  - toggle HUD (player 2),
* F7  - toggle mirror,
* F8  - toggle music,
* F9  - toggle sound effects,
* F10 - brightness,
* F11 - reset car.

## Additional information:

* Arch Linux package is available in AUR as `nfs2se-git`.
* Compilation on *BSD systems probably needs changes in compilation script (not tested).
* Cockpit view and night driving are unavailable (original 3D-accelerated version doesn't have this), see [NFSIISEN](https://github.com/zaps166/NFSIISEN) repository.
* OpenGL 1.x only: if the game crashes it might not restore the gamma properly. In this case run: `xgamma -gamma 1.0`.
* There is Docker based build environment available on [GitHub](https://github.com/thomas-mc-work/nfsiise-build-env).

## Patches:

* This directory contains patch for SDL 2.0.3 (SDL 2.0.4 has already this bugfix). It allows to use all axes in DualShock3 gamepad! You must also modify `nfs2se.conf` file (Joystick0Axes, Joystick0Buttons).
  * Unfortunately, only main 6 axes in DualShock 3 are accessible since Linux 4.12.

# Zynq Build
Preconditions:

Clone SDL2 and Rasterix in the same directory in which you have cloned this repository.

Before you can start building this repository, you have to build SDL2 to get the `libSDL2-2.0.so` and `libGL.so` from the Rasterix repository. 

The `libGL.so` is build automatically when building the Rasterix repository.

Build SDL2
```sh
git clone https://github.com/libsdl-org/SDL.git
cd SDL
checkout SDL2
export SYSROOTS=/opt/petalinux/2022.2/sysroots
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=../Rasterix/toolchains/toolchain_zynq.cmake  -DSDL_SYSTEM_ICONV=false
cmake --build build
```

If you have done this, copy `libSDL2-2.0.so` as `libSDL2-2.0.so.0` and `libGL.so` as `libGL.so.1` into the same directory in which you have copied the `nfs2se` binary. This build will always check local directories first before it searches at other directories for the shared libraries.

To cross compile, use the following steps:

```sh
git clone https://github.com/ToNi3141/NFSIISE.git
cd NFSIISE
export SYSROOTS=/opt/petalinux/2022.2/sysroots
cmake --preset zynq_embedded_linux -DCMAKE_TOOLCHAIN_FILE=../Rasterix/toolchains/toolchain_zynq.cmake
cmake --build build/zynq/ --parallel
```
Copy the NFSIISE data on your device (similar to the steps above). Copy the new binary `nfs2se` on your device and run it.
