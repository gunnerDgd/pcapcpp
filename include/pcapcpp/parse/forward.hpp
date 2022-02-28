#pragma once
#include <pcapcpp/parse/protocol/arp.hpp>
#include <pcapcpp/parse/protocol/ethernet.hpp>
#include <pcapcpp/parse/protocol/v4.hpp>

#include <variant>

namespace pcapcpp::parser {
	using arp	   = basic_parser<protocol::arp_type>	  ;
	using ethernet = basic_parser<protocol::ethernet_type>;
	using v4	   = basic_parser<protocol::ipv4_type>	  ;
}