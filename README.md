# RngStreams
MRG32k3a random number generator with multiple streams and substreams

## Build

Clone the project
``` sh
git clone git@gitlab.inria.fr:slegrand/paracirce.git
```


For single configuration generator, such as Unix Makefiles, the default configuration is Release.
You can specify Debug configuration giving this command-line option to CMake: ``-DCMAKE_BUILD_TYPE=Debug``.

``` sh
mkdir build
cd build
cmake .. [-DCMAKE_BUILD_TYPE=Debug] [-DCMAKE_INSTALL_PREFIX=<install_path>]
make
```

## Installation

To install **RngStreams** in the install path specified with the option ``CMAKE_INSTALL_PREFIX``, execute the **install** target, e.g. on Linux:

``` sh
make install
```

## Compile against **RngStreams**

Add these lines to you CMakeLists.txt:

``` cmake
find_package(RngStreams REQUIRED)
target_link_libraries(<your_target>
    PRIVATE RngStreams::RngStreams)
```

If the **RngStreams** installation path is not standard, set RngStreams_ROOT to the installation
path when invoking cmake:

``` bash
cmake -DRngStreams_ROOT=/paracirce/install/path ...
```

## Tests

If you want to run RngStreams tests, first, get [doctest](https://github.com/onqtam/doctest) submodule
``` sh
git submodule update --init --recursive
```

Then re-generate the project with the ``RngStreams_BUILD_TESTS`` variable set to ``ON``:

``` sh
cd build
cmake .. -DRngStreams_BUILD_TESTS=ON
make
```

Finally, run the test
``` sh
make test
```
