import subprocess
import re


def get_mininet_ip():
    try:
        # Run ifconfig and capture the output
        result = subprocess.run(["ifconfig"], capture_output=True, text=True)
        output = result.stdout

        # Find the first non-loopback interface with an IPv4 address
        interface = None
        ip_address = None

        for line in output.splitlines():
            # Match interface names like h2-eth0, h1-eth0, etc.
            match = re.match(r"^(\S+):", line)
            if match:
                interface = match.group(1)

            # Find the IPv4 address line for that interface
            if "inet " in line and "127.0.0.1" not in line:
                ip_address = line.split()[1]
                break

        return interface, ip_address

    except Exception as e:
        print(f"Error getting IP address: {e}")
        return None, None


if __name__ == "__main__":
    interface, ip = get_mininet_ip()
    if ip:
        print(f"My interface: {interface}")
        print(f"My IP address: {ip}")
    else:
        print("Could not determine IP address")
