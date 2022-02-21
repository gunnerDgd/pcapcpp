#include <pcapcpp/device/device.hpp>
#include <pcapcpp/packet/raw.hpp>

#include <type_traits>

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
		template <typename RawType>
		bool capture_once    (RawType&&);
		template <typename RawBeginIterator, typename RawEndIterator>
		bool capture_multiple(RawBeginIterator&&, RawEndIterator&&);

	private:
		device_type& __M_ep_device;
	};
}

template <typename RawType>
bool pcapcpp::endpoint::capture_once(RawType&& raw)
{
	endpoint_header	ep_hdr;
	std::uint8_t*   ep_raw = (std::uint8_t*)pcap_next(__M_ep_device.__M_if_device_handle, &ep_hdr);

	if (!ep_raw) return false;
	
	raw = std::decay_t<RawType>(ep_raw, (std::size_t)ep_hdr.caplen);
	return true;
}

template <typename RawBeginIterator, typename RawEndIterator>
bool pcapcpp::endpoint::capture_multiple(RawBeginIterator&& begin, RawEndIterator&& end)
{
	endpoint_header cap_hdr;
	std::uint8_t*   cap_ptr;

	for(auto it_cap = begin ; it_cap != end ; it_cap++)
	{
		     cap_ptr = (std::uint8_t*)pcap_next(__M_ep_device.__M_if_device_handle, &cap_hdr);
		if (!cap_ptr) return false;

		*it_cap = typename RawBeginIterator::value_type(cap_ptr, (std::size_t)cap_hdr.caplen);
	}

	return true;
}