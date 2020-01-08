// Bandersnatch.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <array>
#include <time.h>
#include <Windows.h>
#include <wincon.h>
#include <string>

int Felder[237][125];

void gotoxy(short x, short y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };

	SetConsoleCursorPosition(hStdout, position);
}

bool OnWeg(int x, int y)
{
	if (x < 0 || x > 237 || y < 0 || y > 125)
	{
		return false;
	}
	if (Felder[x][y] == 1)
	{
		return true;
	}
	return false;
}
bool isBlocked(int x1, int x2, int y1, int y2, int x, int y, bool del = false)
{
	if (x <= x1 || y <= y1 || x >= x2 || y >= y2)
	{
		return true;
	}
	if (Felder[x][y] == 2)
	{
		return true;
	}
	return false;
}
void GenerateMap(int hoehe, int breite, short x, short y, int dir, std::vector<std::vector<std::array<short, 2>>>& ExWeg)
{
	bool broken = false;
	int counter, counter2 = 0;
	int temp, x1, x2, y1, y2;
	temp = breite / 2;
	if (x - temp < 0)
	{
		x1 = 0;
		x2 = breite;
	}
	else if (x + temp > 237)
	{
		x2 = 237;
		x1 = 237 - breite;
	}
	else
	{
		x1 = x - temp;
		temp = breite - temp;
		x2 = x + temp;
	}
	temp = hoehe / 2;
	if (y - temp < 0)
	{
		y1 = 0;
		y2 = hoehe;
	}
	else if (y + temp > 125)
	{
		y2 = 125;
		y1 = 125 - hoehe;
	}
	else
	{
		y1 = y - temp;
		temp = hoehe - temp;
		y2 = y + temp;
	}
	float ran;
	float zahl;
	std::vector<std::array<float, 9>> pfade = { { (float)x, (float)y, (float)dir, 105, -1, -1, -1, -1, -1 } };
	while (pfade.size() > 0)
	{
		for (int i = pfade.size() - 1; i >= 0; i--)
		{
			if (isBlocked(x1, x2, y1, y2, pfade[i][0], pfade[i][1]))
			{
				if (pfade.size() == 1)
				{
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsole, 30);
				}
				if (ExWeg.size() > 1)
					ExWeg.erase(ExWeg.begin() + i);
				pfade.erase(pfade.begin() + i);
				continue;
			}
			zahl = 0;
			counter = 0;
			if (pfade[i][2] == 1)
			{
				if (isBlocked(x1, x2, y1, y2, pfade[i][0] + 1, pfade[i][1]))
				{
					zahl += pfade[i][3] + pfade[i][4] + pfade[i][5] + pfade[i][6] + pfade[i][7];
					pfade[i][3] = pfade[i][4] = pfade[i][5] = pfade[i][6] = pfade[i][7] = 0;
				}
				if (isBlocked(x1, x2, y1, y2, pfade[i][0] + 1, pfade[i][1] + 1))
				{
					zahl += pfade[i][4];
					pfade[i][4] = 0;
				}
				if (isBlocked(x1, x2, y1, y2, pfade[i][0] + 1, pfade[i][1] - 1))
				{
					zahl += pfade[i][5];
					pfade[i][5] = 0;
				}
			}
			else if (pfade[i][2] == 2)
			{
				if (isBlocked(x1, x2, y1, y2, pfade[i][0], pfade[i][1] + 1))
				{
					zahl += pfade[i][3] + pfade[i][4] + pfade[i][5] + pfade[i][6] + pfade[i][7];
					pfade[i][3] = pfade[i][4] = pfade[i][5] = pfade[i][6] = pfade[i][7] = 0;
				}
				if (isBlocked(x1, x2, y1, y2, pfade[i][0] - 1, pfade[i][1] + 1))
				{
					zahl += pfade[i][4];
					pfade[i][4] = 0;
				}
				if (isBlocked(x1, x2, y1, y2, pfade[i][0] + 1, pfade[i][1]) + 1)
				{
					zahl += pfade[i][5];
					pfade[i][5] = 0;
				}
			}
			else if (pfade[i][2] == 3)
			{
				if (isBlocked(x1, x2, y1, y2, pfade[i][0] - 1, pfade[i][1]))
				{
					zahl += pfade[i][3] + pfade[i][4] + pfade[i][5] + pfade[i][6] + pfade[i][7];
					pfade[i][3] = pfade[i][4] = pfade[i][5] = pfade[i][6] = pfade[i][7] = 0;
				}
				if (isBlocked(x1, x2, y1, y2, pfade[i][0] - 1, pfade[i][1] + 1))
				{
					zahl += pfade[i][4];
					pfade[i][4] = 0;
				}
				if (isBlocked(x1, x2, y1, y2, pfade[i][0] - 1, pfade[i][1]) - 1)
				{
					zahl += pfade[i][5];
					pfade[i][5] = 0;
				}
			}
			else if (pfade[i][2] == 4)
			{
				if (isBlocked(x1, x2, y1, y2, pfade[i][0], pfade[i][1] - 1))
				{
					zahl += pfade[i][3] + pfade[i][4] + pfade[i][5] + pfade[i][6] + pfade[i][7];
					pfade[i][3] = pfade[i][4] = pfade[i][5] = pfade[i][6] = pfade[i][7] = 0;
				}
				if (isBlocked(x1, x2, y1, y2, pfade[i][0] + 1, pfade[i][1] - 1))
				{
					zahl += pfade[i][4];
					pfade[i][4] = 0;
				}
				if (isBlocked(x1, x2, y1, y2, pfade[i][0] - 1, pfade[i][1]) - 1)
				{
					zahl += pfade[i][5];
					pfade[i][5] = 0;
				}
			}
			for (int z = 3; z < pfade[i].size(); z++)
			{
				if (pfade[i][z] != 0)
				{
					counter++;
				}
			}
			zahl /= counter;
			for (int z = 3; z < pfade[i].size(); z++)
			{
				if (pfade[i][z] != 0)
				{
					pfade[i][z] += zahl;
				}
			}
			ran = rand() % 100 + 1;
			for (int j = 3; j < pfade[i].size(); j++)
			{
				ran -= pfade[i][j];
				if (ran <= 0)
				{
					switch (j)
					{
					case 3:
						if (pfade[i][2] == 1)
						{
							pfade[i][0] += 1;
						}
						else if (pfade[i][2] == 2)
						{
							pfade[i][1] += 1;
						}
						else if (pfade[i][2] == 3)
						{
							pfade[i][0] -= 1;
						}
						else if (pfade[i][2] == 4)
						{
							pfade[i][1] -= 1;
						}
						if (pfade[i][2] == 1 || pfade[i][2] == 3)
						{
							if (!OnWeg(pfade[i][0], pfade[i][1] + 1))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] + 1] = 2;
							}
							if (!OnWeg(pfade[i][0], pfade[i][1] - 1))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] - 1] = 2;
							}
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
						}
						else
						{
							if (!OnWeg(pfade[i][0] + 1, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] + 1][(short)pfade[i][1]] = 2;
							}
							if (!OnWeg(pfade[i][0] - 1, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] - 1][(short)pfade[i][1]] = 2;
							}
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
						}
						break;
					case 4:
						if (pfade[i][2] == 1)
						{
							pfade[i][0] += 1;
							if (!OnWeg(pfade[i][0], pfade[i][1] - 1))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] - 1] = 2;
							}
							if (!OnWeg(pfade[i][0] + 1, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] + 1][(short)pfade[i][1]] = 2;
							}
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 2;
						}
						else if (pfade[i][2] == 2)
						{
							pfade[i][1] += 1;
							if (!OnWeg(pfade[i][0], pfade[i][1] + 1))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] + 1] = 2;
							}
							if (!OnWeg(pfade[i][0] + 1, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] + 1][(short)pfade[i][1]] = 2;
							}
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});

							pfade[i][2] = 3;
						}
						else if (pfade[i][2] == 3)
						{
							pfade[i][0] -= 1;
							if (!OnWeg(pfade[i][0], pfade[i][1] + 1))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] + 1] = 2;
							}
							if (!OnWeg(pfade[i][0] - 1, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] - 1][(short)pfade[i][1]] = 2;
							}
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 4;
						}
						else if (pfade[i][2] == 4)
						{
							pfade[i][1] -= 1;
							if (!OnWeg(pfade[i][0], pfade[i][1] - 1))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] - 1] = 2;
							}
							if (!OnWeg(pfade[i][0] - 1, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] - 1][(short)pfade[i][1]] = 2;
							}
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 1;
						}
						break;
					case 5:
						if (pfade[i][2] == 1)
						{
							pfade[i][0] += 1;
							if (!OnWeg(pfade[i][0], pfade[i][1] + 1))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] + 1] = 2;
							}
							if (!OnWeg(pfade[i][0] + 1, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] + 1][(short)pfade[i][1]] = 2;
							}
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 4;
						}
						else if (pfade[i][2] == 2)
						{
							pfade[i][1] += 1;
							if (!OnWeg(pfade[i][0], pfade[i][1] + 1))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] + 1] = 2;
							}
							if (!OnWeg(pfade[i][0] - 1, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] - 1][(short)pfade[i][1]] = 2;
							}
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 1;
						}
						else if (pfade[i][2] == 3)
						{
							pfade[i][0] -= 1;
							if (!OnWeg(pfade[i][0], pfade[i][1] - 1))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] - 1] = 2;
							}
							if (!OnWeg(pfade[i][0] - 1, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] - 1][(short)pfade[i][1]] = 2;
							}
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 2;
						}
						else if (pfade[i][2] == 4)
						{
							pfade[i][1] -= 1;
							if (!OnWeg(pfade[i][0], pfade[i][1] - 1))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] - 1] = 2;
							}
							if (!OnWeg(pfade[i][0] + 1, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] + 1][(short)pfade[i][1]] = 2;
							}
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 3;
						}
						break;
					case 6:
						if (pfade[i][2] == 1)
						{
							if (!OnWeg(pfade[i][0] + 2, pfade[i][1] - 1))
							{
								Felder[(short)pfade[i][0] + 2][(short)pfade[i][1] - 1] = 2;
							}
							if (!OnWeg(pfade[i][0] + 2, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] + 2][(short)pfade[i][1]] = 2;
							}
							if (!OnWeg(pfade[i][0] + 2, pfade[i][1] + 1))
							{
								Felder[(short)pfade[i][0] + 2][(short)pfade[i][1] + 1] = 2;
							}
							pfade[i][0] += 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][1] += 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg.push_back(ExWeg[i]);
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 2;
							pfade.push_back(std::array<float, 9> {pfade[i][0], pfade[i][1] - 2, 4, 105, -1, -1, -1, -1, -1});
							Felder[(short)pfade[i][0]][(short)pfade[i][1] - 2] = 1;
							ExWeg[ExWeg.size() - 1].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1] - 2});
						}
						else if (pfade[i][2] == 2)
						{
							if (!OnWeg(pfade[i][0] - 1, pfade[i][1] + 2))
							{
								Felder[(short)pfade[i][0] - 1][(short)pfade[i][1] + 2] = 2;
							}
							if (!OnWeg(pfade[i][0], pfade[i][1] + 2))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] + 2] = 2;
							}
							if (!OnWeg(pfade[i][0] + 1, pfade[i][1] + 2))
							{
								Felder[(short)pfade[i][0] + 1][(short)pfade[i][1] + 2] = 2;
							}
							pfade[i][1] += 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][0] -= 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg.push_back(ExWeg[i]);
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 3;
							pfade.push_back(std::array<float, 9> {pfade[i][0] + 2, pfade[i][1], 1, 105, -1, -1, -1, -1, -1});
							Felder[(short)pfade[i][0] + 2][(short)pfade[i][1]] = 1;
							ExWeg[ExWeg.size() - 1].push_back(std::array<short, 2> {(short)pfade[i][0] + 2, (short)pfade[i][1]});
						}
						else if (pfade[i][2] == 3)
						{
							if (!OnWeg(pfade[i][0] - 2, pfade[i][1] - 1))
							{
								Felder[(short)pfade[i][0] - 2][(short)pfade[i][1] - 1] = 2;
							}
							if (!OnWeg(pfade[i][0] - 2, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] - 2][(short)pfade[i][1]] = 2;
							}
							if (!OnWeg(pfade[i][0] - 2, pfade[i][1] + 1))
							{
								Felder[(short)pfade[i][0] - 2][(short)pfade[i][1] + 1] = 2;
							}
							pfade[i][0] -= 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][1] -= 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg.push_back(ExWeg[i]);
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 4;
							pfade.push_back(std::array<float, 9> {pfade[i][0], pfade[i][1] + 2, 2, 105, -1, -1, -1, -1, -1});
							Felder[(short)pfade[i][0]][(short)pfade[i][1] + 2] = 1;
							ExWeg[ExWeg.size() - 1].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1] + 2});
						}
						else if (pfade[i][2] == 4)
						{
							if (!OnWeg(pfade[i][0] - 1, pfade[i][1] - 2))
							{
								Felder[(short)pfade[i][0] - 1][(short)pfade[i][1] - 2] = 2;
							}
							if (!OnWeg(pfade[i][0], pfade[i][1] - 2))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] - 2] = 2;
							}
							if (!OnWeg(pfade[i][0] + 1, pfade[i][1] - 2))
							{
								Felder[(short)pfade[i][0] + 1][(short)pfade[i][1] - 2] = 2;
							}
							pfade[i][1] -= 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][0] += 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg.push_back(ExWeg[i]);
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 1;
							pfade.push_back(std::array<float, 9> {pfade[i][0] - 2, pfade[i][1], 3, 105, -1, -1, -1, -1, -1});
							Felder[(short)pfade[i][0] - 2][(short)pfade[i][1]] = 1;
							ExWeg[ExWeg.size() - 1].push_back(std::array<short, 2> {(short)pfade[i][0] - 2, (short)pfade[i][1]});
						}
						break;
					case 7:
						if (pfade[i][2] == 1)
						{
							if (!OnWeg(pfade[i][0] + 2, pfade[i][1] - 1))
							{
								Felder[(short)pfade[i][0] + 2][(short)pfade[i][1] - 1] = 2;
							}
							if (!OnWeg(pfade[i][0] + 2, pfade[i][1] + 1))
							{
								Felder[(short)pfade[i][0] + 2][(short)pfade[i][1] + 1] = 2;
							}
							pfade.push_back(std::array<float, 9> {pfade[i][0] + 2, pfade[i][1], 1, 105, -1, -1, -1, -1, -1});
							pfade[i][0] += 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							Felder[(short)pfade[i][0] + 1][(short)pfade[i][1]] = 1;
							ExWeg.push_back(ExWeg[i]);
							ExWeg.push_back(ExWeg[i]);
							ExWeg[ExWeg.size() - 2].push_back(std::array<short, 2> {(short)pfade[i][0] + 1, (short)pfade[i][1]});
							pfade[i][1] += 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2>  {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 2;
							pfade.push_back(std::array<float, 9> {pfade[i][0], pfade[i][1] - 2, 4, 105, -1, -1, -1, -1, -1});
							Felder[(short)pfade[i][0]][(short)pfade[i][1] - 2] = 1;
							ExWeg[ExWeg.size() - 1].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1] - 2});
						}
						else if (pfade[i][2] == 2)
						{
							if (!OnWeg(pfade[i][0] - 1, pfade[i][1] + 2))
							{
								Felder[(short)pfade[i][0] - 1][(short)pfade[i][1] + 2] = 2;
							}
							if (!OnWeg(pfade[i][0] + 1, pfade[i][1] + 2))
							{
								Felder[(short)pfade[i][0] + 1][(short)pfade[i][1] + 2] = 2;
							}
							pfade.push_back(std::array<float, 9> {pfade[i][0], pfade[i][1] + 2, 2, 105, -1, -1, -1, -1, -1});
							pfade[i][1] += 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							Felder[(short)pfade[i][0]][(short)pfade[i][1] + 1] = 1;
							ExWeg.push_back(ExWeg[i]);
							ExWeg.push_back(ExWeg[i]);
							ExWeg[ExWeg.size() - 2].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1] + 1});
							pfade[i][0] -= 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2>  {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 3;
							pfade.push_back(std::array<float, 9> {pfade[i][0] + 2, pfade[i][1], 1, 105, -1, -1, -1, -1, -1});
							Felder[(short)pfade[i][0] + 2][(short)pfade[i][1]] = 1;
							ExWeg[ExWeg.size() - 1].push_back(std::array<short, 2>  {(short)pfade[i][0] + 2, (short)pfade[i][1]});
						}
						else if (pfade[i][2] == 3)
						{
							if (!OnWeg(pfade[i][0] - 2, pfade[i][1] - 1))
							{
								Felder[(short)pfade[i][0] - 2][(short)pfade[i][1] - 1] = 2;
							}
							if (!OnWeg(pfade[i][0] - 2, pfade[i][1] + 1))
							{
								Felder[(short)pfade[i][0] - 2][(short)pfade[i][1] + 1] = 2;
							}
							pfade.push_back(std::array<float, 9> {pfade[i][0] - 2, pfade[i][1], 3, 105, -1, -1, -1, -1, -1});
							pfade[i][0] -= 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							Felder[(short)pfade[i][0] - 1][(short)pfade[i][1]] = 1;
							ExWeg.push_back(ExWeg[i]);
							ExWeg.push_back(ExWeg[i]);
							ExWeg[ExWeg.size() - 2].push_back(std::array<short, 2> {(short)pfade[i][0] - 1, (short)pfade[i][1]});
							pfade[i][1] -= 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2>  {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 4;
							pfade.push_back(std::array<float, 9> {pfade[i][0], pfade[i][1] + 2, 2, 105, -1, -1, -1, -1, -1});
							Felder[(short)pfade[i][0]][(short)pfade[i][1] + 2] = 1;
							ExWeg[ExWeg.size() - 1].push_back(std::array<short, 2>  {(short)pfade[i][0], (short)pfade[i][1] + 2});
						}
						else if (pfade[i][2] == 4)
						{
							if (!OnWeg(pfade[i][0] - 1, pfade[i][1] - 2))
							{
								Felder[(short)pfade[i][0] - 1][(short)pfade[i][1] - 2] = 2;
							}
							if (!OnWeg(pfade[i][0] + 1, pfade[i][1] - 2))
							{
								Felder[(short)pfade[i][0] + 1][(short)pfade[i][1] - 2] = 2;
							}
							pfade.push_back(std::array<float, 9> {pfade[i][0], pfade[i][1] - 2, 4, 105, -1, -1, -1, -1, -1});
							pfade[i][1] -= 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1]});
							Felder[(short)pfade[i][0]][(short)pfade[i][1] - 1] = 1;
							ExWeg.push_back(ExWeg[i]);
							ExWeg.push_back(ExWeg[i]);
							ExWeg[ExWeg.size() - 2].push_back(std::array<short, 2> {(short)pfade[i][0], (short)pfade[i][1] - 1});
							pfade[i][0] += 1;
							Felder[(short)pfade[i][0]][(short)pfade[i][1]] = 1;
							ExWeg[i].push_back(std::array<short, 2>  {(short)pfade[i][0], (short)pfade[i][1]});
							pfade[i][2] = 1;
							pfade.push_back(std::array<float, 9> {pfade[i][0] - 2, pfade[i][1], 3, 105, -1, -1, -1, -1, -1});
							Felder[(short)pfade[i][0] - 2][(short)pfade[i][1]] = 1;
							ExWeg[ExWeg.size() - 1].push_back(std::array<short, 2>  {(short)pfade[i][0] - 2, (short)pfade[i][1]});
						}
						break;
					case 8:
						if (pfade.size() < 10 && broken == false)
						{
							if (counter2 < 10)
							{
								counter2++;
								j = 9;
								break;
							}
						}
						broken = true;
						counter2 = 0;
						if (pfade[i][2] == 1)
						{
							if (!OnWeg(pfade[i][0] + 1, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] + 1][(short)pfade[i][1]] = 2;
							}
						}
						if (pfade[i][2] == 2)
						{
							if (!OnWeg(pfade[i][0], pfade[i][1] + 1))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] + 1] = 2;
							}
						}
						if (pfade[i][2] == 3)
						{
							if (!OnWeg(pfade[i][0] - 1, pfade[i][1]))
							{
								Felder[(short)pfade[i][0] - 1][(short)pfade[i][1]] = 2;
							}
						}
						if (pfade[i][2] == 4)
						{
							if (!OnWeg(pfade[i][0], pfade[i][1] + 1))
							{
								Felder[(short)pfade[i][0]][(short)pfade[i][1] - 1] = 2;
							}
						}
						if (pfade.size() == 1)
						{
							HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hConsole, 23);
						}
						break;
					}
					if (j == 3)
					{

						zahl = 0.2 * pfade[i][j];
						pfade[i][j] -= zahl;
						zahl /= 9;
						for (int z = 4; z < pfade[i].size(); z++)
						{
							if (z != pfade[i].size() - 1)
							{
								pfade[i][z] += zahl;
							}
							pfade[i][z] += zahl;
						}
					}
					else if (j == 8)
					{
						if (ExWeg.size() > 1)
							ExWeg.erase(ExWeg.begin() + i);
						pfade.erase(pfade.begin() + i);
						break;
					}
					else
					{
						for (int z = 4; z < pfade[i].size(); z++)
						{
							zahl = pfade[i][z] * 0.5;
							if (z == j || z == pfade[i].size() - 1)
								zahl = pfade[i][z] * 0.75;
							pfade[i][z] -= zahl;
							pfade[i][3] += zahl;
						}
					}
					break;
				}
			}
		}
	}
}

