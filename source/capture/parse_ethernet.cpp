#include <pcapcpp/capture/protocol/ethernet.hpp>

using namespace pcapcpp;
using			eth_parser = parser_traits<protocol::ethernet_type>;

eth_parser::packet eth_parser::parse_from(null_filter, raw& pkt, upper_protocol& ulp)
{
	packet		 eth_packet;
	std::memcpy(&eth_packet, pkt.__M_raw_pointer + pkt.__M_raw_packet_pointer, protocol_category::size);
							 pkt.__M_raw_packet_pointer += protocol_category::size;

	ulp = (upper_protocol)eth_packet.upper_protocol;
	return				  eth_packet;
}

eth_parser::packet eth_parser::parse_from(filter& flt, raw& pkt, upper_protocol& ulp)
{
	packet		 eth_packet;
	std::memcpy(&eth_packet, pkt.__M_raw_pointer + pkt.__M_raw_packet_pointer, protocol_category::size);
							 pkt.__M_raw_packet_pointer += protocol_category::size;

	if (flt.match_upper_layer(eth_packet.upper_protocol)
	 && flt.match_source	 (eth_packet.source)
	 && flt.match_destination(eth_packet.destination)) goto filter_passed ;
	else											   goto filter_blocked;

filter_passed:
	ulp = (upper_protocol)eth_packet.upper_protocol;
	return				  eth_packet;

filter_blocked:
	ulp = upper_protocol::malformed;

		   eth_packet.upper_protocol = (std::underlying_type_t<upper_protocol>)upper_protocol::malformed;
	return eth_packet;
}