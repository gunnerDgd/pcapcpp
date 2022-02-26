#include <pcapcpp/interface/interface.hpp>
#include <pcapcpp/interface/enumerator.hpp>

pcapcpp::network_interface::network_interface(handle_type hnd) : __M_if_name	   (hnd->name),
																 __M_if_description(hnd->description) 
{
}

pcapcpp::interface_enumerator::interface_enumerator()
{
	char ifenum_message[PCAP_ERRBUF_SIZE];
	int  ifenum_result = pcap_findalldevs(&__M_ifenum_handle, ifenum_message);

	for (auto it_enum = __M_ifenum_handle; it_enum; it_enum = it_enum->next, __M_ifenum_count++);
}

pcapcpp::interface_enumerator::~interface_enumerator()
{
	pcap_freealldevs(__M_ifenum_handle);
}

pcapcpp::network_interface pcapcpp::interface_enumerator::operator[](std::uint32_t index)
{
	if (index >= __M_ifenum_count)
		return interface_type();

	interface_handle   if_hnd   = __M_ifenum_handle;
	for (std::uint32_t it_index = 0; it_index < index; it_index++, if_hnd = if_hnd->next);

	return if_hnd;
}