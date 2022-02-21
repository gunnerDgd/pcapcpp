#pragma once
#include <pcapcpp/capture/filter.hpp>
#include <pcapcpp/endpoint/endpoint.hpp>

#include <pcapcpp/capture/category.hpp>
#include <pcapcpp/packet/category.hpp>

namespace pcapcpp {
	template <>
	class basic_filter<category::arp_type>
	{
	public:
		using					   size_type	   = std::uint16_t;
		using					   packet_category = filter::static_sized;
		static constexpr size_type packet_size	   = 26;

		class packet
		{
		public:
			typedef std::uint8_t mac			 [6];
			typedef std::uint8_t protocol_address[4];

			std::uint16_t    hardware_type, protocol_type;
			std::uint8_t     hardware_address_length, protocol_address_length;
			std::uint16_t    operation;

			mac			     sender_hardware_address;
			protocol_address sender_protocol_address;

			mac				 receiver_hardware_address;
			protocol_address receiver_protocol_address;
		};

	public:
		template <typename PacketType>
		packet operator|(PacketType&&);
	};
}

template <typename PacketType>
