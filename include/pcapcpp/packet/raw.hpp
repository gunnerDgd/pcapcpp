#pragma once
#include <memory>
#include <type_traits>

namespace pcapcpp {
	template <std::size_t RawSize = 4096, typename RawAllocator = std::allocator<std::uint8_t>>
	class raw
	{
	public:
		typedef			 RawAllocator		 allocator_type			 ;
		typedef			 std::uint8_t*		 pointer_type			 ;
		typedef			 std::size_t		 size_type				 ;
		static constexpr std::size_t RawSize allocated_size = RawSize;

	public:
		raw ();
		~raw();

	public:
		size_type packet_size() { return __M_raw_packet_size; }

	private:
		pointer_type   __M_raw_pointer    ;
		size_type      __M_raw_packet_size;
		allocator_type __M_raw_allocator  ;
	};
}

template <std::size_t RawSize, typename RawAllocator>
pcapcpp::raw<RawSize, RawAllocator>::raw() : __M_raw_pointer(__M_raw_allocator.allocate(allocated_size)) {  }

template <std::size_t RawSize, typename RawAllocator>
pcapcpp::raw<RawSize, RawAllocator>::~raw()																 { __M_raw_allocator.deallocate(__M_raw_pointer, allocated_size); }