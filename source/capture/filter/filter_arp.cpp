#pragma once
#include <pcapcpp/capture/protocool/arp.hpp>

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

bool arp_parser::filter::match_source_hardware(packet::mac src)
{
	for (int i = 0; i < 6; i++)
		if ((src[i] & __M_arp_source[i]) != src[i])
			return false;

	return true;
}

bool arp_parser::filter::match_destination_hardware(packet::mac dst)
{
	for (int i = 0; i < 6; i++)
		if ((dst[i] & __M_arp_source[i]) != dst[i])
			return false;

	return true;
}

bool arp_parser::filter::match_source_protocol(packet::protocol_address src)
{
	for (int i = 0; i < 4; i++)
		if ((src[i] & __M_arp_source[i]) != src[i])
			return false;

	return true;
}

bool arp_parser::filter::match_destination_protocol(packet::protocol_address dst)
{
	for (int i = 0; i < 4; i++)
		if ((dst[i] & __M_arp_source[i]) != dst[i])
			return false;

	return true;
}