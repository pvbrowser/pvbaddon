#!/bin/bash
g++ -Wall -o ssl-server SSL-Server.cpp -L/usr/lib -lssl -lcrypto
g++ -Wall -o ssl-client SSL-Client.cpp -L/usr/lib -lssl -lcrypto

