@set path=%path%;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build
call vcvars64.bat

cl.exe main.cpp /link /SUBSYSTEM:CONSOLE b.lib c.lib /OUT:a.exe