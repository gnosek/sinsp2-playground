#include <string>

namespace layers {
namespace thread_colour {

template<class Base>
struct layer : public Base
{
	virtual typename Base::event next();
};

template<class Base>
typename Base::event layer<Base>::next()
{
	typename Base::event ev = Base::next();
	auto tinfo = ev.get_tinfo();

	tinfo->colour = "green";

	return ev;
}

template<class Threadinfo>
struct threadinfo : public Threadinfo
{
	std::string colour;
};

};
};
