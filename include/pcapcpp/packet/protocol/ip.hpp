#pragma once
#include <cstdint>
#include <type_traits>

namespace pcapcpp::protocol {
	class ipv4
	{
	public:
		typedef std::uint8_t address_type[4];

		enum class fragment_flag { not_fragmentated = 1 << 1, fragmentated = 1 << 2 };
		enum class protocol_type 
		{
			icmp = 0x01,
			igmp = 0x02,

			tcp  = 0x06,
			udp  = 0x11
		};

		std::uint8_t  version			 : 4;
		std::uint8_t  header_length		 : 4;

		std::uint8_t  type_of_service    : 6;
		std::uint8_t  notifty_congestion : 2;

		std::uint16_t total_length  ;
		std::uint16_t identification;

		std::uint8_t  fragmentation		 : 3;
		std::uint8_t  fragment_offset	 : 13;

		std::uint8_t  time_to_live;
		std::uint8_t  upper_protocol;
		std::uint16_t header_checksum;

		address_type  source_address;
		address_type  destination_address;
	};

	static_assert(std::is_standard_layout_v<ipv4>, "[COMPILE ERROR] IPv4 Class is not standard layout.\n");
}