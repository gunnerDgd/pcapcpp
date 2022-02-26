#include <pcapcpp/device/device.hpp>

pcapcpp::device::device (interface_type& if_net, operation_mode opmode) : __M_if_device_interface(if_net),
																		  __M_if_device_handle   (pcap_create(if_net.__M_if_name.c_str(), __M_if_device_errmsg)),
																		  __M_if_device_opmode   (opmode)
{
	pcap_set_rfmon  (__M_if_device_handle, (std::underlying_type_t<operation_mode::capture_mode>)__M_if_device_opmode.__M_opmode_capmode);
	pcap_set_promisc(__M_if_device_handle, (std::underlying_type_t<operation_mode::promiscuous>) __M_if_device_opmode.__M_opmode_pmode)  ;
	pcap_set_snaplen(__M_if_device_handle,														 __M_if_device_opmode.__M_opmode_caplen) ;
	pcap_set_timeout(__M_if_device_handle,														 __M_if_device_opmode.__M_opmode_timeout.count());

	pcap_activate   (__M_if_device_handle);
}
pcapcpp::device::~device()																												  
{
	pcap_close(__M_if_device_handle);
}