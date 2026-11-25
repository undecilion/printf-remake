@echo off

gcc main.c -o ..\bin\main.exe ^
 "..\functions\print.c" ^
 "..\functions\ascii\*.c" ^
 "..\functions\floating_point\*.c" ^
 "..\functions\floating_point\IEEE 754\*.c" ^
 "..\functions\integer\*.c" ^
 "..\functions\hex\*.c" ^
 -I "..\headers"
if %errorlevel% equ 0 (
  ..\bin\main.exe
)

pause