#pragma once
#include <pcapcpp/parse/forward.hpp>
#include <type_traits>

namespace pcapcpp::helper {
	template <std::size_t Index, typename... Protocol>
	struct __index;

	template <std::size_t Index, typename ProtocolType, typename ProtocolCompare, typename... ProtocolSet>
	struct __index<Index, ProtocolType, ProtocolCompare, ProtocolSet...>
	{
		static constexpr std::size_t value = (std::is_same_v<ProtocolType, ProtocolCompare>) ? Index : __protocol_index<Index + 1, ProtocolType, ProtocolSet...>::value;
	};

	template <std::size_t Index, typename ProtocolType, typename ProtocolCompare>
	struct __index<Index, ProtocolType, ProtocolCompare>
	{
		static constexpr std::size_t value = (std::is_same_v<ProtocolType, ProtocolCompare>) ? Index : -1;;
	};

	template <typename ProtocolType, typename... ProtocolSet>
	struct index { static constexpr std::size_t value = __protocol_index<0, std::remove_reference_t<ProtocolType>, ProtocolSet...>::value; };
}