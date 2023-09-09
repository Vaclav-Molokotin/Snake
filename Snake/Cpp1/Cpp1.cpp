#include <iostream> 
#include "windows.h"
#include <conio.h>
#include <dos.h>
#include <time.h>
using namespace std;

const int GAME_SPEED = 500;



int main()
{

    setlocale(LC_ALL, "rus");
    int map[25][50] = { 0 };
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 50; j++) {
            map[i][j] = 0;
        }
    }
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 50; j++) {
            if (i != 0 && i != 24 && j != 0 && j != 49) {
            }
            else {
                map[i][j] = 4;

            }
        }
    }
    bool food;
    map[12][22] = 3;
    map[12][23] = 3;
    map[12][24] = 3;
    map[12][24] = 2;
    map[12][30] = 1;
    int xhead = 24;
    int yhead = 12;
    int body = 3;
    int xvector;
    int yvector;
    map[12][24] = 2;
    //int* head;
    //head = &map[xhead][yhead];


    while (true) {
        xvector = !(map[yhead][xhead] >> 5) * (int)pow(-1, (map[yhead][xhead] >> 4));
        yvector = (map[yhead][xhead] >> 5) * (int)pow(-1, (map[yhead][xhead] >> 3));

        if ((map[yhead + yvector][xhead + xvector] & 7) < 2) {  //маска типа
            food = (map[yhead + yvector][xhead + xvector] & 7);
            int bufX;
            bufX = xhead;
            int bufY;
            bufY = yhead;
            int bufVX = xvector;
            int bufVY = yvector;
            map[yhead + yvector][xhead + xvector] = map[yhead][xhead];
            map[yhead][xhead]++;   //преобразование старой головы в тело
            if ((map[yhead - yvector][xhead - xvector] & 7) != 3) {
                map[yhead][xhead] = body;
                bufVX = !(map[bufY][bufX] >> 5) * pow(-1, (map[bufY][bufX] >> 4));
                bufVY = (map[bufY][bufX] >> 5) * pow(-1, (map[bufY][bufX] >> 3));
            }
            xhead += xvector;      //меняем координаты головы
            yhead += yvector;
            while (map[bufY - bufVY][bufX - bufVX] != 0) {
                bufX -= bufVX;
                bufY -= bufVY;
                bufVX = !(map[bufY][bufX] >> 5) * pow(-1, (map[bufY][bufX] >> 4));
                bufVY = (map[bufY][bufX] >> 5) * pow(-1, (map[bufY][bufX] >> 3));
            }
            body = 3 + (map[yhead][xhead] & 56);
            if (!food) {
                map[bufY][bufX] = 0;
            }
            else {
                srand(time(0));
                int i, j;
                i = rand() % 24;
                j = rand() % 49;
                while (map[i][j] > 0) {
                    i = rand();
                    j = rand();
                }
                map[i][j] = 1;
            }
        }
        ///////////
        else {
            system("cls");
            while (true) {
                cout << "Смэрть" << endl;
                while (true);
            }
        }
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 50; j++) {
                switch (map[i][j] & 7) {
                case 2:
                    cout << "%";
                    break;
                case 3:
                    cout << "$";
                    break;
                case 4:
                    cout << "#";
                    break;
                case 0:
                    cout << " ";
                    break;
                case 1:
                    cout << "@";
                }

            }
            cout << endl;
        }

        if ((int)_kbhit()) // слушатель нажатия на клаву
        {
            switch (_getch()) // ждёт нажатия на клаву без Enter после этого
            {
            case 119: //вверх
                map[yhead][xhead] = 42;
                break;
            case 115: //вниз
                map[yhead][xhead] = 34;
                break;
            case 97: //влево 
                map[yhead][xhead] = 18;
                break;
            case 100: //вправо
                map[yhead][xhead] = 2;
                break;
            }


        }
        Sleep(GAME_SPEED);
        system("cls");
    }
}