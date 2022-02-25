#include <pcapcpp/capture/capture.hpp>
#include <pcapcpp/endpoint/endpoint.hpp>

#include <pcapcpp/interface/interface.hpp>
#include <pcapcpp/interface/enumerator.hpp>

#include <iostream>

int main()
{
	pcapcpp::capture<pcapcpp::protocol::ethernet_type, pcapcpp::protocol::arp_type> Capture;
	pcapcpp::interface_enumerator CaptureInterfaceEnumerator;
	pcapcpp::network_interface    CaptureInterface(CaptureInterfaceEnumerator[3]);

	pcapcpp::device				  CaptureDevice  (CaptureInterface, pcapcpp::device::operation_mode{});
	pcapcpp::endpoint			  CaptureEndpoint(CaptureDevice);

	pcapcpp::raw				  CaptureRaw;
	CaptureEndpoint.capture_once (CaptureRaw);

	auto CaptureParsed = Capture(CaptureRaw);
}