@echo off
IF NOT DEFINED MYROOT (GOTO :NOMYROOT)
set SOURCE=%1
set PROFILE=%2
set BACK=%CD%

echo #
echo # win\bat\make_module.bat %SOURCE% %PROFILE%
echo #

cd  %MYROOT%\%SOURCE%

rem ### mingw ############################
:MINGW
qmake       %PROFILE% -o Makefile
mingw32-make          -f Makefile
rem ######################################

cd %BACK%
GOTO :END

:NOMYROOT
echo "ERROR: MYROOT not defined"

:END
IF DEFINED MYPAUSE (PAUSE)
