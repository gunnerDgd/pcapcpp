#pragma once
#include <pcapcpp/parse/parser.hpp>
#include <pcapcpp/capture/index.hpp>
#include <tuple>

namespace pcapcpp {
	template <typename... T>
	class capture;

	template <typename... CaptureProtocol>
	class capture
	{
		template <typename... Protocol1, typename... Protocol2>
		capture(capture<Protocol1...>&, capture<Protocol2...>&);
	public:
		template <typename Protocol>
		using parser	   = basic_parser<Protocol>;
		using parser_tuple = std::tuple<parser<CaptureProtocol>...>;

	public:
		template <typename Protocol>
		capture<Protocol, CaptureProtocol...>	 operator| (parser<Protocol>&);
		template <typename... Protocol>
		capture<Protocol..., CaptureProtocol...> operator| (capture<Protocol...>&);
		void									 operator()(raw&);

	private:
		parser_tuple __M_cp_parser;
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
	capture(CaptureProtocol&&...)->capture<CaptureProtocol...>;
}

template <typename... CaptureProtocol>
template <typename Protocol>
pcapcpp::capture<Protocol, CaptureProtocol...> pcapcpp::capture<CaptureProtocol...>::operator| (parser<Protocol>& parser)
{
	capture<Protcool, CaptureProtocol...> parser_capture;
										  parser_capture.__M_cp_parser = std::tuple_cat(std::make_tuple(parser), __M_cp_parser);

	return parser_capture;
}

template <typename... CaptureProtocol>
template <typename... Protocol>
pcapcpp::capture<Protocol..., CaptureProtocol...> pcapcpp::capture<CaptureProtocol...>::operator| (capture<Protocol...>& parser)
{
	
}

template <typename Protocol>
pcapcpp::capture<Protocol>	  pcapcpp::capture<>::operator| (parser<Protocol>& psr)
{
	capture<Protocol> psr_capture;
				      psr_capture.__M_cp_parser = psr;

	return psr_capture;
}

template <typename... Protocol>
void pcapcpp::capture<Protocol...>::operator()(raw& pkt_raw)
{
	raw::pointer pkt_pointer(pkt_raw);
	
	if constexpr (helper::index<protocol::ethernet_type, Protocol...> == -1)
	{
		auto ulp = parser_traits<protocol::ethernet_type>::upper_layer(pkt_raw);
				
	}
		
}