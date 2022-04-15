#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#define A 30	//Ширина поля
#define B 30	//Высота поля

using namespace std;



void show(int ag[A][B], int score[A][B], int gr) {	//Показываем, где какие агенты на поле
	int x, y;

	if (gr == 1||gr == 3) {
		HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
		for (y = 0; y < B; y++) {
			for (x = 0; x < A; x++) {
				if (ag[x][y] == 2) {
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf(" X");
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
				if (ag[x][y] == 1) {
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					printf(" 0");
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
				if (ag[x][y] == 0) {
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					printf(" П");
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
			}
			printf("\n");
		}
		printf("------------------------------------------------------------------------------------------------------------\n");
	}
	if (gr == 2) {
		HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
		for (y = 0; y < B; y++) {
			for (x = 0; x < A; x++) {
				if (ag[x][y] == 0) {
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					printf(" 0");
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
				if (ag[x][y] == 1) {
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf(" X");
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
			}
			printf("\n");
		}
		printf("------------------------------------------------------------------------------------------------------------\n");
	}
}

void game(int x, int y, int a, int b, int ag[A][B], int score[A][B], int gr) {	//Игра между агентами x, y и a, b
	int win, draw, loose, defeat, res[3][3] = { {4, 4, 0}, {4, 4, 0}, {0, 6, 0} };

	if (gr == 1) {	// Камень - ножницы - бумага
		win = 1;	// <- Очки за победу
		draw = 0;	// <- Очки за ничью
		loose = -1;	// <- Очки за поражение
		if (ag[x][y] == 0 && ag[a][b] == 1) {
			score[x][y] += win;
			score[a][b] += loose;
		}
		if (ag[x][y] == 1 && ag[a][b] == 2) {
			score[x][y] += win;
			score[a][b] += loose;
		}
		if (ag[x][y] == 2 && ag[a][b] == 0) {
			score[x][y] += win;
			score[a][b] += loose;
		}

		if (ag[x][y] == 1 && ag[a][b] == 0) {
			score[x][y] += loose;
			score[a][b] += win;
		}
		if (ag[x][y] == 2 && ag[a][b] == 1) {
			score[x][y] += loose;
			score[a][b] += win;
		}
		if (ag[x][y] == 0 && ag[a][b] == 2) {
			score[x][y] += loose;
			score[a][b] += win;
		}

		if (ag[x][y] == 0 && ag[a][b] == 0) {
			score[x][y] += draw;
			score[a][b] += draw;
		}
		if (ag[x][y] == 1 && ag[a][b] == 1) {
			score[x][y] += draw;
			score[a][b] += draw;
		}
		if (ag[x][y] == 2 && ag[a][b] == 2) {
			score[x][y] += draw;
			score[a][b] += draw;
		}
	}
	if (gr == 2) {	//Ястребы - голуби
		win = 3;	//Выйгрыш ястреба при встрече с голубем
		draw = 2;	//Выйгрыш голубя при встрече с голубем
		loose = 0;	//Выйгрыш ястреба при встрече с ястребом
		defeat = 0;	//Выйгрыш голубя при встрече с ястребом
		if (ag[x][y] == 0 && ag[a][b] == 0) {
			score[x][y] += draw;
			score[a][b] += draw;
		}
		if (ag[x][y] == 1 && ag[a][b] == 0) {
			score[x][y] += win;
			score[a][b] += defeat;
		}
		if (ag[x][y] == 0 && ag[a][b] == 1) {
			score[x][y] += defeat;
			score[a][b] += win;
		}
		if (ag[x][y] == 1 && ag[a][b] == 1) {
			score[x][y] += loose;
			score[a][b] += loose;
		}
	}
	if (gr == 3) {	//Злой-наивный-ненаивный
		score[x][y] = res[ag[x][y]][ag[a][b]];
		score[a][b] = res[ag[a][b]][ag[x][y]];
	}
}

int con(int x, int y, int a, int b, int score[A][B], int gr) {	//Могут ли сыграть агенты x, y и a, b друг с другом?
	int distation;

	if (gr == 1 || gr == 2||gr == 3) {
		distation = 1; // <- Максимальная дистанция между агентами, которые могут играть
		if ((x - a)*(x - a) + (y - b)*(y - b) <= distation * distation && (x != a || y != b)) return 1;
		else return 0;
	}
	return 1;
}

void comp(int ag[A][B], int score[A][B], int gr) {	//Этап игры между всеми агентами
	int x, y, a, b;

	if (gr == 1||gr == 2||gr == 3) {
		for (x = 0; x < A; x++) {
			for (y = 0; y < B; y++) {
				for (a = 0; a < A; a++) {
					for (b = 0; b < B; b++) {
						if (con(x, y, a, b, score, gr)) game(x, y, a, b, ag, score, gr);
					}
				}
			}
		}
	}
}

int dupl(int x, int y, int a, int b, int gr) {	//Может ли агент x, y быть заменён на агента a, b?
	double dist;

	if (gr == 1||gr == 2||gr == 3) {
		dist = 1; // <- Дистанция до потенциального дублируемого агента
		if ((x - a)*(x - a) + (y - b)*(y - b) <= dist * dist) return 1;
		else return 0;
	}
	return 1;
}

void replace(int x, int y, int ag[A][B], int score[A][B], int gr) {	//Заменяем агента x, y на другого
	int a, b, maxscore = -10000;

	if (gr == 1 || gr == 2 || gr == 3) {
		for (a = 0; a < A; a++) {
			for (b = 0; b < B; b++) {
				if (dupl(x, y, a, b, gr) && score[a][b] > maxscore) {
					maxscore = score[a][b];
					ag[x][y] = ag[a][b];
				}
			}
		}
	}
}

void change(int ag[A][B], int score[A][B], int gr) {	//Некоторых агентов убиваем, некоторых дублируем
	int x, y, totscore = 0;
	int chance1 = 50, chance2 = 50;

	if (gr == 1) {
		for (x = 0; x < A; x++) for (y = 0; y < B; y++) totscore += score[x][y];
		for (y = 0; y < B; y++) {
			for (x = 0; x < A; x++) {
				if (score[x][y] * A * B * chance1 < (rand() % 100) * totscore) {
					replace(x, y, ag, score, gr);
				}
			}
		}
	}
	if (gr == 2 || gr == 3) {
		for (x = 0; x < A; x++) for (y = 0; y < B; y++) totscore += score[x][y];
		for (y = 0; y < B; y++) {
			for (x = 0; x < A; x++) {
				if (score[x][y] * A * B * chance2 < (rand() % 100) * totscore) {
					replace(x, y, ag, score, gr);
				}
			}
		}
	}
}

void clear(int ag[A][B], int score[A][B], int gr) {	//Очищаем массив заработанных очков score
	int x, y;

	if (gr == 1) {
		for (x = 0; x < A; x++) {
			for (y = 0; y < B; y++) {
				score[x][y] += 0;
			}
		}
	}
	if (gr == 2 || gr == 3) {
		for (x = 0; x < A; x++) {
			for (y = 0; y < B; y++) {
				score[x][y] = 0;
			}
		}
	}
}

void inject(int ag[A][B], int score[A][B], int gr, int ir) {
	int count, x, y, i, type, m = 0, x0, y0, d;

	if (ir == 0) {
		printf("Агентов какого типа вы хотите добавить и в каком количестве?\n");
		if (gr == 1) printf("(красные - 0, синие - 1, белые - 2)");
		printf("\n");
		cin >> type;
		cin >> count;
		for (i = 0; i < count; i++) {
			x = rand() % A;
			y = rand() % B;
			if (ag[x][y] == type) i--;
			ag[x][y] = type;
			m++;
			if (m > A*B * 1000) {
				printf("Удалось добавить только %i агентов\n", i + 1);
				break;
			}
		}
	}
	if (ir == 1) {
		printf("Агентов какого типа вы хотите добавить, какой радиус области инъекции и каковы её координаты?\n");
		if (gr == 1) printf("(красные - 0, синие - 1, белые - 2)");
		printf("\n");
		cin >> type;
		cin >> d;
		cin >> x0;
		cin >> y0;
		for (x = 0; x < A; x++) {
			for (y = 0; y < A; y++) {
				if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= d * d) ag[x][y] = type;
			}
		}
	}
}

void evolution(int ag[A][B], int score[A][B], int gr) {		//Всё вместе
	int i, a;

	srand(time(NULL));
	for (i = 0;;i++) {
		comp(ag, score, gr);
		show(ag, score, gr);
		change(ag, score, gr);
		clear(ag, score, gr);
		a = _getch();
		if (a == 's') {
			inject(ag, score, gr, 0);
			show(ag, score, gr);
		}
		if (a == 'l') {
			inject(ag, score, gr, 1);
		}
	}
}

int main()
{
	int ag[A][B], score[A][B] = { 0 }, gr, x, y;
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");

	gr = 2; // <- Режим игры (1 - камень-ножницы-бумага, 2 - ястребы-голуби, 3 - злой-наивный-ненаивный)
	for (x = 0; x < A; x++) {	// <- Заполняем поле агентами
		for (y = 0; y < B; y++) {
			ag[x][y] = rand() % 1;
		}
	}
	printf("s - <<рассыпная>> инъекция\nl - локальная инъекция\nЛюбой другой символ - сыграть раунд\n");
	evolution(ag, score, gr);
	return 0;
}
/*
for (x = 0; x < A; x++) {	// <- Заполняем поле агентами
		for (y = 0; y < B; y++) {
			if (y <= 1) ag[x][y] = 0;
			if (y > 1 && x <= 2) ag[x][y] = 1;
			if (y > 1 && x > 2) ag[x][y] = 2;
		}
	}


for (x = 0; x < A; x++) {	// <- Заполняем поле агентами
		for (y = 0; y < B; y++) {
			if (y <= 3) ag[x][y] = 2;
			if (y > 3 && x <= 6) ag[x][y] = 1;
			if (y > 3 && x > 6) ag[x][y] = 0;
		}
	}

	for (x = 0; x < A; x++) {	// <- Заполняем поле агентами
		for (y = 0; y < B; y++) {
			ag[x][y] = rand() % 3;
		}
	}
	void replace(int x, int y, int ag[A][B], int score[A][B], int gr) {	//Заменяем агента x, y на другого
	int a, b, maxscore = -10000;

	if (gr == 1||gr == 2) {
		for (a = 0; a < A; a++) {
			for (b = 0; b < B; b++) {
				if (dupl(x, y, a, b, gr) && score[a][b] > maxscore) {
					maxscore = score[a][b];
					ag[x][y] = ag[a][b];
				}
			}
		}
	}
}
		win = 3;	//Выйгрыш ястреба при встрече с голубем
		draw = 2;	//Выйгрыш голубя при встрече с голубем
		loose = 0;	//Выйгрыш ястреба при встрече с ястребом
		defeat = 0;	//Выйгрыш голубя при встрече с ястребом

*/