void Markieren(int x, int y, std::vector<std::array<short, 2>> &Gelaufen, std::array<short, 2> Ziel, int* Key, bool GKey, std::array<short, 2> Door, std::vector<std::array<short, 2>> Weg, bool aufgedeckt, short Sichtweite, bool ZAZ, bool Mittig)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (Sichtweite > 0)
	{
		for (int i = x - (Sichtweite + 1); i <= x + (Sichtweite + 1); i++)
		{
			if (i < 0 && Mittig == false)
				i = 0;
			if (i > 236 && Mittig == false)
				break;
			for (int j = y - (Sichtweite + 1); j <= y + (Sichtweite + 1); j++)
			{
				if (j < 0 && Mittig == false)
					j = 0;
				if (j > 124 && Mittig == false)
					break;
				if (sqrt((x - i) * (x - i) + (y - j) * (y - j)) <= Sichtweite || i == Ziel[0] && j == Ziel[1] && ZAZ == true)
				{
					if (i < 0 || i > 236 || j < 0 || j > 124)
					{
						SetConsoleTextAttribute(hConsole, 102);
						gotoxy(118 - x + i, 62 - y + j); std::cout << " ";
					}
					else if (Felder[i][j] == 2 || Felder[i][j] == 0)
					{
						SetConsoleTextAttribute(hConsole, 72);
						if (Mittig == true)
						{
							gotoxy(118 - x + i, 62 - y + j); std::cout << " ";
						}
						else
						{
							gotoxy(i, j); std::cout << " ";
						}
					}
					else if (aufgedeckt == true && Felder[i][j] == 1)
					{
						SetConsoleTextAttribute(hConsole, 25);
						for (int z = 0; z < Weg.size() - 2; z++)
						{
							if (i == Weg[z][0] && j == Weg[z][1])
							{
								gotoxy(Weg[z][0], Weg[z][1]); std::cout << " ";
							}
						}
					}
					else if (i == Ziel[0] && j == Ziel[1])
					{
						SetConsoleTextAttribute(hConsole, 15);
						if (Mittig == true)
						{
							gotoxy(118 - x + i, 62 - y + j); std::cout << "o";
						}
						else
						{
							gotoxy(i, j); std::cout << "o";
						}
					}
					else if (i == Door[0] && j == Door[1])
					{
						SetConsoleTextAttribute(hConsole, 15);
						if (Mittig == true)
						{
							gotoxy(118 - x + i, 62 - y + j); std::cout << "O";
						}
						else
						{
							gotoxy(i, j); std::cout << "O";
						}
					}
					else if (Felder[i][j] == 1)
					{
						SetConsoleTextAttribute(hConsole, 0);
						if (Mittig == true)
						{
							gotoxy(118 - x + i, 62 - y + j); std::cout << " ";
						}
					}
					if (GKey == false)
					{
						if (i == Key[0] && j == Key[1])
						{
							SetConsoleTextAttribute(hConsole, 102);
							if (Mittig == true)
							{
								gotoxy(118 - x + i, 62 - y + j); std::cout << "S";
							}
							else
							{
								gotoxy(i, j); std::cout << "S";
							}
						}
					}
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 0);
					if (Mittig == true)
					{
						gotoxy(118 - x + i, 62 - y + j); std::cout << " ";
					}
					else
					{
						gotoxy(i, j); std::cout << " ";
					}
				}
			}
		}
	}
	SetConsoleTextAttribute(hConsole, 15);
	if (Mittig == true)
	{
		gotoxy(118, 62); std::cout << "x";
	}
	else
	{
		gotoxy(x, y); std::cout << "x";
	}
	SetConsoleTextAttribute(hConsole, 15);
	for (int i = 0; i < Gelaufen.size(); i++)
	{
		if (Gelaufen[i][0] == x && Gelaufen[i][1] == y)
		{
			return;
		}
	}
	Gelaufen.push_back({ (short)x, (short)y });
}

