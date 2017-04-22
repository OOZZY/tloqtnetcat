# tloqtnetcat

A simple netcat implementation.

## Build Requirements

* CMake
* C++14 development environment for which CMake can generate build files
* Qt 5

## Clone, Build, and Run

```
$ git clone <url/to/tloqtnetcat.git> # clone into tloqtnetcat directory
$ mkdir tloqtnetcatbuild
$ cd tloqtnetcatbuild
$ cmake -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Debug ../tloqtnetcat
$ make
$ ./tloqtnetcat
$ ./tloqtnetcatgui
```
