void outputDataToUdp()
{
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(AcXAvg);
    Udp.write(", ");
    Udp.write(AcYAvg);
    Udp.write(", ");
    Udp.write(AcZAvg);
    Udp.write(", ");
    Udp.write(GyXAvg);
    Udp.write(", ");
    Udp.write(GyYAvg);
    Udp.write(", ");
    Udp.write(GyZAvg);
    Udp.endPacket();
}

