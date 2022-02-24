#pragma once
#include <pcapcpp/parse/parser.hpp>
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
		static packet upper_layer(raw::pointer&);
		static packet parse_from (null_filter, raw::pointer&);
		static packet parse_from (filter&	 , raw::pointer&);
	};

	class parser_traits<protocol::ethernet_type>::filter
	{
		friend class parser_traits<protocol::ethernet_type>;
	public:
		static constexpr packet::mac		 all	   = { 0xFF, };
		static constexpr packet::upper_layer all_layer = packet::upper_layer::malformed;

		filter		   (packet::mac, packet::mac, packet::upper_layer);
		bool operator==(packet&);

	private:
		packet::mac			__M_filter_sender, __M_filter_receiver;
		packet::upper_layer __M_filter_ulp;
	};
}