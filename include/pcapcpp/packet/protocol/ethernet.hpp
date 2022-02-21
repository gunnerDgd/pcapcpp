#pragma once
#include <cstdint>
#include <cstddef>

namespace pcapcpp::protocol {
	class packet
	{
	public:
		typedef std::uint8_t  mac[6];
		typedef std::uint16_t protocol_type;
		enum class			  upper_layer : protocol_type { arp = 0x0806, ipv4 = 0x0800, ipv6 = 0x0806 };

		mac			  source, destination;
		protocol_type upper_protocol;
	};
}