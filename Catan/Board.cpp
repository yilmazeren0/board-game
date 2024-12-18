#include "Board.h"
#include <iostream>
Board::Board(sf::RenderWindow* window) : window{window}, currentPlayerID{0}
{
	initBoard();
}

Board::~Board()
{
}

void Board::update(int currentPlayerID)
{
	
	if (currentPlayerID != this->currentPlayerID) {
		
		updateEdgeHighlights(currentPlayerID);
		updateVertexHighlights(currentPlayerID);
		this->currentPlayerID = currentPlayerID;
	}


	updateMousePosition();

	for (auto& hex : hexes) {
		hex.update();
	}
	
	for (std::size_t i = 0; i < edges.size(); i++) {

		if(edges[i].getAvailability() && placingRoad){

			if (setupPhase) {

				edges[i].setHighlight(true);
			}
			else{
				if (highlightedEdges.count(static_cast<int>(i)) > 0) {
					edges[i].setHighlight(true);
				}
				else {
					edges[i].setHighlight(false);
				}
			}
		}
		else {
			edges[i].setHighlight(false);
		}
		edges[i].update(mousePosition);
	}
	
	for (std::size_t i = 0; i < vertices.size(); i++) {

		if (vertices[i].getAvailability() && placingSettlement) {
		
			if (highlightedVertices.count(static_cast<int>(i)) > 0) {
				vertices[i].setHighlight(true);
			}
			else {
				vertices[i].setHighlight(false);
			}
			
		}
		else {
			vertices[i].setHighlight(false);
		}
		
		vertices[i].update(mousePosition);
	}
}

void Board::draw()
{
	for (auto& hex : hexes) {
		hex.draw();
	}
	for (auto& edge : edges) {
		edge.draw();
	}
	for (auto& vertex : vertices) {
		vertex.draw();
	}
}

bool Board::placeRoad(Player* player, sf::Vector2f clickPosition)
{

	for (auto& edge : edges) {
		if (edge.getAvailability() && edge.isHightlighted() && edge.getBox().contains(clickPosition)) {
			roads.emplace_back(player, player->getColor());
			edge.placeRoad(&(roads.back()));
			updateEdgeHighlights(currentPlayerID);
			updateVertexHighlights(currentPlayerID);
			return true;
		}
	}
	
	return false;
}

bool Board::placeSettlement(Player* player, sf::Vector2f clickPosition)
{

	for (std::size_t i = 0; i < vertices.size(); i++) {
		if (vertices[i].getAvailability() && vertices[i].isHightlighted() && vertices[i].getBox().contains(clickPosition)) {
			settlements.emplace_back(player, player->getColor());
			vertices[i].placeSettlement(&(settlements.back()));

			for (int neighbor : vertexNeighbours[i]) {
				int neighborIndex = neighbor - 1;
				if (neighborIndex >= 0 && neighborIndex < vertices.size()) {
					vertices[neighborIndex].setAvailability(false);
				}
			}

			updateEdgeHighlights(currentPlayerID);
			updateVertexHighlights(currentPlayerID);

			return true;
		}
	}
	return false;
}

void Board::setSetupPhase(bool setupPhase)
{
	this->setupPhase = setupPhase;
}

void Board::setplacingRoad(bool placingRoad)
{
	this->placingRoad = placingRoad;
}

void Board::setplacingSettlement(bool placingSettlement)
{
	this->placingSettlement = placingSettlement;
}

void Board::initBoard()
{
	setupPhase = false;
	placingRoad = false;
	placingSettlement = false;
	vertices.reserve(54);
	for (int i = 0; i < 54; i++) {
		vertices.emplace_back(window, i);
	}
	hexes.reserve(19);
	for (int i = 0; i < 19; i++) {
		hexes.emplace_back(window, hexAndOwnedVertices[i], i);
	}
	edges.reserve(72);
	for (int i = 0; i < 72; i++) {
		edges.emplace_back(window, edgeAndOwnedVertices[i], i);
	}
	
}

void Board::updateMousePosition() {
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
	mousePosition = window->mapPixelToCoords(pixelPos);
}

void Board::updateEdgeHighlights(int currentPlayerID)
{
	highlightedEdges.clear();

	for (std::size_t i = 0; i < edges.size(); i++) {
		if (edges[i].isOwnedByPlayer(currentPlayerID)) 
		{
			const std::vector<int>& neighbors = edgeNeighbours[i];
			
			for (int neighborIndex : neighbors) {
				if (edges[neighborIndex - 1].getAvailability()) {
					highlightedEdges.insert(neighborIndex - 1);
				}
			}
		}
	}
	
}

void Board::updateVertexHighlights(int currentPlayerID)
{	
	highlightedVertices.clear();
	for (std::size_t i = 0; i < edges.size(); i++) {
		if (edges[i].isOwnedByPlayer(currentPlayerID)) {
			const std::array<int, 2>& ownedVertices = edges[i].getOwnedVertices();

			for (int ownedVertex : ownedVertices) {
				if (vertices[ownedVertex - 1].getAvailability()) {
					highlightedVertices.insert(ownedVertex - 1);
				}
			}
		}
	}
}



