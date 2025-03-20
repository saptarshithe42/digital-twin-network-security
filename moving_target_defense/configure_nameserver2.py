import random
import time
import os


fileName = "virtual_ip_pool.txt"

virtual_ips = []
with open(fileName, "r") as file:
    virtual_ips = file.read().split("\n")

SHUFFLE_INTERVAL = 30
RECONFIGURATION_INTERVAL = 10


while True:
    current_seed = int(time.time() / SHUFFLE_INTERVAL)
    previous_seed = current_seed - 1

    random.seed(current_seed)
    current_index = random.randint(0, len(virtual_ips) - 1)

    random.seed(previous_seed)
    previous_index = random.randint(0, len(virtual_ips) - 1)

    # Graceful handling of potential desync
    dns_server_ip = virtual_ips[current_index]
    if os.system(f"ping -c 1 {dns_server_ip}") != 0:  # If unreachable, fall back
        dns_server_ip = virtual_ips[previous_index]

    print(f"current_seed = {current_seed}, current_index = {current_index}")
    print(f"previous_seed = {previous_seed}, previous_index = {previous_index}")

    os.system(f'echo "nameserver {dns_server_ip}" | sudo tee /etc/resolv.conf')
    time.sleep(RECONFIGURATION_INTERVAL)
