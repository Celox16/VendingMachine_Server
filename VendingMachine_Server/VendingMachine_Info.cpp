#include <stdio.h>
#include <string.h>

void SetVendingMachineInfo(char vendingMachineInfo[]) {
	// 0~4 = drink list
	// 5~11 = money list
	// 48 = 0
	// 49 = 1
	// 50 = 2
	// 51 = 3
	// 52

	vendingMachineInfo[0] = '3'; // water
	vendingMachineInfo[1] = '3'; // coffee
	vendingMachineInfo[2] = '3'; // ion_drink
	vendingMachineInfo[3] = '3'; // fine_coffee
	vendingMachineInfo[4] = '3'; // carbo_drink
	vendingMachineInfo[5] = '5'; // 5000won
	vendingMachineInfo[6] = '5'; // 1000won
	vendingMachineInfo[7] = '5'; // 500won
	vendingMachineInfo[8] = '5'; // 100won
	vendingMachineInfo[9] = '5'; // 50won
	vendingMachineInfo[10] = '5'; // 10won
}

void ReSetVendingFromClient(char vendingMachineInfo[], char ClientVending[])
{
	for (int i = 0; i < 12; i++) {
		vendingMachineInfo[i] = ClientVending[i];
	}
}