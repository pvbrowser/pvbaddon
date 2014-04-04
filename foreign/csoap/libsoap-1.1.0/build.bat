set PVBDIR     = Z:\cc\priv\cvs\pvb 
set LIBXML2DIR = Z:\temp\win\libxml2-2.6.23.win32\libxml2-2.6.23.win32 
set CSOAPDIR   = Z:\temp\csoap\libsoap-1.1.0 
set OPENSSLDIR = Z:\temp\win\openssl-0.9.7e.win32\openssl-0.9.7e.win32 
qmake libsoap.pro -o Makefile.win
nmake /f Makefile.win

