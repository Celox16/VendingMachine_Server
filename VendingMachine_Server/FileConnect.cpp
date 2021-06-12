#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MONEY_SIZE 5
#define DRINK_SIZE 5

struct drinkInfo {
	char name[20];
	int price;
	int count;
};

struct moneyInfo {
	int value;
	int count;
};

void ReadFile(drinkInfo initialDrink[], moneyInfo initialMoeny[]) {
	FILE* drinkFile = NULL;
	FILE* moneyFile = NULL;

	drinkFile = fopen("drink.txt", "r");
	moneyFile = fopen("money.txt", "r");

	if (drinkFile == NULL || moneyFile == NULL) {
		fprintf(stderr, "file read fail!");
		exit(1);
	}

	for (int i = 0; i < DRINK_SIZE; i++) {
		fscanf(drinkFile, "%s %d %d", &initialDrink[i].name, &initialDrink[i].price, &initialDrink[i].count);
	}

	for (int i = 0; i < MONEY_SIZE; i++) {
		fscanf(moneyFile, "%d %d", &initialMoeny[i].value, &initialMoeny[i].count);
	}

	fclose(drinkFile);
	fclose(moneyFile);
}

void WriteDrinkFile(drinkInfo modifyDrink[]) {
	FILE* drinkFile = NULL;

	drinkFile = fopen("drink.txt", "w");

	if (drinkFile == NULL) {
		fprintf(stderr, "file read fail!");
		exit(1);
	}

	for (int i = 0; i < DRINK_SIZE; i++) {
		fprintf(drinkFile, "%s %d %d\n", modifyDrink[i].name, modifyDrink[i].price, modifyDrink[i].count);
	}

	fclose(drinkFile);
}

void WriteMoneyFile(moneyInfo modifyMoney[]) {
	FILE* moneyFile = NULL;

	moneyFile = fopen("money.txt", "w");

	if (moneyFile == NULL) {
		fprintf(stderr, "file read fail!");
		exit(1);
	}

	for (int i = 0; i < MONEY_SIZE; i++) {
		fprintf(moneyFile, "%d %d\n", modifyMoney[i].value, modifyMoney[i].count);
	}

	fclose(moneyFile);
}