# 🍍 durian

## Anatomy of a Durian

![durian](https://1.bp.blogspot.com/-jJ5DtPM9oyU/VYQpCLwgUHI/AAAAAAAADYY/SHDM56_cm98/s400/cross-section%2B6-7%2Bwk%2Bdurian.jpg)

## Dependencies

```bash
git submodule update --init --recursive
```

## Building

If you use CLion IDE, the project should "just work" if you import it as a new project (since CMake is integrated into CLion),
and you should be able to click the build/run button, which will put build artifacts into the `cmake-build-debug/` directory by default.

If you are using a Unix-based system (i.e. Linux or macOS) and you would like to build from the command line,
you can do so with the following set of commands in the repo's main directory:

```bash
mkdir build
cd build/
cmake ..
make
```

To briefly explain, this:

* Creates a new directory named `build/` and enters it.
* Calls CMake to create the build system in the current directory (i.e. `build/`), telling it that the CMakeLists.txt config file is in the parent directory (i.e. `..`).
* Calls make (i.e. the generated build system) in the `build/` directory to compile the code.

## Durian Sample Code
```
$ durian example.dur shit
         88                        88
         88                        ""
         88
 ,adPPYb,88 88       88 8b,dPPYba, 88 ,adPPYYba, 8b,dPPYba,
a8"    `Y88 88       88 88P'   "Y8 88 ""     `Y8 88P'   `"8a
8b       88 88       88 88         88 ,adPPPPP88 88       88
"8a,   ,d88 "8a,   ,a88 88         88 88,    ,88 88       88
 `"8bbdP"Y8  `"YbbdP'Y8 88         88 `"8bbdP"Y8 88       88

@ UBC Launch Pad 2018!

thiabaud is eaten!
Delicious!
Yikes!
```