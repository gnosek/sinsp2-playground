#include <unordered_map>
#include <memory>

namespace layers {
namespace parsers {

template<class Event, class Threadinfo> struct event;

template<class Event, class Threadinfo>
static inline void init_event(event<Event, Threadinfo>& evt, int tid, std::shared_ptr<Threadinfo> tinfo)
{
	evt.tid = tid;
	evt.tinfo = tinfo;
}

template<class Base, class Threadinfo>
struct layer : public Base
{
	using threadinfo = Threadinfo;

	virtual typename Base::event next();

private:
	std::unordered_map<int, std::shared_ptr<Threadinfo>> threads;
};

template<class Base, class Threadinfo>
typename Base::event layer<Base, Threadinfo>::next()
{
	typename Base::event ev = Base::next();

	Threadinfo* tinfo = new Threadinfo;
	tinfo->tid = 100;

	auto tinfo_ptr = std::shared_ptr<Threadinfo>(tinfo);
	threads[100] = tinfo_ptr;

	init_event(ev, 100, tinfo_ptr);

	return ev;
};

template<class Event, class Threadinfo>
struct event : public Event
{
private:
	int tid;
	std::shared_ptr<Threadinfo> tinfo;

public:
	int get_tid() const { return tid; }
	std::shared_ptr<Threadinfo> get_tinfo() { return tinfo; }

	friend void init_event<>(event<Event, Threadinfo>& evt, int tid, std::shared_ptr<Threadinfo> tinfo);
};

struct threadinfo
{
	int tid;
};

};
};
