#pragma once
#include <pcapcpp/interface/interface.hpp>

#include <chrono>
#include <climits>

namespace pcapcpp {
	class device
	{
		friend class endpoint;
	public:
		class		 operation_mode
		{
			friend class device;
		public:
			enum class capture_mode : int { managed = 0, monitor = 1 };
			enum class promiscuous  : int { promiscuous = 1, non_promiscuous = 0 };
		public:
			typedef std::chrono::milliseconds timeout_type;
			typedef std::uint32_t			  size_type   ;

		public:
			static constexpr timeout_type block_until			 = std::chrono::milliseconds(0);
			static constexpr size_type    default_capture_length = USHRT_MAX;

		public:
			operation_mode(timeout_type op_timeout = block_until		   ,
						   size_type    op_caplen  = default_capture_length,
						   capture_mode op_capmode = capture_mode::managed ,
						   promiscuous  op_pmode   = promiscuous::promiscuous) : __M_opmode_timeout(op_timeout),
																				 __M_opmode_caplen (op_caplen) ,
																				 __M_opmode_capmode(op_capmode),
																				 __M_opmode_pmode  (op_pmode)  {  }

		private:
			timeout_type __M_opmode_timeout;
			size_type    __M_opmode_caplen ;

			capture_mode __M_opmode_capmode;
			promiscuous  __M_opmode_pmode  ;
		};
	public:
		typedef pcap_t*					  handle_type   ;
		typedef network_interface		  interface_type;
		typedef char					  message_type[PCAP_ERRBUF_SIZE];

		typedef std::uint32_t			  size_type;
		typedef std::chrono::milliseconds timeout_type;

	public:
		device (interface_type&, operation_mode);
		~device();
	
	private:
		interface_type& __M_if_device_interface;
		handle_type     __M_if_device_handle   ;

		message_type    __M_if_device_errmsg;
		operation_mode  __M_if_device_opmode;
	};
}