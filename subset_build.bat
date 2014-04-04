@echo off
set CURRENT=%CD%
IF NOT DEFINED MYROOT (GOTO :ERROR)
cd %MYROOT%
cd win
call bat\build_subset.bat
del /q %MYROOT%\win\temp\*.*
cd %CURRENT%
goto :END


:ERROR
echo MYROOT is not set ! run login.bat


:END
