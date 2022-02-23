#pragma once
#include <pcapcpp/capture/protocool/ethernet.hpp>

using namespace pcapcpp;
using			eth_parser = parser_traits<protocol::ethernet_type>;

eth_parser::filter::filter(packet::mac src, packet::mac dst, packet::upper_layer ulp)
	: __M_filter_ulp(ulp)
{
	std::memcpy(__M_filter_sender  , src, 6);
	std::memcpy(__M_filter_receiver, dst, 6);
}

bool eth_parser::filter::match_source(packet::mac& src)
{
	for (int i = 0; i < 6; i++)
		if ((src[i] & __M_filter_sender[i]) != src[i])
			return false;

	return true;
}

bool eth_parser::filter::match_destination(packet::mac& dst)
{
	for (int i = 0; i < 6; i++)
		if ((dst[i] & __M_filter_sender[i]) != dst[i])
			return false;

	return true;
}

bool eth_parser::filter::match_upper_layer(packet::protocol_type ulp)
{
	auto lhs = (std::underlying_type_t<packet::upper_layer>)ulp,
		 rhs = (std::underlying_type_t<packet::upper_layer>)__M_filter_ulp;

	return (lhs & rhs) == lhs;
}