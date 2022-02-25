#include <pcapcpp/parse/protocol/ethernet.hpp>
#include <WinSock2.h>

using namespace pcapcpp;
using			eth_parser = parser_traits<protocol::ethernet_type>;

eth_parser::packet eth_parser::parse_from(null_filter, raw::pointer& pkt)
{
	return pkt.extract_from<packet>();
}

eth_parser::packet eth_parser::parse_from(filter& flt, raw::pointer& pkt)
{
	packet&		   pkt_extract = pkt.extract_from<packet>();
	return (flt == pkt_extract) ? packet(pkt_extract) : packet();
}

eth_parser::upper_protocol eth_parser::upper_layer(raw::pointer& pkt)
{
	packet&							  pkt_view = pkt.view_from<packet>();
	return (packet::upper_layer)ntohs(pkt_view.upper_protocol);
}

eth_parser::upper_protocol eth_parser::upper_layer(packet& pkt)
{
	return (packet::upper_layer)ntohs(pkt.upper_protocol);
}