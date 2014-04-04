set PVBDIR=Z:\cc\priv\cvs\pvb
set LIBXML2DIR=Z:\temp\win\libxml2-2.6.27
set CSOAPDIR=Z:\temp\csoap\libsoap-1.1.0
set OPENSSLDIR=Z:\temp\win\openssl-0.9.7e.win32
qmake opcxmlda_client.pro -o Makefile.win
nmake /f Makefile.win

