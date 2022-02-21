#pragma once
#include <memory>
#include <type_traits>

namespace pcapcpp {
	/*
	* pcapcpp::raw Class
	* 
	* - Description
	*		--> "Raw" Class Stores raw packet data for parsing.
	*			The pointer which contains 
	* 
	*/
	class raw
	{
		template <typename FilterCategory>
		friend class basic_filter;
		friend class endpoint;
	public:
		typedef			 std::uint8_t* pointer_type;
		typedef			 std::size_t   size_type   ;

		raw ();
		~raw();
	private:
		raw (pointer_type, size_type);
	
	public:
		raw			  (raw&) = delete;
		raw& operator=(raw&) = delete;
		
		raw			  (raw&&);
		raw& operator=(raw&&);
		
	public:
		size_type packet_size() { return   __M_raw_packet_size		  ; }
		operator bool		 () { return !(__M_raw_pointer == nullptr); }

	private:
		pointer_type   __M_raw_pointer    ;
		size_type      __M_raw_packet_size;
	};
}

pcapcpp::raw::raw(pointer_type ptr, size_type size)
{
	if (!ptr)
		return;

	__M_raw_pointer     = new std::uint8_t[size];
	__M_raw_packet_size = size;
	
	std::memcpy(reinterpret_cast<void*>(__M_raw_pointer), ptr, size);
}

pcapcpp::raw::raw(raw&& move) : __M_raw_pointer	   (move.__M_raw_pointer)   ,
								__M_raw_packet_size(move.__M_raw_packet_size)
{
	move.__M_raw_packet_size = 0;
	move.__M_raw_pointer     = nullptr;
}

pcapcpp::raw& pcapcpp::raw::operator=(raw&& move)
{
	delete[] __M_raw_pointer;

	__M_raw_pointer			 = move.__M_raw_pointer	 ;
	__M_raw_packet_size		 = move.__M_raw_packet_size;

	move.__M_raw_pointer	 = nullptr;
	move.__M_raw_packet_size = 0;

	return *this;
}

pcapcpp::raw::raw() : __M_raw_pointer    (nullptr), 
					  __M_raw_packet_size(0)      {  }

pcapcpp::raw::~raw()							  { if(__M_raw_pointer) delete[] __M_raw_pointer; }