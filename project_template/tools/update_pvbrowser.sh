#!/bin/bash
# Install new version of pvbrowser and pvbaddon
#
# Give the project to the customer and
# then execute this file to install pvbrowser + pvbaddon.
# When pvbrowser is updatet you can execute this file again.
#
mkdir -p ~/pvbrowser/temp
cd       ~/pvbrowser/temp
rm -f pvb*.tar.gz

if [ "${HOSTTYPE}" = "x86_64" ]; then
  echo "Get 64 Bit Version"
  rm -f pvb64.tar.gz
  wget http://pvbrowser.de/pvbrowser/tar/pvb64.tar.gz
  tar -zxf pvb64.tar.gz
else
  echo "Get 32 Bit Version"
  rm -f pvb.tar.gz
  wget http://pvbrowser.de/pvbrowser/tar/pvb.tar.gz
  tar -zxf pvb.tar.gz
fi
wget http://pvbrowser.de/pvbrowser/tar/pvbaddon.tar.gz
tar -zxf pvbaddon.tar.gz

echo "Enter root password for installation"
sudo bash -c "cd pvb && ./install.sh && cd ../pvbaddon && ./install.sh"

rm -rf pvb/
rm -rf pvbaddon/

cd ~/pvbrowser
if [ -e readme.txt ]; then
  echo "~/pvbrowser is now updated"
else
  cp -r /opt/pvbaddon/project_template .
  echo "~/pvbrowser is now installed for the first time"
  echo "now you can create your own pvserver(s) within ~/pvbrowser"
fi

if [ -e ~/Desktop ]; then
  cp /opt/pvb/*.desktop ~/Desktop/
  echo "you can now start pvbrowser or pvdevelop using the desktop icons" 
fi

