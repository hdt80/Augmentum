#ifndef _SKILL_TREE_H
#define _SKILL_TREE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Perk.h"
#include "Vector2.h"

class SkillTree;
class Unit;

// Each Node has 2 child Nodes, each child Node requiring the parent node
// to be unlocked.
class SkillNode {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////

	// Nullary ctor
	SkillNode();

	// SkillNode ctor
	// parent - Parent SkillNode in the SkillTree
	// perk - Perk attached to this SkillNode
	SkillNode(SkillNode* parent, Perk* perk);

	// SkillNode dtor
	~SkillNode();
	
	// Methods /////////////////////////////////////////////////////////////////

	// When cloning a Node, it must also be put into a vector for the new tree
	// vec - std::vector to clone into
	// returns: A copy of the SkillNode
	SkillNode* clone(std::vector<SkillNode*>* vec);

	// Add a new child Node in the order of left then right
	// node - Node to add as our child
	// returns: If the Node was added
	bool add(SkillNode* node);

	// Print out the values of the SkillNode
	void print() const;

	// Unlocked if no parent, if parent is unlocked, and we dont have max points
	// returns: If this SkillNode is unlocked
	bool unlocked() const;

	// Get the name of the SkillNode's perk
	// returns: perk->getName
	const std::string& name() const { return perk->getName(); }

	// Set the position of this SkillNode
	// newPos - Position to set
	inline void setPos(const Vector2& newPos) { pos = newPos; }

	// Get the x coord of this SkillNode
	// returns: pos.X
	inline float getX() const { return pos.X; }

	// Get the y coord of this SKillNode
	// returns: pos.Y
	inline float getY() const { return pos.Y; }

	// Check if a point is within the bounds of the SkillNode
	// x - X coord to check
	// y - Y coord to check
	// returns: If the point (x, y) is within the bounds of the SkillNode
	bool contains(float x, float y) const;

	// Set how many points the SkillNode has. This will also update the color
	//		to draw the node as. Red means its locked and no points can be put
	//		into it. White means its unlocked and points can be put into it,
	//		but none have. Gray means its unlocked and some points are in it,
	//		while green means the SkillNode has max points
	// p - Points to set to
    void setPoints(int p);

	// Increase the amount of points that the SkillNode has by 1
    inline void incPoints() { setPoints(points + 1); }

	// Decrease the amount of points that the SkillNode has by 1
    inline void decPoints() { setPoints(points - 1); }

	// Tree this SkillNode is a part of
    SkillTree* tree;
	Unit* attached; // What object this Node is attached to

	Vector2 pos; // Position of the Node when drawing. From the center
	sf::RectangleShape box;

	int points;    // Current points in Node
	int maxPoints; // Max points in a Node
	int depth;     // Level this Node is on
	bool isLeft;   // Is to the left of the root Node

	SkillNode* nodePrereq; // Node we must have to have this perk, parent Node
	Perk* perk; // Perk attached to this Node

	// Child Nodes
	SkillNode* left;
	SkillNode* right;
};

class SkillTree : public sf::Drawable {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// SkillTree ctor
	// size - Size to draw the SkillTree as
	SkillTree(const Vector2& size = Vector2(0.0f, 0.0f));

	// SkillTree dtor
	~SkillTree();

	// Methods /////////////////////////////////////////////////////////////////

	// Print out all the SkillNodes that make up the SkillTree
	// node - Node to print
	// pos - Should printing also print out the position of each SKillNode?
	void print(SkillNode* node, bool pos = false) const;

	// Create a copy of the SkillTree
	// returns: A copy of the SkillTree
	SkillTree* clone();

	// Max depth of the tree
	// node - Node to iterator from
	// returns: The max depth of a single Node
	int maxDepth(const SkillNode* node) const;

	// Depth of the specific node
	int depth(const SkillNode* node) const;

	// Number of Nodes with that depth
	int nodesOnDepth(const SkillNode* node, int d) const;

	// Number of children (Including children of children)
	int childCount(const SkillNode* node) const;

	// Add a new Perk with a preq. Node
	// parent - Parent SkillNode
	// perk - Perk to create a SkillNode for
	// returns: Created SkillNode
	SkillNode* addPerk(SkillNode* parent, Perk* perk);

	// Set if the SkillTree is completed
	// b - Completed or not
	inline void setComp(bool b) { _comp = b; }

	// Set the head SKillNode
	// h - SkillNode to make the head
	inline void setHead(SkillNode* h) { _head = h; }

	// Set the Unit the SkillTree is attached to
	// o - Unit the SkillTree is attached to
	void setAttached(Unit* o);

	// Get the Unit the SkillTree is attached to
	// returns: _attached
	inline Unit* getAttached() const { return _attached; }

	// Set the data of the SkillTree
	// v - Vector of data to set
	inline void setData(std::vector<SkillNode*>* v) { _data = *v; }

	// We've finished creating this Tree, create the drawable arrays
	void end();

	// Set the size of the SkillTree
	// w - Width of the SkillTree
	// h - Height of the SkillNode
	inline void setSize(float w, float h) { _size.X = w; _size.Y = h; }

	// Get the width of the SkillTree
	// returns: _size.X
	inline float getWidth() const { return _size.X; }

	// Get the height of the SkillTree
	// returns: _size.Y
	inline float getHeight() const { return _size.Y; }

	// Get the Node that is at the (x, y)
	// x - X coord of the point to check
	// y - Y coord of the point to check
	// returns: The SkillNode at that point, or nullptr if no Node was found
	SkillNode* getNode(float x, float y) const;

	// Get the number of SkillNodes in the SkillTree
	// returns: _count
	inline int getCount() const { return _count; }

	// Get the head SkillNode
	// returns: _head
	inline SkillNode* getHead() const { return _head; }

	// Get the data of the SkillTree
	// returns: _data
	inline const std::vector<SkillNode*>& data() const { return _data; }

protected:
	// Methods ////////////////////////////////////////////////////////////////
	
	// Inherited from sf::Drawable
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	// Set the position of a Node and return where its drawn
	// node - Node to set and get the position of
	// returns: The position of the Node from the top-left corner in pixels.
	//		This is relative to the top-left corner of the window
	Vector2 pos(SkillNode* node);

	// Methods for creating the Arrays
	void genLines();
	void genNodes();

	// Vars ////////////////////////////////////////////////////////////////////

	sf::VertexArray _lines; // Lines between the Nodes
	sf::VertexArray _nodes; // Boxes that represent the Nodes
	Unit* _attached; // Object we're attached to

    int nodeWidth; // Width of a single Node in pixels
    int nodeHeight; // Height of a single Node in pixels

	SkillNode* _head; // Head node, root
	std::vector<SkillNode*> _data;

	int _count; // How many nodes are in the SkillTree
	bool _comp; // If the tree is done being created

	Vector2 _size; // Width and Height of the sf::Window it's being drawn to
};

namespace SkillTrees {
	extern void createTrees(Vector2 size = Vector2(0.0f, 0.0f));

	extern SkillTree* basicTree;
}

#endif
