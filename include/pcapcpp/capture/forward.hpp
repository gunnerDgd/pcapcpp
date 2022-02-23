#pragma once
#include <pcapcpp/capture/protocool/arp.hpp>
#include <pcapcpp/capture/protocool/ethernet.hpp>
#include <pcapcpp/capture/protocool/v4.hpp>

namespace pcapcpp::parser {
	using arp	   = basic_parser<protocol::arp_type>	  ;
	using ethernet = basic_parser<protocol::ethernet_type>;
	using v4	   = basic_parser<protocol::ipv4_type>	  ;	
}