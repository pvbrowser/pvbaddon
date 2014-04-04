#####################################
# Modbus TCP simulator and          #
# Modbus TCP to RS232/RS485 Gateway #
# usage: mtss <filename.ini>        #
# default ini file = mtss.ini       #
#####################################

This is a commandline tool for simulating ModbusTCP.
You can use it as a Gateway also.
An INI file is used to configure mtts

#############
# Simulator #
#############
Within INI file you set
[TTY]
NAME=simulation
Then mtss will go to simulation mode and accept a Modbus TCP client on the given port.

[TCP]
PORT=5502
Instead of the standard Modbus port 502 it might be convenient to use a port>1024
because on Linux the lower ports can only be opened by processes with root privileges.

Depending on the
[OPTIONS]
mtss will print more or less.

For simulation it might be a good idea to set
[OPTIONS]
SHOW_REQUEST=0
SHOW_RESPONSE=0
SHOW_READ_REQUESTS=0
SHOW_WRITE_REQUESTS=1
In that case you will only see the data that is written by the Modbus client within the terminal.

While mtss is running you should open the INI file with an ASCII editor.
Please define the data that can be read by the Modbus TCP client within the INI file.
Example:
[SLAVE_1]
read0x00000=12 34 56 78 9a bc
This defines 6 bytes of hex data starting with address 0x00000Hex for slave 1.
You can define any address range for any valid slave address.
The Modbus read functions will read this data.
If data is not defined within the INI file it will be returned as 0.

If you change data within the INI file and write the file to disk mtss will use it.
Thus you are able to simulate changing input data.

#####################################
# Modbus TCP to RS232/RS485 Gateway #
#####################################
For using mtss as a gateway you must define the name of the tty/COM port.
Example for Linux:
[TTY]
NAME=/dev/ttyUSB0
BAUDRATE=B9600
Example for Windows:
[TTY]
NAME=COM1
BAUDRATE=B9600

Valid BAUDRATE are:
B300
B600
B1200
B1800
B2400
B9600
B19200
B38400
B57600
B115200
B230400
B460800
B500000

If
[TCP]
ALLOWED_CLIENT=any
any client will be allowed to connect to the gateway.
If
[TCP]
ALLOWED_CLIENT=127.0.0.1
only localhost will be allowed to connect to the gateway.
You may define the IP address of the client that is allowed the same way if it is not localhost.

