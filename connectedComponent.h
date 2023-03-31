#ifndef _connectedComponent_h
#define _connectedComponent_h

#include <vector>

namespace MVHASA001
{

	using namespace std;
	class ConnectedComponent
	{
		private:
			char *id;
			std::vector< std::pair<int,int> > points;
		public:
			ConnectedComponent(); // default construct
			~ConnectedComponent(); // default destruct

			ConnectedComponent(const ConnectedComponent & rhs); // copy
			ConnectedComponent & operator=(const ConnectedComponent & rhs);

			ConnectedComponent(ConnectedComponent && rhs) : points(move(rhs.points)) {}; // move
			ConnectedComponent & operator=(ConnectedComponent && rhs)
			{
				if (this != &rhs)
				{
					this->points = move(rhs.points);
					return *this;
				}
			}

			ConnectedComponent & operator+=(const std::pair<int,int> & rhs);
	};
	


} // namespace MVHASA001




#endif