#include <pcapcpp/packet/raw.hpp>

pcapcpp::raw::raw(pointer_type ptr, size_type size)
{
	if (!ptr) return;

	__M_raw_pointer		= new std::uint8_t[size];
	__M_raw_packet_size = size;

	std::memcpy(reinterpret_cast<void*>(__M_raw_pointer), ptr, size);
}

pcapcpp::raw::raw(raw&& move) : __M_raw_pointer	   (move.__M_raw_pointer),
								__M_raw_packet_size(move.__M_raw_packet_size)
{
	move.__M_raw_packet_size = 0;
	move.__M_raw_pointer	 = nullptr;
}

pcapcpp::raw& pcapcpp::raw::operator=(raw&& move)
{
	delete[] __M_raw_pointer;

	__M_raw_pointer		= move.__M_raw_pointer;
	__M_raw_packet_size = move.__M_raw_packet_size;

	move.__M_raw_pointer	 = nullptr;
	move.__M_raw_packet_size = 0;

	return *this;
}

pcapcpp::raw::raw() : __M_raw_pointer(nullptr),
					  __M_raw_packet_size(0)  {  }
pcapcpp::raw::~raw()						  { if (__M_raw_pointer) delete[] __M_raw_pointer; }