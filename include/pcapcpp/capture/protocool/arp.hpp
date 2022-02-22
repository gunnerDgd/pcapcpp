#pragma once
#include <pcapcpp/capture/filter.hpp>
#include <pcapcpp/endpoint/endpoint.hpp>

#include <pcapcpp/capture/category.hpp>
#include <pcapcpp/packet/category.hpp>

namespace pcapcpp {
	template <>
	class basic_filter<category::arp_type>
	{
	public:
		using					   size_type	   = std::uint16_t;
		using					   packet_category = filter::static_sized;
		static constexpr size_type packet_size	   = 26;

		
	};
}

template <typename PacketType>
