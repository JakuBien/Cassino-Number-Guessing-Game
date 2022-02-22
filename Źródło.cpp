#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


class LotteryMachine {
public:
	int numbers[6];

	//Maszyna losujaca
	void startMachine() {
		for (int i = 0; i < 6; i++) {
			int num = (rand() % 49) + 1;

			for (int j = 0; j < 6; j++) {
				if (numbers[j] == num) {
					i--;
					break;
				}
			}

			numbers[i] = num;
		}
	}

	//Metoda wyswietla wygrywajace numery
	void printWinningNumb() {
		cout << "\nWinning numbers:" << endl;
		for (int i = 0; i < 6; i++) {
			cout << numbers[i] << "\t";
		}
	}
};

class Player {
	int player_num[6];
	int c;
	int start;
	int counter;
public:
	Player() : start(0), counter(0) {};

	//Ta metoda umozliwia graczowi ustawic swoje wyniki
	void setNumbers() {
		for (int i = 0; i < 6; i++) {
			cout << "Set " << i+1 << " number: ";
			cin >> c;
			if (!cin.good() || c > 49 || c < 1) {
				cout << "You can't choose this number. Try again." << endl;
				i--;
				continue;
			}

			int flag = checkNumbers(c);
			if (!flag) {
				cout << "You already chose that number." << endl;
				i--;
				continue;
			}
			player_num[i] = c;
		}
	}

	//Sprawdzenie czy wbrane liczby wygrywaja
	bool checkNumbers(int num) {
		for (int i = 0 ; i < 6 ; i++) {
			if (num == player_num[i]) {
				return false;
			}
		}
		return true;
	}

	//Komunikat rozpoczynajacy gre
	void startGame() {
		counter = 0;
		while (!start) {
			cout << "Choose 6 numbers between 1-49." << endl;
			setNumbers();

			cout << "Your numbers are set. Do you want to change them?" << endl;
			cout << "Start the game - 1\tChange numbers - 0" << endl;

			cin >> start;
			while (!cin.good() && (start != 1 && start != 0)) {
				cout << "No operation found. Try again: ";
				cin >> start;
			}
		}
	}

	//Metoda wyswietla numery gracza
	void printNumbers() {
		cout << "Your numbers:" << endl;
		for (int i = 0; i < 6; i++) {
			cout << player_num[i] << "\t";
		}
	}

	//Metoda oblicza koncowy wynik gracza
	void checkLottery(LotteryMachine lot) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				if (player_num[i] ==  lot.numbers[j]){
					counter++;
					cout << "\nWinning number: " << player_num[i];
					break;
				}
			}
		}
		cout << "\nScore: " << counter << "/6" << endl;
	}
};

int main() {
	cout << "Number Guessing Game" << endl << endl;
	srand(time(NULL));
	LotteryMachine machine;
	Player player;

	while (true) {
		player.startGame();
		machine.startMachine();

		player.printNumbers();
		machine.printWinningNumb();

		player.checkLottery(machine);

		cout << "Do you want to play again?" << endl;
		cout << "Play again - 1\tExit - 0" << endl;
		cout << "Input: ";
		int a;
		cin >> a;
		while (!cin.good() || (a != 0 && a != 1)) {
			cout << "Wrong input. Try again: ";
			cin >> a;
		}

		if (a == 0) {
			break;
		}
	}
	
	
	cout << "\nKoniec programu." << endl;
}