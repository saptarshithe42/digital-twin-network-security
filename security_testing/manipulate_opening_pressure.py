from pymodbus.client import ModbusTcpClient

# host = "192.168.0.106"
host = input("Enter Host IP : ")
client = ModbusTcpClient(host)
client.connect()

# opening pressure value
opening_pressure_value = client.read_holding_registers(1, 1).registers[0]
print("Opening Pressure Value : ", opening_pressure_value)

# new_value = 3500
new_value = int(input("Enter new opening pressure : "))
client.write_register(1, new_value)