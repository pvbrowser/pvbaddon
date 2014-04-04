#!/bin/bash

find . -name "*~"                -exec rm "{}" ";"
# find . -name "*.a"               -exec rm "{}" ";"
find . -name "*.o"               -exec rm "{}" ";"
# find . -name "lib*.so.*"         -exec rm "{}" ";"
find . -name "moc_*"             -exec rm "{}" ";"
# find . -name "qrc_*"             -exec rm "{}" ";"
find . -name "ui_*"              -exec rm "{}" ";"
