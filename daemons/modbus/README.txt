You can now use pvbaddon/daemons/modbus/client/modbus_client for data aquistion on modbus based systems.
modbus_client uses an ini file to describe what should be read from modbus.
If you choose modbus_client you can access the variables with clear text.

If you don't want to use variables in clear text because of performance issues
you can use Modbus over serial line and TCP as supported by the codegenerator
that is integrated into pvdevelop.  See: pvbaddon/demos/modbusserial

