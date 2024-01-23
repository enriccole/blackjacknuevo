#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARDS 52
#define CARD_VALUES 13
#define MAX_HAND 10

// Representación de las cartas
char *values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *suits[] = {"Corazones", "Diamantes", "Picas", "Tréboles"};

// Estructura para una carta
struct carta {
    char *value;
    char *suit;
    int numericValue;
};

struct carta deck[TOTAL_CARDS];
struct carta playerHand[MAX_HAND];
int numPlayerCards = 0;
int playerSum = 0;
char choice;

void initializeDeck() {
    for (int i = 0; i < TOTAL_CARDS; i++) {
        deck[i].value = values[i % CARD_VALUES];
        deck[i].suit = suits[i / CARD_VALUES];
        deck[i].numericValue = (i % CARD_VALUES) + 2;
        if (deck[i].numericValue > 10) deck[i].numericValue = 10;
        if (i % CARD_VALUES == CARD_VALUES - 1) deck[i].numericValue = 11;
    }
}

void shuffleDeck() {
    srand(time(NULL));
    for (int i = 0; i < TOTAL_CARDS; i++) {
        int j = rand() % TOTAL_CARDS;
        struct carta temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void showCard(struct carta c) {
    printf("  %s de %s\n", c.value, c.suit);
}

int sumHand(struct carta hand[], int numCards) {
    int sum = 0;
    for (int i = 0; i < numCards; i++) {
        sum += hand[i].numericValue;
    }
    return sum;
}

int main() {
    initializeDeck();
    shuffleDeck();

    printf("Bienvenido al Blackjack!\n");

    playerHand[numPlayerCards++] = deck[0];
    playerHand[numPlayerCards++] = deck[1];
    playerSum = sumHand(playerHand, numPlayerCards);

    printf("Tus cartas:\n");
    showCard(playerHand[0]);
    showCard(playerHand[1]);
    printf("Suma total: %d\n", playerSum);

    while (playerSum < 21) {
        printf("¿Quieres otra carta? (s/n): ");
        scanf(" %c", &choice);

        if (choice == 's' || choice == 'S') {
            playerHand[numPlayerCards] = deck[numPlayerCards +1];
            playerSum = sumHand(playerHand, ++numPlayerCards);

            printf("Nueva carta:\n");
            showCard(playerHand[numPlayerCards - 1]);
            printf("Suma total: %d\n", playerSum);
        } else {
            break;
        }
    }

    if (playerSum == 21) {
        printf("¡Blackjack! Has ganado.\n");
    } else if (playerSum > 21) {
        printf("Te has pasado. Fin del juego.\n");
    } else {
        printf("Te has plantado con %d. Fin del juego.\n", playerSum);
    }

    return 0;
}
