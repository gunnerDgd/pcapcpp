#pragma once
#include <memory>
#include <type_traits>

namespace pcapcpp {
	template <std::size_t RawSize = 4096, typename RawAllocator = std::allocator<std::uint8_t>>
	class raw
	{
		friend class endpoint;
	public:
		typedef			 RawAllocator				allocator_type		    ;
		static constexpr std::size_t				allocated_size = RawSize;

		typedef			 std::uint8_t*				pointer_type			;
		typedef			 std::size_t				size_type			    ;
		typedef			 raw<RawSize, RawAllocator> this_type				;

	private:
		raw(pointer_type, size_type);
		raw();
	
	public:
		raw (this_type&);
		raw (this_type&&);
		~raw();

	public:
		size_type packet_size() { return   __M_raw_packet_size		  ; }
		operator bool		 () { return !(__M_raw_pointer == nullptr); }

	public:
		this_type& operator=(this_type&);
		this_type& operator=(this_type&&);

	private:
		pointer_type   __M_raw_pointer    ;
		size_type      __M_raw_packet_size;
		allocator_type __M_raw_allocator  ;
	};
}

template <std::size_t RawSize, typename RawAllocator>
pcapcpp::raw<RawSize, RawAllocator>::raw(pointer_type ptr, size_type size) : __M_raw_pointer    (__M_raw_allocator.allocate(allocated_size)),
																			 __M_raw_packet_size(size)
{
	if (!ptr) return;
	std::memcpy((void*)__M_raw_pointer, ptr, size);
}

template <std::size_t RawSize, typename RawAllocator>
pcapcpp::raw<RawSize, RawAllocator>::raw(this_type& copy) : __M_raw_pointer    (copy.__M_raw_pointer),
															__M_raw_packet_size(copy.__M_raw_packet_size),
															__M_raw_allocator  (copy.__M_raw_allocator)  {  }

template <std::size_t RawSize, typename RawAllocator>
pcapcpp::raw<RawSize, RawAllocator>::raw(this_type&& move) : __M_raw_pointer	(move.__M_raw_pointer)    ,
															 __M_raw_packet_size(move.__M_raw_packet_size),
															 __M_raw_allocator  (move.__M_raw_allocator)
{
	move.__M_raw_packet_size = 0;
	move.__M_raw_pointer     = nullptr;
}

template <std::size_t RawSize, typename RawAllocator>
pcapcpp::raw<RawSize, RawAllocator>::this_type& pcapcpp::raw<RawSize, RawAllocator>::operator=(this_type& copy)
{
	__M_raw_pointer     = copy.__M_raw_pointer;
	__M_raw_packet_size = copy.__M_raw_packet_size;
	__M_raw_allocator   = copy.__M_raw_allocator;

	return *this;
}

template <std::size_t RawSize, typename RawAllocator>
pcapcpp::raw<RawSize, RawAllocator>::this_type& pcapcpp::raw<RawSize, RawAllocator>::operator=(this_type&& move)
{
	__M_raw_pointer     = move.__M_raw_pointer;
	__M_raw_packet_size = move.__M_raw_packet_size;
	__M_raw_allocator   = move.__M_raw_allocator;

	move.__M_raw_pointer	 = nullptr;
	move.__M_raw_packet_size = 0;

	return &this;
}
template <std::size_t RawSize, typename RawAllocator>
pcapcpp::raw<RawSize, RawAllocator>::raw() : __M_raw_pointer(nullptr) {  }

template <std::size_t RawSize, typename RawAllocator>
pcapcpp::raw<RawSize, RawAllocator>::~raw()
{
	if (__M_raw_pointer && __M_raw_packet_size)
		__M_raw_allocator.deallocate(__M_raw_pointer, allocated_size); 
}