#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("StaticRoutingSlash32Test");

int
main(int argc, char* argv[])
{
    // Allow the user to override any of the defaults and the above
    // DefaultValue::Bind ()s at run-time, via command-line arguments
    CommandLine cmd(__FILE__);
    cmd.Parse(argc, argv);

    Ptr<Node> nA = CreateObject<Node>();
    Ptr<Node> nB = CreateObject<Node>();
    Ptr<Node> nC = CreateObject<Node>();

    NodeContainer c = NodeContainer(nA, nB, nC);

    InternetStackHelper internet;
    Ipv4StaticRoutingHelper staticRoutingHelper;
    internet.SetRoutingHelper(staticRoutingHelper);
    internet.Install(c);

    // Point-to-point links
    NodeContainer nAnB = NodeContainer(nA, nB);
    NodeContainer nBnC = NodeContainer(nB, nC);

    // We create the channels first without any IP addressing information
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));
    NetDeviceContainer dAdB = p2p.Install(nAnB);

    NetDeviceContainer dBdC = p2p.Install(nBnC);

    // Later, we add IP addresses.
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0", "255.255.255.252");
    Ipv4InterfaceContainer iAiB = ipv4.Assign(dAdB);

    ipv4.SetBase("10.1.2.0", "255.255.255.252");
    Ipv4InterfaceContainer iBiC = ipv4.Assign(dBdC);

    Ipv4StaticRoutingHelper ipv4RoutingHelper;
    // Create static routes from A to C
    Ptr<Ipv4StaticRouting> staticRoutingA = ipv4RoutingHelper.GetStaticRouting(nA->GetObject<Ipv4>());
    // The ifIndex for this outbound route is 1; the first p2p link added
    staticRoutingA->AddHostRouteTo(Ipv4Address("10.1.2.2"), Ipv4Address("10.1.1.2"), 1);
    Ptr<Ipv4StaticRouting> staticRoutingB = ipv4RoutingHelper.GetStaticRouting(nB->GetObject<Ipv4>());
    // The ifIndex we want on node B is 2; 0 corresponds to loopback, and 1 to the first point to
    // point link
    staticRoutingB->AddHostRouteTo(Ipv4Address("10.1.2.2"), Ipv4Address("10.1.2.2"), 2);

    uint16_t port = 9; // Discard port (RFC 863)
    UdpClientHelper client ( iBiC.GetAddress(1), 9);
    client.SetAttribute ("MaxPackets", UintegerValue (3));
    client.SetAttribute ("Interval", TimeValue (Seconds (0.05)));
    client.SetAttribute ("PacketSize", UintegerValue (1024));

    ApplicationContainer apps = client.Install (c.Get (0));
    apps.Start (Seconds (1.0));
    apps.Stop (Seconds (10.0));

    // Create a packet sink to receive these packets
    UdpServerHelper server (port);
    apps = server.Install(nC);
    apps.Start(Seconds(1.0));
    apps.Stop(Seconds(10.0));

    AsciiTraceHelper ascii;
    p2p.EnableAsciiAll(ascii.CreateFileStream("static-routing-slash32.tr"));
    p2p.EnablePcapAll("static-routing-slash32");

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
