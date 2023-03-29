#ifndef _connectedComponent_h
#define _connectedComponent_h

#include <vector>

namespace MVHASA001
{

	using namespace std;
	class ConnectedComponent
	{
		private:
			vector<int> points;
		public:
			ConnectedComponent(int index); // default construct
			virtual ~ConnectedComponent() = default; // default destruct

			ConnectedComponent(const ConnectedComponent & rhs) = default; // copy
			ConnectedComponent & operator=(const ConnectedComponent & rhs) = default;

			ConnectedComponent(ConnectedComponent && rhs) : points(move(rhs.points)) {}; // move
			ConnectedComponent & operator=(ConnectedComponent && rhs)
			{
				if (this != &rhs)
				{
					this->points = move(rhs.points);
					return *this;
				}
			}
	};
	


} // namespace MVHASA001




#endif