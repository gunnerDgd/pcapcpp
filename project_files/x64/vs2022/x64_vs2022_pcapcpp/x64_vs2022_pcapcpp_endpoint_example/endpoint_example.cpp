#include <pcapcpp/endpoint/endpoint.hpp>
#include <pcapcpp/interface/enumerator.hpp>

#include <iostream>

int main()
{
	pcapcpp::interface_enumerator if_enum;
	pcapcpp::network_interface    if_network = if_enum[3];

	for(int i = 0 ; i < if_enum.count() ; i++)
		std::cout << if_enum[i].description() << std::endl;

	pcapcpp::device::operation_mode if_device_opmode;
	pcapcpp::device					if_device  (if_network, if_device_opmode);
	pcapcpp::endpoint				if_endpoint(if_device);
	
	pcapcpp::raw<>  if_raw_packet;
					if_endpoint  .capture_once(if_raw_packet);
	std::cout << if_raw_packet.packet_size() << std::endl;
}