const std::array<std::array<int, 6>, 19> Board::hexAndOwnedVertices = {{
	{1, 2, 3, 9, 10, 11},		//hex1
	{3, 4, 5, 11, 12, 13},		//hex2
	{5, 6, 7, 13, 14, 15},		//hex3
	{8, 9, 10, 18, 19, 20},		//hex4
	{10, 11, 12, 20, 21, 22},	//hex5
	{12, 13, 14, 22, 23, 24},	//hex6
	{14, 15, 16, 24, 25, 26},	//hex7
	{17, 18, 19, 28, 29, 30},	//hex8
	{19, 20, 21, 30, 31, 32},	//hex9
	{21, 22, 23, 32, 33, 34},	//hex10
	{23, 24, 25, 34, 35, 36},	//hex11
	{25, 26, 27, 36, 37, 38},	//hex12
	{29, 30, 31, 39, 40, 41},	//hex13
	{31, 32, 33, 41, 42, 43},	//hex14
	{33, 34, 35, 43, 44, 45},	//hex15
	{35, 36, 37, 45, 46, 47},	//hex16
	{40, 41, 42, 48, 49, 50},	//hex17
	{42, 43, 44, 50, 51, 52},	//hex18
	{44, 45, 46, 52, 53, 54},	//hex19
}};

const std::array<std::array<int, 2>, 72> Board::edgeAndOwnedVertices = { {
	//1
	{1, 9},		//edge1
	{1, 2},		//edge2
	{2, 3},		//edge3
	{3, 11},	//edge4
	{10, 11},	//edge5
	{9, 10},	//edge6
	//2
	{3, 4},		//edge7
	{4, 5},		//edge8
	{5, 13},	//edge9
	{12, 13},	//edge10
	{11, 12},	//edge11
	//3
	{5, 6},		//edge12
	{6, 7},		//edge13
	{7, 15},	//edge14
	{14, 15},	//edge15
	{13, 14},	//edge16
	//4
	{8, 18},	//edge17
	{8, 9},		//edge18
	{10, 20},	//edge19
	{19, 20},	//edge20
	{18, 19},	//edge21
	//5
	{12, 22},	//edge22
	{21, 22},	//edge23
	{20, 21},	//edge24
	//6
	{14, 24},	//edge25
	{23, 24},	//edge26
	{22, 23},	//edge27
	//7
	{15, 16},	//edge28 
	{16, 26},	//edge29 
	{25, 26},	//edge30
	{24, 25},	//edge31 
	//8
	{17, 28},	//edge32 
	{17, 18},	//edge33 
	{19, 30},	//edge34
	{29, 30},	//edge35
	{28, 29},	//edge36
	//9
	{21, 32},	//edge37 
	{31, 32},	//edge38
	{30, 31},	//edge39
	//10
	{23, 34},	//edge40
	{33, 34},	//edge41
	{32, 33},	//edge42
	//11
	{25, 36},	//edge43
	{35, 36},	//edge44
	{34, 35},	//edge45
	//12
	{26, 27},	//edge46 
	{27, 38},	//edge47 
	{37, 38},	//edge48 
	{36, 37},	//edge49 
	//13
	{29, 39},	//edge50 
	{31, 41},	//edge51 
	{40, 41},	//edge52 
	{39, 40},	//edge53 
	//14
	{33, 43},	//edge54 
	{42, 43},	//edge55 
	{41, 42},	//edge56 
	//15
	{35, 45},	//edge57  
	{44, 45},	//edge58 
	{43, 44},	//edge59
	//16
	{37, 47},	//edge60  
	{46, 47},	//edge61 
	{45, 46},	//edge62 
	//17
	{40, 48},	//edge63 
	{42, 50},	//edge64 
	{49, 50},	//edge65 
	{48, 49},	//edge66 
	//18
	{44, 52},	//edge67 
	{51, 52},	//edge68 
	{50, 51},	//edge69 
	//19
	{46, 54},	//edge70 
	{53, 54},	//edge71 
	{52, 53},	//edge72
} };

