#include <pcapcpp/capture/capture.hpp>
#include <pcapcpp/endpoint/endpoint.hpp>

#include <pcapcpp/interface/interface.hpp>
#include <pcapcpp/interface/enumerator.hpp>

#include <iostream>
#include <WinSock2.h>

int main()
{
	pcapcpp::capture<pcapcpp::protocol::ethernet_type, pcapcpp::protocol::ipv4_type> Capture;
	pcapcpp::interface_enumerator CaptureInterfaceEnumerator;
	pcapcpp::network_interface    CaptureInterface(CaptureInterfaceEnumerator[3]);

	pcapcpp::device				  CaptureDevice  (CaptureInterface, pcapcpp::device::operation_mode{});
	pcapcpp::endpoint			  CaptureEndpoint(CaptureDevice);

	for (int i = 0; i < CaptureInterfaceEnumerator.count(); i++)
		std::cout << CaptureInterfaceEnumerator[i].description() << std::endl;

	while (true)
	{
		pcapcpp::raw					   CaptureRaw;
		decltype(Capture)::captured_packet CapturePacket;
		
		CaptureEndpoint.capture_once(CaptureRaw);
		if (Capture(CaptureRaw, CapturePacket))
			std::cout << CapturePacket[pcapcpp::protocol::v4] << std::endl;
	}
}