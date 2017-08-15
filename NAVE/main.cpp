#include <QCoreApplication>
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <list>

/*
Autor: @fenixbinario
Fecha: 15/08/2017
IDE: QT Creator
*/

using namespace std;

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80


void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void OcultarCursor()
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon,&cci);
}

void SizeCursor()
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon,&cci);
}

void pintar_limites()
{
    for(int i = 2; i<78 ; i++)
    {
        gotoxy(i,3); printf("%c",205);
        gotoxy(i,33); printf("%c",205);
    }
    for (int i = 4; i < 33 ; i++)
    {
        gotoxy(2, i); printf("%c",186);
        gotoxy(77, i); printf("%c",186);
    }

    //esquinas
    gotoxy(2, 3); printf("%c",201);
    gotoxy(2, 33); printf("%c",200);
    gotoxy(77, 3); printf("%c",187);
    gotoxy(77, 33); printf("%c",188);
}

void intro()
{
    pintar_limites();
    gotoxy(12,15);
    printf("NAVES Y ASTEROIDES ");
    Sleep(800);
    gotoxy(12,16);
    printf("Autor: @fenixbinario");
    Sleep(800);
    gotoxy(12,17);
    printf("TECLADO --> DISPARAR [BARRA ESPACIO]");
    Sleep(800);
    gotoxy(12,18);
    printf("TECLADO --> CONTROL [FLECHAS]");
    //cin.get();
    gotoxy(12,20);
    system("pause");
    system("cls");
    pintar_limites();
    gotoxy(37,17);
    printf("3");
    Sleep(1000);
    gotoxy(37,17);
    printf("2");
    Sleep(1000);
    gotoxy(37,17);
    printf("1");
    Sleep(1000);
    gotoxy(37,17);
    printf("GO!");
    Sleep(1000);
    system("cls");
}

void NuevaPartida(int puntos, int nivel)
{
    system("cls");
    pintar_limites();
    gotoxy(34,18);

    printf("GAME OVER");
    Sleep(1000);
    system("cls");
    pintar_limites();
    Sleep(800);
    gotoxy(12,15);
    printf("TOTAL PUNTOS: %d", puntos);
    Sleep(800);
    gotoxy(12,16);
    printf("");
    Sleep(800);
    gotoxy(12,17);
    printf("NIVEL %d/5", nivel);
    Sleep(800);
    gotoxy(12,18);
    printf("EMPEZAR NUEVA PARTIDA . . .");
    //cin.get();
    gotoxy(12,20);
    system("pause");
    system("cls");
    pintar_limites();
}

void GanadorPartida(int puntos, int nivel)
{
    system("cls");
    pintar_limites();
    gotoxy(34,18);

    printf("WINNER");
    Sleep(1000);
    system("cls");
    pintar_limites();
    Sleep(800);
    gotoxy(12,15);
    printf("TOTAL PUNTOS: %d", puntos);
    Sleep(800);
    gotoxy(12,16);
    printf("");
    Sleep(800);
    gotoxy(12,17);
    printf("NIVEL %d/5", nivel);
    Sleep(800);
    gotoxy(12,18);
    printf("EMPEZAR NUEVA PARTIDA . . .");
    //cin.get();
    gotoxy(12,20);
    system("pause");
    system("cls");
    pintar_limites();
}

class NAVE
{
    int x,y;
    int corazones;
    int vidas;
 public:
    NAVE(int _x, int _y, int _corazones, int _vidas) : x(_x),y(_y),corazones(_corazones), vidas(_vidas){}
    int X(){ return x;}
    int Y(){ return y;}
    int VID() {return vidas;}
    void COR() { corazones--;}
    void pintar();
    void borrar();
    void mover();
    void pintar_corazones();
    void morir();
    void reset();
};


void NAVE::pintar()
{
    gotoxy(x,y); printf("  %c",30);
    gotoxy(x,y+1); printf(" %c%c%c",40,207,41);
    gotoxy(x,y+2); printf("%c%c %c%c",30,190,190,30);
}

void NAVE::borrar()
{
    gotoxy(x,y);   printf("     ");
    gotoxy(x,y+1); printf("     ");
    gotoxy(x,y+2); printf("     ");
}

void NAVE::mover()
{
    if(kbhit())
        {
            char tecla = getch();
            borrar();
            if(tecla == IZQUIERDA && x > 3) x--;
            if(tecla == DERECHA && x+6 < 78) x++;
            if(tecla == ARRIBA && y > 4) y--;
            if (tecla == ABAJO && y+3 < 33) y++;

            pintar();
            pintar_corazones();
        }
}

void NAVE::pintar_corazones()
{
    gotoxy(50,2); printf("VIDAS %d", vidas);
    gotoxy(64,2); printf("ESCUDO");
    gotoxy(72,2); printf("     ");
    for(int i = 0; i < corazones; i++)
    {
        gotoxy(72+i,2); printf("%c",3);
    }
}

