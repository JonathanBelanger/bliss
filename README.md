README for the BLISS-LLVM Compiler
==================================

This is the source package for the BLISS compiler, a portable
cross-compiler for the BLISS programming language.
Visit the [project website](http://github.com/JonathanBelanger/blisscpp)
for more information about BLISS.

Why a BLISS compiler
--------------------

There are a number of reasons why I wanted to write a BLISS compiler.  The
top ones are:

 * When I worked at DEC on the IBM Interconnect product set, the OpenVMS versions
 of these products, all 14 of them, were written in BLISS.
 * I also wrote and SDL compiler, OpenSDL, that will eventually generate BLISS
  REQUIRE output files, and I wanted a way to be able to test them.
 * I love the BLISS way of defining MACROs.  The fact that a MACRO can refer to
 itself, as well as other MACROs and vice versa, is incredibly powerful.
 * I have never written a compiler before and was recently introduced to LLVM,
 so it seems like a good place to start.
 
 Available BLISS compilers
 -------------------------

There are a few BLISS compilers out there:

#. The original, which only runs on OpenVMS (VAX, Alpha, and IA64),
[OpenVMS Freeware CD V8.0](https://www.digiater.nl/openvms/freeware/v80/bliss/)
#. A [FreeVMS Portable BLISS for GCC](ftp://freevms.nvg.org/pub/vms/freevms/bliss)
#. One implemented by VMS Sofware - [VSI June 2019 OpenVMS Roadmap](http://vmssoftware.com/pdfs/VSI_Roadmap_20190722.pdf)).
#. One written by Matt Madison [The BLISS-M Compiler Project](http://madisongh.github.io/blissc)

Current Status
--------------

Work in progress.  This is, in effect, a re-implementation of the BLISS-M compiler
project for more information.  BLISS-M was written in C and to LLVM 3.9-5.0.  This
implementation will be written in C++ and to LLVM 8.0-9.0 (and possibly 10.0) and
support any available LLVM enhancements.

Prerequisites
-------------

Known to build Ubuntu 19.04 and later (64-bit).

The code generator uses LLVM 8.0, 9.0 or 10.0, which you can download
directly from llvm.org.  On Ubuntu systems, you can install one
of the llvm-dev packages using apt.

The build system uses CMake 3.13 or later.

Building the compiler
---------------------

1. Clone [the repository](https://github.com/JonathanBelanger/blisscpp.git).
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
All sources are released under the GPL 3.0 license.  See the
[LICENSE](https://github.com/JonathanBelanger/blisscpp/blob/master/LICENSE)
file for the license text.
