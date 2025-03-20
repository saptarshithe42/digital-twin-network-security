import random
import time
import os

fileName = "virtual_ip_pool.txt"

file = open(file=fileName, mode="r")

virtual_ips = file.read().split("\n")
print(virtual_ips)
file.close()

SHUFFLE_INTERVAL = 30
RECONFIGURATION_INTERVAL = 5

while True:
    seed = int(time.time() / SHUFFLE_INTERVAL) 
    random.seed(seed)
    index = random.randint(0, len(virtual_ips) - 1)
    dns_server_ip = virtual_ips[index]
    print(f"seed = {seed}, random index = {index}")

    os.system(f'echo "nameserver {dns_server_ip}" | sudo tee /etc/resolv.conf')
    time.sleep(RECONFIGURATION_INTERVAL)
