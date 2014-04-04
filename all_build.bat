@echo off
set CURRENT=%CD%
IF NOT DEFINED MYROOT (GOTO :ERROR)

rem make foreign
cd %MYROOT%
cd foreign
call build.bat %1

rem myapps
cd %MYROOT%
cd win
call bat\build.bat
del /q %MYROOT%\win\temp\*.*
cd %CURRENT%
goto :END


:ERROR
echo MYROOT is not set ! run login.bat


:END
