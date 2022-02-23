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
		template <typename ParserProtocol, typename ParserTraits>
		friend class basic_parser;
		template <typename ParserProtocol>
		friend class parser_traits;
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
		pointer_type   __M_raw_pointer		 ;
		size_type      __M_raw_packet_size	 ;
		size_type      __M_raw_packet_pointer;
	};
}
