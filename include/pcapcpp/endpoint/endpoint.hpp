#include <pcapcpp/device/device.hpp>
#include <pcapcpp/packet/raw.hpp>

#include <thread>

namespace pcapcpp {
	class endpoint
	{
	public:
		typedef device	    device_type;
		typedef std::thread thread_type;
		typedef pcap_pkthdr endpoint_header;

	public:
		endpoint (device_type&);
		~endpoint();

	public:

	private:
		device_type& __M_ep_device;
		thread_type* __M_ep_capture_thread = nullptr;
		void		 __M_ep_capture_routine(std::uint8_t*, endpoint_header*, const std::uint8_t*);
	};
}