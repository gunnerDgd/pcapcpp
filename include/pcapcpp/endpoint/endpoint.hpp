#include <pcapcpp/device/device.hpp>
#include <pcapcpp/packet/raw.hpp>

namespace pcapcpp {
	class endpoint
	{
	public:
		typedef device	    device_type;
		typedef pcap_pkthdr endpoint_header;

	public:
		endpoint (device_type&);
		~endpoint();

	public:
		raw<> operator()();

	private:
		device_type& __M_ep_device;
	};
}