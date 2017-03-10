echo off
REM echo %1
set cmake_path=%1
REM echo %cmake_path%
cd %cmake_path%
conan install