#include <iostream>
#include <random>
#include <time.h>

using namespace std;

// global variable
int numbers[9] = {1,2,3,4,5,6,7,8,9};
char types[3] = {'s','m','p'}; // 索子/条子，万子，筒子/饼子

/*
 * 0,1,2,3 = 1s
 * 4,5,6,7 = 2s
 * ...
 */

void shuffle(int quadPlot[]);
void findTile(int id);
void quadDistribution (int hand[], int &currentHand, int quadPlot[], int &remainTile);
void singleDistribution (int hand[], int &currentHand, int quadPlot[], int &remainTile);
void displayHand (int hand[], int currentHand);
void rankHandTile (int hand[], int currentHand);
void initialHand (int p1h[], int p2h[], int p3h[], int p4h[], int &p1c, int &p2c, int &p3c, int &p4c, int quadPlot[], int &remainTile);
int diceIndicator ();

int main() {
    srand(time(0)); // set seed

    int quadPlot[108];
    int playerDongHand[14];
    int playerNanHand[14];
    int playerXiHand[14];
    int playerBeiHand[14];
    int currentPlayerDongHandTileCount = 0;
    int currentPlayerNanHandTileCount = 0;
    int currentPlayerXiHandTileCount = 0;
    int currentPlayerBeiHandTileCount = 0;
    int remainTile = 108;

    shuffle(quadPlot);

    cout << "The result of two dices: " << diceIndicator() << endl;

    initialHand(playerDongHand, playerNanHand, playerXiHand, playerBeiHand, currentPlayerDongHandTileCount, currentPlayerNanHandTileCount, currentPlayerXiHandTileCount, currentPlayerBeiHandTileCount, quadPlot, remainTile);

    // Zhuang starts with one more tile
    singleDistribution(playerDongHand, currentPlayerDongHandTileCount, quadPlot, remainTile);

    cout << "Dong: ";
    displayHand(playerDongHand, currentPlayerDongHandTileCount);
    cout << endl;
    cout << "Nan: ";
    displayHand(playerNanHand, currentPlayerNanHandTileCount);
    cout << endl;
    cout << "Xi: ";
    displayHand(playerXiHand, currentPlayerXiHandTileCount);
    cout << endl;
    cout << "Bei: ";
    displayHand(playerBeiHand, currentPlayerBeiHandTileCount);
    cout << endl;

    cout << "Display tile mountain: " << endl;
    for (int i = 0; i < remainTile; i++) {
        findTile(quadPlot[remainTile - i]);

    }

    return 0;
}

void shuffle(int quadPlot[]) {
    for (int i = 0; i < 108; i++) {
        quadPlot[i] = i;
    }
    for (int i = (108 - 1); i >= 1; i--) {
        int j = rand() % (i + 1);
        int temp = quadPlot[i];
        quadPlot[i] = quadPlot[j];
        quadPlot[j] = temp;
    }
}

void findTile (int id) {
    int tileNumber = -1;
    char tileType = 'a';

    if (id % 36 >= 0 && id % 36 <= 3) {
        tileNumber = 1;
    }
    else if (id % 36 >= 4 && id % 36 <= 7) {
        tileNumber = 2;
    }
    else if (id % 36 >= 8 && id % 36 <= 11) {
        tileNumber = 3;
    }
    else if (id % 36 >= 12 && id % 36 <= 15) {
        tileNumber = 4;
    }
    else if (id % 36 >= 16 && id % 36 <= 19) {
        tileNumber = 5;
    }
    else if (id % 36 >= 20 && id % 36 <= 23) {
        tileNumber = 6;
    }
    else if (id % 36 >= 24 && id % 36 <= 27) {
        tileNumber = 7;
    }
    else if (id % 36 >= 28 && id % 36 <= 31) {
        tileNumber = 8;
    }
    else if (id % 36 >= 32 && id % 36 <= 35) {
        tileNumber = 9;
    }

    if (id >= 0 && id <= 35) {
        tileType = 's';
    }
    else if (id >= 36 && id <= 71) {
        tileType = 'm';
    }
    else if (id >= 72 && id <= 107) {
        tileType = 'p';
    }

    cout << tileNumber << tileType << " ";
}

void quadDistribution (int hand[], int &currentHand, int quadPlot[], int &remainTile) {
    for (int i = currentHand; i < 4 + currentHand; i++) {
        hand[i] = quadPlot[108 - remainTile];
        remainTile--;
    }
    currentHand += 4;
}

void singleDistribution (int hand[], int &currentHand, int quadPlot[], int &remainTile) {
    hand[currentHand] = quadPlot[108 - remainTile];
    remainTile--;
    currentHand++;
}

void rankHandTile (int hand[], int currentHand) {
    int temp = 0;
    for (int i = 0; i < currentHand - 1; i++) {
        for (int j = 0; j < currentHand - i - 1; j++) {
            if (hand[j] > hand[j + 1]) {
                temp = hand[j];
                hand[j] = hand[j + 1];
                hand[j + 1] = temp;
            }
        }
    }
}

void displayHand (int hand[], int currentHand) {
    rankHandTile(hand, currentHand);
    for (int i = 0; i < currentHand; i++) {
        findTile(hand[i]);
    }
}

void initialHand (int p1h[], int p2h[], int p3h[], int p4h[], int &p1c, int &p2c, int &p3c, int &p4c, int quadPlot[], int &remainTile) {
    for (int i = 0; i < 3; i++) {
        quadDistribution(p1h, p1c, quadPlot, remainTile);
        quadDistribution(p2h, p2c, quadPlot, remainTile);
        quadDistribution(p3h, p3c, quadPlot, remainTile);
        quadDistribution(p4h, p4c, quadPlot, remainTile);

        singleDistribution(p1h, p1c, quadPlot, remainTile);
        singleDistribution(p2h, p2c, quadPlot, remainTile);
        singleDistribution(p3h, p3c, quadPlot, remainTile);
        singleDistribution(p4h, p4c, quadPlot, remainTile);
    }
}

int diceIndicator () {
    int diceOneResult = rand() % 6 + 1;
    int diceTwoResult = rand() % 6 + 1;
    return diceOneResult + diceTwoResult;
}

//void rankPlotTile (int quadPlot[], int diceTotal) {
//    // 定义0号在哪里
//    if (diceTotal % 4 == 1) { // start with the plot in front of Dong
//
//    }
//}