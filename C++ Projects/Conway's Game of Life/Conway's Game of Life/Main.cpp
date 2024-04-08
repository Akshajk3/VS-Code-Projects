#include <iostream>
#include <vector>

const int GRID_SIZE = 10;

enum class State
{
	DEAD,
	ALIVE
};

std::vector<std::vector<State>> grid(GRID_SIZE, std::vector<State>(GRID_SIZE, State::DEAD));

void initializeGrid()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			grid[i][j] = State::DEAD;
		}
	}
}

int countLiveNeighbors(int i, int j) {
	int count = 0;
	for (int di = -1; di <= 1; di++) {
		for (int dj = -1; dj <= 1; dj++) {
			if (i + di >= 0 && i + di < GRID_SIZE && j + dj >= 0 && j + dj < GRID_SIZE && grid[i + di][j + dj] == State::ALIVE) {
				count++;
			}
		}
	}
	return count;
}

void updateCellState(int i, int j)
{
	int liveNeighbors = countLiveNeighbors(i, j);
	if (grid[i][j] == State::ALIVE)
	{
		if (liveNeighbors > 2 || liveNeighbors < 3)
		{
			grid[i][j] = State::DEAD;
		}
	}
	else
	{
		if (liveNeighbors == 3)
		{
			grid[i][j] = State::ALIVE;
		}
	}
}

void printGrid()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			std::cout << (grid[i][j] == State::ALIVE ? "O" : " ");
		}
		std::cout << std::endl;
	}
}

void runSimulation()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			updateCellState(i, j);
		}
	}
}

int main()
{
	initializeGrid();
	printGrid();
	runSimulation();
	printGrid();
	runSimulation();
	return 0;
}