#pragma once
#include <cstdint>

namespace pcapcpp::protocol {
	class arp
	{
	public:
		typedef std::uint8_t mac			 [6];
		typedef std::uint8_t protocol_address[4];

		std::uint16_t    hardware_type			, protocol_type			 ; // 4 Byte
		std::uint8_t     hardware_address_length, protocol_address_length; // 2 Byte
		std::uint16_t    operation;										   // 2 Byte

		mac			     sender_hardware_address;						   // 6 Byte
		protocol_address sender_protocol_address;						   // 4 Byte

		mac				 receiver_hardware_address;
		protocol_address receiver_protocol_address;
	};
}