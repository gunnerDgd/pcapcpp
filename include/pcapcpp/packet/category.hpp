#pragma once
#include <type_traits>
#include <variant>

namespace pcapcpp::protocol {

	class static_sized  {};
	class dynamic_sized {};

	class ethernet_type 
	{
	public:
		using						  sizing = static_sized;
		static constexpr std::size_t  size   = 14;
		static constexpr std::uint8_t layer  = 0;
	};

	class arp_type
	{
	public:
		using						  sizing = static_sized;
		static constexpr std::size_t  size   = 26;
		static constexpr std::uint8_t layer  = 1;
	};

	class ipv4_type
	{
	public:
		using						  sizing = static_sized;
		static constexpr std::size_t  size   = 16;
		static constexpr std::uint8_t layer  = 1;
	};

	class tcp_type  
	{
	public:
		using						  sizing = static_sized;
		static constexpr std::size_t  size   = 20;
		static constexpr std::uint8_t layer  = 2;
	};
	
	class udp_type  
	{
	public:
		using						  sizing = static_sized;
		static constexpr std::size_t  size   = 8;
		static constexpr std::uint8_t layer  = 2;
	};

	static constexpr arp_type	   arp;
	static constexpr ethernet_type ethernet;

	static constexpr ipv4_type	   v4;

	static constexpr tcp_type	   tcp;
	static constexpr udp_type      udp;
}