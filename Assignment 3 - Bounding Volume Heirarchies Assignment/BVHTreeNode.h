#include <string>
#include "AABB.h"
#ifndef _BVH_TREE_NODE
#define _BVH_TREE_NODE

struct BVHTreeNode{
    BVHTreeNode *parent, *leftChild, *rightChild;
    AABB aabb;
    std::string name;
    bool isLeaf;
    BVHTreeNode(AABB _aabb, std::string _name, bool _isLeaf): aabb(_aabb), name(_name), isLeaf(_isLeaf){
        parent = leftChild = rightChild = 0;
    }

	// check node has child or not
    bool hasChild() {
        return (leftChild == 0 && rightChild == 0) ? false : true;
    }

	// check node has parent or not
    bool hasParent() {
        return parent == 0 ? false : true;
    }

	static bool findDirectionOfExistingLeaf(BVHTreeNode*& newNode, BVHTreeNode*& existingLeaf) {
		bool isLeft = false;
		// find the direction of the leaf
		while (!existingLeaf->isLeaf) {
			int increaseInRightTreeSize = AABB::unionArea(newNode->aabb,
				existingLeaf->rightChild->aabb) - existingLeaf->rightChild->aabb.getArea();
			int increaseInLeftTreeSize = AABB::unionArea(newNode->aabb,
				existingLeaf->leftChild->aabb) - existingLeaf->leftChild->aabb.getArea();

			if (increaseInRightTreeSize < increaseInLeftTreeSize) {
				// right child
				existingLeaf = existingLeaf->rightChild;
				isLeft = false;
			}
			else {
				// left child
				isLeft = true;
				existingLeaf = existingLeaf->leftChild;
			}
		}
		return isLeft;
	}

	// adding branch from two nodes
	static BVHTreeNode* addBranchNode(BVHTreeNode* &newNode, BVHTreeNode* &root) {
		BVHTreeNode* branchNode = new BVHTreeNode(newNode->aabb + root->aabb, "branch", false);
		branchNode->leftChild = newNode;
		newNode->parent = branchNode;
		branchNode->rightChild = root;
		root->parent = branchNode;
		root = branchNode;
		return branchNode;
	}

	// finding sibling of the node
	static BVHTreeNode* getSiblingOfNode(BVHTreeNode*& parentBranch, BVHTreeNode*& deletedNode) {
		if (parentBranch->rightChild == deletedNode) {
			return parentBranch->leftChild;
		} else {
			return parentBranch->rightChild;
		}
	}
};
#endif