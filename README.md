# Image-Processing
CSC3022F Assignment 3 - Image processing with connected components

This project is an image processor implemented in C++ which can do the following:

* Read in an input PGM file
* Color code the background/foreground pixelgroups
* extract foreground pixels groups into `ConnectedComponent` objects
* Print out information on about the components
* Print out the color coded input image

## Usage
`$ findcomp.out [options] <inputPGMfile>`

`<inputPGMfile>` is a valid PGM image

`-s <int> <int>` (-s min max) set the minimum and maximum valid components size
[min default = 3, max = image width*img height i.e. unlimited]

`-t <int>` set the threshold for component detection (default=128, limit to [0. . . 255])

`-p` print out all the component data as well as the total
component number and the sizes of the smallest and largest components.

`-b` print out all the component data (including the number of boundary pixels) as well as the total
component number and the sizes of the smallest and largest components.

`-w <outPGMfile>` write out all retained components (as foreground/background pixels) to a new PGM file, `<outPGMfile>`


## Files
Files used in the implementation

### 1. driver.cpp
This contains our main function. It handles input/output from the user

### 2. driver_test.cpp
This contains the test used for driver.cpp.
#### 2.1. catch.hpp
This contains the catch2 framework used by driver_test

### 3. connectedComponent.h
This file is the header file used for `ConnectedComponent` class declarations

### 4. connectedComponent.cpp
This file contains class implementations for the `ConnectedComponent` class declarations in the header file

### 5. imageProcessor.cpp
This file is the header file used for `imageProcessor` class declarations

### 6. imageProcessor.cpp
This file contains class implementations for the `imageProcessor` class declarations in the header file.






### Component Extraction

A `PGMimageProcessor` class object 'a' is constructed. It takes in the name of a PGM file as its parameter.

When `a.extractComponents(threshold, minSize)` is called, the input file is converted into a (foreground/background) image, with pixels with intensity higher than the threshold being whited out and those lower than the threshold intensity being blacked out. This image is saved on the stack. Each foreground component is then extracted as a `ConnectedComponent` object created dynamically and handled by a smart pointer. After extraction, the object is saved in a multiset if it is bigger or equal to the minSize. If it is not, it will be discarded

`filterComponentsBySize(int minSize, int maxSize)` will get all the smart pointers of objects not in the filter range, get 1 of its coordinate points, and use that point to flood_fill that component in the processed image saved in memory. Afterwards, the object is removed from the multiset

`writeComponents(const std::string & outFileName)` will write out all the data in the processed image that is in memory, out to a file and name it the parameter in the `outFileName` field

`calcBoundaries(const std::vector< std::pair<int,int> > & points)` calculates how many points in the vector are boundary points. It call on the `isBoundary(const std::pair<int,int> & point)` function on each point and uses an algorithm similar to flood fill to get if the given point is a boundary point.