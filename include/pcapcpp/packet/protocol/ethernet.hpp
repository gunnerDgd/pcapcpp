#pragma once
#include <cstdint>
#include <cstddef>

namespace pcapcpp::protocol::packet {
	class ethernet
	{
	public:
		typedef std::uint8_t  mac[6];
		typedef std::uint16_t protocol_type;
		enum class			  upper_layer : protocol_type { malformed = 0xFFFF, arp = 0x0806, ipv4 = 0x0800, ipv6 = 0x0806 };

		mac			  source, destination;
		protocol_type upper_protocol;

	public:
		ethernet() : upper_protocol(std::underlying_type_t<upper_layer>(upper_layer::malformed)) {  }
	};
}