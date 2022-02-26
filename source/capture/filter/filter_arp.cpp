#pragma once
#include <pcapcpp/parse/protocol/arp.hpp>

using namespace pcapcpp;
using			arp_parser = parser_traits<protocol::arp_type>;

arp_parser::filter::filter(packet::mac src, packet::mac dst,
						   packet::protocol_address proto_src, packet::protocol_address proto_dst)
{
	std::memcpy(__M_arp_source	   , src, 6);
	std::memcpy(__M_arp_destination, dst, 6);

	std::memcpy(__M_arp_source_proto	 , src, 4);
	std::memcpy(__M_arp_destination_proto, dst, 4);
}

bool arp_parser::filter::operator==(packet& cmp)
{
	for (int i = 0; i < 6; i++) {
		if ((cmp.receiver_hardware_address[i] & __M_arp_destination[i]) != cmp.receiver_hardware_address[i]
		 || (cmp.sender_hardware_address  [i] & __M_arp_source     [i]) != cmp.sender_hardware_address  [i])
			return false;
	}

	for (int i = 0; i < 4; i++) {
		if ((cmp.receiver_protocol_address[i] & __M_arp_destination_proto[i]) != cmp.receiver_protocol_address[i]
		 || (cmp.sender_protocol_address  [i] & __M_arp_source_proto     [i]) != cmp.sender_protocol_address  [i])
			return false;
	}

	return true;
}