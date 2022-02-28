#pragma once
#include <cstdint>
#include <cstddef>

#include <type_traits>

#include <pcapcpp/packet/protocol/arp.hpp>
#include <pcapcpp/packet/protocol/ip.hpp>
#include <pcapcpp/packet/protocol/ethernet.hpp>
#include <pcapcpp/packet/protocol/tcp.hpp>

#define DEFINE_PROTOCOL_TYPE(name, v_size, v_layer) struct name {\
	static constexpr std::size_t  size  = v_size;\
	static constexpr std::uint8_t layer = v_layer;\
	};

namespace pcapcpp::protocol {
	DEFINE_PROTOCOL_TYPE(ethernet_type, 14, 0)
	DEFINE_PROTOCOL_TYPE(arp_type	  , 26, 1)
	DEFINE_PROTOCOL_TYPE(ipv4_type	  , 14, 1)
	DEFINE_PROTOCOL_TYPE(tcp_type	  , 20, 2)
	DEFINE_PROTOCOL_TYPE(udp_type	  , 8 , 2)

	static constexpr arp_type	   arp;
	static constexpr ethernet_type ethernet;

	static constexpr ipv4_type	   v4;

	static constexpr tcp_type	   tcp;
	static constexpr udp_type      udp;
}