https://mathias-kettner.de/lw_ca_zertifikat_erstellen.html

cd murxca

(xterm1)
./pvsexample -port=5051

(xterm2)
lehrig@nb5lehrig:~/cc/priv/pvbaddon/foreign/gnutls/murxca> /home/lehrig/cc/priv/pvbaddon/foreign/gnutls/gnutls/doc/examples/tlsproxy/build/tlsproxy -c localhost:5051 -l localhost:5052 -s -A cacert.pem -C servercert.pem -K serverkey.pem -n -n

(xterm3)
lehrig@nb5lehrig:~/cc/priv/pvbaddon/foreign/gnutls/murxca> /home/lehrig/cc/priv/pvbaddon/foreign/gnutls/gnutls/doc/examples/tlsproxy/build/tlsproxy -c localhost:5052 -l localhost:5053 -A cacert.pem -C servercert.pem -K serverkey.pem -n -n

(xterm4)
pvbrowser localhost:5053

Everything except tlsproxy was removed from gnutls folder
Original see: http://www.gnutls.org/

