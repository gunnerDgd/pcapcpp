#pragma once

namespace pcapcpp {
	template <typename FilterProtocol, typename FilterTraits>
	class basic_filter
	{
	public:
		using protocol		  = FilterTraits;
		using protocol_sizing = FilterProtocol::sizing;
		
		using filter_policy   = FilterTraits::filter_policy;
		using filter_packet   = FilterTraits::packet_type  ;
	
	public:
		basic_filter();

	public:
		template <typename InputPolicy>
		std::enable_if_t<std::is_same_v		    <filter_policy, 
						 std::remove_reference_t<InputPolicy>>> operator >> (InputPolicy&&);

		
	};
}