namespace layers {
namespace scap {

struct event
{
	int num;
};

template<class Event>
struct layer
{
	using event = Event;

	virtual Event next();

private:
	int counter = 0;
};

template<class Event>
Event layer<Event>::next()
{
	Event e;
	e.num = ++counter;
	return e;
}

};
};
