#include <pcapcpp/endpoint/endpoint.hpp>
#include <iostream>

pcapcpp::endpoint::endpoint (device_type& if_dev) : __M_ep_device(if_dev) {  }
pcapcpp::endpoint::~endpoint()											  {  }

pcapcpp::raw<> pcapcpp::endpoint::operator()()
{
	endpoint_header	    ep_hdr;
	const std::uint8_t* ep_raw = pcap_next(__M_ep_device.__M_if_device_handle, &ep_hdr);

	return raw<>((raw<>::pointer_type)ep_raw, ep_hdr.len);
}