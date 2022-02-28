#pragma once
#include <pcapcpp/layer/network_layer.hpp>

namespace pcapcpp {
	template <typename... LayerProtocol>
	class network_layer_parser
	{
	public:
		using this_type    = network_layer_parser<LayerProtocol...>;
		using layer_type   = network_layer		 <LayerProtocol...>;

		using parser_tuple = std::tuple<basic_parser<LayerProtocol>...>;
		class null_parser { };

	public:
		network_layer_parser();
	public:
		template <typename ParserPacket>
		auto	   upper_layer(ParserPacket&&);
		template <typename ParserProtocol>
		this_type& operator|  (typename basic_parser<ParserProtocol>::filter&);
		template <typename ParserPacket>
		bool	   operator() (ParserPacket&&, raw::pointer&);

	private:
		parser_tuple __M_layer_parser;
	};
}

template <typename... LayerProtocol>
pcapcpp::network_layer_parser<LayerProtocol...>::network_layer_parser()
{
	static_assert(!layer::is_same_layer_v<LayerProtocol...>, "[FATAL][LAYERED_PARSER] Protocol Layer is not same with each other.\n");
	((std::get<protocol::layer_v<LayerProtocol>>(__M_layer_parser) = basic_parser<LayerProtocol>), ...);
}

template <typename... LayerProtocol>
template <typename ParserProtocol>
pcapcpp::network_layer_parser<LayerProtocol...>& pcapcpp::network_layer_parser<LayerProtocol...>::operator| (typename basic_parser<ParserProtocol>::filter& flt)
{
	if constexpr (layer::is_contained_v<ParserProtocol, LayerProtocol...>)
		std::get<protocol::layer_v<ParserProtocol>>(__M_layer_parser).set_filter(flt);

	return *this;
}

template <typename... LayerProtocol>
template <typename ParserPacket>
bool pcapcpp::network_layer_parser<LayerProtocol...>::operator()(ParserPacket&& parsed, raw::pointer& raw_ptr)
{
	if constexpr (layer::is_contained_v<layer::packet_protocol_t<ParserPacket>, LayerProtocol...>)
		return false;

	parsed = std::get<protocol::layer_v<layer::packet_protocol_t<ParserPacket>>>(__M_layer_parser);
	return true;
}

template <typename... LayerProtocol>
template <typename ParserPacket>
auto pcapcpp::network_layer_parser<LayerProtocol...>::upper_layer(ParserPacket&& packet)
{
	if constexpr (!layer::is_contained_v<ParserPacket> 
			   || !layer::packet_protocol_t<ParserPacket>::notifies_upper_protocol) return null_filter{};

	return std::get<protocol::layer_v<layer::packet_protocol_t<ParserPacket>>>(__M_layer_parser).upper_layer(packet);
}