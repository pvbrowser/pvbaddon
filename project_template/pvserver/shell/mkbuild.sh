echo "create shell/build.sh"
find . -name "*.pro" -printf "shell/make.sh %h \$1\n" > shell/build.sh
chmod ugoa+x shell/build.sh

