import socket
from cryptography.fernet import Fernet

MULTICAST_GROUP = "224.0.0.1"  # Reserved multicast IP range
PORT = 5000

# Shared encryption key (same one from the controller)
key = b"zycV5r2A98In8HHBF9aGq3JZhbUVnOrehDa-_WmeGwU="  # Same key used in the controller
cipher = Fernet(key)

# Setup socket to listen to multicast
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# Bind to the Mininet host's specific IP
host_ip = "10.0.0.2"  # Change this for each host, e.g. h2 -> 10.0.0.2, h3 -> 10.0.0.3
sock.bind((host_ip, PORT))

# Join multicast group
mreq = socket.inet_aton(MULTICAST_GROUP) + socket.inet_aton(host_ip)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

# Receive encrypted message
while True:
    data, _ = sock.recvfrom(1024)
    decrypted_ip = cipher.decrypt(data).decode()

    print(f"Received virtual DNS IP: {decrypted_ip}")

    # Update resolv.conf (requires sudo)
    with open("/etc/resolv.conf", "w") as f:
        f.write(f"nameserver {decrypted_ip}\n")


# from cryptography.fernet import Fernet
# import socket

# # Host Side:


# def host_receive(key, local_ip, port):
#     sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#     sock.bind((local_ip, port))
#     f = Fernet(key)
#     while True:
#         encrypted_data, addr = sock.recvfrom(1024)
#         try:
#             decrypted_data = f.decrypt(encrypted_data).decode("utf-8")
#             print(f"Received: {decrypted_data}")
#         except:
#             print("decryption failure")


# local_ip = "0.0.0.0"  # listen to all IPs for incomming udp packets.
# # host_receive(key, local_ip, port)
# host_receive(b"zycV5r2A98In8HHBF9aGq3JZhbUVnOrehDa-_WmeGwU=", local_ip, 5000)
