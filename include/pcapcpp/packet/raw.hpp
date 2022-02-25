#pragma once
#include <memory>
#include <type_traits>

/*
	* pcapcpp::raw Class
	*
	* - Description
	*		--> "Raw" Class Stores raw packet data for parsing.
	*			The pointer which contains 
	*
	*/

namespace pcapcpp {
	class raw
	{
		template <typename... Protocol>
		friend class capture;
		friend class endpoint;
	public:
		class				  pointer;
		typedef std::uint8_t* pointer_type;
		typedef std::size_t   size_type   ;

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
		operator  bool		 () { return !(__M_raw_pointer == nullptr); }

	private:
		pointer_type   __M_raw_pointer	  ;
		size_type      __M_raw_packet_size;
	};

	class raw::pointer
	{
		template <typename... T>
		friend class capture;
		friend class endpoint;
		friend class raw;

		pointer(raw&);
	public:
		template <typename ReadType>
		ReadType& extract_from();
		template <typename ReadType>
		ReadType& view_from   ();

	private:
		pointer_type __M_raw_ptr;
		size_type    __M_raw_size = 0, __M_raw_current = 0;
	};
}

pcapcpp::raw::pointer::pointer(raw& pkt) : __M_raw_ptr (pkt.__M_raw_pointer),
										   __M_raw_size(pkt.__M_raw_packet_size) {  }

template <typename ReadType>
ReadType& pcapcpp::raw::pointer::extract_from()
{
	ReadType& rd_context = *reinterpret_cast<ReadType*>(__M_raw_ptr + __M_raw_current);
																	  __M_raw_current += sizeof(ReadType);
	return    rd_context;
}

template <typename ReadType>
ReadType& pcapcpp::raw::pointer::view_from()
{
	return *reinterpret_cast<ReadType*>(__M_raw_ptr + __M_raw_current);
}