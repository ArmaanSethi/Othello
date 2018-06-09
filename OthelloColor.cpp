#include <windows.h>
#include<iostream>
#include<stdio.h>
#include <cstdlib>
#include <ctime>

COORD coord = {0,0};

using namespace std;

int linex= 30;

class Piece {
private:
    int x, y, color;
public:
    Piece() {x = y = color = -1;}
    int getx() {return x;}
    int gety() {return y;}
    int getcolor() {return color;}
    void setcolor(int c) {color = c;}
    void set(int xpos, int ypos, int c) {x = xpos;y = ypos;color = c;}//start of the game
    void set(int xpos, int ypos) {x = xpos;y = ypos;}//placing
    void display();
};

class Board {
private:
    Piece list[64];
    int x1, y1, status, redp, whitep, winner;//Where it will be placed. Turn, Number on Board, Who Wins.
    void move();//everything goes inside this
    int inRange(int x, int y);//if it is a valid input
    int pieceatLoc(int x, int y);//if there is already a piece
    int validplace(int x, int y);//if it can be placed
    int check_color(int x, int y);
    int flip(int x, int y);
    void display();
public:
    Board() {

        /*int a = 0;
        for(int i = 1; i <= 8; i++)
        {
            for(int j = 1; j <= 8; j++)
            {
                list[a].set(i,j,(rand()%2));
                a++;
            }
        }*/
        list[0].set(4, 4, 0);
        list[1].set(4, 5, 1);
        list[2].set(5, 4, 1);
        list[3].set(5, 5, 0);
        /*list[0].set(4, 4, 0);
        list[1].set(4, 5, 1);
        list[2].set(5, 4, 1);
        list[3].set(5, 5, 0);
        list[4].set(4, 4, 0);
        list[5].set(4, 5, 1);
        list[6].set(5, 4, 1);
        list[7].set(5, 5, 0);
        list[8].set(4, 4, 0);
        list[9].set(4, 5, 1);
        list[10].set(5, 4, 1);
        list[11].set(5, 5, 0);
        list[12].set(4, 4, 0);
        list[13].set(4, 5, 1);
        list[14].set(5, 4, 1);
        list[15].set(5, 5, 0);
        list[16].set(4, 4, 0);
        list[17].set(4, 5, 1);
        list[18].set(5, 4, 1);
        list[19].set(5, 5, 0);
        list[20].set(4, 4, 0);
        list[21].set(4, 5, 1);
        list[22].set(5, 4, 1);
        list[23].set(5, 5, 0);
        list[24].set(4, 4, 0);
        list[25].set(4, 5, 1);
        list[26].set(5, 4, 1);
        list[27].set(5, 5, 0);
        list[28].set(4, 4, 0);
        list[29].set(4, 5, 1);
        list[30].set(5, 4, 1);
        list[31].set(5, 5, 0);
        list[32].set(4, 4, 0);
        list[33].set(4, 5, 1);
        list[34].set(5, 4, 1);
        list[35].set(5, 5, 0);
        list[36].set(4, 4, 0);
        list[37].set(4, 5, 1);
        list[38].set(5, 4, 1);
        list[39].set(5, 5, 0);
        list[40].set(4, 4, 0);
        list[41].set(4, 5, 1);
        list[42].set(5, 4, 1);
        list[43].set(5, 5, 0);
        list[44].set(4, 4, 0);
        list[45].set(4, 5, 1);
        list[46].set(5, 4, 1);
        list[47].set(5, 5, 0);
        list[48].set(4, 4, 0);
        list[49].set(4, 5, 1);
        list[50].set(5, 4, 1);
        list[51].set(5, 5, 0);
        list[52].set(4, 4, 0);
        list[53].set(4, 5, 1);
        list[54].set(5, 4, 1);
        list[55].set(5, 5, 0);
        list[56].set(4, 4, 0);
        list[57].set(4, 5, 1);
        list[58].set(5, 4, 1);
        list[59].set(5, 5, 0);
        list[60].set(4, 4, 0);
        list[61].set(4, 5, 1);
        list[62].set(5, 4, 1);
        list[63].set(5, 5, 0);*/
        };
    void execute();
};

void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int Board::flip(int x2, int y2)
{
    gotoxy(0, linex++);
    cout << "flip " << x2 << " " << y2;

    for(int i = 0; i < 64; i++)
    {
        if((list[i].getx() == x2) && (list[i].gety() == y2))
        {
            list[i].setcolor(status%2);
        }
    }
}

