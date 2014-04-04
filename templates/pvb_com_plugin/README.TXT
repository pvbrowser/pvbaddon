You can substitute the pvbrowser transport layer using plugins.

This might be used for example:
- to do a custom authentification like exchanging a public key on connect and verification against a private key
- to compress data by using zlib
- to encrypt data using openSSL
- to use a serial line instead of TCP
..

The plugins presented here are only a template and do merely the same as the original communication.
You may take them as a starting point for your own experiments.

The plugin on the server side is specified by command line args to the server.
Example
./pvsexample -communication_plugin=/opt/pvbaddon/templates/pvb_com_plugin/server/libpvs_com_plugin.so -use_communication_plugin

The plugin on the client side is specified by a parameter within the pvbrowser ini file.
Example:
pvb_com_plugin=/opt/pvbaddon/templates/pvb_com_plugin/client/libpvb_com_plugin.so

The plugins may be active on startup of client and server or
they may be switched on/off while the communication is on.


