#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "imageProcessor.h"
#include <iostream>
#include <cstring>

using namespace std;
using namespace MVHASA001;

TEST_CASE("Initial Parameters","Constructor") 
{
	
	SECTION("No args")
	{
		PGMimageProcessor a;
		REQUIRE(a.getSourceSize() == 0);
		// TODO width and heigh
	}

	SECTION("Args")
	{
		PGMimageProcessor a("squares.pgm");
		REQUIRE(a.getSourceName() == "squares.pgm");
		REQUIRE(a.getSourceSize() == 0);
	}
	
}

TEST_CASE("Extraction","[fileRead]") 
{
	SECTION("Default")
	{
		int minSize = 3;
		int threshold = 128;
		PGMimageProcessor a("squares.pgm");
		REQUIRE(a.extractComponents(threshold, minSize) == 1) ;
		REQUIRE(a.writeComponents("Default.pgm") == true);
		REQUIRE(a.getSourceName() == "squares.pgm");
		REQUIRE(a.getSourceSize() == 505*505);
		REQUIRE(a.getComponentCount() == 1);
		REQUIRE(a.getLargestSize() == 126*126);
		REQUIRE(a.getSmallestSize() == 126*126);
	}

	SECTION("All shapes")
	{
		int minSize = 3;
		int threshold = 1;
		PGMimageProcessor a("squares.pgm");
		REQUIRE(a.extractComponents(threshold, minSize) == 5) ;
		REQUIRE(a.writeComponents("All.pgm")== true);
		REQUIRE(a.getSourceName() == "squares.pgm");
		REQUIRE(a.getSourceSize() == 505*505);
		REQUIRE(a.getComponentCount() == 5);
		REQUIRE(a.getLargestSize() == 22801);
		REQUIRE(a.getSmallestSize() == 2601);
	}
}

TEST_CASE("Filter","[fileRead]") 
{
	SECTION("Half filter")
	{
		int minSize = 3;
		int threshold = 1;
		PGMimageProcessor a("squares.pgm");
		REQUIRE(a.extractComponents(threshold, minSize) == 5) ;
		REQUIRE(a.writeComponents("Half Filter.pgm")== true);
		REQUIRE(a.filterComponentsBySize(3000,12000));

		REQUIRE(a.getComponentCount() == 2);
		REQUIRE(a.getLargestSize() == 10201);
		REQUIRE(a.getSmallestSize() == 5776);
	}

	SECTION("All filter")
	{
		int minSize = 3;
		int threshold = 1;
		PGMimageProcessor a("squares.pgm");
		REQUIRE(a.extractComponents(threshold, minSize) == 5) ;
		REQUIRE(a.writeComponents("Half Filter.pgm")== true);
		REQUIRE(a.filterComponentsBySize(6000,6002) == 0);

		REQUIRE(a.getComponentCount() == 0);
		REQUIRE(a.getLargestSize() == 0);
		REQUIRE(a.getSmallestSize() == 0);
	}
}

TEST_CASE("Print out","[fileRead]") 
{

	int minSize = 3;
	int threshold = 1;
	PGMimageProcessor a("squares.pgm");
	REQUIRE(a.extractComponents(threshold, minSize) == 5) ;
	REQUIRE(a.writeComponents("Print All.pgm")== true);
	
	for (int i = 0; i < a.getComponentCount(); ++i)
	{
		std::ostringstream oss;
		std::ostringstream oss2;

		oss2 << "ID: " 
		<< a.getComponent(i).getID() 
		<< ", Size: " 
		<< a.getComponent(i).getSize()
		<< std::endl;


		auto coutBuffer = std::cout.rdbuf();
		std::cout.rdbuf(oss.rdbuf());

		a.printComponentData(a.getComponent(i));

		std::cout.rdbuf(coutBuffer);

		REQUIRE(oss.str() == oss2.str());

	}
		

	
}

TEST_CASE("Mastery","Boundaries") 
{
	int minSize = 3;
	int threshold = 1;
	PGMimageProcessor a("squares.pgm");
	REQUIRE(a.extractComponents(threshold, minSize) == 5) ;
	
	SECTION("size")
	{
		REQUIRE(a.getComponent(0).getSize() == 2601);
		REQUIRE(a.getComponent(1).getSize() == 5776);
		REQUIRE(a.getComponent(2).getSize() == 10201);
		REQUIRE(a.getComponent(3).getSize() == 15876);
		REQUIRE(a.getComponent(4).getSize() == 22801);
	}
	SECTION("boundary")
	{
		REQUIRE(a.getComponent(0).getBounds() == 200);
		REQUIRE(a.getComponent(1).getBounds() == 300);
		REQUIRE(a.getComponent(2).getBounds() == 400);
		REQUIRE(a.getComponent(3).getBounds() == 500);
		REQUIRE(a.getComponent(4).getBounds() == 600);
	}
	

}