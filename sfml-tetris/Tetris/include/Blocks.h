#pragma once

class Blocks
{
private:

	enum class Color
	{
		Yellow, Red, Green, Purple, Orange, LightBlue, DarkBlue
	};

	enum class Shape
	{
		I, Z, S, T, L, J, O
	};

	const std::array<std::array<int, 4>, 7> blockOrderList
	{ {
		{0,2,4,6}, // I
		{2,4,5,7}, // Z
		{3,5,4,6}, // S
		{3,5,4,7}, // T
		{2,4,6,7}, // L
		{3,5,6,7}, // J
		{2,3,4,5}, // O

	} };

	sf::Texture m_tile_t;
	sf::Sprite m_tile_s;
	Color color{};
	const int PX = 32, XMAX = 9*PX, YMAX = 19*PX;
	const sf::Vector2<int> spawnPoint{ (4*PX),(-4*PX) };
	Shape shape{};
	std::array<sf::Vector2<int>, 4> blockOrder{}, prevBlockOrder{};
	std::vector<std::array<int, 3>> gridBlocks{};
	bool stop{};
	int overlap{};
	float speed{ 3 };

public:
	Blocks();
	void draw(sf::RenderWindow& window);
	void fall(sf::Time time, sf::Clock& clock);
	void move(sf::Vector2<int> dir);
	void rotate();

private:
	void spawn();
	bool OutOfGridBlocks();
	void storeToGridBlocks();
	bool gridIsOccupied();
	void completedLines();
	bool gameOver();
};	