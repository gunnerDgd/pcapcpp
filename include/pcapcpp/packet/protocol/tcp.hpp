#pragma once
#include <cstdint>

namespace pcapcpp::protocol::packet {
	class tcp
	{
	public:
		struct configuration
		{
			std::uint8_t offset   : 3;
			std::uint8_t reserved : 3;

			std::uint8_t ecn_nonce		  : 1;
			std::uint8_t window_reduced   : 1;
			std::uint8_t ecn_echo_capable : 1;
			std::uint8_t urgent			  : 1;
			std::uint8_t acknowledgement  : 1;
			std::uint8_t push			  : 1;
			std::uint8_t reset			  : 1;
			std::uint8_t synchronize      : 1;
			std::uint8_t finish			  : 1;
		};

		std::uint16_t source_port, destination_port;
		std::uint32_t sequence_number;
		std::uint32_t acknowledgement;

		configuration config_field;
		std::uint16_t window_size ;

		std::uint16_t checksum;
		std::uint16_t urgent_pointer;
	};
}