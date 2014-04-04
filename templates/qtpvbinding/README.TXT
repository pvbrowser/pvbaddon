The class PV in qtpvbinding should be used when you want to code your pvserver
with the Qt libraries. It uses QString and avoids casting.
Please derive your own classes from PV.
See also template ../qtDatabase

In order to use Qt you must set the following CONFIG in the project.pro file.

CONFIG   += qt warn_on release
//CONFIG  -= qt  # comment out this line


