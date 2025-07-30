# Purpose

This repository contains a possible implementation of 'Rule' system that are applied to 'Alarm points' to create an alarm state. 

The target of this repository is to provide users an interface where they can:

1. Create their own static rules (e.g. `Point1.Greater(100) or Point2.Less(40)`)
2. Create dynamic rules that rely on other points (e.g. `Point1.Less(Point2) or Point2.Equal(Multiply(Point2, 2))`)  
3. Combine rules into complex ones (e.g. `Point1.Less(-10) || Point1.Less(5)`)
4. Apply rules to a point to create an 'Alarm state' (e.g. `Point1.AddRule(...)`)
5. Create a handler for when alarm state is broken (e.g. `Point1.SetHandler(...)`)

To achieve this there still lots of work to do, so any contribution welcome.

## Build

### Presequitives

1. **Conan V2** is installed globally or locally within python env
2. **CMake** version 3.20 or higher
3. **Clang** or **GCC** compiler
4. Build tool (make, ninja)

### Release build

1. `git clone` repository
2. `cd ./alarm-point-lib`
3. `conan install . -b missing -s:a build_type=Release` to install all necessary dependencies
4. configure with `cmake --preset conan-release -S . -B ./build/Release/` 
5. build with  `cmake --build --preset conan-release`

### Debug build

1. `git clone` repository
2. `cd ./alarm-point-lib`
3. `conan install . -b missing -s:a build_type=Debug` to install all necessary dependencies
4. configure with `cmake --preset conan-debug -S . -B ./build/Debug/`
5. build with  `cmake --build --preset conan-debug`

## Test

To run tests you need:

1. Navigae to build directory: `cd ./build/{Configuration}`
2. Run tests with ctest: `ctest`

Or:

1. Run binary: `./build/{Configuration}/test/tests-all`