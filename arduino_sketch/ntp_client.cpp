#include "ntp_client.h"

#include "tracing.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


// NTP Servers:
static const char ntpServerName[] = "us.pool.ntp.org";
//static const char ntpServerName[] = "time.nist.gov";
//static const char ntpServerName[] = "time-a.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-b.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-c.timefreq.bldrdoc.gov";

NtpClient::NtpClient() : m_udp(NULL)
{
}

NtpClient::~NtpClient()
{
	delete m_udp;
}

void NtpClient::begin(uint16_t udp_listen_port)
{
	m_udp = new WiFiUDP;
	inf_printf("Starting UDP\n");
	m_udp->begin(udp_listen_port);
	inf_printf("Local NTP UDP port: %u\n", m_udp->localPort());
}

time_t getNtpTime(WiFiUDP & udp);

time_t NtpClient::get_time() const
{
	return getNtpTime((WiFiUDP &)*m_udp);
}

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

void sendNTPpacket(WiFiUDP & udp, IPAddress &address);

time_t getNtpTime(WiFiUDP & udp)
{
	IPAddress ntpServerIP; // NTP server's ip address

	while (udp.parsePacket() > 0); // discard any previously received packets
	inf_printf("Transmit NTP Request\n");
	// get a random server from the pool
	WiFi.hostByName(ntpServerName, ntpServerIP);
	inf_printf("%s: %s\n", ntpServerName, ntpServerIP.toString().c_str());
	sendNTPpacket(udp, ntpServerIP);
	uint32_t beginWait = millis();
	while (millis() - beginWait < 1500) {
		int size = udp.parsePacket();
		if (size >= NTP_PACKET_SIZE) {
			inf_printf("Received NTP Response\n");
			udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
			unsigned long secsSince1900;
			// convert four bytes starting at location 40 to a long integer
			secsSince1900 = (unsigned long)packetBuffer[40] << 24;
			secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
			secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
			secsSince1900 |= (unsigned long)packetBuffer[43];
			return secsSince1900 - 2208988800UL;
		}
	}
	inf_printf("No NTP Response :-(\n");
	return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(WiFiUDP & udp, IPAddress &address)
{
	// set all bytes in the buffer to 0
	memset(packetBuffer, 0, NTP_PACKET_SIZE);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	packetBuffer[0] = 0b11100011;   // LI, Version, Mode
	packetBuffer[1] = 0;     // Stratum, or type of clock
	packetBuffer[2] = 6;     // Polling Interval
	packetBuffer[3] = 0xEC;  // Peer Clock Precision
							 // 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12] = 49;
	packetBuffer[13] = 0x4E;
	packetBuffer[14] = 49;
	packetBuffer[15] = 52;
	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:
	udp.beginPacket(address, 123); //NTP requests are to port 123
	udp.write(packetBuffer, NTP_PACKET_SIZE);
	udp.endPacket();
}
