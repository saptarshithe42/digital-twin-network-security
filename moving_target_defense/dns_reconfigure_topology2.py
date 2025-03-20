# #!/usr/bin/env python

# from mininet.net import Mininet
# from mininet.node import Controller, RemoteController, OVSController
# from mininet.node import CPULimitedHost, Host, Node
# from mininet.node import OVSKernelSwitch, UserSwitch
# from mininet.node import IVSSwitch
# from mininet.cli import CLI
# from mininet.log import setLogLevel, info
# from mininet.link import TCLink, Intf
# from subprocess import call


# def myNetwork():

#     net = Mininet(topo=None, build=False, ipBase="10.0.0.0/8")

#     info("*** Adding controller\n")
#     # remote_controller = RemoteController("c0", ip="127.0.0.1", port=6653)
#     # c0 = net.addController(remote_controller)
#     # c0 = net.addController(name="c0", controller=Controller, protocol="tcp", port=6633)

#     info("*** Add switches\n")
#     s1 = net.addSwitch("s1", cls=OVSKernelSwitch, protocols="OpenFlow13")
#     s2 = net.addSwitch("s2", cls=OVSKernelSwitch, protocols="OpenFlow13")
#     s3 = net.addSwitch("s3", cls=OVSKernelSwitch, protocols="OpenFlow13")

#     info("*** Add hosts\n")
#     h1 = net.addHost("h1", cls=Host, ip="10.0.0.1")
#     h2 = net.addHost("h2", cls=Host, ip="10.0.0.2")
#     h3 = net.addHost("h3", cls=Host, ip="10.0.0.3")
#     h4 = net.addHost("h4", cls=Host, ip="10.0.0.4")

#     info("*** Add links\n")
#     net.addLink(h1, s1)
#     net.addLink(h2, s1)
#     net.addLink(s1, s2)
#     net.addLink(s2, s3)
#     net.addLink(s3, h3)
#     net.addLink(s3, h4)

#     info("*** Starting network\n")
#     net.build()
#     info("*** Starting controllers\n")
#     for controller in net.controllers:
#         controller.start()

#     info("*** Starting switches\n")
#     net.get("s1").start([c0])
#     net.get("s2").start([c0])
#     net.get("s3").start([c0])

#     info("*** Post configure switches and hosts\n")

#     net.addNAT().configDefault()

#     CLI(net)


# myNetwork()


# from mininet.topo import Topo


# class MyTopo(Topo):
#     "Simple topology example."

#     def build(self):
#         s1 = self.addSwitch("s1", protocols="OpenFlow13")
#         s2 = self.addSwitch("s2", protocols="OpenFlow13")
#         s3 = self.addSwitch("s3", protocols="OpenFlow13")
#         h1 = self.addHost("h1", ip="10.0.0.1", defaultRoute=None)
#         h2 = self.addHost("h2", ip="10.0.0.2", defaultRoute=None)
#         h3 = self.addHost("h3", ip="10.0.0.3", defaultRoute=None)
#         h4 = self.addHost("h4", ip="10.0.0.4", defaultRoute=None)
#         self.addLink(h1, s1)
#         self.addLink(h2, s1)
#         self.addLink(s1, s2)
#         self.addLink(s2, s3)
#         self.addLink(s3, h3)
#         self.addLink(s3, h4)


# topos = {"mytopo": (lambda: MyTopo())}


from mininet.topo import Topo


class MyTopo(Topo):
    "Simple topology example."

    def build(self):
        s1 = self.addSwitch("s1", ip="0.0.0.0")
        s2 = self.addSwitch("s2", ip="0.0.0.0")
        h1 = self.addHost("h1", ip="10.0.0.1", defaultRoute=None)
        h2 = self.addHost("h2", ip="10.0.0.2", defaultRoute=None)
        h3 = self.addHost("h3", ip="10.0.0.3", defaultRoute=None)
        h4 = self.addHost("h4", ip="10.0.0.4", defaultRoute=None)
        self.addLink(h1, s1)
        self.addLink(s1, h2)
        self.addLink(s1, s2)
        self.addLink(s2, h3)
        self.addLink(s2, h4)


topos = {"mytopo": (lambda: MyTopo())}
