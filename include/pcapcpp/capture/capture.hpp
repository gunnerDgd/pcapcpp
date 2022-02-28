#pragma once
#include <pcapcpp/layer/layer.hpp>

namespace pcapcpp {
	class stream_capture
	{
	public:
		
	public:
		stream_capture(endpoint&);
		
		template <typename ProtocolType>
		auto operator()(ProtocolType&&);

	private:
		endpoint&			   __M_strcap_endpoint;

		layer::datalink_parser __M_strcap_datalink;
		layer::network_parser  __M_strcap_network ;
	};
}