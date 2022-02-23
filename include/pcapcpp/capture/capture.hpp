#pragma once
#include <pcapcpp/capture/capture_helper.hpp>
#include <tuple>

namespace pcapcpp {
	template <typename... CaptureProtocol>
	class capture
	{
	public:
		template <typename T>
		using index		 =    protocol_index_v<T, CaptureProtocol...>;
		using this_type  =    capture<CaptureProtocol...>;
		
		using parser_set = std::tuple<basic_parser<CaptureProtocol>...>;
		using filter_set = std::tuple<typename CaptureProtocol::filter...>;
		using packet_set = std::tuple<typename basic_parser<CaptureProtocol>::packet...>;

	public:
		class packet
		{
			template <typename ProtocolType>
			using packet_t = basic_parser<ProtocolType>::packet&;

			template <typename... PacketType>
			packet(PacketType&&...);
		public:
			template <typename ProtocolType>
			std::enable_if_t<index<ProtocolType> == -1>						    operator[](ProtocolType&&) {}
			template <typename ProtocolType>
			std::enable_if_t<index<ProtocolType> != -1, packet_t<ProtocolType>> operator[](ProtocolType&&)
			{
				return std::get<index<ProtocolType>>(__M_packet_set);
			}

		private:
			packet_set __M_packet_set;
		};
		
	public:
		template <typename ProtocolType, typename FilterType>
		std::enable_if_t<index<ProtocolType> != -1> set_filter(ProtocolType&&, FilterType&& filter)
		{
			std::get<protocol_index_v<ProtocolType, CaptureProtocol...>>(__M_cp_filter) = filter;
		}

		template <typename ProtocolType, typename FilterType>
		std::enable_if_t<index<ProtocolType> == -1> set_filter(ProtocolType&&, FilterType&&) {  }

	public:
		packet operator()(raw&);

	private:
		template <typename ExecuteProtocol, typename... Remaining>
		void	   __M_cp_filter_execute(raw&);
		template <typename ExecuteProcotol>
		void	   __M_cp_filter_execute(raw&)
		{
			
		}

		parser_set __M_cp_parser;
		filter_set __M_cp_filter;
	};
}