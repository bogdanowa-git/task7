

#include <iostream>
#include<string>
#include <sstream>
#include <fstream>

using namespace std;

int Sum(string str_);
void InputFileName(string& fileName_);
bool isExFile(string fileName_);

int main()
{
	setlocale(LC_ALL, "Russian");
	int fl;
	do {
		system("cls");
		string fileName = "";
		cout << " Введите имя файла. Изначальный файл для теста: test.txt" << endl;
		cout << "Имя файла: ";
		
		InputFileName(fileName); //ввод и проверка имени файла для корректной работы программы дальше

		ifstream in(fileName); // Открытие файла на чтение
		string str;

		while (!in.eof()) // пока не конец файла считываем из него строки и направляем в функцию
		{
			getline(in, str); //считывание данных из файла и направление в функцию
			cout << "Сумма чисел из файла: " << Sum(str) << "\n";
		}
		system("pause");

		cout << "Введите строку: ";
		getline(cin, str); //считывание строки с клавиатуры и направление в функцию
		cout << "Сумма чисел из введенной строки: " << Sum(str) << "\n"; //вывод суммы строки с клавиатуры

		cout << "Повторить программу? 0 - нет, 1 - да: "; //повторение программы через цикл do while
		cin >> fl;
		

	} while (fl == 1);
}

int Sum(string str_)
{
	int sum = 0, num = 0, minusNum = 0; // sum - общая сумма, num - положительное число, minusNum - отрицательное число
	string numStr = "", minusNumStr = ""; // numStr - в этой строке хранится положительное число, minusNumStr - в этой строке хранится отрицательное число
	int i = 0;
	
	while (i < str_.length()) // до конца строки
	{
		
		if (str_[i] == '-' && isdigit(str_[i + 1])) // Определяем отрицательное число в строке. Если мы встречаем знак минус и след символ число, то:
		{
			
			i++; // переходим к символу, которое число
			
			while (isdigit(str_[i])) // пока символы являются числами (т.е мы считваем число)
			{
				
				minusNumStr += str_[i]; // в минусовую строку добавляем эти символы
				// Для того чтобы считать последнее число проверяем условие, что позиция в цикле последняя и что на этой позиции
				// стоит символ являющийся числом
				if (i == str_.length() - 1 && isdigit(str_[i]))
				{
					
					istringstream(minusNumStr) >> minusNum; // превращаем строку string в int
					
					sum -= minusNum; // из общей суммы вычитаем только что найденное отрицательное число
					minusNumStr = ""; // и "обнуляем" строку и число
					minusNum = 0;
				}
				
				i++; // переход к след. символу
			}
		}
		else
		{
			
			if (isdigit(str_[i])) // Если встретили не отрицательное число
			{
				while (isdigit(str_[i]))
				{
					numStr += str_[i]; //в строку добавляем символы
					// Для того чтобы считать последнее число проверяем условие, что позиция в цикле последняя и что на этой позиции
				    // стоит символ являющийся числом
					if (i == str_.length() - 1 && isdigit(str_[i]))
					{
						istringstream(numStr) >> num; // превращаем строку string в int
						sum += num; //к общей сумме прибавляем положительное число
						numStr = ""; //обнуляем число и строку
						num = 0;
					}
					i++; // переход к след. символу
				}
			}
			else  //Если дальше нет ни отриц., ни полож.чисел
			{
				istringstream(numStr) >> num; // преобразовываем строки minusNumStr и numStr в числа
				istringstream(minusNumStr) >> minusNum;
				sum = sum + num - minusNum; //добавляем преобразованные числа в сумму
				numStr = ""; //"обнуляем" строки и числа
				minusNumStr = "";
				num = 0;
				minusNum = 0;
			}
		}
		i++;
	}

	return sum;
}

void InputFileName(string& fileName_) //ввод и проверка имени файла
{
	
	do
	{
		getline(cin, fileName_); //ввод имени файла
		bool isCheck = true;
		if (!isExFile(fileName_)) //проверка на открытие файла
		{
			cout << "Файл с таким именем не открыт. Введите имя файла еще раз.\n";
			fileName_ = "";
		}
		else
			cout << "Все отлично!\n";
	} while (fileName_ == "");
}





bool isExFile(string fileName_) // Проверка на существование и открытие файла c введенным именем
{
	ifstream in(fileName_);
	if (in.is_open())
	{
		in.close();
		return true;
	}
	else
		return false;
}
