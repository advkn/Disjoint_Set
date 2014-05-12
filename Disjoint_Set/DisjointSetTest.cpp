#include <iostream>
#include "DisjointSets.h"

void printElementSets(const DisjointSets &s) {
	for(int i = 0; i < s.NumElements(); i++) {
		std::cout << s.FindSet(i) << " ";
	}
	std::cout << std::endl;
}

int main() {

	DisjointSets s(10);
	printElementSets(s);

	s.Union(s.FindSet(5), s.FindSet(3));
	printElementSets(s);

	s.Union(s.FindSet(2), s.FindSet(9));
	printElementSets(s);

	s.AddElements(5);
	printElementSets(s);

	s.Union(s.FindSet(0), s.FindSet(13));
	printElementSets(s);

	s.Union(s.FindSet(13), s.FindSet(4));
	printElementSets(s);

	std::cout << s.FindSet(9);
	
	//create a new empty disjoint set and copy an existing set into it.
	DisjointSets s2(s);
	std::cout << "\n\n\n";

	printElementSets(s2);
	

	getchar();
	return 0;
};