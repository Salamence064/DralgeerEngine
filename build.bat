@echo off

@REM Can only be compiled with GNU

if not exist "build" (
    echo "Creating 'build' directory"
    mkdir "build"
)

if not exist "build/vendor" (
    echo "Creating 'build/vendor' directory"
    mkdir "build/vendor"
)

if not exist "lib" (
    echo "Creating 'lib' directory"
    mkdir "lib"
)


@REM check if GLFW folder is empty
dir /b /s /a "glfw/" | findstr . > nul || (
    @REM The program should never really run this nest of commands
    echo GLFW Folder is empty

    pushd "glfw"
    call git submodule init
    call git submodule update
    popd
)

if exist "build/vendor/glfw3.dll" (
    GOTO skip_GLFW_build
)

@REM --------- Start of GLFW Build ------------

echo Building GLFW
copy "glfw_config.h" "glfw/src" >nul
pushd "glfw/src"

if not exist "../../include/GLFW" (
    robocopy ../include/GLFW ../../include/GLFW  /E /NJH /NJS /NFL /NDL
)

if not exist "build" (
    echo "Creating 'build' directory"
    mkdir "build/"
)

if not exist "temp" (
    echo "Creating 'temp' directory"
    mkdir "temp/"
)  

@REM move files not related to windows to temporary directory
set source_folder=.\
set search_words=x11 wl linux cocoa glx xkb posix
set destination_folder=.\temp

for %%W in (%search_words%) do (
    for /R %source_folder% %%F in (*%%W*) do (
        move "%%F" "%destination_folder%" >nul
    )
)

pushd "./build"
    gcc -c ../*.c -I../../deps -D_GLFW_BUILD_DLL -D_GLFW_USE_CONFIG_H -lOpengl32 -lShell32 -lGdi32 -lUser32
    gcc -shared -o glfw3.dll *.o -Wl,--out-implib,libglfw3.a -lOpengl32 -lShell32 -lGdi32 -lUser32
    copy "glfw3.dll" "../../../build/vendor" 
    copy "libglfw3.a" "../../../lib"
popd

@REM restore files from temporary directory
for %%W in (%search_words%) do (
    for /R %destination_folder% %%F in (*%%W*) do (
        move "%%F" "%source_folder%" >nul
    )
)

rmdir "temp"

@REM --------- End of GLFW Build ------------

set source_folder= 
set destination_folder= 
set search_words= 

popd

:skip_GLFW_build
pushd "build"


@REM Compiling with g++
g++ -g -std=c++17 ..\main.cpp -o main -I..\include -L..\lib -l:libglfw3.a -lOpengl32

popd
