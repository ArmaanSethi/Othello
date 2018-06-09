#include <windows.h>
#include<iostream>
#include<stdio.h>

COORD coord = {0,0};

using namespace std;

void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    int a;
    for(int i = 0; i < 10; i++) {
        gotoxy(5*i, 3*i+2);
        cout << "Testing" << i;
        cin >> a;
    }
    gotoxy(10,5);
    cout << endl << "Hello" << endl;
    return 0;
}
