#pragma once
#include <pcapcpp/packet/category.hpp>
#include <pcapcpp/packet/raw.hpp>

#include <optional>

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
		using packet			= typename traits_type::packet;
		
		using filter			= typename traits_type::filter;
		using filter_option		= std::optional<filter>;

		static constexpr bool notifies_upper_protocol =		     ParserTraits::notifies_upper_protocol;
		using						   upper_protocol = typename ParserTraits::upper_protocol		  ;

	public:
		template <typename FilterType>
		void		   set_filter (FilterType&& flt)  { __M_parse_filter = flt; }
		void		   set_filter (null_filter)       { __M_parse_filter = std::nullopt_t; }

		upper_protocol upper_layer(raw::pointer& ptr) { return traits_type::upper_layer(ptr); }
		upper_protocol upper_layer(packet& pkt)       { return traits_type::upper_layer(pkt); }
		
		packet		   parse_from (raw::pointer& pkt) { return (__M_parse_filter) ? traits_type::parse_from (*__M_parse_filter, pkt) 
																				  : traits_type::parse_from (no_filter        , pkt); }

	private:
		filter_option __M_parse_filter;
	};
}