#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <algorithm>
#include <io.h>
using namespace std;

enum Color
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown,
	LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, esc = 27 };

void setCursor(int x, int y)
{
	COORD myCoords = { x,y };
	SetConsoleCursorPosition(hStdOut, myCoords);
}

struct User
{
	char login[20];
	char password[20];
	int score = 0;
};

struct Card
{
	int mast;
	int nominal;
};

int X, Y;

char NominalFunc(Card karta[], int index)
{
	if (karta[index].nominal == 6)
	{
		return '6';
	}
	else if (karta[index].nominal == 7)
	{
		return '7';
	}
	else if (karta[index].nominal == 8)
	{
		return '8';
	}
	else if (karta[index].nominal == 9)
	{
		return '9';
	}
	else if (karta[index].nominal == 10)
	{
		return '1';
	}
	else if (karta[index].nominal == 11)
	{
		return 'V';
	}
	else if (karta[index].nominal == 12)
	{
		return 'D';
	}
	else if (karta[index].nominal == 13)
	{
		return 'K';
	}
	else if (karta[index].nominal == 14)
	{
		return 'T';
	}
}

void printCard(char mas[][7], const int row, const int col, char symbol)
{
	mas[3][3] = symbol;
	for (size_t i = 0; i < row; i++)
	{
		setCursor(X + i, Y);
		for (size_t j = 0; j < col; j++)
		{
			setCursor(X + i, Y + j);
			if ((j == 0 || j == col - 1) || (i == 0 || i == row - 1))
			{
				setColor(Magenta, Magenta);
			}
			else if (i == 3 && j == 3)
			{
				setColor(Magenta, Yellow);
			}
			else
			{
				setColor(Yellow, Yellow);
			}
			cout << mas[i][j];
		}
		cout << endl;
	}
	setColor(White, Black);
}

void printCard(char mas[][7], const int r, const int c, Color color)
{
	for (size_t i = 0; i < r; i++)
	{
		setCursor(X + i, Y);
		for (size_t j = 0; j < c; j++)
		{
			if ((i == 0 || i == r - 1) || (j == 0 || j == c - 1))
			{
				setColor(color, color);
			}
			else if ((i == j && j < r - 2 && j > 1 && i > 1 && i < c - 2) || (i + j == r - 1 && i > 1 && i < r - 2))
			{
				setColor(color, color);
			}
			else
			{
				setColor(White, White);
			}
			setCursor(X + i, Y + j);
			cout << mas[i][j];
		}
		cout << endl;
	}
	setColor(White, Black);
}

void printCard(char mas[][5], int r, int c, Color color)
{
	for (size_t i = 0; i < r; i++)
	{
		setCursor(X + i, Y);
		for (size_t j = 0; j < c; j++)
		{
			if ((i == 0 || i == r - 1) || (j == 0 || j == c - 1))
			{
				setColor(color, color);
			}
			else
			{
				setColor(White, White);
			}
			setCursor(X + i, Y + j);
			cout << mas[i][j];
		}
		cout << endl;

	}
	setColor(White, Black);
}

void printCard(char mas[][7], Card arr[], int r, int c, int index, Color color)
{
	Color color_2 = Yellow;

	mas[3][3] = NominalFunc(arr, index);
	if (mas[3][3] == '1')
	{
		mas[4][3] = '0';
	}

	mas[1][1] = arr[index].mast;
	mas[1][5] = arr[index].mast;
	mas[5][1] = arr[index].mast;
	mas[5][5] = arr[index].mast;

	if (arr[index].mast == 3 || arr[index].mast == 4)
	{
		color_2 = Red;
	}
	else if (arr[index].mast == 5 || arr[index].mast == 6)
	{
		color_2 = Black;
	}

	for (size_t i = 0; i < r; i++)
	{
		setCursor(X + i, Y);
		for (size_t j = 0; j < c; j++)
		{
			setCursor(X + i, Y + j);
			if ((i == 0 || i == r - 1) || (j == 0 || j == c - 1))
			{
				setColor(color, color);
			}
			else if ((i == 1 && j == 1) || (i == 5 && j == 5) || (i == 1 && j == 5) || (i == 5 && j == 1) || (i == 3 && j == 3) || (i == 4 && j == 3 && arr[index].nominal == 10))
			{
				setColor(color_2, White);
			}
			else
			{
				setColor(White, White);
			}
			cout << mas[i][j];
		}
		cout << endl;
	}
	setColor(White, Black);
}

void ChangeKoord(int na_skolko_X, int na_skolko_Y = 0)
{
	X += na_skolko_X;
	Y += na_skolko_Y;
	setCursor(X, Y);
}

void MenuFunc(string mas[], const int size, int menu_point)
{
	for (size_t i = 0; i < size; i++)
	{
		setCursor(X, Y + i);
		if (i == menu_point)
		{
			setColor(Black, Yellow);
		}
		else
		{
			setColor(White, Black);
		}
		cout << mas[i];
	}
	setColor(White, Black);
}

void DelFunc(string mas[], const int size)
{
	for (size_t i = 0; i < size; i++)
	{
		setCursor(X, Y + i);
		setColor(Black, Black);
		cout << mas[i];
	}
	setColor(White, Black);
}

void DelFunc(const int size, char mas[])
{
	for (size_t i = 0; i < size; i++)
	{
		setCursor(X + i, Y);
		setColor(Black, Black);
		cout << mas[i] << endl;
	}
	setColor(White, Black);
}

void DelFunc()
{
	setColor(White, White);
	cout << "22";
}

void DelFunc(char mas[][7], const int r, const int c)
{
	for (size_t i = 0; i < r; i++)
	{
		setCursor(X + i, Y);
		for (size_t j = 0; j < c; j++)
		{
			setCursor(X + i, Y + j);
			setColor(Black, Black);
			cout << mas[i][j];
		}
		cout << endl;
	}
	setColor(White, Black);
}

void DelFunc(char mas[][5], const int r, const int c)
{
	for (size_t i = 0; i < r; i++)
	{
		setCursor(X + i, Y);
		for (size_t j = 0; j < c; j++)
		{
			setCursor(X + i, Y + j);
			setColor(Black, Black);
			cout << mas[i][j];
		}
		cout << endl;
	}
	setColor(White, Black);
}

bool isBigger(Card a, Card b)
{
	return a.nominal < b.nominal;
}

int index;

int PodkinutComp(Card hand[], Card stol[], int count, int index_stol)
{
	index = -1;
	for (size_t i = 0; i < count; i++)
	{
		for (size_t j = 0; j <= index_stol; j++)
		{
			if (hand[i].nominal == stol[j].nominal)
			{
				index = i;
				break;
			}
		}
	}
	return index;
}

bool PodkinutPlayer(Card hand[], Card stol[], int index, int index_stol)
{
	for (size_t i = 0; i <= index_stol; i++)
	{
		if (hand[index].nominal == stol[i].nominal)
		{
			return true;
			break;
		}
	}
	return false;
}

