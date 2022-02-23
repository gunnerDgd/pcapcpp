#pragma once
#include <pcapcpp/capture/parser.hpp>
#include <pcapcpp/packet/protocol/ip.hpp>

namespace pcapcpp {
	template <>
	class parser_traits<protocol::ipv4_type>
	{
	public:
		class filter;
		using protocol_category = protocol::ipv4_type;
		using packet			= protocol::packet::ipv4;

		static constexpr bool notifies_upper_protocol = true;
		using						   upper_protocol = packet::upper_layer;
		
	public:
		static packet parse_from(null_filter, raw&, upper_protocol&);
		static packet parse_from(filter&    , raw&, upper_protocol&);
	};

	class parser_traits<protocol::ipv4_type>::filter
	{
		friend class parser_traits<protocol::ipv4_type>;
	public:
		static constexpr packet::address_type all = { 0xFF, };
		filter(packet::address_type, packet::address_type, packet::upper_layer);

	private:
		packet::address_type __M_v4_source, __M_v4_destination;
		packet::upper_layer  __M_v4_ulp;

	private:
		bool match_source	  (packet::address_type) ;
		bool match_destination(packet::address_type) ;
		bool match_upper_layer(packet::protocol_type);
	};
}

