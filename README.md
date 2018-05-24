# durian

## Building

If you use CLion IDE, the project should "just work" if you import it as a new project (since CMake is integrated into CLion),
and you should be able to click the build/run button, which will put build artifacts into the `cmake-build-debug/` directory by default.

If you are using a Unix-based system (i.e. Linux or macOS) and you would like to build from the command line,
you can do so with the following set of commands in the repo's main directory:

```
mkdir build
cd build/
cmake ..
make
```

To briefly explain, this:

* Creates a new directory named `build/` and enters it.
* Calls CMake to create the build system in the current directory (i.e. `build/`), telling it that the CMakeLists.txt config file is in the parent directory (i.e. `..`).
* Calls make (i.e. the generated build system) in the `build/` directory to compile the code.
