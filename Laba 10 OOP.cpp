#include <iostream>
#include <fstream>

using namespace std;

class Pair {

private:

	int First;
	double Second;

public:

	Pair() {}

	Pair(int first, double second) {

		setFirst(first);
		setSecond(second);
	}
	
	void setFirst(int first) { First = first; }
	void setSecond(double second) { Second = second; }

	int getFirst() { return First; }
	double getSecond() { return Second; }

	friend istream& operator>>(istream& stream, Pair& pair);
	friend ostream& operator<<(ostream& stream, Pair& pair);
	friend fstream& operator<<(fstream& stream, Pair& pair);
	friend fstream& operator>>(fstream& stream, Pair& pair);
	
	Pair& operator += (double variable) {

		int fullPart = variable;
			
		if (variable - fullPart == 0)
			First += variable;
		else
			Second += variable;

		return *this;
	}

};

istream& operator>>(istream& stream, Pair& pair) {

	cout << "Введите первое число пары: "; stream >> pair.First;
	cout << "Введите второе число пары: "; stream >> pair.Second;

	return stream;
}

ostream& operator<<(ostream& stream, Pair& pair) { return { stream << pair.First << " : " << pair.Second }; }

fstream& operator<<(fstream& stream, Pair& pair) {

	stream << pair.First << endl << pair.Second << endl;
	return stream;
}

fstream& operator>>(fstream& stream, Pair& pair) {

	stream >> pair.First;
	stream >> pair.Second;
	
	return stream;
}

void WriteToFile(int length) {

	fstream F1("F1.txt", ios::out | ios::trunc);

	if (!F1) {

		cout << "Не удалось открыть файл.";
		return;
	}

	for (int i = 0; i < length; i++) {

		Pair pair;
		cin >> pair;

		F1 << pair;
		cout << endl;
	}
	
	F1.close();
}

void printAFile() {

	fstream F1("F1.txt", ios::in);

	if (!F1) {

		cout << "Не удалось открыть файл.";
		return;
	}

	Pair pair;

	while (F1 >> pair) { cout << pair << endl; }
}

void addNumToPair(double num) {

	fstream F1("F1.txt", ios::in);

	fstream Temp("Temp.txt", ios::out | ios::trunc);

	Pair buffer;

	while (F1 >> buffer) {

		buffer += num;
		Temp << buffer << endl;
	}

	F1.close();
	Temp.close();

	remove("F1.txt");
	rename("Temp.txt", "F1.txt");
}

void addKElems(int position, int k) {

	if (position <= 0 || k <= 0) {

		cout << "Неправильная позиция: она должна быть >= 1" << endl;
		return;
	}

	fstream F1("F1.txt", ios::in);

	if (!F1) {

		cout << "Не удалось открыть файл.";
		return;
	}

	fstream Temp("Temp.txt", ios::out | ios::trunc);

	Pair buffer;

	int counter = 0;

	while (F1 >> buffer) {

		counter++;
		Temp << buffer << endl;

		if (counter == position) {
			
			for (int i = 0; i < k; i++) {
				
				Pair newPair;
				cin >> newPair;
				Temp << newPair << endl;
			}
		}
	}
	
	if (counter < position) { cout << "Введена позиция, которой нет в файле." << endl; }
	
	F1.close();
	Temp.close();

	remove("F1.txt");
	rename("Temp.txt", "F1.txt");
}

int main() {

	system("chcp 1251 > Null");

	int lenght;

	do { cout << "Введите кол-во пар в файле: "; cin >> lenght; } while (lenght <= 0);

	WriteToFile(lenght);

	bool shouldStop = false;

	while (!shouldStop) {

		cout << endl << endl;
		cout << "1 - Пересоздать файл\n2 - Добавить L ко всем элементам\n3 - Добавить К пар\n4 - Распечатать файл\n5 - Закончить работу программы";

		int choice;

		cout << "\n\nВаш выбор: "; cin >> choice;
		cout << endl;

		Pair comparePair;

		switch (choice) {

		case 1:

			do {

				cout << "Введите кол-во пар: "; cin >> lenght;
			} while (lenght <= 0);
			
			WriteToFile(lenght);
			break;

		case 2:
			
			double L;
			cout << "Введите число, на которое увеличиваем: "; cin >> L;
			cout << endl;

			addNumToPair(L);
			break;

		case 3:

			int k, position;

			cout << "Введите, на какую позицию добавляем: "; cin >> position;
			cout << "Введите, сколько пар добавляем: "; cin >> k;
			cout << endl;

			addKElems(position, k);
			break;

		case 4:

			printAFile();
			break;

		case 5:

			shouldStop = true;
			break;

		default:

			cout << "\nТакой команды нет." << endl;
			break;
		}
	}
	return 0;
}