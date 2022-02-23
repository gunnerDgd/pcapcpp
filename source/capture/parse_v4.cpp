#include <pcapcpp/capture/protocool/v4.hpp>

using namespace pcapcpp;
using			v4_parser = parser_traits<protocol::ipv4_type>;

v4_parser::packet v4_parser::parse_from(null_filter, raw& pkt, upper_protocol& ulp)
{
	packet		 v4_packet;
	std::memcpy(&v4_packet, pkt.__M_raw_pointer + pkt.__M_raw_packet_pointer, protocol_category::size);
							pkt.__M_raw_packet_pointer += protocol_category::size;

	ulp = (upper_protocol)v4_packet.upper_protocol;
	return				  v4_packet;
}

v4_parser::packet v4_parser::parse_from(filter& flt, raw& pkt, upper_protocol& ulp)
{
	packet		 v4_packet;
	std::memcpy(&v4_packet, pkt.__M_raw_pointer + pkt.__M_raw_packet_pointer, protocol_category::size);

	if(flt.match_source		(v4_packet.source_address)
	&& flt.match_destination(v4_packet.destination_address)
	&& flt.match_upper_layer(v4_packet.upper_protocol)) goto filter_passed ;
	else												goto filter_blocked;

filter_passed:
	ulp = (upper_protocol)v4_packet.upper_protocol;
	return				  v4_packet;

filter_blocked:
	ulp = upper_protocol::malformed;
	return v4_packet;
}