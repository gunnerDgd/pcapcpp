#pragma once
#include <pcapcpp/parse/protocol/arp.hpp>
#include <pcapcpp/parse/protocol/ethernet.hpp>
#include <pcapcpp/parse/protocol/v4.hpp>

namespace pcapcpp::parser {
	using arp	   = basic_parser<protocol::arp_type>	  ;
	using ethernet = basic_parser<protocol::ethernet_type>;
	using v4	   = basic_parser<protocol::ipv4_type>	  ;
}

namespace pcapcpp {
	enum class protocol_category : std::uint16_t
	{
		ethernet = 0,
		arp		 = 1,

		v4		 = 1, 
		v6		 = 1,
		tcp		 = 2, 
		udp	     = 2
	};
}