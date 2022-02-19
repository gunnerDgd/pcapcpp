#include <pcapcpp/device/device.hpp>

pcapcpp::device::device(interface_type& if_net, size_type if_cap_size, time_type if_timeout)
{
	__M_if_device_handle = pcap_open_live(if_net.__M_if_name.c_str(), if_cap_size, 1, if_timeout.count(), __M_if_device_errmsg);
}

pcapcpp::device::~device()
{
	pcap_close(__M_if_device_handle);
}