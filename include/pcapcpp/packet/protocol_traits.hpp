#pragma once
#include <pcapcpp/packet/protocol.hpp>

namespace pcapcpp::protocol {
	template <typename ProtocolType>
	constexpr std::size_t layer_v = ProtocolType::layer;

	template <typename ProtocolType>
	constexpr std::size_t size_v  = ProtocolType::size;

	template <typename Protocol, typename UpperLayer>
	constexpr bool is_upper_layer(UpperLayer) { return false; }

	template <>
	constexpr bool is_upper_layer<arp_type>(packet::ethernet::upper_layer ulp) 
	{ 
		return (ulp == packet::ethernet::upper_layer::arp);
	}

	template <>
	constexpr bool is_upper_layer<ipv4_type>(packet::ethernet::upper_layer ulp)
	{
		return (ulp == packet::ethernet::upper_layer::ipv4);
	}
}