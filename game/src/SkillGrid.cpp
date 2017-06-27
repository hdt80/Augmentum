#include "game/SkillGrid.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

SkillGrid::SkillGrid(int rows, int columns)
	: _rows(rows), _columns(columns) {
	
	_nodes.resize(rows);

	for (unsigned int i = 0; i < _nodes.size(); ++i) {
		_nodes[i].resize(columns);
	}
}

SkillGrid::~SkillGrid() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

const GridNode& SkillGrid::getNode(int row, int column) const {
	if (row > _rows || row < 0) {
		return _defaultNode;
	}

	if (column > _columns || row < 0) {
		return _defaultNode;
	}

	return _nodes[row][column];
}

bool SkillGrid::contains(int row, int column) const {
	const GridNode& node = getNode(row, column);

	return node == _defaultNode;
}

unsigned int SkillGrid::nodeCount() const {
	unsigned int count = 0;

	for (unsigned int i = 0; i < _rows; ++i) {
		for (unsigned int j = 0; j < _columns; ++j) {
			if (contains(i, j)) {
				++count;
			}
		}
	}

	return count;
}