int Board::check_color(int x3, int y3)
{

    if(x3 <= 0 || y3 <= 0 || x3 >=9 || y3 >=9)
    {

        return -1;
    }
    for(int i = 0; i < 64; i++)
    {
        if((list[i].getx() == x3) && (list[i].gety() == y3))
           {
               gotoxy(0,linex++);
               cout << "Check Color found " << x3 << " " << y3 << " " << list[i].getcolor();
               return list[i].getcolor();
           }
    }

    return -1;
}
int Board::validplace(int x2, int y2)
{
    gotoxy(0, linex++);
    cout << "validplace X2: " << x2 << " Y2: " << y2;
    int a = 0;
    int c = 0;
    gotoxy(0,34);
    a = check_color(x2-1, y2-1);

    gotoxy(0, linex++);
    cout << "Check Color 1 " << x2 -1 << " " << y2 -1 << " " << a ;
    if(a == ((status+1)%2))
    {
        for(int j = 1; j < 8; j++)
        {
            a = check_color(x2-1-j,y2-1-j);
            if(a == (status%2))
            {
                //change the color
                for(int i = 0; i < j; i++)
                {
                    flip(x2-1-i, y2-1-i);
                    c++;
                }
            }else if(a == -1)
            {
                //get out of the loop
                j = 9;
            }
        }
    }
    a = check_color(x2, y2-1);
    gotoxy(0,linex++);
    cout << "Check Color 2 " << x2  << " " << y2 -1 << " "  << a ;
    if(a == ((status+1)%2))
    {
        for(int j = 1; j < 8; j++)
        {
            a = check_color(x2,y2-1-j);
            if(a == (status%2))
            {
                // change color
                for(int i = 0; i < j; i++)
                {
                    flip(x2, y2-1-i);
                    c++;
                }
            }else if(a == -1)
            {
                //get out of for loop
                j = 9;
            }
        }
    }
    a = check_color(x2+1, y2-1);
    gotoxy(0,linex++);
    cout << "Check Color 3 " << x2 +1 << " " << y2 -1 << " " << a ;
    if(a == (((status+1)%2)))
    {        for(int j = 1; j < 8; j++)
        {
            a = check_color(x2+1+j,y2-1-j);
            if(a == (status%2))
            {
                // change color
                for(int i = 0; i < j; i++)
                {
                    flip(x2+1+i, y2-1-i);
                    c++;
                }
            }else if(a == -1)
            {
                j = 9;
                //get out of for loop
            }
        }
    }
    a = check_color(x2-1, y2);
    gotoxy(0,linex++);
    cout << "Check Color 4 " << x2 -1 << " " << y2 << "a = " << a << "status =" << status ;
    if(a == ((status+1)%2))
    {
        for(int j = 1; j < 8; j++)
        {
            a = check_color(x2-1-j,y2);
            if(a == (status%2))
            {
                // change color

                for(int i = 0; i < j; i++)
                {
                    flip(x2-1-i, y2);
                    c++;
                }
            }else if(a == -1)
            {
                j = 9;
                //get out of for loop
            }
        }

    }
    a = check_color(x2+1, y2);
    gotoxy(0,linex++);
    cout << "Check Color 5 " << x2 +1 << " " << y2  << " a = " << a << " status = " << status ;
    if(a == ((status+1)%2))
    {
        gotoxy(0,linex++);
        cout << "Check Color 5 in 1 " << x2 +1 << " "<< y2  << " "<< a ;
        for(int j = 1; j < 8; j++)
        {
            a = check_color(x2+1+j,y2);
            gotoxy(0, linex++);
            cout << "Check Color 5 in 2 " << x2 +1 +j << " " << y2  << " "<< a ;
            if(a == (status%2))
            {
                // change color
                for(int i = 0; i < j; i++)
                {
                    flip(x2+1+i, y2);
                    c++;
                }
            }else if(a == -1)
            {
                //get out of for loop
                j= 9;
            }
        }

    }
    a = check_color(x2-1, y2+1);
    gotoxy(0,linex++);
    cout << "Check Color 6 " << x2 -1 << " " << y2 +1  << " " << a ;
    if(a == ((status+1)%2))
    {
        for(int j = 1; j < 8; j++)
        {
            a = check_color(x2-1-j,y2+1+j);
            if(a == (status%2))
            {
                // change color
                for(int i = 0; i < j; i++)
                {
                    flip(x2-1-i, y2+1+i);
                    c++;
                }
            }else if(a == -1)
            {
                //get out of for loop
                j=9;
            }
        }

    }
    a = check_color(x2, y2+1);
     gotoxy(0,linex++);
    cout << "Check Color 7 " << x2 << " " << y2 +1  << " " << a ;
    if(a == ((status+1)%2))
    {
        for(int j = 1; j < 8; j++)
        {
            a = check_color(x2,y2+1+j);
            if(a == (status%2))
            {
                // change color
                for(int i = 0; i < j; i++)
                {
                    flip(x2, y2+1+i);
                    c++;
                }
            }else if(a == -1)
            {
                //get out of for loop
                j=9;
            }
        }

    }
    a = check_color(x2+1, y2+1);
     gotoxy(0,linex++);
    cout << "Check Color 8 " << x2 +1 << " " << y2 +1  << " " << a ;
    if(a == ((status+1)%2))
    {
        for(int j = 1; j < 8; j++)
        {
            a = check_color(x2+1+j,y2+1+j);
            if(a == (status%2))
            {
                // change color
                for(int i = 0; i < j; i++)
                {
                    flip(x2+1+i, y2+1+i);
                    c++;
                }
            }else if(a == -1)
            {
                //get out of for loop
                j=9;
            }
        }

    }
    gotoxy(0,linex++);
    cout << "C: " << c;
    return c;
}

