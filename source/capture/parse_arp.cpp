#include <pcapcpp/capture/protocol/arp.hpp>

using namespace pcapcpp;
using			arp_parser = parser_traits<protocol::arp_type>;

arp_parser::packet arp_parser::parse_from(null_filter, raw& pkt)
{
	packet       arp_packet;
	std::memcpy(&arp_packet, pkt.__M_raw_pointer + pkt.__M_raw_packet_pointer, protocol_category::size);
							 pkt.__M_raw_packet_pointer += protocol_category::size;

	return		 arp_packet;
}

arp_parser::packet arp_parser::parse_from(filter& flt, raw& pkt)
{
	packet		 arp_packet;
	std::memcpy(&arp_packet, pkt.__M_raw_pointer + pkt.__M_raw_packet_pointer, protocol_category::size);
							 pkt.__M_raw_packet_pointer += protocol_category::size;

	if (flt.match_source_hardware	  (arp_packet.sender_hardware_address)
	 && flt.match_destination_hardware(arp_packet.receiver_hardware_address)

	 && flt.match_source_protocol	  (arp_packet.sender_protocol_address)
	 && flt.match_destination_protocol(arp_packet.receiver_protocol_address)) goto filter_passed ;
	else																	  goto filter_blocked;

filter_passed:
	return arp_packet;

filter_blocked:
		   arp_packet.operation = (std::underlying_type_t<packet::operation_code>)packet::operation_code::malformed;
	return arp_packet;
}