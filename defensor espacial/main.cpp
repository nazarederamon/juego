#include<stdio.h>//dibuja mejor
#include<windows.h>//una de las cosas que nos permite dar posicion
#include<conio.h>//da color a los textos
#include<stdlib.h>//memoria dinamica
#include <list>//crea una lista
#include <iostream>
using namespace std;
#define ARRIBA 72 //hace una definicion LOS NUMEROS SON DE ACSII
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
void gotoxy(int x,int y){//no espera un resultado
    HANDLE b;//identificador de ventana
    b =GetStdHandle(STD_OUTPUT_HANDLE);//recupera el identificador de la consola tiene un parametro de control de salida ya que da posicion de salida
    COORD a;//son las coordenadas esta invertida
    a.X=x;//importante que sea mayuscula
    a.Y=y;
    SetConsoleCursorPosition(b,a);
}


void entorno(){
    for(int i=2; i<78;i++){
        gotoxy(i,3);printf("%c",205);
        gotoxy(i,33);printf("%c",205);
    }
    for(int i=4; i<33 ;i++){
        gotoxy(2,i);printf("%c",186);
        gotoxy(77,i);printf("%c",186);
    }
    gotoxy(2,3);printf("%c",201);
    gotoxy(2,33);printf("%c",200);
    gotoxy(77,3);printf("%c",187);
    gotoxy(77,33);printf("%c",188);
}

class COM{ //CLASE NOS PERMITE DEFINIR OBJETOS; atrivutos mayoritariamente privados solo son publicos si se pone public{//clase tiene un constructor eso nos permite inicializar
    int x,y;
    int cor;
    int vid;
public:
    COM(int _x,int _y,int _cor,int _vid);
    int X(){return x;}//nos retorna el valor de x
    int Y(){return y;}
    void COR() {cor--;}
    void pin();
    void bor();
    void mov();
    void pin_cor();
    void mor ();
};
COM::COM(int _x,int _y,int _cor,int _vid){//clase
    x = _x;
    y = _y;
    cor = _cor;
    vid= _vid;

    }
void COM::pin(){//permiite acceder a los metodos de la clase
    gotoxy(x,y);printf("  %c",30);//manda imprimir un caracer (%c)del codigo ascii
    gotoxy(x,y+1);printf(" %c%c%c",185,219,204);
    gotoxy(x,y+2);printf("%c%c %c%c",203,203,203,203);
}
void COM::bor(){
gotoxy(x,y);  printf("     ");
gotoxy(x,y+1);printf("     ");
gotoxy(x,y+2);printf("     ");
}
void COM::mov(){
 if (kbhit ()){//detecta si se presiona una tecla
                    char tecla = getch();//guarda la tecla presiona getch
                    bor();
                    if(tecla == IZQUIERDA && x>3)
                    x--;

                    if(tecla ==DERECHA && (x+5 <77) )x++;// mas 7 ya que tenemos mas caracteres a la orilla
                    if(tecla ==ARRIBA && y > 5)y--;
                    if(tecla ==ABAJO && (y+3<33) )y++;
                    pin();
                    pin_cor();
}
}

void pin_cor();
void COM::pin_cor(){
    gotoxy(50,2); printf("VIDAS %d",vid);//%d imprime numero entero
    gotoxy(64,2); printf("Salud");
    gotoxy(70,2); printf("      ");
    for (int i=0 ; i<cor ; i++){
    gotoxy(70+i,2) ;printf ("%c",3);

    }
}
void COM::mor(){
    if(cor==0){
        bor();
        gotoxy(x,y);  printf(" **");//explosion animacion
        gotoxy(x,y+1);printf("****");//explosion animacion
        gotoxy(x,y+2);printf(" **");//explosion animacion
        Sleep(200);//descansa el computador

        bor();
        gotoxy(x,y);  printf("*  *");//explosion animacion
        gotoxy(x,y+1);printf(" ** ");//explosion animacion
        gotoxy(x,y+2);printf("*  *");//explosion animacion
        Sleep(200);
        bor();
            vid--;
            cor = 3;
            pin_cor();
            pin();
    }

}
class AST{//asteroides puedo usar las mismas variables que las anteriores ya que los metodos estan fija en esta clase
    int x,y;
public:
    AST(int _x, int _y):x(_x),y(_y){}//otra forma de comparar
    void pin();
    void mov();
    void choque(class COM &C);
};
void AST::pin(){
    gotoxy(x,y); printf("%c",02);//caracter asteroide
}
void AST::mov(){
    gotoxy(x,y);printf(" ");//borrar espacio en blanco
    y++;
    if(y>32){
        x = rand()%71 + 4;//limete 71 y 4
        y=4;//lo sube de nuevo)
    }
    pin();
    }
