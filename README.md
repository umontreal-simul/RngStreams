# RngStreams

**RngStreams** is an object-oriented random-number package with many long streams and substreams,
based on the MRG32k3a RNG from reference [1] below and proposed in [2].

This repository is a C++ implementation, but **RngStreams** is also available for C, Java, R, OpenCL, and some other languages.

e-mail: <lecuyer@iro.umontreal.ca>  
web page: <http://www.iro.umontreal.ca/~lecuyer/>

If you use it for your research, please cite the following relevant publications in which MRG32k3a
and the package with multiple streams were proposed:

[1] P. L'Ecuyer, Good Parameter Sets for Combined Multiple Recursive Random Number Generators,
Operations Research, 47, 1 (1999), 159--164.  
See <https://www-labs.iro.umontreal.ca/~lecuyer/myftp/papers/opres-combmrg2-1999.pdf>

[2] P. L'Ecuyer, R. Simard, E. J. Chen, and W. D. Kelton,
An Objected-Oriented Random-Number Package with Many Long Streams and Substreams,
Operations Research, 50, 6 (2002), 1073--1075  
See <https://www-labs.iro.umontreal.ca/~lecuyer/myftp/papers/streams00.pdf>

## License

The package is under an Apache 2.0 license, copyrighted by Pierre L'Écuyer and the University of Montreal. It can be used freely for any purpose.

## Build

Clone the project
``` sh
git clone git@github.com:umontreal-simul/RngStreams.git
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
cmake -DRngStreams_ROOT=/rngstreams/install/path ...
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
