#pragma once
#include <pcapcpp/capture/forward.hpp>
#include <type_traits>

namespace pcapcpp {
	template <typename... T>
	struct filter_type;

	template <typename T, typename CompareProtocol, typename... CaptureProcotol>
	struct filter_type<T, CompareProtocol, CaptureProcotol...> 
	{ 
		typedef type std::conditional_t<
					 std::is_same_v    <T, typename CompareProtocol::protocol_category>,
										   typename CompareProtocol::protocol_category, 
										   typename filter_type<T, CaptureProcotol...>::type>; 
	};

	template <typename T, typename CompareProtocol>
	struct filter_type<T, CompareProtocol> 
	{ 
		typedef type std::conditional_t<T, typename CompareProtocol::protocol_category, void>; 
	};

	template <typename FilterType, typename... T>
	using filter_t = filter_type<std::remove_reference_t<FilterType>, T...>;

	template <std::size_t Index, typename... Protocol>
	struct __protocol_index;

	template <std::size_t Index, typename ProtocolType, typename ProtocolCompare, typename... ProtocolSet>
	struct __protocol_index<Index, ProtocolType, ProtocolCompare, ProtocolSet...>
	{
		static constexpr std::size_t value;
		constexpr __protocol_index()
		{
			if constexpr (std::is_same_v<ProtocolType, ProtocolCompare>)
				value = Index;
			else
				value = __protocol_index<Index + 1, ProtocolType, ProtocolSet...>;
		}
	};

	template <std::size_t Index, typename ProtocolType, typename ProtocolCompare>
	struct __protocol_index<Index, ProtocolType, ProtocolCompare>
	{
		static constexpr std::size_t value;
		constexpr __protocol_index()
		{
			if constexpr (std::is_same_v<ProtocolType, ProtocolCompare>)
				value = Index;
			else
				value = -1;
		}
	};

	template <typename ProtocolType, typename... ProtocolSet>
	struct protocol_index { static constexpr std::size_t value = __protocol_index<0, ProtocolType, ProtocolSet...>};
	template <typename... Protocol>
	using  protocol_index_v = protocol_index<std::remove_reference_t<Protocol>...>::value;

}