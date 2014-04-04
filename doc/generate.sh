#!/bin/bash
########################
# generate the example #
########################

cd ..

echo "h2=pvbaddon Verzeichnis Struktur" > doc/de_tree.txt
echo "pre=begin"                       >> doc/de_tree.txt
tree -d                                >> doc/de_tree.txt
echo "pre=end"                         >> doc/de_tree.txt

echo "h2=pvbaddon directory structure"  > doc/en_tree.txt
echo "pre=begin"                       >> doc/en_tree.txt
tree -d                                >> doc/en_tree.txt
echo "pre=end"                         >> doc/en_tree.txt

cd doc

### english ###################################################################
rm html/en_*
rlbb2html -hmax=2 -language=en "-back=Back"        "-home=Home"   "-forward=Forward" "-banner=pvbrowser addon" "-title=pvbaddon (c) pvbrowser 2008"

### deutsch ###################################################################
rm html/de_*
rlbb2html -hmax=2 -language=de "-back=Zur&uuml;ck" "-home=Inhalt" "-forward=Vor"     "-banner=pvbrowser addon" "-title=pvbaddon (c) pvbrowser 2008"