int Pobit(Card hand[], Card stol[], Card pobit[], int count, int index_stol, Card kozyr)
{
	int kol = 0;
	index = -1;
	for (size_t i = 0, j = 0; i < count; i++)
	{
		if (hand[i].mast == stol[index_stol].mast)
		{
			pobit[j] = hand[i];
			kol++;
			j++;
		}
	}

	if (kol > 1)
	{
		sort(pobit, pobit + kol, isBigger);
	}

	if (kol)
	{
		for (size_t i = 0; i < kol; i++)
		{
			if (pobit[i].nominal > stol[index_stol].nominal)
			{
				for (size_t j = 0; j < count; j++)
				{
					if (hand[j].mast == pobit[i].mast && hand[j].nominal == pobit[i].nominal)
					{
						index = j;
						break;
					}
				}
				break;
			}
		}
	}

	if (index == -1)
	{
		kol = 0;

		if (stol[index_stol].mast != kozyr.mast)
		{
			for (size_t i = 0, j = 0; i < count; i++)
			{
				if (hand[i].mast == kozyr.mast)
				{
					pobit[j] = hand[i];
					kol++;
					j++;
				}
			}

			if (kol > 1)
			{
				sort(pobit, pobit + kol, isBigger);
			}

			if (kol)
			{
				for (size_t i = 0; i < count; i++)
				{
					if (hand[i].mast == pobit[0].mast && hand[i].nominal == pobit[0].nominal)
					{
						index = i;
					}
				}
			}
		}
	}
	return index;
}

void printZastavka(char mas[][7], const int r, const int c, char simvol, int spat = 0)
{
	X = 35, Y = 1;
	simvol = 'D';
	printCard(mas, r, c, simvol);
	ChangeKoord(8, 2);
	Sleep(spat);
	simvol = 'U';
	printCard(mas, r, c, simvol);
	ChangeKoord(8, -2);
	Sleep(spat);
	simvol = 'R';
	printCard(mas, r, c, simvol);
	ChangeKoord(8, 2);
	Sleep(spat);
	simvol = 'A';
	printCard(mas, r, c, simvol);
	ChangeKoord(8, -2);
	Sleep(spat);
	simvol = 'K';
	printCard(mas, r, c, simvol);
	Sleep(spat);
}

template <typename T>
void printParam(T mas[], const int size)
{
	for (size_t i = 0; i < size; i++)
	{
		setColor(Yellow, Black);
		cout << mas[i];
	}
	setColor(White, Black);
}

void CopyMas(Card hand[], int count, int index)
{
	for (size_t i = index; i < count; i++)
	{
		hand[i] = hand[i + 1];
	}
}

int Koord_X_hand(int index, int step = 10)
{
	X = index * step + 30;
	return X;
}

int Koord_X_stol(int index)
{
	int indexMas[12] = { 20,24,32,36,44,48,56,60,68,72,80,84 };
	return indexMas[index];
}

int Koord_Y_stol(int index)
{
	if (index % 2 == 0)
	{
		Y = 14;
	}
	else if (index % 2 != 0)
	{
		Y = 17;
	}
	return Y;
}

int KlacKlac(string arr[], const int size)
{
	int menupoint = 0;
	int key;
	do
	{
		MenuFunc(arr, size, menupoint);
		key = _getch();
		if (key == Down)
		{
			if (menupoint < size)
			{
				menupoint++;
			}
			if (menupoint == size)
			{
				menupoint = 0;
			}
		}
		if (key == Up)
		{
			if (menupoint >= 0)
			{
				menupoint--;
			}
			if (menupoint == -1)
			{
				menupoint = size - 1;
			}
		}
		if (key == Enter)
		{
			return menupoint;
		}
	} while (key != esc);
}

int KlacKlac(Card arr[], const int size, int& menupoint)
{
	int key;
	do
	{
		key = _getch();
		if (key == Right)
		{
			if (menupoint < size)
			{
				menupoint++;
			}
			if (menupoint == size)
			{
				menupoint = 0;
			}
		}
		else if (key == Left)
		{
			if (menupoint >= 0)
			{
				menupoint--;
			}
			if (menupoint == -1)
			{
				menupoint = size - 1;
			}
		}
		else if (key == Enter)
		{
			menupoint = 66;
		}
		else if (key == esc)
		{
			menupoint = 99;
		}
		return menupoint;
	} while (key != esc);
}

int SourceCard(Card hand[], int count, Card kozyr, int min)
{
	index = -1;
	for (size_t i = 0; i < count; i++)
	{
		if (hand[i].mast == kozyr.mast && hand[i].nominal == min)
		{
			index = i;
			break;
		}
	}
	return index;
}

void DelCard(char mas[][7], const int r, const int c, int count, int shag)
{
	for (size_t i = 0; i <= count; i++)
	{
		setCursor(X, Y);
		DelFunc(mas, r, c);
		X += shag;
	}
}

void cardPrint(char mas[][7], Card hand[], const int r, const int c, Color color, int count, int shag)
{
	for (size_t i = 0; i < count; i++)
	{
		setCursor(X, Y);
		printCard(mas, hand, r, c, i, color);
		X += shag;
	}
}

void cardPrint(char mas[][7], const int r, const int c, Color color, int count, int shag)
{
	for (size_t i = 0; i < count; i++)
	{
		setCursor(X, Y);
		printCard(mas, r, c, color);
		X += shag;
	}
}

bool isUser(FILE* file, User user, User& temp)
{
	int size, count;
	if (file != nullptr)
	{
		size = _filelength(_fileno(file));
		if (size > 0)
		{
			count = size / sizeof(User);
			for (size_t i = 0; i < count; i++)
			{
				fread(&temp, sizeof(User), 1, file);
				if (!_stricmp(temp.login, user.login))
				{
					return true;
				}
			}
			return false;
		}
	}
}

bool isPass(FILE* file, User user, User& temp)
{
	int size, count;
	if (file != nullptr)
	{
		size = _filelength(_fileno(file));
		if (size > 0)
		{
			count = size / sizeof(User);
			for (size_t i = 0; i < count; i++)
			{
				fread(&temp, sizeof(User), 1, file);
				if (!strcmp(temp.password, user.password))
				{
					return true;
				}
			}
			return false;
		}
	}
}

void ClearPole(char mas[][7], const int r, const int c)
{
	X = 20, Y = 14;
	for (size_t i = 0; i < 10; i++)
	{
		setCursor(X, Y);
		DelFunc(mas, r, c);
		X += r;
	}

	X = 20, Y = 17;
	for (size_t i = 0; i < 10; i++)
	{
		setCursor(X, Y);
		DelFunc(mas, r, c);
		X += r;
	}
}

int ShagFunc(int chislo)
{
	int step;
	if (chislo < 7)
	{
		step = 10;
	}
	else if (chislo > 6 && chislo < 10)
	{
		step = 8;
	}
	else
	{
		step = 5;
	}
	return step;
}

void SortMas(Card mas[], Card mas_temp[], const int size, int count, Card kozyrnaya)
{
	int countt = 0, koll = 0;
	bool check;

	for (size_t i = 0; i < count; i++)
	{
		mas_temp[i] = mas[i];
	}

	for (size_t i = 0, j = 0; i < count; i++)
	{
		if (mas_temp[i].mast == 3)
		{
			mas[j] = mas_temp[i];
			j++;
			countt++;
		}
	}

	if (countt > 1)
	{
		do
		{
			check = false;
			for (size_t i = 0; i < countt - 1; i++)
			{
				if (mas[i].nominal > mas[i + 1].nominal)
				{
					check = true;
					swap(mas[i], mas[i + 1]);
				}
			}
		} while (check);

	}

	koll = countt;
	countt = 0;
	for (size_t i = 0, j = koll; i < count; i++)
	{
		if (mas_temp[i].mast == 4)
		{
			mas[j] = mas_temp[i];
			j++;
			countt++;
		}
	}
	if (countt > 1)
	{
		do
		{
			check = false;
			for (size_t i = koll; i < countt + koll - 1; i++)
			{
				if (mas[i].nominal > mas[i + 1].nominal)
				{
					check = true;
					swap(mas[i], mas[i + 1]);
				}
			}
		} while (check);

	}

	koll += countt;
	countt = 0;
	for (size_t i = 0, j = koll; i < count; i++)
	{
		if (mas_temp[i].mast == 5)
		{
			mas[j] = mas_temp[i];
			j++;
			countt++;
		}
	}
	if (countt > 1)
	{
		do
		{
			check = false;
			for (size_t i = koll; i < countt + koll - 1; i++)
			{
				if (mas[i].nominal > mas[i + 1].nominal)
				{
					check = true;
					swap(mas[i], mas[i + 1]);
				}
			}
		} while (check);
	}

	koll += countt;
	countt = 0;
	for (size_t i = 0, j = koll; i < count; i++)
	{
		if (mas_temp[i].mast == 6)
		{
			mas[j] = mas_temp[i];
			j++;
			countt++;
		}
	}
	if (countt > 1)
	{
		do
		{
			check = false;
			for (size_t i = koll; i < countt + koll - 1; i++)
			{
				if (mas[i].nominal > mas[i + 1].nominal)
				{
					check = true;
					swap(mas[i], mas[i + 1]);
				}
			}
		} while (check);
	}

	do
	{
		check = false;
		for (size_t i = 0; i < count - 1; i++)
		{
			if (mas[i].mast == kozyrnaya.mast && mas[i + 1].mast != kozyrnaya.mast)
			{
				swap(mas[i], mas[i + 1]);
				check = true;
			}
		}
	} while (check);
}

