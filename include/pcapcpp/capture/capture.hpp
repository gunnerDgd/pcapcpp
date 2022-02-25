#pragma once
#include <pcapcpp/parse/parser.hpp>
#include <pcapcpp/capture/index.hpp>

#include <tuple>
#include <utility>

namespace pcapcpp {
	template <typename... T>
	class capture;

	template <typename... CaptureProtocol>
	class capture
	{
	public:
		template <typename... Protocol1, typename... Protocol2>
		capture(capture<Protocol1...>&, capture<Protocol2...>&);
		capture();

	public:
		template <typename Protocol>
		using parser_type =			 basic_parser<Protocol>;
		template <typename Protocol>
		using packet_type = typename basic_parser<Protocol>::packet;
		class captured_packet;

	public:
		template <typename Protocol>
		capture<Protocol, CaptureProtocol...>	 operator| (parser_type<Protocol>&);
		template <typename... Protocol>
		capture<Protocol..., CaptureProtocol...> operator| (capture<Protocol...> &);

	public:
		template <typename ProtocolType>
		parser_type<ProtocolType>&				 operator[](ProtocolType);
		bool									 operator()(raw&, captured_packet&);
	private:
		template <typename ProtocolType, typename NextProtocol, typename... Remaining>
		bool				 __M_cp_parser_execute(captured_packet&, raw::pointer&);
		template <typename ProtocolType>
		bool				 __M_cp_parser_execute(captured_packet&, raw::pointer&);

		parser::layer_parser __M_cp_parser;
	};

	template <>
	class capture<>
	{
	public:
		template <typename Protocol>
		using parser = basic_parser<Protocol>;
	public:
		template <typename Protocol>
		capture<Protocol> operator| (parser<Protocol>&);
	};

	template <typename... CaptureProtocol>
	class capture<CaptureProtocol...>::captured_packet
	{
		friend class capture<CaptureProtocol...>;
		template <typename Protocol, typename PacketType>
		void									set_packet(Protocol, PacketType&&);
	public:
		template <typename Protocol>
		typename basic_parser<Protocol>::packet operator[](Protocol);

	private:
		parser::layer_packet __M_cp_packet;
	};
}

template <typename... CaptureProtocol>
pcapcpp::capture<CaptureProtocol...>::capture() {  }

template <typename... CaptureProtocol>
template <typename ProtocolType, typename NextProtocol, typename... Remaining>
bool pcapcpp::capture<CaptureProtocol...>::__M_cp_parser_execute(captured_packet& cp_pkt, raw::pointer& raw_ptr)
{
	auto parser_protocol = ProtocolType{};
	auto parser_var      = std::get<ProtocolType::layer>	  (__M_cp_parser);
	auto parser_proto	 = std::get<parser_type<ProtocolType>>(parser_var);

	if constexpr (parser_type<ProtocolType>::notifies_upper_protocol)
	{	
		auto ulp		= parser_proto.upper_layer(raw_ptr);
		cp_pkt.set_packet(parser_protocol, parser_proto.parse_from (raw_ptr));

		if (!parser::is_upper_layer<NextProtocol>(ulp))
			return false;
		else
			return __M_cp_parser_execute<NextProtocol, Remaining...>(cp_pkt, raw_ptr);
	}
	else
	{
		cp_pkt.set_packet(parser_protocol, parser_proto.parse_from(raw_ptr));
		return true;
	}
}

template <typename... CaptureProtocol>
template <typename ProtocolType>
bool pcapcpp::capture<CaptureProtocol...>::__M_cp_parser_execute(captured_packet& cp_pkt, raw::pointer& raw_ptr)
{
	auto parser_protocol    = ProtocolType{};
	auto parser_var         = std::get<ProtocolType::layer>		 (__M_cp_parser);
	auto parser_proto	    = std::get<parser_type<ProtocolType>>(parser_var)   ;
	
	cp_pkt.set_packet(parser_protocol, parser_proto.parse_from(raw_ptr));
	return true;
}

template <typename... CaptureProtocol>
template <typename Protocol>
pcapcpp::capture<Protocol, CaptureProtocol...> pcapcpp::capture<CaptureProtocol...>::operator| (parser_type<Protocol>& parser)
{
	capture<Protocol, CaptureProtocol...> parser_capture;
	((std::get<CaptureProtocol::layer>(parser_capture.__M_cp_parser) = std::get<CaptureProtocol::layer>(__M_cp_parser)), ...); // Fold Expression. Usable Above C++ 17.
	  std::get<Protocol::layer>		  (parser_capture.__M_cp_parser) = parser;

	return parser_capture;
}

template <typename... CaptureProtocol>
template <typename... Protocol>
pcapcpp::capture<Protocol..., CaptureProtocol...> pcapcpp::capture<CaptureProtocol...>::operator| (capture<Protocol...>& parser)
{
	pcapcpp::capture<Protocol..., CaptureProtocol...> parser_capture;
	((std::get<Protocol::layer>(parser_capture.__M_cp_parser) = std::get<Protocol::layer>(__M_cp_parser))		, ...);
	((std::get<Protocol::layer>(parser_capture.__M_cp_parser) = std::get<Protocol::layer>(parser.__M_cp_parser)), ...);

	return parser_capture;
}

template <typename Protocol>
pcapcpp::capture<Protocol>	  pcapcpp::capture<>::operator| (parser<Protocol>& psr)
{
	capture<Protocol>		  parser_capture;
	std::get<Protocol::layer>(parser_capture.__M_cp_parser) = psr;

	return parser_capture;
}

template <typename... CaptureProtocol>
bool pcapcpp::capture<CaptureProtocol...>::operator()(raw& pkt_raw, captured_packet& pkt_capture)
{
	raw::pointer												  cp_raw_pointer(pkt_raw);
	return __M_cp_parser_execute<CaptureProtocol...>(pkt_capture, cp_raw_pointer);
}

template <typename... CaptureProtocol>
template <typename Protocol>
typename pcapcpp::basic_parser<Protocol>::packet pcapcpp::capture<CaptureProtocol...>::captured_packet::operator[](Protocol)
{
	auto		parser_var = std::get<Protocol::layer>(__M_cp_packet);
	std::size_t proto_idx  = helper::index<Protocol, CaptureProtocol...>::value;

	return (proto_idx == parser_var.index() && parser_var.index() != std::variant_npos)
		  ? std::get<basic_parser<Protocol>::packet>(parser_var)
		  :			 basic_parser<Protocol>::packet ();
}

template <typename... CaptureProtocol>
template <typename Protocol, typename PacketType>
void pcapcpp::capture<CaptureProtocol...>::captured_packet::set_packet(Protocol, PacketType&& pkt)
{
	std::get<Protocol::layer>(__M_cp_packet) = pkt;
}