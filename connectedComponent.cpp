#include "connectedComponent.h"

using namespace MVHASA001;

ConnectedComponent::ConnectedComponent() : id(nullptr), points()
{
}

ConnectedComponent &ConnectedComponent::operator+=(const std::pair<int, int> &rhs)
{
	this->points.push_back(rhs);
	return *this;
}
