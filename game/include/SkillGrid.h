#pragma once

#include "game/Database.h"
#include "game/GridNode.h"

#include <vector>

class SkillGrid {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// SkillGrid ctor
	// rows - Number of rows to create the SkillGrid with
	// columns - Number of columns to create the SkillGrid with
	SkillGrid(int rows, int columns);

	// SkillGrid dtor. This will clean up all the GridNodes stored
	~SkillGrid();

	// Methods /////////////////////////////////////////////////////////////////
	
	// Get a GridNode at a specific place in the SkillGrid
	// row - Row of the GridNode to get. This is 0 indexed
	// colum - Column of the GridNoe to get. This is 0 indexed
	// returns: The GridNode at the specific position, or a default GridNode if
	//		no GridNode is stored at that position
	const GridNode& getNode(int row, int column) const;

	// Check if a GridNode is at a specific position in the SkillGrid
	// row - Row of the GridNode to get. This is 0 indexed
	// colum - Column of the GridNoe to get. This is 0 indexed
	// returns: If the SkillGrid has a GridNode at the position (row, column).
	//		A GridNode is not there if it is the default GridNode, having the
	//		name of "DEFAULT". If either row or column is out of bounds this
	//		will return false
	bool contains(int row, int column) const;

	// Get how many GridNodes are in the SkillGrid. This will iterate thru each
	//		GridNode in _nodes to check if its the _defaultNode
	// returns: How many GridNodes are in the SkillGrid
	unsigned int nodeCount() const;

	// Get how many rows are in the SkillGrid
	// returns: _rows
	inline int getRows() const { return _rows; }

	// Get how many columns are in the SkillGrid
	// returns: _columns
	inline int getColumns() const { return _columns; }

	// Static vars /////////////////////////////////////////////////////////////
	
	// Pointers to all the GridNodes that have been loaded. This Database is
	// only populated after all GridNodes have been loaded, and before this it
	// will be empty. This is used in GridNode::finalize() for GridNode parent
	// pointer lookup
	static Database<GridNode*> GridNodes;

	// Static methods //////////////////////////////////////////////////////////

	// Load all GridNode from a specific directory. The directory will go
	//		through each file in it, and try to load all entries from that file
	//		into the GridNodes database. Any invalid entry or file will silently
	//		be ignored
	// dir - Directory to load all the files from. This is relative to the
	//		current working directory of the program
	static void loadGridNodes(const std::string& dir);

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	int _rows; // Number of rows in the SkillGrid
	int _columns; // Number of columns in the SkillGrid

	// Vector of GridNodes that make up the SkillGrid. The first index will
	// be the row, and the second index will be the column
	std::vector<std::vector<GridNode>> _nodes;

	// Default GridNode used in getNode() if the (row, column) is out of bounds
	GridNode _defaultNode;
};
