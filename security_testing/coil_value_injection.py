from pymodbus.client import ModbusTcpClient
import time

# host = "192.168.0.106"
host = input("Enter Host IP : ")
client = ModbusTcpClient(host)
client.connect()

# current pressure value
current_pressure_value = client.read_input_registers(100, 1).registers[0]
print("Current Pressure : ", current_pressure_value)

# opening pressure value
opening_pressure_value = client.read_holding_registers(1, 1).registers[0]
print("Opening Pressure Value : ", opening_pressure_value)

# coil value
coil_value = client.read_coils(0, 1).bits[0]
print("Coil Status : ", coil_value)

# new_coil_value = False 
new_coil_value = bool(input("Enter new coil value (True / False) : "))

while True:
    # time.sleep(0.01)
    client.write_coil(0, new_coil_value)
    coil_value = client.read_coils(0, 1).bits[0]
    print("Coil Status : ", coil_value)