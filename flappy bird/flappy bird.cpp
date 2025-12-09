
#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

const int hight = 20;
const int widght = 20;

class Bird {
private:
	int x = 5;
	float y = hight / 2.0f;
	float velocity = 0.0f;
	float gravity = 0.5f;
public:

	void Update() {
		velocity += gravity;
		y += velocity;
}

	void Flap() {
		velocity =  -2.0f;
	}

	int getBirdY() {
		return y;
	}

	int getBirdX() {
		return x;
	}
};

class Pipe {
private:
	int x;
	int gapY;
	int gapSize = 6;
public:

	Pipe(int startX, int startgapY) {
		x = startX;
		gapY = startgapY;
	}
	void Move() {
		x--;
	}

	int getPipeX() {
		return x;
	}

	bool IsCollision(int birdY) {
		int topLimit = gapY - gapSize / 2;
		int botLimit = gapY + gapSize / 2;

		if (birdY < topLimit || birdY > botLimit) {
			return true;
		}
		else {
			return false;
		}

	}
};


class Map {
private:
	Bird bird;
	std::vector<Pipe> pipes;
	int pipeTimer = 0;
	int spawnrate = 10;
	int score = 0;
	bool isOver = false;
public:

	void Input() {
		if (_kbhit()) {
			switch (_getch()) {
			case ' ':
				bird.Flap();
				break;
			}
		}
	}

	void Logic() {

		if (isOver) {
			return;
		}

		bird.Update();
		pipeTimer++;

		if (pipeTimer >= spawnrate) {
			int randgap = rand() % (hight - 10) + 4;
			pipes.push_back((Pipe(widght - 1, randgap)));
			pipeTimer = 0;
		}

		for (int i = 0; i < pipes.size(); i++) {
			pipes[i].Move();
		}

		if (!pipes.empty() && pipes[0].getPipeX() < 0) {
			pipes.erase(pipes.begin());
			score++;
		}

		if (bird.getBirdY() >= hight - 1 || bird.getBirdY() <= 0) {
			isOver = true;
		}

		for (int i = 0; i < pipes.size(); i++) {
			if (pipes[i].getPipeX() == bird.getBirdX()) {
				if (pipes[i].IsCollision(bird.getBirdY())) {
					isOver = true;
				}
			}
		}
	}




	void Draw() {
		system("cls");
		if (isOver) {
			std::cout << "Game Over!" << std::endl;
			exit(0);
		}
		for (int i = 0; i < hight; i++) {
			for (int j = 0; j < widght; j++) {
				if (i == bird.getBirdY() && j == bird.getBirdX()) {
					std::cout << "@";
				}
				else {
					bool isPipe = false;
					for (int k = 0; k < pipes.size(); k++) {
						if (pipes[k].getPipeX() == j) {
							if (pipes[k].IsCollision(i)) {
								std::cout << "#";
								isPipe = true;
							}
						}
					}
					if (!isPipe) {
						if (i == 0 || i == hight - 1) {
							std::cout << "=";
						}
						else {
							std::cout << " ";
						}
					}
				}
			}
			std::cout << std::endl;
		}
		std::cout << "Score: " << score << std::endl;
	}
	bool GameOver() {
		return isOver;
	}
};


int main()
{
	srand(time(0));
	Map flappy;

	while (!flappy.GameOver()) {
		flappy.Input();
		flappy.Logic();
		flappy.Draw();
		Sleep(100);
	}

}