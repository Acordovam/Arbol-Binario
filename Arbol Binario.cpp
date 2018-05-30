#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <fstream>

#define DERECHA 1
#define IZQUIERDA 0
#define TRUE 1
#define FALSE 0


using namespace std;

void gotoxy(int x, int y) {		//Gotoxy para configurar le movimiento en la pantalla
	HANDLE hConsoleOutput;		//Propiedades de la terminal
	COORD Cursor_Pos = { x,y };	//Posicionamiento del cursor
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

struct Nodo {
	int dato;
	int FE;//factor equilibrio
	Nodo *der;
	Nodo *izq;
	Nodo *padre;
};


//prototipos
void menu();
Nodo *crearNodo(int, Nodo *);
void insertarNodo(Nodo*&, int, Nodo *);
void mostrarArbol(Nodo*,int);
bool busqueda(Nodo *, int);
void eliminarizq(Nodo* , int);
void eliminarNodo(Nodo *);
Nodo *minimo (Nodo *);
void reemplazar(Nodo*, Nodo*);
void destruirnodo(Nodo*);
void eliminarder(Nodo* , int);
void eliminarNodo2(Nodo *);
Nodo *maximo (Nodo *);
void reemplazar2(Nodo*, Nodo*);
void destruirnodo2(Nodo*);

//prototipos avl
int EsHoja(Nodo *);
int NUMNodos(Nodo*, int*  );
int Altura_Nodo(Nodo *, int);
void Equilibrar (Nodo *,Nodo *, int, int);
void RSI(Nodo *, Nodo *);
void RSD(Nodo *, Nodo *);
void RDI(Nodo *, Nodo *);
void RDD(Nodo *, Nodo *);
void auxContador(Nodo *, int*);
void auxAltura(Nodo *, int, int*);                                                                                                                                                                                                                                                                                        
void Mostrar(int *);                                                                                                                                                                                                                                                                                                                                                        
                     

Nodo *arbol=NULL;


Nodo *crearNodo(int n, Nodo *padre){
	Nodo *nuevo_nodo = new Nodo();
	
	nuevo_nodo->dato=n;
	nuevo_nodo->der=NULL;
	nuevo_nodo->izq=NULL;
	nuevo_nodo->padre=padre;
	
	
	return nuevo_nodo;
}

void insertarNodo(Nodo *&arbol, int n, Nodo *padre){
	if(arbol==NULL){//si esta vacio
	  
	  Nodo *nuevo_nodo= crearNodo(n, padre);
	  arbol = nuevo_nodo;
		
	}
	else{//si tiene nodos existentes
	int valorRaiz=arbol->dato;
	
	if(n < valorRaiz){ //menor a la raiz izq
		insertarNodo(arbol->izq,n, arbol);
	}
	else{// mayor a l derecha
		insertarNodo(arbol->der,n,arbol);
	}
		
	}
}

//////////////MOSTRAR////////////////

int auxX =0;


void mostrarArbol(Nodo *arbol, int auxY=0){//auxY es el nivel del arbol

		auxX=0;

     if(arbol == NULL){//Arbol vacio nada que mostrar

         return;
     }

     auxX += 2;//variable que permite posicionarse en el eje X

     mostrarArbol(arbol -> izq,auxY+2);//Se para hasta el nodo mas a la izquierda del árbol construye primero el subarbol izq porque sus valores en X son menores

     gotoxy(30 + auxX - auxY , 5 + auxY);//posiciona el nodo segun sus variables en X y en Y

     cout << arbol -> dato << endl << endl;//Muestra el dato del nodo respectivo


     mostrarArbol(arbol -> der,auxY+2);//Se para hasta el nodo mas a la derecho del árbol
     
     
}

//////////////// BUSCAR //////////////

bool busqueda (Nodo *arbol, int n){
	if (arbol== NULL){ // arbol vacio
	return false;
	}
	else if(arbol ->dato ==n){
	return true;
	}
	else if (n < arbol -> dato){
		return busqueda(arbol -> izq, n);
	}
	else{
		return busqueda(arbol ->der,n);
	}
}

///////////////////////////////////////////


//////////// ELIMINAR POR LA IZQUIERDA ///////////////////////

void eliminarizq (Nodo *arbol, int n){
	if(arbol==NULL){
		return;
	}
	
	else if(n< arbol->dato){
		eliminarizq(arbol->izq,n);// busca por la izquierda
	}
	
	else if( n> arbol ->dato){
		eliminarizq(arbol->der,n);//busca por la derecha
	}
	
	else { //si se encontro el valor
	
	eliminarNodo(arbol);
	}
}


void eliminarNodo(Nodo *nodoeliminar){
	
	if(nodoeliminar->izq && nodoeliminar->der){//con dos hijos
		Nodo *menor = minimo(nodoeliminar -> der);
		nodoeliminar->dato=menor->dato;
		eliminarNodo(menor);
		
	}
	
	else if(nodoeliminar->izq){
		
		reemplazar(nodoeliminar,nodoeliminar->izq);
		destruirnodo(nodoeliminar);		
	}
	
	else if(nodoeliminar->der){
		reemplazar(nodoeliminar,nodoeliminar->der);
		destruirnodo(nodoeliminar);
	}
	
	else{		
		reemplazar(nodoeliminar,NULL);
		destruirnodo(nodoeliminar);	
	}
	
	
}

Nodo *minimo(Nodo *arbol){
	
	if(arbol==NULL){
		return NULL;
	}
	
	if(arbol->izq){
		return minimo(arbol -> izq);
	}
	
	else{
		return arbol;
	}
}

void reemplazar(Nodo *arbol, Nodo*nuevonodo){
	if(arbol -> padre){
		
		if(arbol->dato == arbol->padre->izq->dato){
			arbol->padre->izq=nuevonodo;
			
		}
		
		else if(arbol->dato==arbol->padre->der->dato){
			arbol->padre->der= nuevonodo;
		}
	}
	
	if(nuevonodo){
		nuevonodo->padre=arbol->padre;
	}
	
}

void destruirnodo(Nodo *nodo){
	
	nodo->izq=NULL;
	nodo->der=NULL;
	
	delete nodo;
	
}

//////////////////////////////////////////////////////////////////

//////////// ELIMINAR POR LA DERECHA///////////////////////

void eliminarder (Nodo *arbol, int n){
	if(arbol==NULL){
		return;
	}
	
	else if(n< arbol->dato){
		eliminarder(arbol->izq,n);// busca por la izquierda
	}
	
	else if( n> arbol ->dato){
		eliminarder (arbol->der,n);//busca por la derecha
	}
	
	else { //si se encontro el valor
	
	eliminarNodo(arbol);
	}
}

void eliminarNodo2(Nodo *nodoeliminar){
	
	if(nodoeliminar->izq && nodoeliminar->der){//con dos hijos
		Nodo *menor = maximo(nodoeliminar -> der);
		nodoeliminar->dato=menor->dato;
		eliminarNodo(menor);
		
	}
	
	else if(nodoeliminar->izq){
		
		reemplazar(nodoeliminar,nodoeliminar->izq);
		destruirnodo(nodoeliminar);		
	}
	
	else if(nodoeliminar->der){
		reemplazar(nodoeliminar,nodoeliminar->der);
		destruirnodo(nodoeliminar);
	}
	
	else{		
		reemplazar(nodoeliminar,NULL);
		destruirnodo(nodoeliminar);	
	}
	
	
}

Nodo *maximo(Nodo *arbol){
	
	if(arbol==NULL){
		return NULL;
	}
	
	if(arbol->izq){
		return maximo(arbol -> der);
	}
	
	else{
		return arbol;
	}
}

void reemplazar2(Nodo *arbol, Nodo*nuevonodo){
	if(arbol -> padre){
		
		if(arbol->dato == arbol->padre->izq->dato){
			arbol->padre->izq=nuevonodo;
			
		}
		
		else if(arbol->dato==arbol->padre->der->dato){
			arbol->padre->der= nuevonodo;
		}
	}
	
	if(nuevonodo){
		nuevonodo->padre=arbol->padre;
	}
	
}

void destruirnodo2(Nodo *nodo){
	
	nodo->izq=NULL;
	nodo->der=NULL;
	
	delete nodo;
	
}

//////////////////////////////////////////////////////////////////


void menu1(){
	int dato;
	int op;
	
		do
		{
			
			cout<< "**************MENU************"<<endl;
			cout<< "1. Insertar un nuevo nodo"<<endl;
			cout<< "2. Mostrar arbol"<<endl;
			cout<< "3. Buscar Elemento"<<endl;
			cout<< "4. Eliminar Nodo IZQUIERDA"<<endl;
			cout<< "5. Eliminar Nodo DERECHA"<<endl;
			cout<< "OPCION:  ";
			cin>>op;
			
			switch(op){
				case 1: 
						cout<< "Ingrese un numero: ";
						cin>> dato;
						insertarNodo(arbol,dato,NULL);
						cout<<"\n";
						system ("pause");
						break;
						
				case 2: 
						system("cls");
						cout<< "Arbol Completo"<<endl;
						
						mostrarArbol(arbol, 0);
						cout << "   " << endl;
						gotoxy(1, 2);
						system("pause");
						break;
						
				case 3: 
				        system("cls");
						cout<< "Digite el elemento a buscar"<<endl;
						cin >> dato;
						if(busqueda(arbol,dato)== true){
							cout<< "Elemento" << dato << " Encontrado!!";
						}
						
						else{
							
							cout<< "Elemento no encontrado";
						}
						cout<<"\n";
						system ("pause");
						break;
						
				case 4:
						system("cls");
						cout<< "Ingrese el nodo a eliminar";
						cin>> dato;
						eliminarizq(arbol,dato);
						cout<< "\n";
						system ("pause");
						break;
						
				case 5:
						system("cls");
						cout<< "Ingrese el nodo a eliminar";
						cin>> dato;
						eliminarder(arbol,dato);
						cout<< "\n";
						system ("pause");
						break;
					
							}
		system ("cls");
		}
		while (op !=5);
}



int main()
{
menu1();	

}

