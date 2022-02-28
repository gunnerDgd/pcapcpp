#pragma once
#include <variant>
#include <tuple>

#include <pcapcpp/parse/parser.hpp>
#include <pcapcpp/layer/layer_types.hpp>

namespace pcapcpp {
	template <typename... LayerProtocol>
	class network_layer
	{
	public:
		using layer_variant = std::variant<typename basic_parser<LayerProtocol>::packet...>;
		class null_packet {};

	public:
		network_layer();
	public:
		std::size_t current_layer()			   { return __M_nlayer_packet.index(); }
		template <typename ProtocolType>
		auto&		operator[]   (ProtocolType);
		template <typename PacketType>
		void		operator=    (PacketType&&);

	private:
		layer_variant __M_nlayer_packet;
	};
}

template <typename... LayerProtocol>
pcapcpp::network_layer<LayerProtocol...>::network_layer()
{
	static_assert(!layer::is_same_layer_v<LayerProtocol...>, "[FATAL][NETWORK_LAYER] Protocol Layer is not same with each other.\n");
}

template <typename... LayerProtocol>
template <typename ProtocolType>
auto& pcapcpp::network_layer<LayerProtocol...>::operator[](ProtocolType)
{
	if constexpr (layer::is_contained_v<ProtocolType, LayerProtocol...>)
		return null_packet{};
	else
		return std::get<protocol::layer_v<ProtocolType>>(__M_nlayer_packet);
}

template <typename... LayerProtocol>
template <typename PacketType>
void  pcapcpp::network_layer<LayerProtocol...>::operator=(PacketType&& packet)
{
	if constexpr (!layer::is_contained_v<layer::is_protocol_packet_v<PacketType, LayerProtocol...>>)
		return;

	std::get<protocol::layer_v<layer::packet_protocol_t<PacketType>>> = packet;
}