void NAVE::morir()
{
    if(corazones == 0)
    {
        borrar();
        gotoxy(x,y);   printf("  +  ");
        gotoxy(x,y+1); printf(" +++ ");
        gotoxy(x,y+2); printf("  +  ");
        Sleep(150);
        borrar();

        gotoxy(x,y);   printf("+ * +");
        gotoxy(x,y+1); printf(" *** ");
        gotoxy(x,y+2); printf("+ * +");
        Sleep(150);
        borrar();

        gotoxy(x,y);   printf("  +  ");
        gotoxy(x,y+1); printf(" +++ ");
        gotoxy(x,y+2); printf("  +  ");
        Sleep(150);
        borrar();

        gotoxy(x,y);   printf("+ * +");
        gotoxy(x,y+1); printf(" *** ");
        gotoxy(x,y+2); printf("+ * +");
        Sleep(150);
        borrar();


        vidas--;
        corazones = 5;
        pintar_corazones();
        pintar();
    }
}

void NAVE::reset()
{
    x = 32;
    y = 30;
    corazones = 5;
    vidas = 3;
}

class AST
{
 int x,y;
public:
 AST(int _x, int _y) : x(_x), y(_y){}
 void pintar();
 void mover();
 void choque(NAVE &N);
 int X(){ return x;}
 int Y(){ return y;}
};

void AST::pintar()
{
    gotoxy(x,y); printf("%c",184);
}

void AST::mover()
{
    gotoxy(x,y); printf(" ");
    y++;
    if(y > 32)
    {
        x = rand()%71 + 4;
        y = 4;
    }

    pintar();
}

void AST::choque(NAVE &N) //choque de el asteroide con la nave
{
    if( x >= N.X() && x < N.X() + 6 && y >= N.Y() && y <= N.Y() +2 )
    {
        N.COR();
        N.borrar();
        N.pintar();
        N.pintar_corazones();
        x = rand()%71 + 4;
        y = 4;
    }
}

class BALA
{
    int x,y;
public:
    BALA(int _x, int _y) : x(_x), y(_y){}
    int X() {return x;}
    int Y() {return y;}
    void mover();
    bool fuera();
};

void BALA::mover()
{
    gotoxy(x,y); printf(" ");
    y--;
    gotoxy(x,y); printf("*");
}

bool BALA::fuera()
{
    if( y == 4) return true;
    return false;
}

int main()
{
    OcultarCursor();
    intro();

    NAVE N(37,30,5,3);
    pintar_limites();

    pintar_limites();
    N.pintar();
    N.pintar_corazones();


    list<AST*> A;
    list<AST*>::iterator itA;

    for(int i = 0; i < 5 ; i++)
    {
        A.push_back(new AST(rand()%75+3, rand()%5+4));
    }

    list<BALA*> B;
    list<BALA*> :: iterator it;

    int puntos = 0;
    int nivel = 0;
    int nivel_vel = 60;

    bool game_over = false;
    while(!game_over)
    {
        gotoxy(4,2); printf("PUNTOS: %d", puntos);
        gotoxy(20,2); printf("NIVEL: %d", nivel);
        Sleep(nivel_vel);
        if(kbhit())
        {
            char tecla = getch();
            if(tecla == 32)
            B.push_back(new BALA (N.X() + 2, N.Y() - 1));
        }

        for(it = B.begin(); it != B.end() ; it++)
        {
            (*it)->mover();
            if( (*it)->fuera() )
            {
                gotoxy( (*it)->X(), (*it)->Y() ); printf(" ");
                delete(*it);
                it = B.erase(it);
            }
        }

        for(itA = A.begin(); itA != A.end(); itA++)
        {
            (*itA)->mover();
            (*itA)->choque(N);
        }

        for(itA = A.begin(); itA != A.end(); itA++)
        {
            for(it = B.begin(); it != B.end(); it ++)
            {
                if( (*itA)->X() == (*it)->X() && ( (*itA)->Y()+1 == (*it)->Y() || (*itA)->Y() == (*it)->Y() ) )
                {
                    gotoxy((*it)->X(), (*it)->Y()); printf(" ");
                    delete(*it);
                    it = B.erase(it);

                    A.push_back(new AST(rand()%75+3, 4) );
                    gotoxy( (*itA)->X(), (*itA)->Y() ); printf(" ");
                    delete (*itA);
                    itA= A.erase(itA);

                    puntos += 5;


                    if( puntos < 10) nivel = 0;
                    if( puntos > 10 && puntos < 20) nivel = 1;
                    if( puntos > 20 && puntos < 30) nivel = 2;
                    if( puntos > 30 && puntos < 40) nivel = 3;
                    if( puntos > 40 && puntos < 60) nivel = 4;
                    if( puntos > 60 && puntos < 80) nivel = 5;

                    if( nivel == 0) nivel_vel = 60;
                    if( nivel == 1) nivel_vel = 50;
                    if( nivel == 2) nivel_vel = 45;
                    if( nivel == 3) nivel_vel = 35;
                    if( nivel == 4) nivel_vel = 30;
                    if( nivel == 5) nivel_vel = 28;


                }
            }
        }


        N.morir();
        N.mover();
        if(N.VID() == 0)
        {
            NuevaPartida(puntos,nivel);
            N.reset();
            puntos = 0;
            nivel = 0;
            N.pintar();
            N.pintar_corazones();

        }
        if (nivel == 5)
        {
            GanadorPartida(puntos,nivel);
            N.reset();
            puntos = 0;
            nivel = 0;
            N.pintar();
            N.pintar_corazones();

        }



    }

    return 0;
}
