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