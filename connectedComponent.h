#ifndef _connectedComponent_h
#define _connectedComponent_h

#include <vector>
#include <ostream>

namespace MVHASA001
{

	using namespace std;
	class ConnectedComponent
	{
		private:
			int id;
			int size = 0;
			std::vector< std::pair<int,int> > points;
		public:
			ConnectedComponent(); // default construct
			ConnectedComponent(int x);
			~ConnectedComponent(); // default destruct

			ConnectedComponent(const ConnectedComponent & rhs); // copy
			ConnectedComponent & operator=(const ConnectedComponent & rhs);

			ConnectedComponent(ConnectedComponent && rhs); // move
			ConnectedComponent & operator=(ConnectedComponent && rhs);

			ConnectedComponent & operator+=(const std::pair<int,int> & rhs);

			friend std::ostream & operator<<(std::ostream & os, const ConnectedComponent& rhs);

			std::pair<int,int> getPoint() const;

			int getSize() const;
			void setSize(int i);

			// for sorting
			bool operator<(const ConnectedComponent& other) const;

	};

} // namespace MVHASA001




#endif