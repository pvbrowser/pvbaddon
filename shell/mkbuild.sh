echo "create shell/build.sh"
find . -name "*.pro" -printf "shell/make.sh %h \$1\n" > shell/build.sh
chmod ugoa+x shell/build.sh

echo "create win/bat/build.bat"
find . -name "*.pro" -printf "call bat\\\make_module.bat %h %f\n" > win/temp/find1.dat
sed -e 's/.\///'         win/temp/find1.dat > win/temp/find2.dat
sed -e 's/\//\\/g'       win/temp/find2.dat > win/bat/build.bat