const std::array<std::vector<int>, 54> Board::vertexNeighbours = { {
	{2, 9},			//vertex1
	{1, 3},			//vertex2
	{2, 4, 11},		//vertex3
	{3, 5},			//vertex4
	{4, 6, 13},		//vertex5
	{5, 7},			//vertex6
	{6, 15},		//vertex7
	{9, 18},		//vertex8
	{1, 8, 10},		//vertex9
	{9, 11, 20},	//vertex10
	{3, 10, 12},	//vertex11
	{11, 13, 22},	//vertex12
	{5, 12, 14},	//vertex13
	{13, 15, 24},	//vertex14
	{7, 14, 16},	//vertex15
	{15, 26},		//vertex16
	{18, 28},		//vertex17
	{8, 17, 19},	//vertex18
	{18, 20, 30},	//vertex19
	{10, 19, 21},	//vertex20
	{20, 22, 32},	//vertex21
	{12, 21, 23},	//vertex22
	{22, 24, 34},	//vertex23
	{14, 23, 25},	//vertex24
	{24, 26, 36},	//vertex25
	{16, 25, 27},	//vertex26
	{26, 38},		//vertex27
	{17, 29},		//vertex28
	{28, 30, 39},	//vertex29
	{19, 29, 31},	//vertex30
	{30, 32, 41},	//vertex31
	{21, 31, 33},	//vertex32
	{32, 34, 43},	//vertex33
	{23, 33, 35},	//vertex34
	{34, 36, 45},	//vertex35
	{25, 35, 37},	//vertex36
	{36, 38, 47},	//vertex37
	{27, 37},		//vertex38
	{29, 40},		//vertex39
	{39, 41, 48},	//vertex40
	{31, 40, 42},	//vertex41
	{41, 43, 50},	//vertex42
	{33, 42, 44},	//vertex43
	{43, 45, 52},	//vertex44
	{35, 44, 46},	//vertex45
	{45, 47, 54},	//vertex46
	{37, 46},		//vertex47
	{40, 49},		//vertex48
	{48, 50},		//vertex49
	{42, 49, 51},	//vertex50
	{50, 52},		//vertex51
	{44, 51, 53},	//vertex52
	{52, 54},		//vertex53
	{46, 53},		//vertex54
} };
//1 to 7
//8 to 16
//17 to 27
//28 to 38
//39 to 47
//48 to 54


const std::array<std::vector<int>, 72> Board::edgeNeighbours = { {
	{2, 6, 18},			//edge1
	{1, 3},				//edge2
	{2, 4, 7},			//edge3
	{3, 5, 7, 11},		//edge4
	{4, 6, 11, 19},		//edge5
	{1, 5, 18, 19},		//edge6
	{3, 4, 8},			//edge7
	{7, 9, 12},			//edge8
	{8, 10, 12, 16},	//edge9
	{9, 11, 16, 22},	//edge10
	{4, 5, 10, 22},		//edge11
	{8, 9, 13},			//edge12
	{12, 14},			//edge13
	{13, 15, 28},		//edge14
	{14, 16, 25, 28},	//edge15
	{9, 10, 15, 25},	//edge16
	{18, 21, 33},		//edge17
	{1, 6, 17},			//edge18
	{5, 6, 20, 24},		//edge19
	{19, 21, 24, 34},	//edge20
	{17, 20, 33, 34},	//edge21
	{10, 11, 23, 27},	//edge22
	{22, 24, 27, 37},	//edge23
	{19, 20, 23, 37},	//edge24
	{15, 16, 26, 31},	//edge25
	{25, 27, 31, 40},	//edge26
	{22, 23, 26, 40},	//edge27
	{14, 15, 29},		//edge28
	{28, 30, 46},		//edge29
	{29, 31, 43, 46},	//edge30
	{25, 26, 30, 43},	//edge31
	{33, 36},			//edge32
	{17, 21, 32},		//edge33
	{20, 21, 35, 39},	//edge34
	{34, 36, 39, 50},	//edge35
	{32, 35, 50},		//edge36
	{23, 24, 38, 42},	//edge37
	{37, 39, 42, 51},	//edge38
	{34, 35, 38, 51},	//edge39
	{26, 27, 41, 45},	//edge40
	{40, 42, 45, 54},	//edge41
	{37, 38, 41, 54},	//edge42
	{30, 31, 44, 49},	//edge43
	{43, 45, 49, 57},	//edge44
	{40, 41, 44, 57},	//edge45
	{29, 30, 47},		//edge46
	{46, 48},			//edge47
	{47, 49, 60},		//edge48
	{43, 44, 48, 60},	//edge49
	{35, 36, 53},		//edge50
	{38, 39, 52, 56},	//edge51
	{51, 53, 56, 63},	//edge52
	{50, 52, 63},		//edge53
	{41, 42, 55, 59},	//edge54
	{54, 56, 59, 64},	//edge55
	{51, 52, 55, 64},	//edge56
	{44, 45, 58, 62},	//edge57
	{57, 59, 62, 67},	//edge58
	{54, 55, 58, 67},	//edge59
	{48, 49, 61},		//edge60
	{60, 62, 70},		//edge61
	{57, 58, 61, 70},	//edge62
	{52, 53, 66},		//edge63
	{55, 56, 65, 69},	//edge64
	{64, 66, 69},		//edge65
	{63, 65},			//edge66
	{58, 59, 68, 72},	//edge67
	{67, 69, 72},		//edge68
	{64, 65, 68},		//edge69
	{61, 62, 71},		//edge70
	{70, 72},			//edge71
	{67, 68, 71},		//edge72
} };