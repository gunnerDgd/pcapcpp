#pragma once
#include <pcapcpp/parse/protocol/ethernet.hpp>

using namespace pcapcpp;
using			eth_parser = parser_traits<protocol::ethernet_type>;

eth_parser::filter::filter(packet::mac src, packet::mac dst, packet::upper_layer ulp)
	: __M_filter_ulp(ulp)
{
	std::memcpy(__M_filter_sender  , src, 6);
	std::memcpy(__M_filter_receiver, dst, 6);
}

bool eth_parser::filter::operator==(packet& cmp)
{
	for (int i = 0; i < 6; i++) {
		if((cmp.source	   [i] & __M_filter_sender  [i]) != cmp.source     [i]
		|| (cmp.destination[i] & __M_filter_receiver[i]) != cmp.destination[i]) return false;
	}

	return true;
}