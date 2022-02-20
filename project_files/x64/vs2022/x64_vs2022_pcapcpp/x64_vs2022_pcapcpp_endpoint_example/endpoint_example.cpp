#include <pcapcpp/endpoint/endpoint.hpp>
#include <pcapcpp/interface/enumerator.hpp>

#include <iostream>

int main()
{
	pcapcpp::interface_enumerator if_enum;
	pcapcpp::network_interface    if_network = if_enum[6];

	for(int i = 0 ; i < if_enum.count() ; i++)
		std::cout << if_enum[i].description() << std::endl;

	pcapcpp::device				  if_device  (if_network, 65535);
	pcapcpp::endpoint			  if_endpoint(if_device);

	auto&& if_captured			= if_endpoint();
	std::cout << if_captured.packet_size() << std::endl;
}