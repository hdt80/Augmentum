#include "game/SkillGridWindow.h"

#include "game/SkillGrid.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

SkillGridWindow::SkillGridWindow(SkillGrid* grid)
	: _grid(grid) {

	generateVertexArrays();
}

SkillGridWindow::~SkillGridWindow() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void SkillGridWindow::pause() {

}

void SkillGridWindow::update(int diff) {

}

void SkillGridWindow::keyEvent(sf::Event& e) {

}

void SkillGridWindow::mouseEvent(sf::Event& e) {

}

void SkillGridWindow::render(sf::RenderWindow& window) {

}

////////////////////////////////////////////////////////////////////////////////
// Protected methods
////////////////////////////////////////////////////////////////////////////////

void SkillGridWindow::generateVertexArrays() {
	unsigned int count = _grid->nodeCount();

	_nodeLines.setPrimitiveType(sf::PrimitiveType::Quads);
	_nodeLines.resize(count * 4); // Each Node has 4 corners

	sf::Vertex* quad;
	GridNode* node;

	for (unsigned int i = 0; i < _grid->getRows(); ++i) {
		for (unsigned int j = 0; j < _grid->getColumns(); ++j) {
			if (!_grid->contains(i, j)) {
				continue;
			}

		}
	}

	//for (unsigned int i = 0; i < _data.size(); ++i) {
	//	node = _data[i];
	//	quad = &_nodes[i * 4];
	//	// Draw clockwise, top left, top right, bottom right, bottom left
	//	quad[0].position = sf::Vector2f(node->getX() - nodeWidth,
	//		node->getY() - nodeHeight);
	//	quad[1].position = sf::Vector2f(node->getX() + nodeWidth,
	//		node->getY() - nodeHeight);
	//	quad[2].position = sf::Vector2f(node->getX() + nodeWidth,
	//		node->getY() + nodeHeight);
	//	quad[3].position = sf::Vector2f(node->getX() - nodeWidth,
	//		node->getY() + nodeHeight);
	//}
}

////////////////////////////////////////////////////////////////////////////////
// Static vars
////////////////////////////////////////////////////////////////////////////////

unsigned int SkillGridWindow::WIDTH = 900;
unsigned int SkillGridWindow::HEIGHT = 720;
unsigned int SkillGridWindow::NODE_WIDTH = 40;
unsigned int SkillGridWindow::NODE_HEIGHT = 30;
