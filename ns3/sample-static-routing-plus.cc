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
    NodeContainer c;
    c.Create (8);

    InternetStackHelper internet;
    Ipv4StaticRoutingHelper staticRoutingHelper;
    internet.SetRoutingHelper(staticRoutingHelper);
    internet.Install(c);

    // We create the channels first without any IP addressing information
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));

    NetDeviceContainer deviceLine1 = p2p.Install(c.Get(1), c.Get(3));
    NetDeviceContainer deviceLine2 = p2p.Install(c.Get(2), c.Get(3));
    NetDeviceContainer deviceLine3 = p2p.Install(c.Get(0), c.Get(3));
    NetDeviceContainer deviceLine4 = p2p.Install(c.Get(4), c.Get(3));
    NetDeviceContainer deviceLine5 = p2p.Install(c.Get(5), c.Get(3));
    NetDeviceContainer deviceLine6 = p2p.Install(c.Get(6), c.Get(3));
    NetDeviceContainer deviceLine7 = p2p.Install(c.Get(7), c.Get(3));

    // Later, we add IP addresses.
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0", "255.255.255.252");
    Ipv4InterfaceContainer interLine1 = ipv4.Assign(deviceLine1);
    ipv4.SetBase("10.1.2.0", "255.255.255.252");
    Ipv4InterfaceContainer interLine2 = ipv4.Assign(deviceLine2);
    ipv4.SetBase("10.1.3.0", "255.255.255.252");
    Ipv4InterfaceContainer interLine3 = ipv4.Assign(deviceLine3);
    ipv4.SetBase("10.1.4.0", "255.255.255.252");
    Ipv4InterfaceContainer interLine4 = ipv4.Assign(deviceLine4);
    ipv4.SetBase("10.1.5.0", "255.255.255.252");
    Ipv4InterfaceContainer interLine5 = ipv4.Assign(deviceLine5);
    ipv4.SetBase("10.1.6.0", "255.255.255.252");
    Ipv4InterfaceContainer interLine6 = ipv4.Assign(deviceLine6);
    ipv4.SetBase("10.1.7.0", "255.255.255.252");
    Ipv4InterfaceContainer interLine7 = ipv4.Assign(deviceLine7);

    Ipv4StaticRoutingHelper ipv4RoutingHelper;
    Ptr<Ipv4StaticRouting> staticRoutingA = ipv4RoutingHelper.GetStaticRouting(c.Get(1)->GetObject<Ipv4>());
    staticRoutingA->AddHostRouteTo(Ipv4Address("10.1.4.1"), Ipv4Address("10.1.1.2"), 1);
    Ptr<Ipv4StaticRouting> staticRoutingB = ipv4RoutingHelper.GetStaticRouting(c.Get(3)->GetObject<Ipv4>());
    staticRoutingB->AddHostRouteTo(Ipv4Address("10.1.4.1"), Ipv4Address("10.1.4.1"), 4);

    uint16_t port = 9;
    UdpClientHelper client ( interLine4.GetAddress(0), 9);
    client.SetAttribute ("MaxPackets", UintegerValue (3));
    client.SetAttribute ("Interval", TimeValue (Seconds (0.05)));
    client.SetAttribute ("PacketSize", UintegerValue (1024));

    ApplicationContainer apps = client.Install (c.Get(1));
    apps.Start (Seconds (1.0));
    apps.Stop (Seconds (10.0));

    UdpServerHelper server (port);
    apps = server.Install(c.Get(4));
    apps.Start(Seconds(1.0));
    apps.Stop(Seconds(10.0));

    AsciiTraceHelper ascii;
    p2p.EnableAsciiAll(ascii.CreateFileStream("static-routing-slash32.tr"));
    p2p.EnablePcapAll("static-routing-slash32");

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