void main()
{

	srand(time(NULL));

	int const row = 7, col = 7, row_2 = 11, col_2 = 5, size_menu = 4, size_param = 2, max_card = 36, otboy = 12, leaders = 6;
	char simvol = '*', card[row][col], card_2[row_2][col_2], points[size_menu]{ '.','.','.' }, status = 'n';
	int punktmenu, size_users, count_parol = 0, count_login = 0, nominal, mast = 3, kolodaSize, temp_nominal, KEY = 0, size;
	int kol_bukv = 32, index_karty, min_pl = 15, min_comp = 15, count_player = 6, count_comp = 6, kol, kolich, count_leaders;
	int kol_kozyr = 0, hand_player_Y = 30, hand_comp_Y = 1, shag_player = 10, shag_comp = 10, punkt_choice, size_leaders, count;
	int ostatok, index_vkolode = 0, up_card = 26, hand_X = 30, kol_otboi = 0, kol_podkin, menu_point, index_table;
	bool isCorrect = true, key, end = false, create = false, all_end = false, play, player, computer, verno, check;
	string menu[size_menu]{ "New account", "Log in", "Leaders table", "Exit" };
	string parametr_1[size_param]{ "24 cards", "36 cards" };
	string parametr_2[size_param]{ "Green Shirt", "Magenta Shirt" }, parametry[size_param]{ "Select ", "options:" };
	Card Koloda[max_card], hand_comp[max_card], hand_player[max_card], hand_player_temp[max_card], hand_comp_temp[max_card];
	Card kozyr, otboi[otboy], table[max_card], kozyr_player[max_card], kozyr_comp[max_card], pobit[max_card];
	FILE* f, * f_temp, * f_temp_2;
	User user, temp, leader_mas[leaders];
	Color color;

	do
	{
		// отрисовка заставки
		printZastavka(card, row, col, simvol, 400);
		do
		{
			// меню
			X = 47, Y = 12;
			setCursor(X, Y);
			printParam(parametry, size_param);

			// выбор пункта меню
			setColor(White, Black);
			ChangeKoord(0, 2);
			punktmenu = KlacKlac(menu, size_menu);
			DelFunc(menu, size_menu);
			ChangeKoord(8, -2);
			DelFunc(parametry, size_param);
			ChangeKoord(-8);

			// регистрация, автризация
			if (!punktmenu)
			{
				cout << "Registration\n"; //регистрация
				errno_t error = fopen_s(&f, "Users.txt", "r");
				if (!error)
				{
					size_users = _filelength(_fileno(f));
					if (size_users > 0)
					{
						do
						{
							fclose(f);
							fopen_s(&f, "Users.txt", "r");
							do
							{
								key = true;
								cout << "\nEnter login (only small english without spaces):\n";
								cin.getline(user.login, 20);
								if (strlen(user.login) == 0)
								{
									key = false;
								}
								if (key)
								{
									for (size_t i = 0; i < strlen(user.login); i++)
									{
										if (!isalpha(user.login[i]))
										{
											key = false;
											break;
										}
									}
								}
							} while (!key);
							if (isUser(f, user, temp))
							{
								isCorrect = false;
								cout << "\nLogin is busy!\n";
								cout << "Enter other login!\n";
							}
							else
							{
								isCorrect = true;
								fclose(f);
							}
						} while (!isCorrect);
					}
					else
					{
						key = false;
						fclose(f);
					}
				}
				else
				{
					key = false;
				}
				if (!key)
				{
					do
					{
						key = true;
						ChangeKoord(15, 1);
						cout << "\nEnter login (only small english without spaces):\n";
						cin.getline(user.login, 20);
						if (strlen(user.login) == 0)
						{
							key = false;
						}
						if (key)
						{
							for (size_t i = 0; i < strlen(user.login); i++)
							{
								if (!isalpha(user.login[i]))
								{
									key = false;
									break;
								}
							}
						}
					} while (!key);
				}
				do
				{
					key = true;
					cout << "\nEnter password (only small english or numbers without spaces):\n";
					cin.getline(user.password, 20);
					if (strlen(user.password) == 0)
					{
						key = false;
					}
					if (key)
					{
						for (size_t i = 0; i < strlen(user.password); i++)
						{
							if (!isalpha(user.password[i]) && !isdigit(user.password[i]))
							{
								key = false;
								break;
							}
						}
					}
				} while (!key);
				end = true;
				cout << "\nRegistration is correct!\n";
				status = 'r';
				end = false;
				Sleep(1000);
			}
			else if (punktmenu == 1) //авторизация
			{
				cout << "Autorization\n";
				errno_t error = fopen_s(&f, "Users.txt", "r");
				if (!error)
				{
					size_users = _filelength(_fileno(f));
					if (size_users > 0)
					{
						do
						{
							fclose(f);
							fopen_s(&f, "Users.txt", "r");
							do
							{
								count_parol = 0;
								key = true;
								cout << "\nEnter login (only small english without spaces):\n";
								cin.getline(user.login, 20);
								if (strlen(user.login) == 0)
								{
									key = false;
								}
								if (key)
								{
									for (size_t i = 0; i < strlen(user.login); i++)
									{
										if (!isalpha(user.login[i]))
										{
											key = false;
											break;
										}
									}
								}
							} while (!key);
							if (isUser(f, user, temp))
							{
								isCorrect = true;
								cout << "\nLogin is found!\n";
								do
								{
									fclose(f);
									fopen_s(&f, "Users.txt", "r");
									do
									{
										fclose(f);
										fopen_s(&f, "Users.txt", "r");
										key = true;
										cout << "\nEnter password (only small english or numbers without spaces):\n";
										cin.getline(user.password, 20);
										if (strlen(user.login) == 0)
										{
											key = false;
										}
										if (key)
										{
											for (size_t i = 0; i < strlen(user.password); i++)
											{
												if (!isalpha(user.password[i]) && !isdigit(user.password[i]))
												{
													key = false;
													break;
												}
											}
										}
									} while (!key);
									if (isPass(f, user, temp))
									{
										isCorrect = true;
										cout << "\nPassword is true!\n";
										cout << "Autorization is correct!\n";
										status = 'a';
										end = false;
										Sleep(1000);
									}
									else
									{
										isCorrect = false;
										cout << "\nPassword is false!\n";
										count_parol++;
										if (count_parol != 3)
										{
											cout << "Try again!\n";
										}
										count_login = 0;
										if (count_parol == 3)
										{
											end = true;
											break;
										}
									}
								} while (!isCorrect);
							}
							else
							{
								isCorrect = false;
								cout << "\nLogin is not found!\n";
								count_login++;
								end = true;
								if (count_login != 3)
								{
									cout << "Enter other login!\n";
								}
								count_parol = 0;
								if (count_login == 3)
								{
									end = true;
									break;
								}
							}
						} while (!isCorrect);
					}
					else
					{
						create = true;
						end = true;
						fclose(f);
					}
				}
				else
				{
					create = true;
					end = true;
				}
				if (create)
				{
					do
					{
						key = true;
						cout << "\nEnter login (only small english without spaces):\n";
						cin.getline(user.login, 20);
						if (strlen(user.login) == 0)
						{
							key = false;
						}
						if (key)
						{
							for (size_t i = 0; i < strlen(user.login); i++)
							{
								if (!isalpha(user.login[i]))
								{
									key = false;
									break;
								}
							}
						}
					} while (!key);
				}
				if (end)
				{
					do
					{
						key = true;
						cout << "\nEnter password (only small english or numbers without spaces):\n";
						cin.getline(user.password, 20);
						if (strlen(user.login) == 0)
						{
							key = false;
						}
						if (key)
						{
							for (size_t i = 0; i < strlen(user.password); i++)
							{
								if (!isalpha(user.password[i]) && !isdigit(user.password[i]))
								{
									key = false;
									break;
								}
							}
						}
					} while (!key);
					if (f != nullptr)
					{
						cout << "\nRegistration is correct!\n";
						status = 'r';
						end = false;
						Sleep(1000);
					}
				}
				if (count_login == 3)
				{
					Sleep(1000);
					system("cls");
					continue;
				}
			}
			else if (punktmenu == 2)
			{
				X = 47, Y = 12;
				setCursor(X, Y);
				DelFunc(parametry, size_param);
				errno_t error = fopen_s(&f_temp, "Users_leaders.txt", "r");
				if (!error)
				{
					size_leaders = _filelength(_fileno(f_temp));
					if (size_leaders > 0)
					{
						count_leaders = size_leaders / sizeof(User);
						/*	fopen_s(&f_temp, "Users_leaders.txt", "r");*/
						for (size_t i = 0; i < count_leaders; i++)
						{
							fread(&leader_mas[i], sizeof(User), 1, f_temp);
						}
					}
					else
					{
						/*fopen_s(&f_temp, "Users_leaders.txt", "r");*/
						for (size_t i = 0; i < count_leaders; i++)
						{
							leader_mas[i].score = -1;
						}
					}
				}
				fclose(f_temp);

				X = 47, Y = 12;
				setCursor(X, Y);
				setColor(Yellow, Black);
				cout << "Leaders table:\n\n";
				setColor(White, Black);
				bool klik;
				do
				{
					klik = false;
					for (size_t i = 0; i < leaders - 1; i++)
					{
						if (leader_mas[i].score < leader_mas[i + 1].score)
						{
							swap(leader_mas[i], leader_mas[i + 1]);
							klik = true;
						}
					}
				} while (klik);

				for (size_t i = 0; i < leaders - 1; i++)
				{
					cout << i + 1 << ") " << leader_mas[i].login << ": " << leader_mas[i].score << endl;
				}

				KEY = _getch();   //получаем числовой код нажатия клавиши
				if (KEY)
				{
					X = 47, Y = 12;
					setCursor(X, Y);
					setColor(Black, Black);
					cout << "Leaders table:\n\n";
					for (size_t i = 0; i < leaders; i++)
					{
						cout << i + 1 << ") " << leader_mas[i].login << ": " << leader_mas[i].score << endl;
					}
					setColor(White, Black);
					end = true;
				}
			}
			else
			{
				system("cls");
				system("pause>>NULL");
				cout << "See you later!\n";
				all_end = true;
			}
		} while (end);

		if (!all_end)
		{
			system("cls");
			//отрисовка заставки
			printZastavka(card, row, col, simvol);

			// меню продолжение //параметры
			ChangeKoord(-20, 11);
			printParam(parametry, size_param);

			ChangeKoord(0, 2);
			punktmenu = KlacKlac(parametr_1, size_param);// первый параметр
			DelFunc(parametr_1, size_param);
			if (punktmenu)
			{
				kolodaSize = 36;
				nominal = 6;
			}
			else
			{
				kolodaSize = 24;
				nominal = 9;
			}

			punktmenu = KlacKlac(parametr_2, size_param);// второй параметр
			DelFunc(parametr_2, size_param);
			if (punktmenu)
			{
				color = Magenta;
			}
			else
			{
				color = Green;
			}

			temp_nominal = nominal;
			for (size_t i = 0; i < kolodaSize; i++) //создаем колоду
			{
				Koloda[i].mast = mast;
				Koloda[i].nominal = nominal++;
				if (nominal == 15)
				{
					mast++;
					nominal = temp_nominal;
				}
			}

			do
			{
				for (size_t i = 0; i < kolodaSize; i++)
				{
					swap(Koloda[rand() % (kolodaSize)], Koloda[rand() % (kolodaSize)]); //перемешиваем колоду
				}

				// игровое поле
				system("cls");
				kozyr = Koloda[kolodaSize - 1];

				for (size_t i = 0; i < count_player; i++)
				{
					hand_player[i] = Koloda[i]; // карты игрока
				}

				SortMas(hand_player, hand_player_temp, max_card, count_player, kozyr);

				for (size_t i = 0, j = count_player; i < count_comp; i++, j++)
				{
					hand_comp[i] = Koloda[j];    // карты компьютера
				}

				X = Koord_X_hand(0), Y = hand_comp_Y;
				for (size_t i = 0; i < count_comp; i++)
				{
					setCursor(X, Y);
					printCard(card, row, col, color);   // печать карт компьютера
					Sleep(200);
					X += shag_comp;
				}

				X = Koord_X_hand(0), Y = hand_player_Y;
				for (size_t i = 0; i < count_player; i++)
				{
					setCursor(X, Y);
					printCard(card, hand_player, row, col, i, color); // печать карт игрока
					Sleep(200);
					X += shag_player;
				}

				index_vkolode = count_comp + count_player;
				ostatok = kolodaSize - index_vkolode;

				Sleep(500);
				// козырь //печать карты
				X = 5, Y = 13;
				setCursor(X, Y);
				printCard(card, Koloda, row, col, kolodaSize - 1, color);

				Sleep(500);
				// колода //печать карты
				X = 3, Y = 11;
				setCursor(X, Y);
				printCard(card_2, row_2, col_2, color);
				Sleep(1000);

				// поиск козырей
				X = 41, Y = 18;
				setCursor(X, Y);
				Sleep(200);
				cout << "Finding the smallest trumps card" << endl;
				Sleep(10);

				ChangeKoord(12, 1);
				printParam(points, size_param);

				X = 41, Y = 18;
				setCursor(X, Y);
				DelFunc(kol_bukv, points);
				ChangeKoord(12, 1);
				DelFunc(count_player, points); //очистка

				for (size_t i = 0, j = 0; i < count_comp; i++)
				{
					if (hand_comp[i].mast == kozyr.mast)
					{
						kozyr_comp[j] = hand_comp[i]; //козыри компьютера
						j++;
						kol_kozyr++;
					}
				}

				// поиск меньшего козыря
				for (size_t i = 0; i < kol_kozyr; i++)
				{
					if (kozyr_comp[i].nominal < min_comp)
					{
						min_comp = kozyr_comp[i].nominal;    //среди козырей компьютера
					}
				}

				kol_kozyr = 0;
				for (size_t i = 0, j = 0; i < count_player; i++)
				{
					if (hand_player[i].mast == kozyr.mast)
					{
						kozyr_player[j] = hand_player[i]; //козыри игрока
						j++;
						kol_kozyr++;
					}
				}

				// поиск меньшего козыря
				for (size_t i = 0; i < kol_kozyr; i++)
				{
					if (kozyr_player[i].nominal < min_pl)
					{
						min_pl = kozyr_player[i].nominal; //среди козырей игрока
					}
				}
				if (min_comp < min_pl)
				{
					play = true;    //нашли козырь //игра началась
					computer = true;
					player = false; // компьютер ходит
					index_karty = SourceCard(hand_comp, count_comp, kozyr, min_comp);
					X = Koord_X_hand(index_karty, shag_comp);
					Y = hand_comp_Y;
					setCursor(X, Y);
					DelFunc(card, row, col); //удаляем карту из руки компьютера
					X = 51, Y = 14;
					setCursor(X, Y);   //переносим на центр стола
					printCard(card, hand_comp, row, col, index_karty, color);
					X = 47, Y = 22;
					setCursor(X, Y);
					cout << "Computer is walking!"; //печать //кто ходит
					Sleep(2000);
					X = 51, Y = 14;
					setCursor(X, Y);
					DelFunc(card, row, col);  //удаляем с центра поля
					X = 47, Y = 22;
					setCursor(X, Y);
					DelFunc(kol_bukv, points);
					X = Koord_X_hand(index_karty, shag_comp);
					Y = hand_comp_Y;
					setCursor(X, Y);                 //печатаем в руке
					printCard(card, row, col, color);
				}
				else if (min_comp > min_pl)
				{
					play = true;      //нашли козырь //игра началась
					player = true;
					computer = false;  // игрок ходит
					index_karty = SourceCard(hand_player, count_player, kozyr, min_pl);
					X = Koord_X_hand(index_karty, shag_player);
					Y = hand_player_Y;
					setCursor(X, Y);
					DelFunc(card, row, col); //удаляем карту из руки компьютера
					X = 51, Y = 14;
					setCursor(X, Y); //печатаем в центре стола
					printCard(card, hand_player, row, col, index_karty, color);
					X = 47, Y = 22;
					setCursor(X, Y);
					cout << "Player is walking!"; //кто ходит
					Sleep(2000);
					X = 51, Y = 14;
					setCursor(X, Y);
					DelFunc(card, row, col); //удаляем с центра стола
					X = 47, Y = 22;
					setCursor(X, Y);
					DelFunc(kol_bukv, points);
					X = Koord_X_hand(index_karty, shag_player); //печатаем в руке игрока
					Y = hand_player_Y;
					setCursor(X, Y);
					printCard(card, hand_player, row, col, index_karty, color);
				}
				else if (min_comp == min_pl)
				{
					play = false;   //игра не начнется 
					system("cls");
					X = 40, Y = 20;
					setCursor(X, Y);
					cout << "No trumps found!"; //козырей не найдено
					ChangeKoord(0, 1);
					cout << "Retake the cards!";
					Sleep(1500);
					system("cls");
				}
			} while (!play);
			// первый ход
			do
			{
				index_table = -1;

				X = 9, Y = 13;
				setCursor(X, Y);
				DelFunc();

				if (ostatok > 1) // остаток карт - печать на колоде
				{
					X = 8, Y = 13;
					setCursor(X, Y);
					setColor(color, White);
					cout << ostatok;
				}

				if (ostatok < 2)  // удаляем колоду(визуал) - остается козырь
				{
					X = 3, Y = 11;
					setCursor(X, Y);
					DelFunc(card_2, row_2, col_2);

					X = 5, Y = 13;
					setCursor(X, Y);
					printCard(card, Koloda, row, col, kolodaSize - 1, color);
				}

				if (ostatok < 1)  // удаляем колоду и козырь(визуал)
				{
					X = 3, Y = 11;
					setCursor(X, Y);
					DelFunc(card_2, row_2, col_2);

					X = 5, Y = 13;
					setCursor(X, Y);
					DelFunc(card, row, col);
				}

				if (player)
				{
					if (!kol_otboi)                  // количество карт, которые можно подкинуть 
					{                                // исходя из количества карт соперника и количества отбоев
						kol_podkin = 5;
					}
					else if (kol_otboi && count_comp >= 6)
					{
						kol_podkin = 6;
					}
					else if (kol_otboi && count_comp < 6)
					{
						kol_podkin = count_comp;
					}

					if (count_comp && count_player)
					{
						menu_point = 0;
						kolich = 0;
						do
						{
							X = hand_X, Y = hand_player_Y;
							punkt_choice = KlacKlac(hand_player, count_player, menu_point); // клацаем
							if (punkt_choice == 66)
							{
								index_table++;
								table[index_table] = hand_player[index_karty]; //вносим в массив стола
								kol_podkin--;

								Y = up_card;
								X = Koord_X_hand(index_karty, shag_player);
								setCursor(X, Y);
								DelFunc(card, row, col); //удаляем со старого места

								X = Koord_X_stol(index_table);
								Y = Koord_Y_stol(index_table);
								setCursor(X, Y); //ставим в середину поля
								printCard(card, hand_player, row, col, index_karty, color);

								CopyMas(hand_player, count_player, index_karty);         // перебираем наш массив карт 
								count_player--;

								X = hand_X, Y = hand_player_Y;
								DelCard(card, row, col, count_player, shag_player);      // удаляем (визуал)

								shag_player = ShagFunc(count_player);                    // с учетом расстояния

								X = hand_X, Y = hand_player_Y;                           // печатаем
								cardPrint(card, hand_player, row, col, color, count_player, shag_player);

							}
							if (kolich && punkt_choice != 66 && punkt_choice != 99)
							{
								Y = up_card;
								X = Koord_X_hand(index_karty, shag_player);
								setCursor(X, Y);
								DelFunc(card, row, col);

								ChangeKoord(0, 4); //ставим на место предыдущую карту
								printCard(card, hand_player, row, col, index_karty, color);
							}
							if (punkt_choice != 66 && punkt_choice != 99)
							{
								index_karty = punkt_choice;
								Y = hand_player_Y;
								X = Koord_X_hand(index_karty, shag_player); //поднимаем выбранную карту
								setCursor(X, Y);
								DelFunc(card, row, col);
								ChangeKoord(0, -4);
								printCard(card, hand_player, row, col, index_karty, color);
								kolich++;
							}
							if (punkt_choice == 99)
							{
								menu_point = 0;
							}
						} while (punkt_choice != 66);
					}
					else
					{
						player = false;
						computer = false;
					}
				}

				if (player)
				{
					do
					{
						index_karty = Pobit(hand_comp, table, pobit, count_comp, index_table, kozyr);  // комп кроет

						if (index_karty >= 0)
						{
							index_table++;
							table[index_table] = hand_comp[index_karty];

							Sleep(1500);
							X = Koord_X_stol(index_table);
							Y = Koord_Y_stol(index_table);
							setCursor(X, Y);
							printCard(card, hand_comp, row, col, index_karty, color); //карта на столе

							CopyMas(hand_comp, count_comp, index_karty);            // перебираем массив карт
							count_comp--;

							X = hand_X, Y = hand_comp_Y;                            // удаляем визуал
							DelCard(card, row, col, count_comp, shag_comp);

							shag_comp = ShagFunc(count_comp);                       // учитывая шаг

							X = hand_X, Y = hand_comp_Y;                            // печатаем карты
							cardPrint(card, row, col, color, count_comp, shag_comp);

							if (!count_comp)
							{
								break;
							}

							if (count_player)
							{
								menu_point = 0;
								kolich = 0;
								do
								{

									if (!kol_podkin && !kol_otboi)
									{
										X = 41, Y = 10;
										setCursor(X, Y);
										cout << "First rebound five cards!" << endl;           // нельзя подкинуть
										X = 41, Y = 10;
										setCursor(X, Y);
										DelFunc(kol_bukv, points);
										break;
									}
									else if (!kol_podkin && kol_otboi)                         // нельзя подкинуть
									{
										X = 41, Y = 10;
										setCursor(X, Y);
										cout << "Rebound six cards!" << endl;
										X = 41, Y = 10;
										setCursor(X, Y);
										DelFunc(kol_bukv, points);
										break;
									}
									else if (kol_podkin)                                       // подкинуть можно
									{
										verno = true;
										X = hand_X, Y = hand_player_Y;
										punkt_choice = KlacKlac(hand_player, count_player, menu_point); // клацаем
										if (punkt_choice == 66)
										{
											verno = false;
											if (PodkinutPlayer(hand_player, table, index_karty, index_table))
											{
												index_table++;
												table[index_table] = hand_player[index_karty]; // вписываем в массив стол
												kol_podkin--;

												Y = up_card;
												X = Koord_X_hand(index_karty, shag_player);
												setCursor(X, Y);
												DelFunc(card, row, col);   // удаляем из руки

												X = Koord_X_stol(index_table);
												Y = Koord_Y_stol(index_table);
												setCursor(X, Y); // печатаем в центр поля
												printCard(card, hand_player, row, col, index_karty, color);

												CopyMas(hand_player, count_player, index_karty);   // перебираем массив
												count_player--;

												X = hand_X, Y = hand_player_Y;
												DelCard(card, row, col, count_player, shag_player); // удаляем визуал

												shag_player = ShagFunc(count_player);               // с учетом шага

												X = hand_X, Y = hand_player_Y;                       // печатаем новый
												cardPrint(card, hand_player, row, col, color, count_player, shag_player);

												verno = true;
												break;
											}
											else
											{
												X = 41, Y = 10;
												setCursor(X, Y);
												cout << "You can't get throw it!" << endl;       // мы не можем подкинуть
												X = 46, Y = 11;
												setCursor(X, Y);
												cout << "Choose another card!";
												Sleep(1500);

												verno = false;
												Y = up_card;
												X = Koord_X_hand(index_karty, shag_player);
												setCursor(X, Y);
												DelFunc(card, row, col);   // удаляем из руки

												ChangeKoord(0, 4);       //опускаем предыдущую карту // печатаем
												printCard(card, hand_player, row, col, index_karty, color);

												menu_point = index_karty;

												X = 41, Y = 10;
												setCursor(X, Y);
												DelFunc(kol_bukv, points);
												X = 41, Y = 11;
												setCursor(X, Y);
												DelFunc(kol_bukv, points);
											}

										}
										if (kolich && punkt_choice != 66)
										{
											Y = up_card;
											X = Koord_X_hand(index_karty, shag_player);  //опускаем предыдущую карту // удаляем
											setCursor(X, Y);
											DelFunc(card, row, col);

											ChangeKoord(0, 4);       //опускаем предыдущую карту // печатаем
											printCard(card, hand_player, row, col, index_karty, color);
										}
										if (punkt_choice == 99)
										{
											break;
										}

										if (punkt_choice != 66)
										{
											index_karty = punkt_choice; //присваиваем клац клац индекс карты
											Y = hand_player_Y;
											X = Koord_X_hand(index_karty, shag_player);
											setCursor(X, Y);
											DelFunc(card, row, col); //поднимаем нашу карту

											ChangeKoord(0, -4);
											printCard(card, hand_player, row, col, index_karty, color);
											kolich++;
										}
									}
								} while (punkt_choice != 66 || !verno);
							}
							else
							{
								break;
							}
						}
						else
						{
							break;
						}
					} while (punkt_choice != 99 && kol_podkin); // продолжаем цикл если удалось подкинуть, компьютер должен отбиться
				}

				if (computer)
				{
					Sleep(2000);
					if (!kol_otboi)
					{
						kol_podkin = 5;
					}
					else if (kol_otboi && count_player >= 6)   // можно подкинуть карт исходя из
					{                                          // количества карт  соперника и количества отбоев
						kol_podkin = 6;
					}
					else if (kol_otboi && count_player < 6)
					{
						kol_podkin = count_player;
					}

					if (count_comp && count_player)
					{
						min_comp = 15;
						for (size_t i = 0; i < count_comp; i++)
						{
							if (hand_comp[i].nominal < min_comp && hand_comp[i].mast != kozyr.mast)
							{
								min_comp = hand_comp[i].nominal; // компьютер ходит с маленькой некозырной
								index_karty = i;
							}
						}
						if (min_comp == 15)
						{
							for (size_t i = 0; i < count_comp; i++)      // если все козыри - с маленькой козырной
							{
								if (hand_comp[i].nominal < min_comp)
								{
									min_comp = hand_comp[i].nominal;
									index_karty = i;
								}
							}
						}

						index_table++;
						table[index_table] = hand_comp[index_karty]; //вносим карту в массив стола
						kol_podkin--;

						Y = hand_comp_Y;
						X = hand_X;
						setCursor(X, Y);
						DelFunc(card, row, col); //удаляем из рук компьютера карту

						X = Koord_X_stol(index_table);
						Y = Koord_Y_stol(index_table);
						setCursor(X, Y); //печатаем карту на середине стола
						printCard(card, hand_comp, row, col, index_karty, color);

						CopyMas(hand_comp, count_comp, index_karty);        // перебираем массив карт
						count_comp--;

						X = hand_X, Y = hand_comp_Y;
						DelCard(card, row, col, count_comp, shag_comp);     // удаляем визуал

						shag_comp = ShagFunc(count_comp);                   // с учетом шага

						X = hand_X, Y = hand_comp_Y;                        // печатаем массив карты
						cardPrint(card, row, col, color, count_comp, shag_comp);
					}
					else
					{
						player = false;
						computer = false;
					}
				}

				if (computer)
				{
					verno = true;
					do
					{
						menu_point = 0;
						kolich = 0;
						do
						{
							X = hand_X, Y = hand_player_Y;
							punkt_choice = KlacKlac(hand_player, count_player, menu_point); //клацаем
							if (punkt_choice == 66)
							{
								verno = false;
								if ((hand_player[index_karty].nominal > table[index_table].nominal && hand_player[index_karty].mast == table[index_table].mast) || (table[index_table].mast != kozyr.mast && hand_player[index_karty].mast == kozyr.mast))
								{
									index_table++;
									table[index_table] = hand_player[index_karty]; // вписываем в массив стол

									Y = up_card;
									X = Koord_X_hand(index_karty, shag_player);
									setCursor(X, Y);
									DelFunc(card, row, col);  //удаляем карту из руки

									X = Koord_X_stol(index_table);
									Y = Koord_Y_stol(index_table);
									setCursor(X, Y); //печатаем в центр поля
									printCard(card, hand_player, row, col, index_karty, color);

									CopyMas(hand_player, count_player, index_karty);     // перебираем массив
									count_player--;

									X = hand_X, Y = hand_player_Y;
									DelCard(card, row, col, count_player, shag_player);  // удаляем визуал

									shag_player = ShagFunc(count_player);               // с учетом шага

									X = hand_X, Y = hand_player_Y;                      // печатаем массив карт
									cardPrint(card, hand_player, row, col, color, count_player, shag_player);

									verno = true; //карта подходит
									break;
								}
								else
								{
									X = 41, Y = 10;
									setCursor(X, Y);
									cout << "You can't get covered with it!" << endl;     // этой картой нельзя покрыть
									X = 46, Y = 11;
									setCursor(X, Y);
									cout << "Choose another card!";
									Sleep(1500);

									Y = up_card;
									X = Koord_X_hand(index_karty, shag_player);
									setCursor(X, Y); //опускаем предыдущую карту//удаляем
									DelFunc(card, row, col);

									ChangeKoord(0, 4);//опускаем предыдущую карту//удаляем
									printCard(card, hand_player, row, col, index_karty, color);

									menu_point = index_karty;

									X = 41, Y = 10;
									setCursor(X, Y);
									DelFunc(kol_bukv, points);
									X = 46, Y = 11;
									setCursor(X, Y);
									DelFunc(kol_bukv, points);
								}

							}

							if (!kolich && punkt_choice == 99)
							{
								verno = false;
								break;
							}

							if (kolich && punkt_choice != 66 && punkt_choice != 99)
							{
								Y = up_card;
								X = Koord_X_hand(index_karty, shag_player);
								setCursor(X, Y); //опускаем предыдущую карту//удаляем
								DelFunc(card, row, col);

								ChangeKoord(0, 4);//опускаем предыдущую карту//удаляем
								printCard(card, hand_player, row, col, index_karty, color);
							}

							if (punkt_choice == 99)
							{
								Y = up_card;
								X = Koord_X_hand(index_karty, shag_player);
								setCursor(X, Y);      //удаляем
								DelFunc(card, row, col);

								ChangeKoord(0, 4);      // печатаем
								printCard(card, hand_player, row, col, index_karty, color);
								verno = false;
								break;
							}

							if (punkt_choice != 66)
							{
								index_karty = punkt_choice; //присваиваем клац клац индекс карты
								Y = hand_player_Y;
								X = Koord_X_hand(index_karty, shag_player);
								setCursor(X, Y);
								DelFunc(card, row, col); //поднимаем нашу карту
								ChangeKoord(0, -4);
								printCard(card, hand_player, row, col, index_karty, color);
								kolich++;
							}
						} while (menu_point != 66 || !verno);
						Sleep(2000);
						if (verno)
						{
							if (!count_player)
							{
								break;
							}

							if (!kol_podkin)
							{
								verno = false;
							}
							else
							{
								index_karty = PodkinutComp(hand_comp, table, count_comp, index_table);

								if (index_karty >= 0)
								{
									index_table++;
									table[index_table] = hand_comp[index_karty]; //поиск карт которые можно подкинуть
									kol_podkin--;

									Sleep(1500);
									X = Koord_X_stol(index_table);
									Y = Koord_Y_stol(index_table);
									setCursor(X, Y);
									printCard(card, hand_comp, row, col, index_karty, color);  //нашли

									CopyMas(hand_comp, count_comp, index_karty);          // перебираем массив карт
									count_comp--;

									X = hand_X, Y = hand_comp_Y;
									DelCard(card, row, col, count_comp, shag_comp);       // удаляем визуал

									shag_comp = ShagFunc(count_comp);                    // с учетом шага

									X = hand_X, Y = hand_comp_Y;                         // печатаем массив карт
									X = hand_X, Y = hand_comp_Y;
									cardPrint(card, row, col, color, count_comp, shag_comp);
								}
							}
						}
					} while (verno && index_karty >= 0);
				}

				if (index_table % 2 != 0)
				{
					kol_otboi++;
					X = 47, Y = 10;
					setCursor(X, Y);
					cout << "Otboi!!!";  // если ходили мы а последняя карта четная значит отбой
					Sleep(2000);

					X = 47, Y = 10;
					setCursor(X, Y);
					DelFunc(kol_bukv, points);
					X = 5, Y = 20;

					ClearPole(card, row, col);     // очищаем поле между игроками
					ClearPole(card, row, col);

					X = 110 + kol_otboi * 2;       // печатаем отбой (визуал)
					if (kol_otboi % 2 == 0)
					{
						Y = 17;
					}
					else
					{
						Y = 15;
					}
					setCursor(X, Y);
					printCard(card, row, col, color);
					ChangeKoord(2, 2);
					printCard(card, row, col, color);

					if (player)
					{
						player = false;
						computer = true;                // передаем следующий ход сопернику
					}
					else if (computer)
					{
						computer = false;
						player = true;
					}
				}

				else if ((index_table % 2 == 0 && computer))
				{
					X = 47, Y = 10;
					setCursor(X, Y);
					cout << "You are take!";                   // берем карты, если не смогли отбиться
					Sleep(1500);

					X = 47, Y = 10;  // удаляем надпись
					setCursor(X, Y);
					DelFunc(kol_bukv, points);

					kol = 0;
					do
					{
						if (kol_podkin)
						{
							index_karty = PodkinutComp(hand_comp, table, count_comp, index_table);

							if (index_karty >= 0)
							{
								kol++;
								index_table++;
								table[index_table] = hand_comp[index_karty]; //поиск карт которые можно подкинуть
								kol_podkin--;

								X = Koord_X_stol(index_table + kol);
								Y = Koord_Y_stol(index_table + kol);
								setCursor(X, Y);
								printCard(card, hand_comp, row, col, index_karty, color); // нашли
								Sleep(2500);

								CopyMas(hand_comp, count_comp, index_karty);          // перебираем массив карт
								count_comp--;

								X = hand_X, Y = hand_comp_Y;
								DelCard(card, row, col, count_comp, shag_comp);       // удаляем визуал

								shag_player = ShagFunc(count_player);                 // с учетом шага

								X = hand_X, Y = hand_comp_Y;                          // печатаем новый
								cardPrint(card, row, col, color, count_comp, shag_comp);
							}
						}
						else
						{
							break;
						}
					} while (index_karty >= 0 && kol_podkin);

					ClearPole(card, row, col);
					ClearPole(card, row, col);          // чистим поле между игроками

					for (size_t i = count_player, j = 0; i <= count_player + index_table; i++, j++)
					{
						hand_player[i] = table[j]; //добавляем карты из стола к игроку в руку
					}

					X = hand_X, Y = hand_player_Y;
					setCursor(X, Y);
					for (size_t i = 0; i < count_player; i++)
					{
						DelFunc(card, row, col);         // удаляем карты игрока(визуал)
						ChangeKoord(shag_player);
					}

					X = hand_X, Y = hand_comp_Y;
					setCursor(X, Y);
					for (size_t i = 0; i < count_comp; i++)
					{
						DelFunc(card, row, col);            // удаляем карты компа(визуал)
						ChangeKoord(shag_comp);
					}
					count_player = count_player + index_table + 1;
				}

				else if ((index_table % 2 == 0 && player))
				{
					X = 47, Y = 10;
					setCursor(X, Y);
					cout << "Computer takes!"; // если ходили мы а последняя карта нечетная значит компьютер не отбился
					Sleep(1500);
					ChangeKoord(0, 1);

					if (kol_podkin && count_comp > 1)
					{
						X = 42, Y = 11;
						setCursor(X, Y);
						cout << "You can throw in more cards!";        // не можем подкинуть больше карт
						Sleep(2500);
					}

					X = 47, Y = 10;
					setCursor(X, Y);
					DelFunc(kol_bukv, points);
					ChangeKoord(-5, 1);
					DelFunc(kol_bukv, points);

					kol = 0;
					menu_point = 0;
					kolich = 0;

					do
					{
						if (kol_podkin)
						{
							X = hand_X, Y = hand_player_Y;
							punkt_choice = KlacKlac(hand_player, count_player, menu_point); //клацаем
							if (punkt_choice == 66)
							{
								verno = false;
								if (PodkinutPlayer(hand_player, table, index_karty, index_table))
								{
									kol++;
									index_table++;
									table[index_table] = hand_player[index_karty]; // вписываем в массив стол
									kol_podkin--;

									Y = up_card;
									X = Koord_X_hand(index_karty, shag_player);
									setCursor(X, Y);
									DelFunc(card, row, col);  //удаляем карту из руки

									X = Koord_X_stol(index_table + kol);
									Y = Koord_Y_stol(index_table + kol);
									setCursor(X, Y); //печатаем в центр поля
									printCard(card, hand_player, row, col, index_karty, color);

									CopyMas(hand_player, count_player, index_karty);    // перебираем масив карт
									count_player--;

									X = hand_X, Y = hand_player_Y;
									DelCard(card, row, col, count_player, shag_player);   // удалем визуал карт

									shag_player = ShagFunc(count_player);                // с учетом шага

									X = hand_X, Y = hand_player_Y;                       // печатаем массив карт
									cardPrint(card, hand_player, row, col, color, count_player, shag_player);
								}
								else
								{
									X = 47, Y = 10;
									setCursor(X, Y);
									cout << "You can't get throw it!" << endl;       // не можем подкинуть карту
									X = 52, Y = 11;
									setCursor(X, Y);
									cout << "Choose another card!";
									Sleep(1500);

									Y = up_card;
									X = Koord_X_hand(index_karty, shag_player);
									setCursor(X, Y); //опускаем предыдущую карту//удаляем
									DelFunc(card, row, col);

									ChangeKoord(0, 4);//опускаем предыдущую карту//удаляем
									printCard(card, hand_player, row, col, index_karty, color);

									menu_point = index_karty;

									X = 47, Y = 10;
									setCursor(X, Y);
									DelFunc(kol_bukv, points);
									X = 42, Y = 11;
									setCursor(X, Y);
									DelFunc(kol_bukv, points);
								}
							}
							if (kolich && punkt_choice != 66 && punkt_choice != 99)
							{
								Y = up_card;
								X = Koord_X_hand(index_karty, shag_player);
								setCursor(X, Y); //опускаем предыдущую карту//удаляем
								DelFunc(card, row, col);

								ChangeKoord(0, 4);//опускаем предыдущую карту//удаляем
								printCard(card, hand_player, row, col, index_karty, color);
							}

							if (punkt_choice == 99)
							{
								Y = up_card;
								X = Koord_X_hand(index_karty, shag_player);  //опускаем предыдущую карту // удаляем
								setCursor(X, Y);
								DelFunc(card, row, col);
							}

							if (punkt_choice != 66 && punkt_choice != 99)
							{
								index_karty = punkt_choice; //присваиваем клац клац индекс карты
								Y = hand_player_Y;
								X = Koord_X_hand(index_karty, shag_player);
								setCursor(X, Y);
								DelFunc(card, row, col); //поднимаем нашу карту
								ChangeKoord(0, -4);
								printCard(card, hand_player, row, col, index_karty, color);
								kolich++;
							}
							if (punkt_choice == 66)
							{

								menu_point = 0;
							}
						}
						else
						{
							break;
						}
					} while (menu_point != 99 && kol_podkin);


					ClearPole(card, row, col);
					ClearPole(card, row, col);

					for (size_t i = count_comp, j = 0; i <= count_comp + index_table; i++, j++)
					{
						hand_comp[i] = table[j]; //перемещаем со стола карты компьютеру
					}

					X = hand_X, Y = hand_comp_Y;
					setCursor(X, Y);

					shag_comp = ShagFunc(count_comp);
					for (size_t i = 0; i < count_comp; i++)
					{
						DelFunc(card, row, col);
						ChangeKoord(shag_comp);                 // удаляем карты компа
					}

					X = hand_X, Y = hand_player_Y;
					setCursor(X, Y);
					for (size_t i = 0; i < count_player; i++)
					{
						DelFunc(card, row, col);               // удаляем карты игрока
						ChangeKoord(shag_player);
					}
					count_comp = count_comp + index_table + 1;
				}

				if (count_player < 6)
				{
					for (size_t i = count_player; i < kolodaSize; i++)
					{
						if (ostatok)
						{
							hand_player[i] = Koloda[index_vkolode];      // добавляем карты из колоды игроку
							index_vkolode++;
							ostatok--;
							count_player++;
							if (count_player == 6)
							{
								break;
							}
						}
						else
						{
							break;
						}
					}
				}

				if (count_comp < 6)                                      // добавляем карты из колоды игроку
				{
					for (size_t i = count_comp; i < kolodaSize; i++)
					{
						if (ostatok)
						{
							hand_comp[i] = Koloda[index_vkolode];
							ostatok--;
							index_vkolode++;
							count_comp++;
							if (count_comp == 6)
							{
								break;
							}
						}
						else
						{
							break;
						}
					}
				}

				shag_player = ShagFunc(count_player);
				if (count_player)
				{
					SortMas(hand_player, hand_player_temp, max_card, count_player, kozyr);  // сортируем массив игрока
				}

				X = hand_X, Y = hand_player_Y;
				for (size_t i = 0; i < count_player; i++)
				{
					setCursor(X, Y); //рисуем с учетом изменений
					printCard(card, hand_player, row, col, i, color);
					X += shag_player;
				}

				shag_comp = ShagFunc(count_comp);

				X = hand_X, Y = hand_comp_Y;
				for (size_t i = 0; i < count_comp; i++)
				{
					setCursor(X, Y); //рисуем с учетом изменений
					printCard(card, row, col, color);
					X += shag_comp;
				}

			} while ((player || computer));

			system("cls");
			X = 50; Y = 15;
			setCursor(X, Y);

			if (count_comp && !count_player)
			{
				cout << "You are winner!!!";                        // игрок победил
				user.score += 100;
			}

			else if (!count_comp && count_player)
			{
				cout << "Computer is winner!!!"; // комп победил
				user.score += 1;
			}

			else if (!count_comp && !count_player)
			{
				cout << "Draw game!";                                   // ничья
				user.score += 50;
			}

			if (status == 'a')
			{
				fopen_s(&f, "Users.txt", "r");
				fopen_s(&f_temp_2, "Users2.txt", "w");

				size = _filelength(_fileno(f));
				if (size > 0)
				{
					count = size / sizeof(User);
					for (size_t i = 0; i < count; i++)
					{
						fread(&temp, sizeof(User), 1, f);
						if (_stricmp(user.login, temp.login) == 0)
						{
							if (user.score > temp.score)
							{
								temp.score = user.score;
							}
						}
						fwrite(&temp, sizeof(User), 1, f_temp_2);
					}
					fclose(f);
					fclose(f_temp_2);
				}
			}
			else
			{
				fopen_s(&f, "Users.txt", "a");
				fwrite(&user, sizeof(User), 1, f);
				fclose(f);
			}

			check = false;
			for (size_t i = 0; i < leaders; i++)
			{
				if (user.login == leader_mas[i].login)
				{
					check = true;
					if (user.score > leader_mas[i].score)
					{
						leader_mas[i].score = user.score;
						fopen_s(&f_temp, "Users_leaders.txt", "a");
						fwrite(&leader_mas[i], sizeof(User), 1, f_temp);
						fclose(f_temp);
					}
					break;
				}
			}

			if (!check)
			{
				for (size_t i = 0; i < leaders; i++)
				{
					if (user.score > leader_mas[i].score)
					{
						fopen_s(&f_temp, "Users_leaders.txt", "a");
						fwrite(&user, sizeof(User), 1, f_temp);
						fclose(f_temp);
						break;
					}
				}
			}

			system("pause>>NULL");
			X = 50; Y = 15;
			setCursor(X, Y);
			setColor(Black, Black);
			cout << "Computer is winner!!!";
			setColor(White, Black);
			Sleep(1500);
		}

	} while (true);
}
