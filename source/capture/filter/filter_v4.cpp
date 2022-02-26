#include <pcapcpp/parse/protocol/v4.hpp>

using namespace pcapcpp;
using			v4_parser = parser_traits<protocol::ipv4_type>;

v4_parser::filter::filter(packet::address_type src, packet::address_type dst, packet::upper_layer ulp)
	: __M_v4_ulp(ulp)
{
	std::memcpy(__M_v4_source	  , src, 4);
	std::memcpy(__M_v4_destination, dst, 4);
}

bool v4_parser::filter::operator==(packet& cmp)
{
	for (int i = 0; i < 4; i++) {
		if((cmp.source_address	   [i] & __M_v4_source	   [i]) != cmp.source_address	  [i]
		|| (cmp.destination_address[i] & __M_v4_destination[i]) != cmp.destination_address[i])
			return false;
	}

	return true;
}