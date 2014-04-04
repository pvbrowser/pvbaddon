Building opcxmlda_client from source:

First you have to install "libcsoap" and "libxml2".

The version of libcsoap and nanohttp may differ on your system.
Thus you have to adjust this within opcxmlda_client.pro
unix:INCLUDEPATH  += /usr/local/include/libcsoap-1.1
unix:INCLUDEPATH  += /usr/local/include/nanohttp-1.1

Within "nanohttp-1.1/nanohttp/nanohttp-logging.h" there is a small error.
The error is within line 107.
Remove this or comment it out:
##########################
#ifdef __cplusplus
}
#endif
##########################

For building use:
make
