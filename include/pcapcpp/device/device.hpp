#pragma once
#include <pcapcpp/interface/interface.hpp>

namespace pcapcpp {
	class device
	{
		friend class endpoint;
	public:
		typedef pcap_t*					  handle_type   ;
		typedef network_interface		  interface_type;
		
		typedef std::uint32_t			  size_type		;
		typedef char					  message_type[PCAP_ERRBUF_SIZE];

	public:
		device (interface_type&, size_type);
		~device();
	
	private:
		handle_type  __M_if_device_handle;
		message_type __M_if_device_errmsg;
	};
}