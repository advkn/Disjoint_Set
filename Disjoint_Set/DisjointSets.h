//Disjoint Set data structure
#include <vector>

class DisjointSets {

public:

	/*create an empty Disjoint Set data structure*/
	DisjointSets();

	/*Create a Disjoint Set data structure with a specified number of elments (with element id's
	from 0 to count-1).*/
	DisjointSets(int count);

	/*copy ctor*/
	DisjointSets(const DisjointSets &s);

	/*destructor*/
	~DisjointSets();

	/*Find the set identifier that an element currently belongs to.  **Note: some internal
	data is modified for optimization even though this method is constant.*/
	int FindSet(int elementId) const;

	/*Combine two sets into one.  All elements in those two sets will share
	the same id that can be retrieved by FindSet.*/
	void Union(int setId1, int setId2);

	/*Add a specified number of elements to the DisjointSets data structure.  The element id's of the new
	elements are numbered consequtively starting with the first never-before used elementId.*/
	void AddElements(int numToAdd);

	/*Returns the number of elements in the DisjointSet's data structure*/
	int NumElements() const;

	/*Returns the number of sets in the DisjointSet's data structure*/
	int NumSets() const;

private:

	/*Internal node structure used for representing an element*/
	struct Node {
		int rank;			/*roughly represents the height of a node in a tree.*/
		int index;			/*index of the element the node represents.*/
		Node* parent;		/*parent node of the node.*/
	};

	int m_numElements;		/*represents the number of elements currently in the DisjointSet data structure.*/
	int m_numSets;			/*represents the number of sets currently in the DisjointSet data structure.*/

	/*list of nodes representing the structure.*/
	std::vector<Node*> m_nodes;

};