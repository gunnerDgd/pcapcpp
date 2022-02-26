#pragma once
#include <pcap/pcap.h>
#include <string>

namespace pcapcpp {
	class network_interface
	{
		friend class device;
		friend class interface_enumerator;
	public:
		typedef pcap_if_t*  handle_type;
		typedef std::string string_type;

	private:
		network_interface(handle_type);
		network_interface(std::nullptr_t) {  }
		network_interface()				  {  }

	public:
		string_type name	   () { return  __M_if_name		   ; }
		string_type description() { return  __M_if_description ; }
		operator bool		   () { return !__M_if_name.empty(); }

	private:
		string_type __M_if_name,
					__M_if_description;
	};
}

