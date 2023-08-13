#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "Blocks.h"

Blocks::Blocks()
{
	m_tile_t.loadFromFile(".\\.\\.\\assets\\tiles.png");
	m_tile_s.setTexture(m_tile_t);
	spawn();
}

void Blocks::draw(sf::RenderWindow& window)
{
	if (OutOfGridBlocks() || gridIsOccupied())
	{
		blockOrder = prevBlockOrder;
		if (stop == true)
		{
			storeToGridBlocks();
			completedLines();
			if (gameOver()) gridBlocks.clear();
			spawn();
			stop = false;
		}
	}
	//draw falling block
	for (size_t i{}; i < 4; i++)
	{
		m_tile_s.setPosition(sf::Vector2f(blockOrder[i]));
		window.draw(m_tile_s);
	}

	//draw grid lines
	for (size_t i{}; i < gridBlocks.size(); i++)
	{
		Color a = static_cast<Color>(gridBlocks[i][2]);
		sf::Sprite f{ m_tile_t };
		f.setTextureRect(sf::IntRect(PX * static_cast<int>(a), 0, PX, PX));
		sf::Vector2<int> p{ gridBlocks[i][0], gridBlocks[i][1] };
		f.setPosition(sf::Vector2f(p));
		window.draw(f);
	}
}

void Blocks::fall(sf::Time time, sf::Clock& clock)
{
	if (1 / speed <= time.asSeconds())
	{
		move(sf::Vector2i(0, 1));
		clock.restart();
	}
}

void Blocks::move(sf::Vector2<int> dir)
{
	prevBlockOrder = blockOrder;

	for (size_t i{}; i < 4; i++)
	{
		blockOrder[i] += (dir * PX);
	}
}

void Blocks::rotate()
{
	prevBlockOrder = blockOrder;
	sf::Vector2i center = blockOrder[1];
	if (shape != Shape::O)
	{
		std::array<sf::Vector2<int>, 4> b = blockOrder;
		for (size_t i{}; i < 4; i++)
		{
			int a = blockOrder[i].x;
			blockOrder[i].x = center.x - (blockOrder[i].y - center.y);
			blockOrder[i].y = center.y + (a - center.x);
		}
	}

	for (size_t i = 0; i < 2; i++)
	{
		if (OutOfGridBlocks() == true || gridIsOccupied() == true)
		{
			for (int i{}; i < 4; i++)
			{
				if (overlap - center.x <= 0) blockOrder[i].x += (PX);
				else blockOrder[i].x += (-PX);
			}
		}
	}
}

void Blocks::spawn()
{
	shape = static_cast<Shape>(rand() % 7);
	color = static_cast<Color>(rand() % 7);
	m_tile_s.setTextureRect(sf::IntRect(PX * static_cast<int>(color), 0, PX, PX));

	for (size_t i{}; i < 4; i++)
	{
		blockOrder[i].x = ((blockOrderList[static_cast<int>(shape)][i] % 2) * PX) + spawnPoint.x;
		blockOrder[i].y = ((blockOrderList[static_cast<int>(shape)][i] / 2) * PX) + spawnPoint.y;
	}
}

bool Blocks::OutOfGridBlocks()
{
	for (size_t i{}; i < 4; i++)
	{
		if (blockOrder[i].x == -PX || blockOrder[i].x == XMAX + PX ||
			blockOrder[i].y == YMAX + PX)
		{
			if (blockOrder[i].y == YMAX + PX)stop = true;
			if (blockOrder[i].x == -PX) overlap = -PX;
			else if (blockOrder[i].x == XMAX + PX) overlap = XMAX + PX;
			return true;
		}
	}
	return false;
}

void Blocks::storeToGridBlocks()
{
	for (size_t i{}; i < 4; i++)
	{
		gridBlocks.push_back({ blockOrder[i].x,blockOrder[i].y,static_cast<int>(color) });
	}
}

bool Blocks::gridIsOccupied()
{
	for (size_t i{}; i < gridBlocks.size(); i++)
	{
		sf::Vector2i store{ gridBlocks[i][0],gridBlocks[i][1] };
		for (int j{}; j < 4; j++)
		{
			if (store == blockOrder[j])
			{
				if (prevBlockOrder[1].y-blockOrder[1].y != 0)stop = 1;
				overlap = store.x;
				return true;
			}
		}
	}

	return false;
}

void Blocks::completedLines()
{
	std::vector<int> linescleared{};

	//check which line is completed
	for (size_t i{ 0 }; i <= static_cast<size_t>(YMAX); i += PX)
	{
		int boxPerLine{};
		for (size_t j{}; j < gridBlocks.size(); j++)
		{
			if (i == gridBlocks[j][1])
			{
				boxPerLine++;
				if (boxPerLine == 10)
				{
					linescleared.push_back(i);
				}
			}
		}
	}

	//remove all blocks from completed line/s
	for (size_t m{}; m < linescleared.size(); m++)
	{
		for (size_t n{}; n < gridBlocks.size(); n++)
		{
			if (gridBlocks[n][1] == linescleared[m])
			{
				gridBlocks.erase(gridBlocks.begin() + n);
				n--;
			}
		}
	}

	//adjust blocks to the bottom
	for (size_t p{ 0 }; p < linescleared.size(); p++)
	{
		for (size_t o{}; o < gridBlocks.size(); o++)
		{
			if (gridBlocks[o][1] < linescleared[p]) gridBlocks[o][1] += PX;
		}
	}
}

bool Blocks::gameOver()
{
	for (size_t i{}; i < 4; i++)
	{
		if (blockOrder[i].y < 0) return true;
	}
	return false;
}

