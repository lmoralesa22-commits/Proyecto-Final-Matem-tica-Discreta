#include <iostream>
#include <climits> // Para INT_MIN y INT_MAX
#include <string>
using namespace std;

//Nodos de arboles 
struct Nodo {
    int dato;
    Nodo *der;
    Nodo *izq;
};

//Función para la creacion de un nodo nuevo
Nodo *crearNodoNuevo(int numero) {
    Nodo *nodo = new Nodo();
    nodo->dato = numero;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

//Buscar un nodo por su valor dentro del arbol
Nodo* buscarValor(Nodo *raiz, int numero) {

    if (raiz == NULL)
        return NULL;

    if (raiz->dato == numero)
        return raiz;

    Nodo *resultado = buscarValor(raiz->izq, numero);
    if (resultado != NULL)
        return resultado;

    return buscarValor(raiz->der, numero);
}

// saber si un valor ya esta existente en el arbol
bool existeValor(Nodo *raiz, int numero) {
    return buscarValor(raiz, numero) != NULL;
}

//Insertar un nuevo hijo en un nodo específico
void agregarNodo(Nodo* raiz) {
    if (raiz == NULL) {
        cout << "Debe de crear la raiz\n";
        return;
    }

    int padre, hijo;
    char posicion;

    cout << "Ingrese el valor del nodo padre: ";
    cin >> padre;

    Nodo *nodoPadre = buscarValor(raiz, padre);
    if (nodoPadre == NULL) {
        cout << "No existe un nodo con ese valor\n";
        return;
    }

    cout << "Ingrese el valor del nuevo hijo: ";
    cin >> hijo;

    if (existeValor(raiz, hijo)) {
        cout << "El valor ya existe en el arbol. No se agregara\n";
        return;
    }

    cout << "Desea colocar a la izquierda (I) o a la derecha (D)? ";
    cin >> posicion;

    Nodo *nuevoHijo = crearNodoNuevo(hijo);

    if ((posicion == 'I' || posicion == 'i') && nodoPadre->izq == NULL) {
        nodoPadre->izq = nuevoHijo;
    }
    else if ((posicion == 'D' || posicion == 'd') && nodoPadre->der == NULL) {
        nodoPadre->der = nuevoHijo;
    }
    else {
        cout << "No se puede agregar: lado ocupado o entrada invalida\n";
    }
}

// Mostrar el arbol de forma textual
void imprimirArbol(Nodo *raiz, int nivel = 0) {
    if (raiz == NULL)
        return;

    imprimirArbol(raiz->der, nivel + 1);

    for (int i = 0; i < nivel; i++)
        cout << "   ";

    cout << raiz->dato << endl;

    imprimirArbol(raiz->izq, nivel + 1);
}

// ---- Funciones de recorrido ----
void preorden(Nodo *nodo);
void inorden(Nodo *nodo);
void postorden(Nodo *nodo);

// Funciones para recorrer árbol en in, pre y post orden
void leerarbol(Nodo *raiz) {
    if (raiz == NULL) {
        cout << "El árbol es nulo o está vacío \n";
        return;
    }

    cout << "Ordenando nodos en pre-orden" << endl;
    preorden(raiz);
    cout << endl;

    cout << "Ordenando nodos en in-orden" << endl;
    inorden(raiz);
    cout << endl;

    cout << "Ordenando nodos en post-orden" << endl;
    postorden(raiz);
    cout << endl;
}

void preorden(Nodo *nodo) {
    if (nodo == NULL) {
        return;
    }

    cout << nodo->dato << " ";
    preorden(nodo->izq);
    preorden(nodo->der);
}

void inorden(Nodo *nodo) {
    if (nodo == NULL) {
        return; // devuelve nada si el árbol no tiene ningún elemento o no encuentra otro nodo que procesar
    }

    inorden(nodo->izq);
    cout << nodo->dato << " ";
    inorden(nodo->der); // Lee primero si hay un nodo izq, sino, lee la raíz, o sino, va hacia la derecha si lo hay. (I.R.D.)
}

void postorden(Nodo *nodo) {
    if (nodo == NULL) {
        return;
    }

    postorden(nodo->izq);
    postorden(nodo->der);
    cout << nodo->dato << " ";
}

// ---- Función para determinar si el árbol es binario ----
bool esa_ondaesbinaria(Nodo* raiz, int menor, int mayor) { //Parámetros: Raíz en cuestión o nodo, nodo menor, nodo mayor
    if (raiz == NULL) {
        return true;
    }

    if (raiz->dato <= menor || raiz->dato >= mayor) {
        return false;
    }

    return esa_ondaesbinaria(raiz->izq, menor, raiz->dato) &&
           esa_ondaesbinaria(raiz->der, raiz->dato, mayor);
} 
// La función lee y verifica si cada nodo tiene dos, más o menos valores, o si es que cumple con las condiciones para considerarlo un árbol binario

void generobinario(Nodo* raiz) {
    if (raiz == NULL) {
        cout << "No hay nada en el árbol aún...";
        return;
    }

    bool esbinaria = esa_ondaesbinaria(raiz, INT_MIN, INT_MAX);

    string motivo_nega = "no cumple con las condiciones, como orden de izquierda a derecha, o algún nodo tiene más de 2 hijos.";
    string motivo_posi = "cumple con las condiciones, como orden de izquierda a derecha y todos los nodos tienen menos de 3 hijos.";

    if (esbinaria == true) {
        cout << "El árbol es binario ya que " << motivo_posi << endl;
    } else {
        cout << "El árbol se identifica como NO binario porque " << motivo_nega << endl;
    }
} // Esta función llama a la función esa_ondaesbinaria para leer el árbol y devolver un valor que procesa esta función e imprime si es binaria o no.

int Altura(Nodo* raiz) {
    if (raiz == NULL)
        return 0;  // Un árbol vacío tiene altura 0
    int alturaIzq = Altura(raiz->izq);
    int alturaDer = Altura(raiz->der);
    return 1 + max(alturaIzq, alturaDer);  // Altura = 1 + altura máxima de subárboles
}

//Menu para seleccionar la opcion que se desea utilizar.
int main() {
    Nodo *raiz = NULL;
    int opcion;

    do {
        cout << "\n***Menu tipos de arboles***" << endl;
        cout << "1. Establecer una raiz" << endl;
        cout << "2. Agregar hijos a un nodo" << endl;
        cout << "3. Mostrar arbol creado" << endl;
        cout << "4. Ordenar nodos en los 3 órdenes" << endl;
        cout << "5. Verificar si es un árbol binario" << endl;
        cout << "6. Obtener el tamaño del árbol" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opcion del menu";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                if (raiz != NULL) {
                    cout << "La raíz ya existe." << endl;
                } else {
                    int valorRaiz;
                    cout << "Ingrese el valor de la raíz: ";
                    cin >> valorRaiz;
                    raiz = crearNodoNuevo(valorRaiz);
                    cout << "Raíz creada correctamente." << endl;
                }
                break;
            }

            case 2:
                agregarNodo(raiz);
                break;

            case 3:
                if (raiz == NULL)
                    cout << "El árbol está vacío.\n";
                else {
                    cout << "Estructura del árbol:\n";
                    imprimirArbol(raiz);
                }
                break;

            case 4:
                leerarbol(raiz);
                break;

            case 5:
                generobinario(raiz);
                break;

            case 6:{
                int h = Altura(raiz);
                cout << "La altura del árbol es de " << h << endl;
                break;
            }
            case 7: {
                cout << "Saliendo del programa..." << endl;
                break;
            }
            default: {
                cout << "La opcion es invalida, ingrese otro numero." << endl;
                break;
            }
        }

    } while (opcion != 7);

    return 0;
}
