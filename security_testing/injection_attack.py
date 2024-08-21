from pymodbus.client import ModbusTcpClient
import time

client = ModbusTcpClient("192.168.0.106")
client.connect()

rr = client.read_holding_registers(1, 1)
print(rr.registers)

input_register = client.read_input_registers(100, 1)
print(input_register.registers)
client.write_register(1, 2800)

time.sleep(2)
coil_value = client.read_coils(0, 1)
print(coil_value.bits[0])


while True:
    # time.sleep(0.01)
    client.write_coil(0, False)
    coil_value = client.read_coils(0, 1)
    print(coil_value.bits[0])