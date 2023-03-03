#include <unordered_map>
#include <memory>
#include <string>

namespace layers {
namespace containers {

template<class Base, class ContainerInfo>
struct layer : public Base
{
	using container_info = ContainerInfo;

	virtual typename Base::event next();

private:
	std::unordered_map<std::string, std::shared_ptr<ContainerInfo>> containers;
};

template<class Base, class ContainerInfo>
typename Base::event layer<Base, ContainerInfo>::next()
{
	typename Base::event ev = Base::next();
	std::shared_ptr<typename Base::threadinfo> tinfo = ev.get_tinfo();

	ContainerInfo* cinfo = new ContainerInfo;

	tinfo->container_id = std::to_string(tinfo->tid);
	cinfo->container_id = tinfo->container_id;
	tinfo->cinfo = std::shared_ptr<ContainerInfo>(cinfo);

	containers[tinfo->container_id] = tinfo->cinfo;

	return ev;
}

template<class Event>
struct event : public Event
{
};

template<class Threadinfo, class ContainerInfo>
struct threadinfo : public Threadinfo
{
	std::string container_id;
	std::shared_ptr<ContainerInfo> cinfo;

	std::shared_ptr<ContainerInfo> get_cinfo() { return cinfo; }
};

struct container_info
{
	std::string container_id;
};

};
};
