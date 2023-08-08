@echo off

@REM todo look up how to precompile headers

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
    echo "GLFW folder is empty"
    GOTO FAILED
)

@REM check if GLEW folder is empty
dir /b /s /a "glew/" | findstr . > nul || (
    echo "GLEW folder is empty"
    GOTO FAILED
)

@REM check if imgui folder is empty
dir /b /s /a "imgui/" | findstr . > nul || (
    echo "imgui folder is empty"
    GOTO FAILED
)

if exist "build/vendor/glfw3.dll" (
    GOTO skip_GLFW_build
)


@REM --------- Start of GLFW Build ------------

echo "Building GLFW"
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

pushd "build"
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

set source_folder= 
set destination_folder= 
set search_words= 

popd

@REM --------- End of GLFW Build ------------


:skip_GLFW_build

if exist "build/vendor/glew32.dll" (
     GOTO SKIP_GLEW_BUILD
)


@REM --------- Start of GLEW Build ------------

echo "Building GLEW"
pushd "glew"

gcc -DGLEW_NO_GLU -O2 -w -Iinclude -DGLEW_BUILD -o src/glew.o -c src/glew.c
gcc -nostdlib -shared -Wl,-soname,libglew32.dll -Wl,--out-implib,lib/libglew32.dll.a -o lib/glew32.dll src/glew.o -L/mingw/lib -lglu32 -lOpengl32 -lGdi32 -lUser32 -lkernel32

@REM Create library file: lib/libglew32.dll.a
ar cr lib/libglew32.a src/glew.o

gcc -DGLEW_NO_GLU -DGLEW_MX -O2 -w -Iinclude -DGLEW_BUILD -o src/glew.mx.o -c src/glew.c
gcc -nostdlib -shared -Wl,-soname,libglew32mx.dll -Wl,--out-implib,lib/libglew32mx.dll.a -o libglew32mx.dll src/glew.mx.o -L/mingw/lib -lglu32 -lOpengl32 -lGdi32 -lUser32 -lkernel32

@REM Create library file: lib/libglew32mx.dll.a
ar cr lib/libglew32mx.a src/glew.mx.o

@REM Copy the files to the project's lib and build/vendor folders
pushd "lib"

copy "glew32.dll" "../../build/vendor"
copy "libglew32.a" "../../lib"
copy "libglew32.dll.a" "../../lib"
copy "libglew32mx.a" "../../lib"
copy "libglew32mx.dll.a" "../../lib"

popd

copy "libglew32mx.dll" "../build/vendor"

popd

@REM --------- End of GLEW Build ------------


:SKIP_GLEW_BUILD

@REM Copy the headers for ImGui to the project's include
if not exist "include/IMGUI/imgui.h" (
    pushd "imgui"
    copy "*.h" "../include/IMGUI"
    
    pushd "backends"
    copy "imgui_impl_glfw.h" "../../include/IMGUI"
    copy "imgui_impl_opengl3.h" "../../include/IMGUI"

    copy "imgui_impl_glfw.h" ".."
    copy "imgui_impl_opengl3*.h" ".."

    copy "imgui_impl_glfw.cpp" ".."
    copy "imgui_impl_opengl3.cpp" ".."
    
    popd
    popd
)

if exist "build/vendor/imgui.dll" (
     GOTO SKIP_IMGUI_BUILD
)


@REM --------- Start of ImGui Build ------------

echo "Building DearImGui"
pushd "imgui/"

if not exist "build" (
    echo "Creating 'build' directory"
    mkdir "build/"
)

if not exist "lib" (
    echo "Creating 'lib' directory"
    mkdir "lib/"
)

@REM create the object and library files
pushd "build/"

    g++ -O2 -w -I../../include -c ../*.cpp
    g++ -shared -Wl,-soname,../libimgui.dll -Wl,--out-implib,../lib/libimgui.a -o ../lib/imgui.dll *.o -L../../lib -l:libglfw3.a -l:libglew32.a -l:libglew32.dll.a -l:libglew32mx.a -l:libglew32mx.dll.a -lOpengl32 -lGdi32 -lUser32 -lkernel32

popd @REM "build/"

@REM copy the library files to the appropriate locations
pushd "lib/"

    copy "imgui.dll" "../../build/vendor/"
    copy "libimgui.a" "../../lib/"

popd @REM "lib/"

popd @REM "imgui/"

@REM --------- End of ImGui Build ------------


:SKIP_IMGUI_BUILD

pushd "build"

@REM Compiling with g++
g++ -g -DUNICODE -D_UNICODE -std=c++17 ../src/*.cpp -o main -I../include -L../lib -l:libglfw3.a -l:libglew32.a -l:libglew32.dll.a -l:libglew32mx.a -l:libglew32mx.dll.a -l:libimgui.a -lOpengl32 -lGdi32

popd

echo "Building complete"

:FAILED
