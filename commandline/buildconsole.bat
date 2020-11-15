echo Start Build
@set path=%path%;G:\Program Files (x86)\vs2017\VC\Tools\MSVC\14.16.27023\bin\Hostx64\x64;G:\Program Files (x86)\vs2017\VC\Auxiliary\Build
call vcvars64.bat
echo Setup Enviroment
cl.exe main.cpp /link /SUBSYSTEM:CONSOLE user32.lib gdi32.lib
echo End Build