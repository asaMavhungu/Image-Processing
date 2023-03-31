#include "connectedComponent.h"

using namespace MVHASA001;

namespace MVHASA001
{

	ConnectedComponent::ConnectedComponent() : id(0), points() // constr
	{
	}

	ConnectedComponent::ConnectedComponent(int x) : id(x), points() // constr
	{
	}

	ConnectedComponent::~ConnectedComponent() = default; // destruct

	ConnectedComponent::ConnectedComponent(const ConnectedComponent &rhs) : id(rhs.id),  size(rhs.size), points(rhs.points) {} // copy

	ConnectedComponent &ConnectedComponent::operator=(const ConnectedComponent &rhs) // copy assign
	{
		if (this == &rhs) return *this;
		points = rhs.points;
		return *this;
	}

	ConnectedComponent::ConnectedComponent(ConnectedComponent && rhs) : points(move(rhs.points)) {}; // move

	ConnectedComponent & ConnectedComponent::operator=(ConnectedComponent &&rhs) 
	{
		if (this == &rhs) return *this;
		points = std::move(rhs.points);
		return *this;
	}

	ConnectedComponent &ConnectedComponent::operator+=(const std::pair<int, int> &rhs)
	{
		this->points.push_back(rhs);
		return *this;
	}

	std::pair<int,int> ConnectedComponent::getPoint()
	{	
		return this->points[0];
	}

	int MVHASA001::ConnectedComponent::getSize() const
	{
		return this->size;
	}

	void MVHASA001::ConnectedComponent::setSize(int i)
	{
		this->size = i;
	}

	std::ostream &operator<<(std::ostream &os, const ConnectedComponent &rhs)
	{
		os << "ID: " << rhs.id << ", Size: " << rhs.size;
		return os;
	}

	bool ConnectedComponent::operator<(const ConnectedComponent& other) const
	{
		return this->size < other.size;
	}



}
