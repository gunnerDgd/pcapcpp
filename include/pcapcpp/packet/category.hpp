#pragma once
#include <type_traits>

namespace pcapcpp::category {
	
	class arp_type {};
	class eth_type {};

	class ipv4_type {};
	class ipv6_type {};

	class tcp_type  {};
	class udp_type  {};

	static constexpr arp_type  arp;
	static constexpr eth_type  ethernet;

	static constexpr ipv4_type v4;
	static constexpr ipv6_type v6;

	static constexpr tcp_type  tcp;
	static constexpr udp_type  udp;
}