bool Bewegen(short& x, short& y, std::vector<std::array<short, 2>> Weg, std::vector<std::array<short, 2>> &Gelaufen, std::array<short, 2> Ziel, int* Key, bool GKey, std::array<short, 2> Door, short Sichtweite, bool ZAZ, bool Mittig)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	static bool aufgedeckt, aufgedeckt2;
	bool moved = false;
	if (_kbhit())
	{
		char c = _getch();
		switch (c)
		{
		case 27: return false;
			break;
		case 'w':
		case 'W': if (OnWeg(x, y - 1)) { if (Mittig == false) { gotoxy(x, y); std::cout << " "; } y--; moved = true; }
				  break;
		case 's':
		case 'S': if (OnWeg(x, y + 1)) { if (Mittig == false) { gotoxy(x, y); std::cout << " "; } y++; moved = true; }
				  break;
		case 'a':
		case 'A': if (OnWeg(x - 1, y)) { if (Mittig == false) { gotoxy(x, y); std::cout << " "; } x--; moved = true; }
				  break;
		case 'd':
		case 'D': if (OnWeg(x + 1, y)) { if (Mittig == false) { gotoxy(x, y); std::cout << " "; } x++; moved = true; }
				  break;
		case 'x':
		case 'X':
			if (Mittig == true)
				break;
			aufgedeckt = !aufgedeckt;
			SetConsoleTextAttribute(hConsole, 0);
			if (aufgedeckt == true)
			{
				SetConsoleTextAttribute(hConsole, 25);
			}
			for (int i = 0; i < Weg.size() - 2; i++)
			{
				gotoxy(Weg[i][0], Weg[i][1]); std::cout << " ";
			}
			SetConsoleTextAttribute(hConsole, 15);
			break;
		case 'm':
		case 'M':
			if (Mittig == true)
				break;
			aufgedeckt2 = !aufgedeckt2;
			SetConsoleTextAttribute(hConsole, 0);
			if (aufgedeckt2 == true)
			{
				SetConsoleTextAttribute(hConsole, 42);
			}
			for (int i = 0; i < Gelaufen.size() - 2; i++)
			{
				gotoxy(Gelaufen[i][0], Gelaufen[i][1]); std::cout << " ";
			}
			SetConsoleTextAttribute(hConsole, 15);
			break;
		}
		if (moved == true)
		{
			Markieren(x, y, Gelaufen, Ziel, Key, GKey, Door, Weg, aufgedeckt, Sichtweite, ZAZ, Mittig);
		}
	}
	return true;
}

