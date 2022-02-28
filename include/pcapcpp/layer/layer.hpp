#pragma once
#include <pcapcpp/layer/layer_parser.hpp>
#include <pcapcpp/layer/layer_types.hpp>
#include <pcapcpp/layer/network_layer.hpp>

namespace pcapcpp::layer {
	using datalink		  = pcapcpp::network_layer<pcapcpp::protocol::ethernet_type>;
	using network		  = pcapcpp::network_layer<pcapcpp::protocol::arp_type, pcapcpp::protocol::ipv4_type>;

	using datalink_parser = pcapcpp::network_layer_parser<pcapcpp::protocol::ethernet_type>;
	using network_parser  = pcapcpp::network_layer_parser<pcapcpp::protocol::arp_type, pcapcpp::protocol::ipv4_type>;
}