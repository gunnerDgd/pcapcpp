#include <pcapcpp/packet/protocol/ip.hpp>
#include <pcapcpp/packet/protocol/arp.hpp>

std::ostream& operator<< (std::ostream& os, const pcapcpp::protocol::packet::ipv4& pkt)
{
	os << "[Internet Protocol Version 4]\n";
	os << "\tSender Address : "; for (int i = 0; i < 4; i++)   os << std::hex << (int)pkt.source_address[i] << " "; os << std::endl;
	os << "\tReceiver Address : "; for (int i = 0; i < 4; i++) os << std::hex << (int)pkt.destination_address[i] << " "; os << std::endl;

	return os;
}

std::ostream& operator<< (std::ostream& os, const pcapcpp::protocol::packet::arp& pkt)
{
	os << "[Address Resolution Protocol]\n";
	os << "\tSender Hardware Address : "; for (int i = 0; i < 6; i++) os << std::hex << (int)pkt.sender_hardware_address[i] << " "; os << std::endl;
	os << "\tSender Protocol Address : "; for (int i = 0; i < 4; i++) os << std::hex << (int)pkt.sender_protocol_address[i] << " "; os << std::endl;

	os << "\tReceiver Hardware Address : "; for (int i = 0; i < 6; i++) os << std::hex << (int)pkt.receiver_hardware_address[i] << " "; os << std::endl;
	os << "\tReceiver Protocol Address : "; for (int i = 0; i < 4; i++) os << std::hex << (int)pkt.receiver_protocol_address[i] << " "; os << std::endl;

	return os;
}