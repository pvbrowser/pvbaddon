@echo off
set FOREIGN=%CD%

echo make csoap
cd csoap/libsoap-1.1.0/win32/MinGW
call %FOREIGN%\make_module.bat %1
cd %FOREIGN%

echo make tuxeip
cd tuxeip\tuxeip-1.0\src
qmake tuxeip.pro.foreign
call %FOREIGN%\make_module.bat %1
cd %FOREIGN%

echo make libxml2
cd libxml2
cd win32
call pvb_build.bat
cd ..
cd ..

cd ..

