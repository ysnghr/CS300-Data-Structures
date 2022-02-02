#include "BVHTree.h"

// Constructor
BVHTree::BVHTree() {
	root = NULL;
}

// Deconstructor
BVHTree::~BVHTree() {
	DestroyRecursive(root);
}

void BVHTree::DestroyRecursive(BVHTreeNode* node) {
	if (node)
	{
		DestroyRecursive(node->leftChild);
		DestroyRecursive(node->rightChild);
		delete node;
	}
}

// Find the node from hasmap and 
// check the new location is in parent of actual node
bool BVHTree::checkLocationHasChanged(AABB oldLocation, AABB newLocation) {
	AABB totalFrame = newLocation + oldLocation;
	if (totalFrame.getArea() - oldLocation.getArea() == 0) {
		return true;
	}
	return false;
}


// Move node from Tree
void BVHTree::moveBVHMember(std::string name, AABB newLocation) {
	if (map.find(name) != map.end()) {
		BVHTreeNode* node = map[name];
		if (this->checkLocationHasChanged(node->parent->aabb, newLocation)) {
			node->aabb = newLocation;
		}
		else {
			removeBVHMember(name);
			addBVHMember(newLocation, name);
		}
	}
}

// Remove node from tree
void BVHTree::removeBVHMember(std::string name) {
	if (map.find(name) != map.end())
	{
		BVHTreeNode* deletedNode = map[name];
		// remove from hashmap
		map.erase(name);

		// if it is root note then just delete the root node
		if (deletedNode == root) {
			delete deletedNode;
			return;
		}

		BVHTreeNode* parentBranch = deletedNode->parent;
		// other child of parent of deleted node
		BVHTreeNode* siblingNode = BVHTreeNode::getSiblingOfNode(parentBranch, deletedNode);

		// if the parent is null then just make the node root
		if (parentBranch->parent == NULL)
		{
			root = siblingNode;
			root->parent = NULL;
			delete deletedNode;
			delete parentBranch;
			return;
		}

		if (parentBranch->parent->leftChild == parentBranch) {
			parentBranch->parent->leftChild = siblingNode;
		} else {
			parentBranch->parent->rightChild = siblingNode;
		}

		siblingNode->parent = parentBranch->parent;
		parentBranch = siblingNode;
		delete deletedNode;

		// updating upper nodes
		updateUpperBranchesOfLeaf(siblingNode->parent);
	}
}


// recursively checks the collided objects
void BVHTree::recursivelyVisitNode(BVHTreeNode* node, std::vector<std::string>& collidedObjects, AABB& object) {
	if (node->aabb.collide(object))
	{
		if (node->leftChild != NULL) {
			recursivelyVisitNode(node->leftChild, collidedObjects, object);
		}
		if (node->rightChild != NULL) {
			recursivelyVisitNode(node->rightChild, collidedObjects, object);
		}
		if (node->leftChild == NULL && node->rightChild == NULL) {
			collidedObjects.push_back(node->name);
		}
	}
}

// Update AABB value of upper branches of leaf node
void BVHTree::updateUpperBranchesOfLeaf(BVHTreeNode* parentOfLeaf) {
	while (parentOfLeaf != NULL) {
		parentOfLeaf->aabb = parentOfLeaf->rightChild->aabb + parentOfLeaf->leftChild->aabb;
		parentOfLeaf = parentOfLeaf->parent;
	}
}



std::vector<std::string> BVHTree::getCollidingObjects(AABB object) {
	std::vector<std::string> collidingObjects;
	BVHTreeNode* leafNode = root;
	recursivelyVisitNode(root, collidingObjects, object);
	return collidingObjects;
}

void BVHTree::addBVHMember(AABB objectArea, std::string name) {
	// if there are not any node in tree
	if (root == NULL) {
		root = new BVHTreeNode(objectArea, name, true);
		map[name] = root;
	}
	// there is only the root
	else if (!root->hasChild()) {
		BVHTreeNode* newNode = new BVHTreeNode(objectArea, name, true);
		map[name] = newNode;
		BVHTreeNode::addBranchNode(newNode, root);
	}
	// more than one node in the tree
	else {
		BVHTreeNode* newNode = new BVHTreeNode(objectArea, name, true);
		map[name] = newNode;
		BVHTreeNode* existingLeaf = root;
		BVHTreeNode* togetherBranch = new BVHTreeNode(newNode->aabb + existingLeaf->aabb, "branch", false);

		togetherBranch->leftChild = newNode; 
		newNode->parent = togetherBranch;
		bool isLeft = BVHTreeNode::findDirectionOfExistingLeaf(newNode, existingLeaf);
		togetherBranch->rightChild = existingLeaf;
		togetherBranch->parent = existingLeaf->parent;
		if (isLeft) {
			existingLeaf->parent->leftChild = togetherBranch;
		} else {
			existingLeaf->parent->rightChild = togetherBranch;
		}

		existingLeaf->parent = togetherBranch;
		updateUpperBranchesOfLeaf(existingLeaf->parent);
	}
}

void BVHTree::printNode(std::ostream &out, BVHTreeNode *node, int level) {
	if (root == nullptr) return;
	for (int i = 0; i < level; i++) {
		out << "  ";
	}
	if (!node->isLeaf) {
		out << "+ branch || ";
		node->aabb.printAABB(out);
		out << std::endl;
		printNode(out, node->rightChild, level + 1);
		printNode(out, node->leftChild, level + 1);
	}
	else {
		out << "- ";
		if (node->parent) {
			if (node->parent->rightChild == node)
				out << "R ";
			else
				out << "L ";
		}
		out << "- leaf: " << node->name << " || ";
		node->aabb.printAABB(out);
		out << std::endl;
	}
}
std::ostream &operator<<(std::ostream &out, BVHTree &tree) {
	tree.printNode(out, tree.root, 0);
	return out;
}