#!/bin/bash
#ffmpeg -i ~/murx.mpg -f mjpeg - | ./webcam_client example2.ini 
ffmpeg -i /var/run/media/lehrig/230B47A713C19410/fotos/album/2008-07-22/katzentoeter.avi -f mjpeg - | ./webcam_client example2.ini
