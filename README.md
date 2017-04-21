# vcpkg-port-tests

This is a collection of sample windows applications using various libraries provided by [vcpkg](https://github.com/Microsoft/vcpkg)

All of these sample applications use [CMake](https://cmake.org/) and the vcpkg-integration to consume ports provided by vcpkg

This collection of sample applications are "sanity tests" to confirm and verify that said ports in vcpkg are:

 * Consumable via CMake
 * Buildable via CMake
 * Runnable by the port consumer

# Ports under test

 * xerces-c
 * xalan-c
 * libgd
 * geos