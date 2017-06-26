#include "../LightMonitorSketch/ntp_client.h"


NtpClient::NtpClient()
{

}

NtpClient::~NtpClient()
{

}

void NtpClient::begin(uint16_t udp_listen_port)
{

}

time_t NtpClient::get_time() const
{
    return time(NULL);
}
