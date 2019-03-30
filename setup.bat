@echo off
IF "%~1"=="init" GOTO init
IF "%~1"=="release" GOTO release
IF "%~1"=="debug" GOTO debug
IF "%~1"=="clean" GOTO clean
GOTO done

:init
git submodule update --init --recursive
cd thirdparty/boost
.\bootstrap
b2 headers
cd ../..
GOTO done

:release
mkdir build && cd build && cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release ..
nmake
cd ..
GOTO done

:debug
mkdir build && cd build && cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
nmake
cd ..
GOTO done

:clean
rd /s /q "build"
rd /s /q "bin"
GOTO done

:done