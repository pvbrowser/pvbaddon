Building the documentation for the Embedded Widgets components
==============================================================

The API documentation for the Embedded Widgets components is included in
source code comments using the markup used by Doxygen.

To build the API documentation, you first need to install Doxygen, either
using a package supplied with your system or from the project's Web site:

  http://www.doxygen.org/

Doxygen should be run from the directory containing the file, "Doxyfile".
At the command line, enter this directory and type

  doxygen Doxyfile

to start the process of generating the documentation. When this has finished,
the API documentation should be present in the src/doc/html directory.
