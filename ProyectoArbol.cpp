#include <iostream>
using namespace std;

// ---------- Estructura del Nodo ----------
struct Nodo {
    int dato;
    Nodo *izq;
    Nodo *der;
};

// ---------- Crear un nuevo nodo ----------
Nodo *crearNodoNuevo(int valor) {
    Nodo *n = new Nodo();
    n->dato = valor;
    n->izq = NULL;
    n->der = NULL;
    return n;
}

// ---------- Insertar nodo automáticamente ----------
void insertarAutomatico(Nodo *&raiz, int valor) {
    if (raiz == NULL) {
        raiz = crearNodoNuevo(valor);
        return;
    }

    if (valor == raiz->dato) {
        cout << "El valor ya existe en el árbol. No se agregará.\n";
        return;
    }

    if (valor < raiz->dato)
        insertarAutomatico(raiz->izq, valor);
    else
        insertarAutomatico(raiz->der, valor);
}

// ---------- Recorridos ----------
void preorden(Nodo *nodo) {
    if (nodo == NULL) return;
    cout << nodo->dato << " ";
    preorden(nodo->izq);
    preorden(nodo->der);
}

void inorden(Nodo *nodo) {
    if (nodo == NULL) return;
    inorden(nodo->izq);
    cout << nodo->dato << " ";
    inorden(nodo->der);
}

void postorden(Nodo *nodo) {
    if (nodo == NULL) return;
    postorden(nodo->izq);
    postorden(nodo->der);
    cout << nodo->dato << " ";
}

// ---------- Calcular la altura ----------
int altura(Nodo *raiz) {
    if (raiz == NULL)
        return 0;
    int izq = altura(raiz->izq);
    int der = altura(raiz->der);
    return (izq > der ? izq : der) + 1;
}

// ---------- Imprimir árbol de forma visual ascendente ----------
void mostrarArbol(Nodo *raiz, int nivel = 0) {
    if (raiz == NULL)
        return;

    // Primero el subárbol derecho (valores mayores)
    mostrarArbol(raiz->der, nivel + 1);

    // Imprime el nodo con sangría para representar el nivel
    for (int i = 0; i < nivel; i++)
        cout << "   ";
    cout << raiz->dato << endl;

    // Luego el subárbol izquierdo (valores menores)
    mostrarArbol(raiz->izq, nivel + 1);
}

// ---------- Verificar si el árbol es binario válido ----------
bool esBinarioValido(Nodo* raiz, int min, int max) {
    if (raiz == NULL)
        return true;
    if (raiz->dato <= min || raiz->dato >= max)
        return false;
    return esBinarioValido(raiz->izq, min, raiz->dato) &&
           esBinarioValido(raiz->der, raiz->dato, max);
}

// ---------- Menú principal ----------
int main() {
    Nodo *raiz = NULL;
    int opcion, valor;

    do {
        cout << "\n======= MENU ÁRBOL BINARIO =======\n";
        cout << "1. Crear raíz del árbol\n";
        cout << "2. Insertar nodo hijo\n";
        cout << "3. Mostrar árbol (ascendente)\n";
        cout << "4. Recorridos (Pre, In, Post)\n";
        cout << "5. Verificar si es un árbol binario válido\n";
        cout << "6. Mostrar altura del árbol\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                if (raiz != NULL)
                    cout << "La raíz ya fue creada.\n";
                else {
                    cout << "Ingrese el valor de la raíz: ";
                    cin >> valor;
                    raiz = crearNodoNuevo(valor);
                    cout << "Raíz creada correctamente.\n";
                }
                break;

            case 2:
                if (raiz == NULL)
                    cout << "Debe crear la raíz primero.\n";
                else {
                    cout << "Ingrese el valor del nuevo nodo: ";
                    cin >> valor;
                    insertarAutomatico(raiz, valor);
                    cout << "Nodo insertado correctamente.\n";
                }
                break;

            case 3:
                if (raiz == NULL)
                    cout << "El árbol está vacío.\n";
                else {
                    cout << "\nEstructura del árbol (ascendente):\n";
                    mostrarArbol(raiz);
                }
                break;

            case 4:
                if (raiz == NULL)
                    cout << "El árbol está vacío.\n";
                else {
                    cout << "\nPreorden: ";
                    preorden(raiz);
                    cout << "\nInorden: ";
                    inorden(raiz);
                    cout << "\nPostorden: ";
                    postorden(raiz);
                    cout << endl;
                }
                break;

            case 5:
                if (raiz == NULL)
                    cout << "El árbol está vacío.\n";
                else {
                    bool valido = esBinarioValido(raiz, -999999, 999999);
                    if (valido)
                        cout << "? El árbol es binario de búsqueda válido.\n";
                    else
                        cout << "? El árbol NO cumple las propiedades de un ABB.\n";
                }
                break;

            case 6:
                cout << "La altura del árbol es: " << altura(raiz) << endl;
                break;

            case 7:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opción inválida, intente de nuevo.\n";
        }

    } while (opcion != 7);

    return 0;
}

