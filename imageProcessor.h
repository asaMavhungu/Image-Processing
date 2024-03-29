#ifndef _imageProcessor_h
#define _imageProcessor_h

#include "connectedComponent.h"

#include <string>
#include <iostream>
#include <set>
#include <memory>

namespace MVHASA001
{

	struct compareComponents
	{
		bool operator()(const std::shared_ptr<ConnectedComponent>& lhs, const std::shared_ptr<ConnectedComponent>& rhs) const 
		{
			return (*lhs).getSize() < (*rhs).getSize();
		}
	};

	class PGMimageProcessor
	{
		private:
			int width, height;
			char *id;
			std::string sourceName;
			std::vector<std::vector<unsigned char>> source;
			// implemted 'compareComponents' as a functor
			std::multiset<std::shared_ptr<ConnectedComponent>, compareComponents> components;
			int sourceSize = 0;
			std::string comment;

		public:

		PGMimageProcessor();// default constructor

		PGMimageProcessor(std::string srcName); // par constructor

		~PGMimageProcessor(); // destructor

		PGMimageProcessor(const PGMimageProcessor& other); // copy constructor

		PGMimageProcessor(PGMimageProcessor&& other); // move constructor

		PGMimageProcessor& operator=(PGMimageProcessor& other); // copy assignment

		PGMimageProcessor& operator=(PGMimageProcessor&& other); // move assignment

		int getSourceSize() const;

		std::string getSourceName() const;

		/* Set image filename
		*/
		void setImage(std::string filename);

		/* Read image filename and process it with a given threshold
		*/
		void readImage(std::string filename, unsigned char threshold);

		/* Use flood_fill algorithm to color a section of the image
		*/
		void floodFill( int row, int col, int target, int replacement);

		/* Calculate number of boundary pixels
		*/
		int calcBoundaries(const std::vector< std::pair<int,int> > & points);

		/* Check if pixel at co-ordinates if a boundary pixel
		*/
		bool isBoundary(const std::pair<int,int> & point) const;

		/* Add a component to the container
		*/
		void addComponent(std::shared_ptr<ConnectedComponent> comp);

		/* Get the reference of the object a smart pointer at 'index' manages.
		*/
		const ConnectedComponent & getComponent(int index) const;

		/* Get read-only access to components in the container
		*/
		const std::multiset<std::shared_ptr<ConnectedComponent>, compareComponents>& getComponents() const;

		/* process the input image to extract all the connected components,
		based on the supplied threshold (0...255) and excluding any components
		of less than the minValidSize. The final number of components that
		you store in your container (after discarding undersized one)
		must be returned.
		*/
		int extractComponents(unsigned char threshold, int minValidSize);

		/* iterate - with an iterator - though your container of connected
		components and filter out (remove) all the components which do not
		obey the size criteria pass as arguments. The number remaining
		after this operation should be returned.
		*/
		int filterComponentsBySize(int minSize, int maxSize);

		/* create a new PGM file which contains all current components
		(255=component pixel, 0 otherwise) and write this to outFileName as a
		valid PGM. the return value indicates success of operation
		*/
		bool writeComponents(const std::string & outFileName);

		// return number of components
		int getComponentCount(void) const;

		// return number of pixels in largest component
		int getLargestSize(void) const;

		// return number of pixels in smallest component
		int getSmallestSize(void) const;

		/* print the data for a component to std::cout
		see ConnectedComponent class;
		print out to std::cout: component ID, number of pixels
		*/
		void printComponentData(const ConnectedComponent & theComponent) const;

		void printAllComponentData(const ConnectedComponent & theComponent) const;
		

	};



}


#endif