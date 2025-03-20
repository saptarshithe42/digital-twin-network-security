import requests.auth
from mininet.topo import Topo
from mininet.net import Mininet
from mininet.cli import CLI
from mininet.node import OVSSwitch, RemoteController, Host
from time import sleep
import random
import threading
import requests
import json
from types import SimpleNamespace


class MyTopo(Topo):
    "Simple topology example."

    def build(self):
        s1 = self.addSwitch("s1", ip="0.0.0.0", protocols="OpenFlow13")
        s2 = self.addSwitch("s2", ip="0.0.0.0", protocols="OpenFlow13")
        s3 = self.addSwitch("s3", ip="0.0.0.0", protocols="OpenFlow13")

        # h1 = self.addHost("h1", ip="10.0.0.1", defaultRoute=None)
        # h2 = self.addHost("h2", ip="10.0.0.2", defaultRoute=None)
        # h3 = self.addHost("h3", ip="10.0.0.3", defaultRoute=None)
        # h4 = self.addHost("h4", ip="10.0.0.4", defaultRoute=None)

        h1 = self.addHost("h1", ip="10.0.0.1")
        h2 = self.addHost("h2", ip="10.0.0.2")
        h3 = self.addHost("h3", ip="10.0.0.3")
        h4 = self.addHost("h4", ip="10.0.0.4")

        self.addLink(s1, s2)
        self.addLink(s2, s3)

        self.addLink(s1, h1)
        self.addLink(s1, h2)
        self.addLink(s3, h3)
        self.addLink(s3, h4)


def startCLI(net):
    CLI(net)


if __name__ == "__main__":
    # Initialize Mininet with the custom topology
    topo = MyTopo()

    remote_controller = RemoteController("c0", ip="127.0.0.1", port=6653)

    net = Mininet(topo=topo, switch=OVSSwitch, build=False, controller=None)

    net.addController(remote_controller)

    net.build()
    net.addNAT().configDefault()
    net.start()

    t2 = threading.Thread(target=startCLI, name="startCLI", args=[net])

    try:
        t2.start()
        h1: Host = net.get("h1")
        h1.cmd("sudo python3 dns_server.py")
        h2: Host = net.get("h2")
        # h2.cmd("sudo python3 configure_nameserver.py")
        h3: Host = net.get("h3")
        # h3.cmd("sudo python3 configure_nameserver.py")
        h4: Host = net.get("h4")
        # h4.cmd("sudo python3 configure_nameserver.py")

    except KeyboardInterrupt:
        print("Stopping the network.")
    finally:
        # CLI(net)  # Drop into CLI for further testing if needed
        t2.join()
        net.stop()
