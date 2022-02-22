#pragma once
#include <type_traits>

namespace pcapcpp::protocol {

	class static_sized  {};
	class dynamic_sized {};
	
	class arp_type 
	{ 
		using						 sizing = static_sized;
		static constexpr std::size_t size   = 26;
	};

	class ethernet_type 
	{
		using						 sizing = static_sized;
		static constexpr std::size_t size   = 14;
	};

	class ipv4_type 
	{
		using						 sizing = static_sized;
		static constexpr std::size_t size   = 16;
	};

	class tcp_type  
	{
		using						 sizing = static_sized;
		static constexpr std::size_t size   = 20;
	};
	
	class udp_type  
	{
		using						 sizing = static_sized;
		static constexpr std::size_t size   = 8;
	};

	static constexpr arp_type	   arp;
	static constexpr ethernet_type ethernet;

	static constexpr ipv4_type	   v4;

	static constexpr tcp_type	   tcp;
	static constexpr udp_type      udp;
}