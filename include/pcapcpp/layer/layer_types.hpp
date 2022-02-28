#pragma once
#include <type_traits>

#include <pcapcpp/packet/protocol/arp.hpp>
#include <pcapcpp/packet/protocol/ethernet.hpp>
#include <pcapcpp/packet/protocol//ip.hpp>

namespace pcapcpp::layer {
	template <typename... T>
	struct __is_contained;

	template <typename T, typename U, typename... Protocol>
	struct __is_contained<T, U, Protocol...> { static constexpr bool value = (std::is_same_v<T, U>) ? true : __is_contained<T, Protocol...>::value; };

	template <typename T>
	struct __is_contained<T>				 { static constexpr bool value = false; };

	template <typename... Protocol>
	struct	 is_contained					 { static constexpr bool value = __is_contained<Protocol...>::value };

	template <typename... T>
	inline constexpr bool is_contained_v = is_contained<T...>::value;


	template <typename Protocol, typename Packet>
	struct is_protocol_packet { static constexpr bool value = false; };

	template <>
	struct is_protocol_packet<pcapcpp::protocol::arp_type, pcapcpp::protocol::packet::arp>			 { static constexpr bool value = true; };

	template <>
	struct is_protocol_packet<pcapcpp::protocol::ethernet_type, pcapcpp::protocol::packet::ethernet> { static constexpr bool value = true; };

	template <>
	struct is_protocol_packet<pcapcpp::protocol::ipv4_type, pcapcpp::protocol::packet::ipv4>		 { static constexpr bool value = true; };

	template <typename... T>
	inline constexpr bool is_protocol_packet_v = is_protocol_packet<std::remove_reference_t<T>...>::value;


	template <typename PacketType>
	struct packet_protocol									    { typedef void type; };

	template <>
	struct packet_protocol<pcapcpp::protocol::packet::arp>		{ typedef pcapcpp::protocol::arp_type type; };

	template <>
	struct packet_protocol<pcapcpp::protocol::packet::ethernet> { typedef pcapcpp::protocol::ethernet_type type; };

	template <>
	struct packet_protocol<pcapcpp::protocol::packet::ipv4>		{ typedef pcapcpp::protocol::ipv4_type type; };

	template <typename PacketType>
	using packet_protocol_t = typename packet_protocol<std::remove_reference_t<PacketType>>::type;


	template <typename... T>
	struct __is_same_layer;

	template <typename LhsProto>
	struct __is_same_layer<LhsProto> { static constexpr bool value = true; };

	template <typename LhsProto, typename RhsProto, typename... Remaining>
	struct __is_same_layer<LhsProto, RhsProto, Remaining...>
	{ 
		static constexpr bool value = (protocol::layer_v<LhsProto> == protocol::layer_v<RhsProto>) 
									? __is_same_layer<LhsProto, Remaining...>::value
								    : false;
	};

	template <typename... PacketType>
	struct is_same_layer { static constexpr bool value = __is_same_layer<PacketType...>::value; };

	template <typename... PacketType>
	inline constexpr bool is_same_layer_v = is_same_layer<PacketType...>::value;
	
}