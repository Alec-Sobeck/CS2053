#ifndef MATH_OCTREE_H
#define MATH_OCTREE_H


#include <iostream>
#include <vector>
#include <set>
#include "physics/aabb.h"
#include "math/ioctreeelement.h"

/**
 * An implementation of Octrees built using AABBs.
 * Any kind of data which has an associated AABB may be stored in this Octree as it stores identifiers for the AABB
 * (based of the total elements passed at creation), and not the AABBs themselves.
 * Rather WIP, may need refining, definitely needs testing. Currently provides methods to build the Tree itself, and to insert an element.
 * @param T the Type of the Object being stored in this Octree. It must implement IOctreeElement.
 */
template<class T>
class Octree
{
private:
    std::set<T> elements;
	std::vector<Octree<T>> children;
	// Whether or not the node is external
	bool isLeaf;
	AABB boundary;
	/**
	 * Creates an Octree with no elements
	 * @param bounds - the bounding box for the tree
	 */
	Octree(AABB bounds, int depth) : elements(std::set<T>()), isLeaf(true), boundary(bounds), CURRENT_DEPTH(depth)
    {
    }

	/**
	 * Fills the children array by splitting the current AABB into 8 chunks based off the midpoint
	 */
	void buildChildren()
    {
        if (this->isLeaf)
        {
            children.push_back(Octree<T>(AABB(this->boundary.getXMin(), this->boundary.getYMin(), this->boundary.getZMin(),
                                        this->boundary.getXCenter(),this->boundary.getYCenter(), this->boundary.getZCenter()),
                                        1 + this->CURRENT_DEPTH));
            children.push_back(Octree<T>(AABB(this->boundary.getXCenter(), this->boundary.getYMin(), this->boundary.getZMin(),
                                        this->boundary.getXMax(),this->boundary.getYCenter(), this->boundary.getZCenter()),
                                        1 + this->CURRENT_DEPTH));
            children.push_back(Octree<T>(AABB(this->boundary.getXMin(), this->boundary.getYCenter(), this->boundary.getZMin(),
                                        this->boundary.getXCenter(),this->boundary.getYMax(), this->boundary.getZCenter()),
                                        1 + this->CURRENT_DEPTH));
            children.push_back(Octree<T>(AABB(this->boundary.getXCenter(), this->boundary.getYCenter(), this->boundary.getZMin(),
                                        this->boundary.getXMax(),this->boundary.getYMax(), this->boundary.getZCenter()),
                                        1 + this->CURRENT_DEPTH));
            children.push_back(Octree<T>(AABB(this->boundary.getXMin(), this->boundary.getYMin(), this->boundary.getZCenter(),
                                        this->boundary.getXCenter(),this->boundary.getYCenter(), this->boundary.getZMax()),
                                        1 + this->CURRENT_DEPTH));
            children.push_back(Octree<T>(AABB(this->boundary.getXCenter(), this->boundary.getYMin(), this->boundary.getZCenter(),
                                        this->boundary.getXMax(),this->boundary.getYCenter(), this->boundary.getZMax()),
                                        1 + this->CURRENT_DEPTH));
            children.push_back(Octree<T>(AABB(this->boundary.getXMin(), this->boundary.getYCenter(), this->boundary.getZCenter(),
                                        this->boundary.getXCenter(),this->boundary.getYMax(), this->boundary.getZMax()),
                                        1 + this->CURRENT_DEPTH));
            children.push_back(Octree<T>(AABB(this->boundary.getXCenter(), this->boundary.getYCenter(), this->boundary.getZCenter(),
                                        this->boundary.getXMax(),this->boundary.getYMax(), this->boundary.getZMax()),
                                        1 + this->CURRENT_DEPTH));
            this->isLeaf = false;
        }
        else
        {
            std::cout << "node already has children." << std::endl;
        }
    }

public:
	// maximum number of elements in the node
	const int OT_NODE_CAPACITY = 8;
	const int MAX_DEPTH = 10;
    int CURRENT_DEPTH = 0;
	/**
	 * Creates an Octree and fills it with elements
	 * @param bounds - the bounding box for the tree
	 * @param elements - the elements to attempt to place inside the tree
	 */
	Octree(AABB bounds, std::vector<T> elements, int depth)
        : elements(std::set<T>()), isLeaf(true), boundary(bounds), CURRENT_DEPTH(depth)
    {
        //Adds all the initial elements to the tree. This is no longer a method as that makes it prone to bugs.
        for(auto e : elements)
        {
            insertElement(e);
        }
    }

	/**
	 * Given an AABB, returns a list of indices which share a cell with the AABB
	 * @param range - the AABB we want to get the objects near (share a cell)
	 * @return the list of indices for objects contained in the range, null if the range and the Octree boundary do not overlap
	 */
    std::set<T> getRange(AABB range)
    {
        if (range.overlaps(this->boundary))
        {
            if (isLeaf)
            {
                return this->elements;
            }
            else
            {
                std::set<T> elements;
                for (int i = 0; i < 8; i++)
                {
                    elements.addAll(this->children.get(i).getRange(range));
                }
                return elements;
            }
        }
        else
        {
            return std::set<T>();
        }
    }

	/**
	 * Inserts an element into the appropriate branch of the tree, splitting if needed
	 * @param allElements - all of the elements attempted to be placed in the tree
	 * @param element - the specific element to add
	 * @param elementID - the ID of the element to add
	 */
	void insertElement(T element)
    {
        if (isLeaf)
        {
            if (element.getAABB().overlaps(this->boundary))
            {
                elements.insert(element);
                if (elements.size() > OT_NODE_CAPACITY && this->CURRENT_DEPTH < MAX_DEPTH)
                {
                    buildChildren();
                    for(T insertEle : this->elements)
                    {
                        for (int j = 0; j < 8; j++)
                        {
                            children.at(j).insertElement(insertEle);
                        }
                    }
                    elements.clear();
                }
            }
        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                children.at(i).insertElement(element);
            }
        }
    }

	AABB getAABB()
    {
        return boundary;
    }

};




#endif
