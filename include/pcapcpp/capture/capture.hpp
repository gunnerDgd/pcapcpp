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
		parser_type<ProtocolType>& operator[](ProtocolType);
		captured_packet			   operator()(raw&);
	private:
		template <typename ProtocolType, typename NextProtocol, typename... Remaining>
		void				   __M_cp_parser_execute   (captured_packet&, raw::pointer&);
		template <typename ProtocolType>
		void				   __M_cp_parser_execute   (captured_packet&, raw::pointer&);

		parser::layer_parser   __M_cp_parser;
	};

	template <>
	class capture<>
	{
	public:
		template <typename Protocol>
		using parser = basic_parser<Protocol>;
	public:
		template <typename Protocol>
		capture<Protocol>	 operator| (parser<Protocol>&);
	};

	template <typename... CaptureProtocol>
	class capture<CaptureProtocol...>::captured_packet
	{
	public:
		template <typename Protocol>
		typename basic_parser<Protocol>::packet& operator[](Protocol);

	private:
		parser::layer_packet __M_cp_packet;
	};
}

template <typename... CaptureProtocol>
pcapcpp::capture<CaptureProtocol...>::capture() {  }

template <typename... CaptureProtocol>
template <typename ProtocolType, typename NextProtocol, typename... Remaining>
void pcapcpp::capture<CaptureProtocol...>::__M_cp_parser_execute(captured_packet& cp_pkt, raw::pointer& raw_ptr)
{
	auto parser_protocol = ProtocolType{};
	auto parser_var      = std::get<ProtocolType::layer>	  (__M_cp_parser);
	auto parser_proto	 = std::get<parser_type<ProtocolType>>(parser_var);

	if constexpr (parser_type<ProtocolType>::notifies_upper_protocol)
	{	
		auto ulp			    = parser_proto.upper_layer(raw_ptr);
		cp_pkt[parser_protocol] = parser_proto.parse_from (raw_ptr);

		if (!parser::is_upper_layer<NextProtocol>(ulp))
			return;
		else
			__M_cp_parser_execute<NextProtocol, Remaining...>(cp_pkt, raw_ptr);
	}
	else
		cp_pkt[parser_protocol] = parser_proto.parse_from(raw_ptr);
}

template <typename... CaptureProtocol>
template <typename ProtocolType>
void pcapcpp::capture<CaptureProtocol...>::__M_cp_parser_execute(captured_packet& cp_pkt, raw::pointer& raw_ptr)
{
	auto parser_protocol    = ProtocolType{};
	auto parser_var         = std::get<ProtocolType::layer>		 (__M_cp_parser);
	auto parser_proto	    = std::get<parser_type<ProtocolType>>(__M_cp_parser);
	
	cp_pkt[parser_protocol] = parser_proto.parse_from(raw_ptr);
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
typename pcapcpp::capture<CaptureProtocol...>::captured_packet pcapcpp::capture<CaptureProtocol...>::operator()(raw& pkt_raw)
{
	captured_packet cp_packet;
	raw::pointer	cp_raw_pointer(pkt_raw);

	__M_cp_parser_execute<CaptureProtocol...>(cp_packet, cp_raw_pointer);
	return									  cp_packet;
}

template <typename... CaptureProtocol>
template <typename Protocol>
typename pcapcpp::basic_parser<Protocol>::packet& pcapcpp::capture<CaptureProtocol...>::captured_packet::operator[](Protocol)
{
	return std::get<Protocol::layer>(__M_cp_packet);
}