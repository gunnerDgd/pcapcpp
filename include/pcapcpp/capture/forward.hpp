#pragma once
#include <pcapcpp/capture/protocol/arp.hpp>
#include <pcapcpp/capture/protocol/ethernet.hpp>
#include <pcapcpp/capture/protocol/v4.hpp>

namespace pcapcpp::parser {
	using arp	   = basic_parser<protocol::arp_type>	  ;
	using ethernet = basic_parser<protocol::ethernet_type>;
	using v4	   = basic_parser<protocol::ipv4_type>	  ;	
}