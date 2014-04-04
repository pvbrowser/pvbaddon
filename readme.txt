Building:

You need qmake installed on your system (qmake is within Qt4 from trolltech).

One example needs libpython2.5 library.
opcxmlda_client needs libxml2 library.
Please install them first.
The other components should build on every system.

### Linux and Mac ########################
./configure
make clean
make

You can
export mypause=true
in order to pause after makeing a module
export mypause=false
in order to reset mypause

### Windows ##############################
login.bat   # adjust this file and make shure to set the environment variables in there
all_build.bat

You can
SET MYPAUSE=TRUE
in order to pause after makeing a module
SET MYPAUSE=
in order to reset MYPAUSE

Attention: opcxmlda_client can only be compiled using Visual C++
           If you use MinGW there are some unresolved symbols.
           But the EXE build with Visual C++ is still available.
