echo Start Build
@set path=%path%;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023\bin\Hostx64\x64;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build
rem @set path=%path%;G:\Program Files (x86)\vs2017\VC\Tools\MSVC\14.16.27023\bin\Hostx64\x64;G:\Program Files (x86)\vs2017\VC\Auxiliary\Build
call vcvars64.bat
echo Setup Enviroment
cl.exe winmain.cpp /link /SUBSYSTEM:WINDOWS user32.lib kernel32.lib gdi32.lib
echo End Build