# import socket
# from cryptography.fernet import Fernet

# # Multicast group and port
# MULTICAST_GROUP = "224.0.0.1"
# PORT = 5007

# # Shared encryption key (generate once and distribute securely)
# # key = Fernet.generate_key()
# key = b"zycV5r2A98In8HHBF9aGq3JZhbUVnOrehDa-_WmeGwU="
# cipher = Fernet(key)

# with open("key.txt", "w") as f:
#     f.write(str(key))

# # Virtual DNS IP to send
# dns_virtual_ip = "192.168.100.10"

# # Encrypt the IP
# encrypted_ip = cipher.encrypt(dns_virtual_ip.encode())

# # Setup multicast socket
# sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
# sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 2)

# # Send encrypted message
# sock.sendto(encrypted_ip, (MULTICAST_GROUP, PORT))

# print(f"Sent encrypted DNS IP: {encrypted_ip}")


from cryptography.fernet import Fernet
import socket

# Controller Side:


def controller_broadcast(data, key, broadcast_ip, port):
    f = Fernet(key)
    encrypted_data = f.encrypt(data.encode("utf-8"))
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.sendto(encrypted_data, (broadcast_ip, port))


key = b"zycV5r2A98In8HHBF9aGq3JZhbUVnOrehDa-_WmeGwU="  # In a real example, this key needs to be shared securely.
broadcast_ip = (
    "224.1.1.1"  # multicast IP address, or use '<broadcast>' for layer 2 broadcast
)
port = 5000
data_to_send = "This is a secret message"
controller_broadcast(data_to_send, key, broadcast_ip, port)
