template for a new pvbrowser based project

./install.sh # will copy it to ~/pvbrowser

############################################################

Within "tools" there are some small shell scripts
that may be usefull to you.

- mymake               # qmake + make
- myrun                # qmake + make + run your pvserver
- mydevelop            # start pvdevelop
- update_pvbrowser.sh  # wget pvbrowser from our server and update it
You may copy them to your ~/bin/ directory.

These tools can now be used in
- Eclipse
- vi(m)
- or any other development environment

In Eclipse define "mymake" as "Build Command" for your project.
In Eclipse define "myrun" + "mydevelop" as "External Commands".
In Eclipse open file /opt/pvb/doc/index.html in order to get our documentation.

vi(m) is excellent for developing pvserver at remote computers.
ssh -X user@remote # in order to login to remote computer and have X11
Now you can use
!myrun
!mydevelop
as shell command from vi(m)

Have a lot of fun:
Your pvbrowser community