void AST::choque(class COM &C){
    if(x >= C.X() && x < C.X()+6 && y>=C.Y() && y <=C.Y() +2)
    {
        C.COR();//le va restar corazones
        C.bor();
        C.pin();
        C.pin_cor();
        x = rand()%71 + 4;
        y=4;
    }
}
class DIS{
int x,y;
public:
    DIS(int _x, int _y):x(_x),y(_y){}
    //int X(){return x;}
    //int Y(){return y;}
    void mov();
    bool salio();
    };
void DIS::mov(){
    gotoxy(x,y); printf(" ");
    if(y>4)y--;//no sobre pase limite de la nave
    gotoxy(x,y); printf("*");
}
bool DIS::salio(){
    if (y==4) return true;
    return false;
}
int main(){
    int res;
    system("cls");
    system("color 1F");//fondo de color azul (1) y letras de color blanco brillante  (F)


    gotoxy(30,10);cout<<"Defensor espacial"<<endl;


    gotoxy(35,15);printf("  %c",30);
    gotoxy(35,16);printf(" %c%c%c",185,219,204);
    gotoxy(35,17);printf("%c%c %c%c",203,203,203,203);

    gotoxy(30,19);cout<<"1_ Jugar"<<endl;
    gotoxy(30,20);cout<<"2_ Istrucciones"<<endl;
    gotoxy(30,21);cout<<"3_ Salir"<<endl;

    gotoxy(30,23);cout<<"digite respuesta"<<endl;
    gotoxy(30,24);cin>>res;

    if(res==1){

    system("cls");
    entorno();
    COM C(7,30,3,3);
    C.pin();
    C.pin_cor();
    AST ast1(10,4),ast2(4,8),ast3(15,10);
    list<DIS*> D;//punteros facilita la creacion de elementos lista = arreglos
    list<DIS*>::iterator it;//con el podemos rrecorrer toda la lista

    bool game_over = false;
    while(!game_over){//para que se ejecute infiniamente
    if(kbhit())
        {
           char tecla = getch();
           if(tecla =='v'|| tecla =='V')
            D.push_back(new DIS(C.X() +2, C.Y() -1));// +2 para que salga al medio y paresca que sale de la nave
        }
        for(it =D.begin();it !=D.end();it++ )//lo empieza desde el primer elemento de la lista
        {
            (*it)->mov();//accede a la informacion hay que poner -> con el * en el caso de no estar guarda la direccion


            }
    ast1.mov();ast1.choque(C);
    ast2.mov();ast2.choque(C);
    ast3.mov();ast3.choque(C);
        C.mor();
        C.mov();
        Sleep(30);
        }
    }
       if(res == 2)
            {
            system("cls");
            gotoxy(30,15);cout<<"INSTRUCCIONES"<<endl;
            gotoxy(2,17);cout<<"Su nave se mueve con las flechas de direccion y dispara con la tecla 'v'."<<endl;
            gotoxy(2,18);cout<<"Usted gana al destruir 50 enemigos. Tiene 3 vidas y cada vida" <<endl;
            gotoxy(2,19);cout<<"tiene 3 corazones de energia."<<endl;
            Sleep(15000);
            main();
        }
        if(res == 3){}
        return 0;

}
