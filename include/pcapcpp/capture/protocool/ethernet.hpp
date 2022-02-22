#pragma once
#include <pcapcpp/capture/filter.hpp>
#include <pcapcpp/endpoint/endpoint.hpp>

#include <pcapcpp/packet/category.hpp>

namespace pcapcpp {
	template <>
	class basic_filter<protocol::eth_type>
	{
	public:
		using					   size_type	   = std::uint16_t;
		using					   packet_category = filter::static_sized ;
		using					   packet_type     = 
		static constexpr size_type packet_size	   = 12;

		
	public:
		template <typename RawType>
		packet operator|(RawType&&);
	};
} 

template <typename RawType>
pcapcpp::basic_filter<pcapcpp::category::eth_type>::packet pcapcpp::basic_filter<pcapcpp::category::eth_type>::operator|(RawType&& raw)
{
	if (!raw.__M_raw_pointer)
		return packet;

	packet		 eth_packet;
	std::memcpy(&eth_packet, raw.__M_raw_pointer, packet_size);

	return eth_packet;
}