@echo off
set myroot=%CD%
set mymake=%MYROOT%\win\bat\make_module.bat

echo You may set MYPAUSE=TRUE to pause after compiling a module 
echo SET MYPAUSE=  in order to reset MYPAUSE
rem set MYPAUSE=TRUE

echo Now run all_build.bat

:MINGW
set PVBDIR=c:\programme\pvb
set MINGWDIR=C:\Qt\5.1.0\Tools\mingw48_32
set QTDIR=C:\Qt\5.1.0\5.1.0\mingw48_32
rem set MINGWDIR=c:\mingw-old
rem set QTDIR=c:\Qt\4.8.2
set PATH=%PVBDIR%\win-mingw\bin;%MINGWDIR%\bin;%QTDIR%\bin;c:\windows;c:\windows\system32
set PYTHONPATH=%PVBDIR%\win-mingw\bin;%PYTHONPATH%

:END
