@set path=%path%;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build
call vcvars64.bat
cl.exe /EHsc /c libd.cpp
LIB.EXE /OUT:d.lib libd.obj