int Board::pieceatLoc(int x2, int y2)
{
    int a = 0;
    for(int i = 0; i < 64; i++)
        if(list[i].getx() == x2)
            if(list[i].gety() == y2)
                a++;

    if(a > 1)
        return 1;
    else
        return 0;
}

int Board::inRange(int x, int y)
{
    if(((x >= 1) && (x <= 8)) && ((y >=1) && (y <=8)))
        if(pieceatLoc(x,y) == 0)
            if(validplace(x,y) >= 1)
                return 1;
    return 0;
}

void Piece::display() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    if(x > 0) {
        gotoxy(3*x,2*y);
        if(color == 0) {
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x1F);
            cout << "W" << endl;
        }
        if(color == 1) {
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x1C);
            cout << "R" << endl;
        }
    }
}

void Board::display() {

    gotoxy(0,0);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x1A);
    for(int i = 0; i < 9; i++) {
        if(i == 0) {
            cout << char(178) << " ";
        } else {
            cout << " " << i << " ";
        }
    }
    cout << endl;
    for(int j = 1; j < 9; j++)
        cout << "                          " << endl << j << "                         " << endl;

    cout << "                          " << endl;

    gotoxy(30, 6);
    cout << "--SCORE--";
    int a = 0;
    for(int i = 0; i < 64; i++)
        if(list[i].getcolor() == 0)
            a++;
    whitep = a;
    gotoxy(30,7);
    cout << "WHITE: " << whitep;
    a = 0;
    for(int i = 0; i < 64; i++)
            if(list[i].getcolor() == 1)
                a++;

    gotoxy(30,8);
    redp = a;
    cout << "RED: " << redp;
    gotoxy(30,9);
    winner = redp + whitep;
    cout << "TOTAL: " << winner;
    for(int i = 0; i < 64; i++)
        list[i].display();
    gotoxy(30,10);
    if((status%2) == 0)
        cout << "WHITE'S TURN             ";
    if((status%2) == 1)
        cout << "RED's TURN               ";

}

void Board::move(){
    gotoxy(30,0);
    cout << "Input: X space Y, To pass input -1 -1" << endl;
    gotoxy(30,2);
    cout << "(X Y): ";
    cin >> x1;
    cin >> y1;
    if((inRange(x1,y1) == 1)&&(x1>=0)) {
        list[status].set(x1,y1,(status%2));
        status++;
    }
}

void Board::execute() {
    status = 4;
    display();
    while(((winner < 64)) && (redp > 0) && (whitep > 0)){
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0F);
        x1 = 0, y1 = 0;
        if(x1 >= 0){
            move();
        }
        display();
    }
    gotoxy(0,20);
    if(whitep> redp)
       cout << "WHITE WINS";
    else if(redp > whitep)
        cout << "RED WINS";
    else
        cout << "ITS A TIE!";
}

int main() {
    srand(time(0));
    Board Othello;
    Othello.execute();
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0F);
    gotoxy(0,30);
}
