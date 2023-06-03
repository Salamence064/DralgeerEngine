@echo off

set CanRun= false

if exist "build/main.exe" (
    set CanRun= true
)

if %CanRun% == true (
    pushd "build/vendor"
    call "../main.exe"
    popd

    GOTO Finish
)

echo "'build/main.exe' not found. Run 'build.bat' first."

:Finish