void Menu(short &x, short &y, short &breite, short &hoehe, short &Sichtweite, bool &entfernt, bool &ZielAnzeigen, bool &Mitte)
{
	int yy = 45, xx = 3, xx2 = 1, xx3 = 2;
	std::string eingabe = "";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	gotoxy(100, 45); std::cout << "Startposition: "; SetConsoleTextAttribute(hConsole, 4); std::cout << "[Zuf\204llig] " << "[Mitte] "; SetConsoleTextAttribute(hConsole, 10); std::cout << "[Entferntester Punkt]";
	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(100, 47); std::cout << "Ziel anzeigen: "; SetConsoleTextAttribute(hConsole, 10); std::cout << "[YES] "; SetConsoleTextAttribute(hConsole, 4); std::cout << "[NO] ";
	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(100, 49); std::cout << "Sichtweite: "; SetConsoleTextAttribute(hConsole, 15); std::cout << Sichtweite;
	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(100, 51); std::cout << "Spielfeldbreite: "; SetConsoleTextAttribute(hConsole, 15); std::cout << breite;
	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(100, 53); std::cout << "Spielfeldh\224he: "; SetConsoleTextAttribute(hConsole, 15); std::cout << hoehe;
	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(100, 55); std::cout << "Spieler immer Mittig: "; SetConsoleTextAttribute(hConsole, 4); std::cout << "[YES] "; SetConsoleTextAttribute(hConsole, 10); std::cout << "[NO] ";
	while (true)
	{
		if (_kbhit())
		{
			char c = _getch();
			switch (c)
			{
			case 'w':
			case 'W': if (yy > 45) { if (eingabe.size() > 0) { if (yy == 49) { try { Sichtweite = std::stoi(eingabe); } catch (...) { ; } } else if (yy == 51) { try { breite = std::stoi(eingabe); } catch (...) { ; } } else if (yy == 53) { try { hoehe = std::stoi(eingabe); } catch (...) { ; } } } yy -= 2; }
					  break;
			case 's':
			case 'S': if (yy < 55) { if (eingabe.size() > 0) { if (yy == 49) { try { Sichtweite = std::stoi(eingabe); } catch (...) { ; } } else if (yy == 51) { try { breite = std::stoi(eingabe); } catch (...) { ; } } else if (yy == 53) { try { hoehe = std::stoi(eingabe); } catch (...) { ; } } } yy += 2; }
					  break;
			case 'a':
			case 'A': if (xx > 1 && yy == 45) { xx--; }
					  else if (xx2 > 1 && yy == 47) { xx2--; }
					  else if (xx3 > 1 && yy == 55) { xx3--; }
					  break;
			case 'd':
			case 'D': if (xx < 3 && yy == 45) { xx++; }
					  else if (xx2 < 2 && yy == 47) { xx2++; }
					  else if (xx3 < 2 && yy == 55) { xx3++; }
					  break;
			case 13: if (eingabe.size() > 0) { if (yy == 49) { try { Sichtweite = std::stoi(eingabe); } catch (...) { ; } } else if (yy == 51) { try { breite = std::stoi(eingabe); } catch (...) { ; } } else if (yy == 53) { try { hoehe = std::stoi(eingabe); } catch (...) { ; } } }
					 break;
			default: if (yy > 47 && eingabe.size() < 3) { eingabe += c; }
					 break;
			}
			if (c == 'w' || c == 'W' || c == 's' || c == 'S' || c == 13)
			{
				eingabe = "";
				SetConsoleTextAttribute(hConsole, 4 + (yy == 45 ? 6 : 0));
				gotoxy(100, 45); std::cout << "Startposition: ";
				SetConsoleTextAttribute(hConsole, 4 + (yy == 47 ? 6 : 0));
				gotoxy(100, 47); std::cout << "Ziel anzeigen: ";
				SetConsoleTextAttribute(hConsole, 4 + (yy == 49 ? 6 : 0));
				gotoxy(100, 49); std::cout << "Sichtweite: ";
				SetConsoleTextAttribute(hConsole, 4 + (yy == 51 ? 6 : 0));
				gotoxy(100, 51); std::cout << "Spielfeldbreite: ";
				SetConsoleTextAttribute(hConsole, 4 + (yy == 53 ? 6 : 0));
				gotoxy(100, 53); std::cout << "Spielfeldh\224he: ";
				SetConsoleTextAttribute(hConsole, 4 + (yy == 55 ? 6 : 0));
				gotoxy(100, 55); std::cout << "Spieler immer Mittig: ";

				SetConsoleTextAttribute(hConsole, 15);
				if (breite > 237)
					breite = 237;
				if (hoehe > 125)
					breite = 125;
				if (breite < 15)
					breite = 15;
				if (hoehe < 15)
					hoehe = 15;
				if (Sichtweite > 20)
					Sichtweite = 20;
				gotoxy(112, 49); std::cout << "   "; gotoxy(112, 49); std::cout << Sichtweite;
				gotoxy(117, 51); std::cout << "   "; gotoxy(117, 51); std::cout << breite;
				gotoxy(115, 53); std::cout << "   "; gotoxy(115, 53); std::cout << hoehe;
				if (Sichtweite == 0)
				{
					xx3 = 2;
					SetConsoleTextAttribute(hConsole, 4 + (xx3 == 1 ? 6 : 0));
					gotoxy(122, 55); std::cout << "[YES] ";
					SetConsoleTextAttribute(hConsole, 4 + (xx3 == 2 ? 6 : 0));
					gotoxy(127, 55); std::cout << "[NO] ";
				}
			}
			else if (c == 'a' || c == 'A' || c == 'd' || c == 'D')
			{
				if (yy == 45)
				{
					SetConsoleTextAttribute(hConsole, 4 + (xx == 1 ? 6 : 0));
					gotoxy(115, 45); std::cout << "[Zuf\204llig] ";
					SetConsoleTextAttribute(hConsole, 4 + (xx == 2 ? 6 : 0));
					gotoxy(126, 45); std::cout << "[Mitte] ";
					SetConsoleTextAttribute(hConsole, 4 + (xx == 3 ? 6 : 0));
					gotoxy(134, 45); std::cout << "[Entferntester Punkt]";
				}
				else if (yy == 47)
				{
					SetConsoleTextAttribute(hConsole, 4 + (xx2 == 1 ? 6 : 0));
					gotoxy(115, 47); std::cout << "[YES] ";
					SetConsoleTextAttribute(hConsole, 4 + (xx2 == 2 ? 6 : 0));
					gotoxy(120, 47); std::cout << "[NO] ";
					if (xx2 == 1)
					{
						xx3 = 2;
						SetConsoleTextAttribute(hConsole, 4 + (xx3 == 1 ? 6 : 0));
						gotoxy(122, 55); std::cout << "[YES] ";
						SetConsoleTextAttribute(hConsole, 4 + (xx3 == 2 ? 6 : 0));
						gotoxy(127, 55); std::cout << "[NO] ";
					}
				}
				else if (yy == 55)
				{
					SetConsoleTextAttribute(hConsole, 4 + (xx3 == 1 ? 6 : 0));
					gotoxy(122, 55); std::cout << "[YES] ";
					SetConsoleTextAttribute(hConsole, 4 + (xx3 == 2 ? 6 : 0));
					gotoxy(127, 55); std::cout << "[NO] ";
					if (xx3 == 1)
					{
						xx2 = 2;
						SetConsoleTextAttribute(hConsole, 4 + (xx2 == 1 ? 6 : 0));
						gotoxy(115, 47); std::cout << "[YES] ";
						SetConsoleTextAttribute(hConsole, 4 + (xx2 == 2 ? 6 : 0));
						gotoxy(120, 47); std::cout << "[NO] ";
						if (Sichtweite == 0)
						{
							Sichtweite = 5;
							SetConsoleTextAttribute(hConsole, 15);
							gotoxy(112, 49); std::cout << "   "; gotoxy(112, 49); std::cout << Sichtweite;
						}
					}
				}
			}
			if (c == 27)
			{
				break;
			}
		}
	}
	switch (xx)
	{
	case 1: x = rand() % (breite - 1) + 1; y = rand() % (hoehe - 1) + 1;
		break;
	case 2: x = breite / 2; y = hoehe / 2;
		break;
	case 3: entfernt = true;
		break;
	}
	if (xx2 == 2)
	{
		ZielAnzeigen = false;
	}
	if (xx3 == 1)
	{
		Mitte = true;
	}
	system("CLS");
}

