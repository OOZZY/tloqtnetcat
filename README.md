# tloqtnetcat

A simple netcat implementation.

## Build Requirements

* CMake
* C++14 development environment for which CMake can generate build files
* Qt 5

## Clone, Build, and Run

Clone into tloqtnetcat directory.

```
$ git clone --branch develop <url/to/tloqtnetcat.git>
```

Build.

```
$ mkdir tloqtnetcatbuild
$ cd tloqtnetcatbuild
$ cmake -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Debug ../tloqtnetcat
$ make
```

Run.

```
$ ./tloqtnetcat
$ ./tloqtnetcatgui
```
