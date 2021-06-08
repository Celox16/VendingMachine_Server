#include <stdio.h>
#include <string.h>

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

//drinkInfo originDrink[DRINK_SIZE];
//moneyInfo originMoney[MONEY_SIZE];

// 처음의 초기값 설정 (고정값, 나중에 DB에서 받아오는 역할)
void SetInitial(drinkInfo initialDrink[], moneyInfo initialMoney[]) {
	//water
	strcpy(initialDrink[0].name, "water");
	initialDrink[0].price = 450;
	initialDrink[0].count = 3;

	//coffee
	strcpy(initialDrink[1].name, "coffee");
	initialDrink[1].price = 500;
	initialDrink[1].count = 3;

	//ion_drink
	strcpy(initialDrink[2].name, "ion_drink");
	initialDrink[2].price = 550;
	initialDrink[2].count = 3;

	//fine_coffee
	strcpy(initialDrink[3].name, "fine_coffee");
	initialDrink[3].price = 700;
	initialDrink[3].count = 3;

	//carbo_drink
	strcpy(initialDrink[4].name, "carbo_drink");
	initialDrink[4].price = 750;
	initialDrink[4].count = 3;

	initialMoney[0].value = 1000;
	initialMoney[0].count = 5;

	initialMoney[1].value = 500;
	initialMoney[1].count = 5;

	initialMoney[2].value = 100;
	initialMoney[2].count = 5;

	initialMoney[3].value = 50;
	initialMoney[3].count = 5;

	initialMoney[4].value = 10;
	initialMoney[4].count = 5;
}

// 클라이언트로 받은 결과를 서버의 drink에 복사하는 역할
void ModifyDrinkInfo(drinkInfo originDrink[], drinkInfo modifyDrink[]) {
	for (int i = 0; i < DRINK_SIZE; i++) {
		strcpy(originDrink[i].name, modifyDrink[i].name);
		originDrink[i].price = modifyDrink[i].price;
		originDrink[i].count = modifyDrink[i].count;
	}
}

// 클라이언트로 받은 결과를 서버의 money에 복사하는 역할
void ModifyMoneyInfo(moneyInfo originMoney[], moneyInfo modifyMoney[]) {
	for (int i = 0; i < MONEY_SIZE; i++) {
		originMoney[i].value = modifyMoney[i].value;
		originMoney[i].count = modifyMoney[i].count;
	}
}