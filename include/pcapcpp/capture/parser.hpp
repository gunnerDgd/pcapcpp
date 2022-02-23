#pragma once
#include <pcapcpp/endpoint/endpoint.hpp>
#include <pcapcpp/packet/category.hpp>

using pcapcpp::protocol::static_sized;
using pcapcpp::protocol::dynamic_sized;


namespace pcapcpp {
	class			 null_filter	    {};
	static constexpr null_filter no_filter;

	template <typename ParserProtocol>
	class parser_traits;

	template <typename ParserProtocol, typename ParserTraits = parser_traits<ParserProtocol>>
	class basic_parser
	{
	public:
		using traits_type		= ParserTraits;
		using packet			= traits_type::packet;
		
		using filter			= traits_type::filter;
		using protocol_category = traits_type::protocol_category;

	public:
#define IF_STATIC_SIZED  std::enable_if_t<traits_type ::notifies_upper_protocol, packet>
#define IF_DYNAMIC_SIZED std::enable_if_t<!traits_type ::notifies_upper_protocol, packet>

		template <typename FilterType>
		IF_STATIC_SIZED  parse_from(FilterType&& flt, raw& pkt, traits_type::upper_protocol& ulp)
		{
			return traits_type::parse_from(flt, pkt, ulp);
		}

		template <typename FilterType>
		IF_DYNAMIC_SIZED parse_from(FilterType&& flt, raw& pkt)
		{
			return traits_type::parse_from(flt, pkt);
		}
	};
}

