#pragma once
#include <pcapcpp/parse/protocol/arp.hpp>
#include <pcapcpp/parse/protocol/ethernet.hpp>
#include <pcapcpp/parse/protocol/v4.hpp>

#include <variant>

namespace pcapcpp::parser {
	using arp	   = basic_parser<protocol::arp_type>	  ;
	using ethernet = basic_parser<protocol::ethernet_type>;
	using v4	   = basic_parser<protocol::ipv4_type>	  ;

	using layer_2	     = std::variant<ethernet>;
	using layer_2_packet = std::variant<typename ethernet::packet>;
	
	using layer_3	     = std::variant<arp, v4> ;
	using layer_3_packet = std::variant<typename arp::packet, typename v4::packet>;

	using layer_parser = std::tuple<layer_2, layer_3>;
	using layer_packet = std::tuple<layer_2_packet, layer_3_packet>;


	template <typename ProtocolType>
	bool is_upper_layer(v4::upper_protocol)		  { return false; }

	template <typename ProtocolType>
	bool is_upper_layer(arp::upper_protocol)      { return false; }

	template <typename ProtocolType>
	bool is_upper_layer(ethernet::upper_protocol) { return false; }

	template <>
	bool is_upper_layer<arp>(ethernet::upper_protocol proto) { return (proto == ethernet::upper_protocol::arp)  ? true : false; }

	template <>
	bool is_upper_layer<v4> (ethernet::upper_protocol proto) { return (proto == ethernet::upper_protocol::ipv4) ? true : false; }
}