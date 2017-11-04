###################
rlproxy description
###################

rlproxy is a commandline tool that uses rllib (rlSocket and rlThread class) and optionally openssl.
It can act as "man in the middle".

You can use several rlproxy instances in a chain.
Either the "accept_side" or the "connect_to_side" of rlproxy can be encrypted with ssl.

Thus it is possibe to use 2 rlproxy instances for encrypting network traffic (for example) over the internet.
The first rlproxy will run within the LAN (for example on localhost).
The second rlproxy will run on the server that is connected over an insecure channel like the internet.
The rlproxy commands could look as follows:
./rlproxy -accept_port=5052 -connect_adr=localhost -connect_port=5060 -forward_after_tunnel -use_socket_on_accept
./rlproxy -accept_port=5060 -forward_after_tunnel -use_ssl_on_accept
Where the first rlproxy would wait on "accept_port=5052" and "forward_after_tunnel". 
The "accept_side" will "use_socket_on_accept" and thus the "connect_to_side" will use ssl.
The second rlproxy would wait on "accept_port=5060" and "use_ssl_on_accept" side and plain socket on the connect_to_side.
A pvbrowser startup could look as follows (proxy can also be specified within the pvbrowser inifile):
pvbrowser pv://pvbrowser.org -proxyadr=localhost -proxyport=5052
Behind the second proxy the connection to "pv://pvbrowser.org" will be done.

Since rlproxy starts "a_connection" thread and "a_receiver" thread for each client that connects,
you can use any number of clients connected over 1 proxy.

It is also possible to use rlproxy as a HTTP Proxy for example with the command:
./rlproxy -accept_port=5050 -forward_before_tunnel
And setting localhost:5050 as proxy within your browser.

Currently rlproxy does NOT support HTTPS Proxy.

######################
Background information
######################

See:
http://simplestcodings.blogspot.de/2010/08/secure-server-client-using-openssl-in-c.html
./rlproxy -accept_port=5060 -connect_adr=pvbrowser.org -connect_port=5050 -use_ssl_on_accept
./rlproxy -accept_port=5050 -connect_adr=localhost -connect_port=5060 -use_socket_on_accept

Alice and Bob agree on a random number x. 
Alice calculates xa, where a is a large prime number known only to Alice, and sends that to Bob. 
Bob calculates xb and sends it to Alice. 
Alice calculates (xb)a, and Bob calculates (xa)b. 
Since (xa)b = (xb)a = xab, 
Alice and Bob now both know the number xab and can use it as an encryption key. 
The beauty of this is that Bob doesn't know a, Alice doesn't know b, and any eavesdroppers don't know either number 
(because calculating a from xa, in the case of large numbers, would take years).

As supercat points out, this by itself is still susceptible to a man-in-the-middle attack, and 
that's why at least one end of the transaction needs to authenticate using a certificate. 
To be accurate, though, it is not the server that checks this, it's the browser, and 
most browsers will let the user continue if the certificate is invalid (or possibly even garbage). 
In that event, the connection will still be considerably more secure than a regular connection. 
To listen in, you'd need to be able to manipulate IP routing or DNS lookups, and 
you'd have to set it up before the connection was first made, which is not easy to do.

BTW the keypairs in certificates are not what's used to encrypt actual traffic;
they are used to establish a new single-use key for a much faster symmetric cipher (such as DES) which then does the rest of the work.

<snip> ...

It's possible to establish an encrypted connection, yes, 
but it would still be possible that you're communicating with a cracked cpmputer instead of the real server. 
Like that, the cracked computer tells the server that he would be the client, decrypt all the data, store it and send the encrypted data to the client 
(and tell him he would be the server). 
So it's just a safe connection if there's no vulnerable point between the server and the client, which no one can guarantee.

See: http://stackoverflow.com/questions/3865039/is-a-https-connection-secure-without-a-valid-ssl-certificate#3865055

http://www.codeproject.com/Articles/326574/An-Introduction-to-Mutual-SSL-Authentication

http://stackoverflow.com/questions/21050366/testing-ssl-tls-client-authentication-with-openssl
openssl s_client -showcerts -connect localhost:5060 -key murx/client_cert/server.key 
http://openssl.6102.n7.nabble.com/Mutual-Authentication-td37588.html

