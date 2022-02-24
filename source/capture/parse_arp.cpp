#include <pcapcpp/parse/protocol/arp.hpp>

using namespace pcapcpp;
using			arp_parser = parser_traits<protocol::arp_type>;

arp_parser::packet arp_parser::parse_from(null_filter, raw::pointer& pkt)
{
	return pkt.extract_from<packet>();
}

arp_parser::packet arp_parser::parse_from(filter& flt, raw::pointer& pkt)
{
	packet&		   pkt_extract = pkt.extract_from<packet>();
	return (flt == pkt_extract) ? packet(pkt_extract) : packet();
}