#/bin/bash
#
# run daemon that 
# - reads the modbus
# - writes the result to shared memory
# - waits for outputs on mailbox
#
../../daemons/modbus/client/modbus_client modbus.ini
