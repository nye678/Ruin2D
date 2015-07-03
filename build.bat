@echo off
cls
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x64

if not exist build mkdir build
pushd .\build

cl /Z7 /MD /FeRuin2D /Fm /EHsc ^
/I"..\lib\rapidjson-0.11\rapidjson\include" ^
/I"..\lib\freetype-2.6\include" ^
/I"..\lib\lpng1617" ^
/I"..\lib\gl3w\include" ^
/I"..\lib\glfw\include" ^
/I"..\lib\glm" ^
/I"..\inc" ^
..\lib\gl3w\src\gl3w.c ^
..\code\*.cpp ^
zlib.lib libpng16.lib freetype.lib glfw3.lib ^
opengl32.lib user32.lib gdi32.lib shell32.lib ^
/link ^
/incremental:no ^
/libpath:"..\lib\glfw\build\src\Release" ^
/libpath:"..\lib\freetype-2.6\x64\Release" ^
/libpath:"..\lib\lpng1617\projects\vstudio\x64\Release Library"

popd

rem kernel32.lib
rem user32.lib
rem gdi32.lib
rem winspool.lib
rem comdlg32.lib
rem advapi32.lib
rem shell32.lib
rem ole32.lib
rem oleaut32.lib
rem uuid.lib
rem odbc32.lib
rem odbccp32.lib