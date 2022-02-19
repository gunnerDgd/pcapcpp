#pragma once
#include <pcapcpp/interface/interface.hpp>

namespace pcapcpp {
	class interface_enumerator
	{
	public:
		typedef network_interface			   interface_type  ;
		typedef network_interface::handle_type interface_handle;

	public:
		interface_enumerator ();
		~interface_enumerator();

	public:
		std::uint16_t  count	 ()			    { return __M_ifenum_count; }
		interface_type operator[](std::uint32_t);

	private:
		interface_handle __M_ifenum_handle;
		std::uint16_t    __M_ifenum_count ;
	};
}