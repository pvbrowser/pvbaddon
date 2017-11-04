http://simplestcodings.blogspot.de/2010/08/secure-server-client-using-openssl-in-c.html

Build certs:
openssl req -x509 -nodes -days 365 -newkey rsa:1024 -keyout mycert.pem -out mycert.pem
