README for the BLISS-LLVM Compiler
===============================

This is the source package for the BLISS-LLVM compiler, a portable
cross-compiler for the BLISS programming language.
Visit the [project website](http://madisongh.github.io/blissc)
for more information about BLISS-LLVM.

Current Status
--------------

Work in progress.  This is a re-implementation of the BLISS-M compiler
project [BLISS-M Project Website](http://madisongh.github.io/blissc) for
more information.  BLISS-M was written in C and to LLVM 3.9-5.0.  This
re-implementation will be written in C++ and to LLVM 8.0-9.0 (and possibly
10.0).

Prerequisites
-------------

Known to build Ubuntu 19.04 and later (64-bit).

The code generator uses LLVM 8.0, 9.0 or 10.0, which you can download
directly from llvm.org.  On Ubuntu systems, you can install one
of the llvm-dev packages using apt.

The build system uses CMake 3.13 or later.

Building the compiler
---------------------

1. Clone [the repository]().

2. cd to the top-level source directory and create a build directory.

3. cd to your build directory.

4. Run `cmake ..`.

5. Run `make` to build the compiler.

6. Run `make check` to test the built compiler.


Running the compiler
--------------------

The build will produce a program called **bliss** in your build
directory.  Run `./bliss --help` for a description of the arguments
and options.


Contributions
-------------

There is a lot more yet to do on this project!  If you are interested
in contributing, contact me (JonathanBelanger on GitHub, or by e-mail at
jbelanger _at_ rochester _dot_ rr _dot_ com).

License
-------
All sources are released under the BSD 2-clause license.  See the
[LICENSE.TXT]()
file for the license text.
