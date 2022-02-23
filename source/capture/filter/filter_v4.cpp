#include <pcapcpp/capture/protocol/v4.hpp>

using namespace pcapcpp;
using			v4_parser = parser_traits<protocol::ipv4_type>;

v4_parser::filter::filter(packet::address_type src, packet::address_type dst, packet::upper_layer ulp)
	: __M_v4_ulp(ulp)
{
	std::memcpy(__M_v4_source	  , src, 4);
	std::memcpy(__M_v4_destination, dst, 4);
}

bool v4_parser::filter::match_source	 (packet::address_type src)
{
	return (*reinterpret_cast<int*>(src) & *reinterpret_cast<int*>(__M_v4_source));
}

bool v4_parser::filter::match_destination(packet::address_type dst)
{
	return (*reinterpret_cast<int*>(dst) & *reinterpret_cast<int*>(__M_v4_destination));
}

bool v4_parser::filter::match_upper_layer(packet::protocol_type ulp)
{
	return (std::underlying_type_t<packet::upper_layer>)ulp
		 & (std::underlying_type_t<packet::upper_layer>)__M_v4_ulp;
}