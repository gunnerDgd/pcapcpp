#pragma once
#include <pcapcpp/capture/parser.hpp>
#include <pcapcpp/packet/protocol/ethernet.hpp>

namespace pcapcpp {
	template <> class parser_traits<protocol::ethernet_type>
	{
	public:
		using protocol_category = protocol::ethernet_type;
		using packet			= protocol::packet::ethernet;

		static constexpr bool notifies_upper_protocol = true;
		using						   upper_protocol = packet::upper_layer;

	public:
		class filter;
		
	public:
		static packet parse_from(null_filter, raw&, upper_protocol&);
		static packet parse_from(filter&	, raw&, upper_protocol&);
	};

	class parser_traits<protocol::ethernet_type>::filter
	{
		friend class parser_traits<protocol::ethernet_type>;
	public:
		static constexpr packet::mac		 all	   = { 0xFF, };
		static constexpr packet::upper_layer all_layer = packet::upper_layer::malformed;

		filter(packet::mac, packet::mac, packet::upper_layer);
		filter()											 { }

	private:
		packet::mac			__M_filter_sender, __M_filter_receiver;
		packet::upper_layer __M_filter_ulp;

	private:
		bool match_source	  (packet::mac&);
		bool match_destination(packet::mac&);
		bool match_upper_layer(packet::protocol_type);
	};
}