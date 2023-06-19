@echo off
REM Initialize variables. 
REM gcc should be set as an environment variable otherwise set the COMMAND variable as the path to gcc.exe
set "COMMAND=gcc"
set "PROJECT_NAME=example"
set "BUILD_DIR=.\bin\"
set "SOURCE_DIR=.\src\*.c"
set "INCLUDE_DIR=.\include"
set "LIB_DIR=.\lib"

REM Cleanup previous build if it exist.
if exist %BUILD_DIR%%PROJECT_NAME%.exe (
    del %BUILD_DIR%%PROJECT_NAME%.exe /Q
)

@echo on
@REM Command to compile the project.
%COMMAND% %SOURCE_DIR% -o%BUILD_DIR%%PROJECT_NAME% -I%INCLUDE_DIR% -L%LIB_DIR% -lmingw32 -lSDL2main -lSDL2 -lcimgui_sdl

@echo off
REM Check if project built successfully or not if it did run the project.
if exist %BUILD_DIR%%PROJECT_NAME%.exe (
    echo Build success!
    cd .\bin\
    START %PROJECT_NAME%.exe
) else (
    echo Build failed!
)