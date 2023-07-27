#include <iostream>
#include <vector>
#include <deque>
#include <utility> // For pair
#include <cstdlib> // For srand and rand
#include <ctime>   // For time
using namespace std;
int getRandomInt(int min, int max) {
    srand(static_cast<unsigned>(time(0)));
    return min + rand() % (max - min + 1);
}

void display(const std::vector<std::vector<int>>& matrix, int n) {
    for (int row = 0; row < n; row++) {
        for (int column = 0; column < n; column++) {
            std::cout << matrix[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    cout<<"enter game size board"<<endl;
    int boardsize;
    cin>>boardsize;
    std::vector<std::vector<int>> gameboard(boardsize, std::vector<int>(boardsize, -1));
    std::deque<std::pair<int, int>> snake;

    gameboard[getRandomInt(0, boardsize-1)][getRandomInt(0, boardsize-1)] = 0;
    gameboard[0][0] = 1;
    snake.push_front({0, 0});

    int move;
    while (true) {
        display(gameboard, boardsize);
        std::cout << "1 for to move top, 2 for to move right, 3 for to move down, 4 for to move left" << std::endl;
        std::cin >> move;

        std::pair<int, int> head = snake.front();
        int headrow = head.first;
        int headcoloum = head.second;
        int newHeadRow = headrow;
        int newHeadColumn = headcoloum;

        if (move == 1) {
            newHeadRow = headrow - 1;
        } else if (move == 2) {
            newHeadColumn = headcoloum + 1;
        } else if (move == 3) {
            newHeadRow = headrow + 1;
        } else if (move == 4) {
            newHeadColumn = headcoloum - 1;
        } else {
            std::cout << "Invalid move. Try again!" << std::endl;
            continue;
        }

        if (newHeadRow < 0 || newHeadRow >= boardsize || newHeadColumn < 0 || newHeadColumn >= boardsize) {
            std::cout << "Game Over! Snake hit the boundary." << std::endl;
            break;
        }

        if (gameboard[newHeadRow][newHeadColumn] == 1) {
            std::cout << "Game Over! Snake hit itself." << std::endl;
            break;
        }

        snake.push_front({newHeadRow, newHeadColumn});
        if (gameboard[newHeadRow][newHeadColumn] != 0) {
            std::pair<int, int> tail = snake.back();
            snake.pop_back();
            int tailrow = tail.first;
            int tailcoloum = tail.second;
            gameboard[tailrow][tailcoloum] = -1;
        } else {
            // The snake ate the food, generate new food position
            gameboard[newHeadRow][newHeadColumn] = 0;
            int foodRow, foodCol;
            do {
                foodRow = getRandomInt(0, boardsize-1);
                foodCol = getRandomInt(0, boardsize-1);
            } while (gameboard[foodRow][foodCol] != -1);
            gameboard[foodRow][foodCol] = 0;
        }

        gameboard[newHeadRow][newHeadColumn] = 1;
    }

    return 0;
}
