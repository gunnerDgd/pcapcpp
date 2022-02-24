#pragma once
#include <pcapcpp/parse/parser.hpp>
#include <pcapcpp/packet/protocol/arp.hpp>

/*
 * Necessary Using Alias Declaration
 *
 * 1) using packet = <protocol-defined packet>
 *	--> Specifies packet that parser will parse from raw packet.
 *	-->
 */

namespace pcapcpp {
	template <> class parser_traits<protocol::arp_type>
	{
	public:
		class filter;
		using protocol_category = protocol::arp_type;

		using packet			= protocol::packet::arp;
		static constexpr bool	  notifies_upper_protocol = false;

	public:
		static packet parse_from(null_filter, raw::pointer&);
		static packet parse_from(filter&	, raw::pointer&);
	};

	class parser_traits<protocol::arp_type>::filter
	{
		friend class parser_traits<protocol::arp_type>;
	public:
		static constexpr packet::mac			  all		   = { 0xFF, };
		static constexpr packet::protocol_address all_protocol = { 0xFF, };

	public:
		filter(packet::mac, packet::mac,
			   packet::protocol_address, packet::protocol_address);

	public:
		bool operator==(packet&);

	private:
		packet::mac				 __M_arp_source		 , __M_arp_destination;
		packet::protocol_address __M_arp_source_proto, __M_arp_destination_proto;
	};
}