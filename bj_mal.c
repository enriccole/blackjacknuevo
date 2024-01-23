#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARTAS 52
#define VALORES_CARTA 13
#define MAX_MANO 10

// Representación de las cartas
char *valores[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *palos[] = {"Corazones", "Diamantes", "Picas", "Treboles"};

// Estructura para una carta
struct carta {
    char *valor;
    char *palo;
    int valorNumerico;
};

struct carta mazo[TOTAL_CARTAS];
struct carta manoJugador[MAX_MANO];
int numCartasJugador = 0;
int sumaJugador = 0;
char eleccion;

// Función para ajustar la suma considerando los ases en la mano
int ajustarPorAses(int sumaActual, int numAses) {
    while (numAses > 0 && sumaActual > 21) {
        sumaActual -= 10;
        numAses--;
    }
    return sumaActual;
}

// Función para calcular la suma de la mano
int sumarMano(struct carta mano[], int numCartas) {
    int suma = 0;
    int numAses = 0;

    for (int i = 0; i < numCartas; i++) {
        suma += mano[i].valorNumerico;
        if (mano[i].valorNumerico == 11) {
            numAses++;
        }
    }

    // Ajuste para ases
    return ajustarPorAses(suma, numAses);
}

// Función para mostrar una carta
void mostrarCarta(struct carta c) {
    printf("  %s de %s\n", c.valor, c.palo);
}

// Función para inicializar el mazo y barajearlo
void inicializarYBarajearMazo() {
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        mazo[i].valor = valores[i % VALORES_CARTA];
        mazo[i].palo = palos[i / VALORES_CARTA];
        mazo[i].valorNumerico = (i % VALORES_CARTA) + 2;
        if (mazo[i].valorNumerico > 10) mazo[i].valorNumerico = 10;
        if (i % VALORES_CARTA == VALORES_CARTA - 1) mazo[i].valorNumerico = 11;
    }

    srand(time(NULL));
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        int j = rand() % TOTAL_CARTAS;
        struct carta temp = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temp;
    }
}

int main() {
    // Inicializar y barajear el mazo
    inicializarYBarajearMazo();

    printf("Bienvenido al Blackjack!\n");

    // Repartir las primeras dos cartas al jugador
    manoJugador[numCartasJugador++] = mazo[0];
    manoJugador[numCartasJugador++] = mazo[1];
    sumaJugador = sumarMano(manoJugador, numCartasJugador);

    printf("Tus cartas:\n");
    mostrarCarta(manoJugador[0]);
    mostrarCarta(manoJugador[1]);
    printf("Suma total: %d\n", sumaJugador);

    // Turno del jugador para recibir más cartas
    while (sumaJugador < 21) {
        printf("Quieres otra carta? (s/n): ");
        scanf(" %c", &eleccion);

        if (eleccion == 's' || eleccion == 'S') {
            manoJugador[numCartasJugador] = mazo[numCartasJugador];
            sumaJugador = sumarMano(manoJugador, ++numCartasJugador);

            printf("Nueva carta:\n");
            mostrarCarta(manoJugador[numCartasJugador - 1]);
            printf("Suma total: %d\n", sumaJugador);
        } else {
            break;
        }
    }

    // Determinar el resultado del juego
    if (sumaJugador == 21) {
        printf("¡Blackjack! Has ganado.\n");
    } else if (sumaJugador > 21) {
        printf("Te has pasado. Fin del juego.\n");
    } else {
        printf("Te has plantado con %d. Fin del juego.\n", sumaJugador);
    }

    return 0;
}
