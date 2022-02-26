#include <pcapcpp/parse/protocol/v4.hpp>

using namespace pcapcpp;
using			v4_parser = parser_traits<protocol::ipv4_type>;

v4_parser::packet v4_parser::parse_from(null_filter, raw::pointer& pkt)
{
	return pkt.extract_from<packet>();
}

v4_parser::packet v4_parser::parse_from(filter& flt, raw::pointer& pkt)
{
	packet&		   pkt_extract = pkt.extract_from<packet>();
	return (flt == pkt_extract) ? packet(pkt_extract) : packet();
}

v4_parser::packet::upper_layer v4_parser::upper_layer(raw::pointer& ptr) 
{ 
	return (packet::upper_layer)ptr.view_from<packet>().upper_protocol;
}

v4_parser::packet::upper_layer v4_parser::upper_layer(packet& pkt) 
{ 
	return (packet::upper_layer)pkt.upper_protocol; 
}