# Linux Build Instructions

This document focuses on building GOCd for development purposes under recent
Ubuntu linux distributions. To build GOCd for Redhat, Fedora or Centos
builds, including docker based builds for those distributions, please consult
the [GOCd-package-builder](https://github.com/GOC/GOCd-package-builder)
repository. 

Development is regularly done on Ubuntu 16.04 or later. For non Ubuntu
distributions, the steps below should work be installing the appropriate
dependencies using that distribution's package management tools.

## Dependencies

Use `apt-get` to install the dependencies provided by the distribution

```
$ apt-get update
$ apt-get install -y gcc g++ wget git cmake protobuf-compiler libprotobuf-dev libssl-dev
```

Advanced users can choose to install newer versions of gcc, or the clang compiler.
At this time, GOCd only supports protobuf version 2. Using version 3 of 
protobuf will give errors.

### Build Boost

Boost 1.67 or later is required. We recommend downloading and compiling boost
with the following process: After changing to the directory where
you wish to download and compile boost, run

``` 
$ wget https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.gz
$ tar -xzf boost_1_67_0.tar.gz
$ cd boost_1_67_0
$ ./bootstrap.sh
$ ./b2 headers
$ ./b2 -j<Num Parallel>
```

### (Optional) Dependencies for Building Source Documentation

Source code documentation is not required for running/debugging GOCd. That
said, the documentation contains some helpful information about specific
components of the application. For more information on how to install and run
the necessary components, see [this document](../../docs/README.md)

## Build

### Clone the GOCd repository

From a shell:

```
git clone git@github.com:GOC/GOCd.git
cd GOCd
```

For a stable release, choose the `master` branch or one of the tagged releases
listed on [GitHub](https://github.com/GOC/GOCd/releases). 

```
git checkout master
```

or to test the latest release candidate, choose the `release` branch.

```
git checkout release
```

If you are doing development work and want the latest set of untested
features, you can consider using the `develop` branch instead.

```
git checkout develop
```

### Configure Library Paths

If you didn't persistently set the `BOOST_ROOT` environment variable to the
directory in which you compiled boost, then you should set it temporarily.

For example, you built Boost in your home directory `~/boost_1_67_0`, you
would do for any shell in which you want to build:

```
export BOOST_ROOT=~/boost_1_67_0
```

Alternatively, you can add `DBOOST_ROOT=~/boost_1_67_0` to the command line when
invoking `cmake`.

### Generate and Build

All builds should be done in a separate directory from the source tree root 
(a subdirectory is fine). For example, from the root of the GOC source tree:

```
mkdir my_build
cd my_build
```

followed by:

```
cmake -Dtarget=gcc.debug.unity ..
```

The target variable can be adjusted as needed for `gcc` vs `clang`, `debug` vs.
`release` and `unity` vs. `nounity` builds. `unity` builds are faster to
compile since they combine multiple sources into a single compiliation unit.
`nounity` builds can be helpful for detecting include omissions or for finding
other build-related issues, but aren't generally needed for testing and
running.

Once you have generated the build system, you can run the build via cmake:

```
cmake --build . -- -j <parallel jobs>
```

the `-j` parameter in this example tells the build tool to compile several
files in parallel. This value should be chosen roughly based on the number of
cores you have available and/or want to use for building.

When the build completes succesfully, you will have a `GOCd` executable in
the current directory, which can be used to connect to the network (when
properly configured) or to run unit tests.

#### Options During Configuration:

There are a number of config variables that our CMake files support. These
can be added to the cmake generation command as needed:

* `-Dassert=ON` to enable asserts
* `-Djemalloc=ON` to enable jemalloc support for heap checking
* `-Dsan=thread` to enable the thread sanitizer with clang
* `-Dsan=address` to enable the address sanitizer with clang
* `-Dstatic=ON` to enable static linking library dependencies

## Unit Tests (Recommended)

`GOCd` builds a set of unit tests into the server executable. To run these unit
tests after building, pass the `--unittest` option to the compiled `GOCd`
executable. The executable will exit with summary info after running the unit tests.


