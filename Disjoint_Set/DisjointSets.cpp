//MAIN implementation file.

#include "assert.h"
#include "DisjointSets.h"

DisjointSets::DisjointSets() {
	m_numElements = 0;
	m_numSets = 0;
}

DisjointSets::DisjointSets(int count) {
	m_numElements = 0;
	m_numSets = 0;
	AddElements(count);
}

/*copy ctor. */
DisjointSets::DisjointSets(const DisjointSets &s) {
	this->m_numElements = s.m_numElements;
	this->m_numSets = s.m_numSets;

	/*Copy nodes. First resize the vector to the re-assigned m_numElements.  Then iterate, while
	copying the supplied DisjointSet to the newly resized vector.*/
	m_nodes.resize(m_numElements);
	for(int i = 0; i < m_numElements; ++i) {
		m_nodes[i] = new Node(*s.m_nodes[i]);
	}

	/*Update pointers to point to the newly copied nodes, rather than the old ones.*/
	for(int i = 0; i < m_numElements; ++i) {
		//ALWAYS check for NULL BEFORE assignment to avoid memory access errors.
		if(m_nodes[i]->parent != NULL) {
			m_nodes[i]->parent = m_nodes[s.m_nodes[i]->parent->index];
		}
	}

}

/*Destructor*/
DisjointSets::~DisjointSets() {
	for(int i = 0; i < m_numElements; ++i) {
		delete m_nodes[i];
	}

	m_nodes.clear();
	m_numElements = 0;
	m_numSets = 0;
}

int DisjointSets::FindSet(int elementId) const {

	assert(elementId < m_numElements);

	Node *currNode;	//facilitates traversal and path compression

	currNode = m_nodes[elementId];
	
	//traverse "up" to the root node.
	while(currNode->parent != NULL) {
		currNode = currNode->parent;
	}

	//"root->index" will be returned to the calling program.  This is the "set name" we are searching for.
	Node *root = currNode;

	/*Path Compression.
	Walk to the root, updating the parent's of 'elementId'.  Make the elements the direct children
	of 'root'.  This optimizes the tree for future FindSet operations.*/
	currNode = m_nodes[elementId];
	while(currNode != root) {
		//basic swap procedure while traversing upwards
		Node *next = currNode->parent;	//our "temp" variable
		currNode->parent = root;	//point the current parent node to the root
		currNode = next;	//currNode now points to the parent node.  rinse and repeat until while is invalidated.
	}

	//return the name (index) of the set that the 'elementId' belongs to
	return root->index;
}

void DisjointSets::Union(int setId1, int setId2) {

	assert(setId1 < m_numElements);
	assert(setId2 < m_numElements);

	//check if already unioned
	if(setId1 == setId2) {
		return;
	}

	//create Node variables in order to directly access the sets and their attributes from the m_nodes vector array.
	Node* set1 = m_nodes[setId1];
	Node* set2 = m_nodes[setId2];

	/*Determine which node representing a set has a higher rank.  The node with the higher rank is likely
	to have a bigger subtree.  So in order to better balance the tree representing the union, the node with the
	higher rank is made the parent of the one with the lower rank and not the other way around.*/
	if(set1->rank > set2->rank) {
		set2->parent = set1;
		++set1->rank;
	}
	else if(set1->rank < set2->rank) {
		set1->parent = set2;
		++set2->rank;
	}
	else {
		//set1->rank == set2->rank
		set2->parent = set1;
		//update rank
		++set1->rank;
	}

	/*Since the two sets have fused into one, there is now one less set.  Therefore, we
	update (in this case: decrement) the set count.*/
	--m_numSets;
}

//AddElements
void DisjointSets::AddElements(int numToAdd) {

	assert(numToAdd >= 0);

	/*Insert (at the end of the vector) and initialize (to NULL) the specified number
	of element nodes to the end of the m_nodes array.*/
	m_nodes.insert(m_nodes.end(), numToAdd, (Node*)NULL);

	for(int i = m_numElements; i < m_numElements + numToAdd; ++i) {
		//create the new nodes, initialize their parents, index, and rank.
		m_nodes[i] = new Node();
		m_nodes[i]->parent = NULL;
		m_nodes[i]->index = i;
		m_nodes[i]->rank = 0;
	}

	//update the element and set counts
	m_numElements += numToAdd;
	m_numSets += numToAdd;
}

//Return the element the count
int DisjointSets::NumElements() const {
	return m_numElements;
}

//Return the element the count
int DisjointSets::NumSets() const {
	return m_numSets;
}