int main()
{
	printf("\e[?25l");
	SetConsoleTitle(L"Labyrinth");

	HWND hwnd = FindWindow(NULL, L"Labyrinth");

	ShowWindow(hwnd, SW_MAXIMIZE);
	Sleep(100);
	int sek = clock();
	srand(sek);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::vector<std::array<short, 2>> Gelaufen;
	std::vector<std::vector<std::array<short, 2>>> ExacteWege;
	while (true)
	{
		short x = 115, y = 50, b = 237, h = 125, s = 5;
		bool entfernt = false, ZAZ = true, Mittig = false, gewonnen = false;
		for (int i = 0; i < 237; i++)
		{
			for (int j = 0; j < 125; j++)
			{
				Felder[i][j] = 0;
			}
		}
		Gelaufen.clear();
		ExacteWege.clear();
		ExacteWege.push_back(std::vector<std::array<short, 2>> { {x, y} });
		Menu(x, y, b, h, s, entfernt, ZAZ, Mittig);
		Felder[x][y] = 1;
		GenerateMap(h, b, x, y, 1, ExacteWege);
		std::array<short, 2> Ziel = ExacteWege[0][ExacteWege[0].size() - 1];
		if (entfernt == true)
		{
			for (int i = 0; i < 237; i++)
			{
				for (int j = 0; j < 125; j++)
				{
					if (Felder[i][j] == 1)
					{
						if (sqrt((Ziel[0] - i) * (Ziel[0] - i) + (Ziel[1] - j) * (Ziel[1] - j)) > sqrt((Ziel[0] - x) * (Ziel[0] - x) + (Ziel[1] - y) * (Ziel[1] - y)))
						{
							x = i; y = j;
						}
					}
				}
			}
		}
		int* Key = new int[2];
		bool GotKey = false;
		std::array<short, 2> Door;
		int zahl = rand() % 10000;
		Key[0] = Door[0] = 0;
		while (zahl > 0)
		{
			for (int i = 0; i < 237; i++)
			{
				for (int j = 0; j < 125; j++)
				{
					if (Felder[i][j] == 1)
					{
						zahl -= 1;
						if (zahl <= 0)
						{
							Key[0] = i;
							Key[1] = j;
							break;
						}
					}
				}
				if (Key[0] != 0)
					break;
			}
		}
		zahl = rand() % 10000;
		while (zahl > 0)
		{
			for (int i = 0; i < 237; i++)
			{
				for (int j = 0; j < 125; j++)
				{
					if (Felder[i][j] == 1)
					{
						zahl -= 1;
						if (zahl <= 0)
						{
							Door = { (short)i, (short)j };
							break;
						}
					}
				}
				if (Door[0] != 0)
					break;
			}
		}
		if (s == 0)
		{
			SetConsoleTextAttribute(hConsole, 72);
			for (int i = 0; i < 237; i++)
			{
				for (int j = 0; j < 125; j++)
				{
					if (Felder[i][j] == 2 || Felder[i][j] == 0)
					{
						gotoxy(i, j); std::cout << " ";
					}
				}
			}
			SetConsoleTextAttribute(hConsole, 15);
			for (int i = 0; i < 237; i++)
			{
				for (int j = 0; j < 125; j++)
				{
					if (Felder[i][j] == 1)
					{
						gotoxy(i, j); std::cout << " ";
					}
				}
			}
		}
		if (ZAZ == true)
		{
			gotoxy(Ziel[0], Ziel[1]); std::cout << "o";
			gotoxy(x, y); std::cout << "x";
		}
		while (gewonnen == false)
		{
			if (Bewegen(x, y, ExacteWege[0], Gelaufen, Ziel, (int*)Key, GotKey, Door, s, ZAZ, Mittig) == false)
			{
				break;
			}
			if (GotKey == false)
			{
				if (x == Key[0] && y == Key[1])
				{
					GotKey = true;
					delete[] Key;
				}
			}
			if (x == Door[0] && y == Door[1] && GotKey == true)
			{
				gewonnen = true;
			}
			if (x == Ziel[0] && y == Ziel[1])
				gewonnen = true;
		}
		SetConsoleTextAttribute(hConsole, 72);
		for (int i = 0; i < 237; i++)
		{
			for (int j = 0; j < 125; j++)
			{
				if (Felder[i][j] == 2 || Felder[i][j] == 0)
				{
					gotoxy(i, j); std::cout << " ";
				}
			}
		}
		SetConsoleTextAttribute(hConsole, 15);
		for (int i = 0; i < 237; i++)
		{
			for (int j = 0; j < 125; j++)
			{
				if (Felder[i][j] == 1)
				{
					gotoxy(i, j); std::cout << " ";
				}
			}
		}
		/*
		SetConsoleTextAttribute(hConsole, 25);
		for (int i = 0; i < ExacteWege[0].size() - 2; i++)
		{
			gotoxy(ExacteWege[0][i][0], ExacteWege[0][i][1]); std::cout << " ";
		}
		*/
		SetConsoleTextAttribute(hConsole, 42);
		for (int i = 0; i < Gelaufen.size() - 2; i++)
		{
			gotoxy(Gelaufen[i][0], Gelaufen[i][1]); std::cout << " ";
		}
		SetConsoleTextAttribute(hConsole, 15);
		gotoxy(Door[0], Door[1]); std::cout << "O";
		gotoxy(x, y); std::cout << "x";
		gotoxy(Ziel[0], Ziel[1]); std::cout << "o";
		if (GotKey == false)
		{
			SetConsoleTextAttribute(hConsole, 102);
			gotoxy(Key[0], Key[1]); std::cout << " ";
		}
		SetConsoleTextAttribute(hConsole, 15);
		_getch();
		system("CLS");
		if (gewonnen == true)
		{
			gotoxy(95, 50); std::cout << "Herzlichen Glueckwunsch, du hast das Ziel erreicht!!!";
			gotoxy(108, 52); std::cout << "Press Esc to Exit";
		}
		else
		{
			gotoxy(95, 50); std::cout << "Du hast das Spiel abgebrochen";
			gotoxy(100, 52); std::cout << "Press Esc to Exit";
		}
		char c = _getch();
		if (c == 27)
			break;
		system("CLS");
	}
}
