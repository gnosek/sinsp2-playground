#include <stdio.h>

#include "layers/scap.hpp"
#include "layers/parsers.hpp"
#include "layers/containers.hpp"
#include "layers/thread_colour.hpp"

class final_container_info : public layers::containers::container_info {};

class final_threadinfo : public layers::thread_colour::threadinfo<layers::containers::threadinfo<layers::parsers::threadinfo, final_container_info>> {};

class final_event : public layers::containers::event<layers::parsers::event<layers::scap::event, final_threadinfo>> {};

class final_sinsp : public layers::thread_colour::layer<layers::containers::layer<layers::parsers::layer<layers::scap::layer<final_event>, final_threadinfo>, final_container_info>> {};

int main()
{
	final_sinsp insp;

	final_event ev = insp.next();
	printf("ev.num=%d, ev.tid=%d\n", ev.num, ev.get_tid());

	auto tinfo = ev.get_tinfo();
	auto cinfo = tinfo->get_cinfo();

	printf("cinfo.container_id = %s\n", cinfo->container_id.c_str());
	printf("tinfo.colour = %s\n", tinfo->colour.c_str());
}
