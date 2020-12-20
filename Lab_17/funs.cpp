#include "funs.h"

using namespace std;

/// <summary>
/// Функция вывода меню в консоль
/// </summary>
void menu()
{
	cout << " ______________________ MENU ______________________\n";
	cout << "|   1 Наибольшее расстояние между точками          |\n";
	cout << "|   2 Записать список сотрудников в файл           |\n";
	cout << "|__________________________________________________|\n";
	cout << "|   3 Точки (бинарно)                              |\n";
	cout << "|   4 Сотрудники (бинарно)                         |\n";
	cout << "|   5 Запись в бинарный файл чисел типа double     |\n";
	cout << "|   6 Поменять первое и последнее числа местами    |\n";
	cout << "|   7 Создать бинарный файл с точками вручную      |\n";
	cout << "|   8 Перезаписать текстовый файл в бинарный       |\n";
	cout << "|  10 Вывести бинарный файл с числами double       |\n";
	cout << "|__________________________________________________|\n";
	cout << "|   9 Меню                                         |\n";
	cout << "|   0 Выход                                        |\n";
	cout << "|__________________________________________________|\n";
}


/// <summary>
/// Функция ищет две точки точки, наиболее удалённые друг от друга
/// </summary>
/// <param name="file"> — исходный файл; в первой строке
/// записано количество точек на плоскости, далее в каждой строке - координаты очередной точки
/// </param>
void fun1(ifstream& file)
{
	int n, pti1{ -1 }, pti2{ -1 };  // n – кол-во точек в файле, pti1 & pti2 – индексы наиболее удалённых друг от друга точек
	double dist, max_dist = DBL_MIN;
	point p;
	file >> n;

	if (n < 2) {
		cout << "В файле недостаточно точек!\n";
		return;
	}

	// Заполяем список точек из файла
	point* points = new point[n];
	for (int i{ 0 }; i < n; ++i) {
		file >> p.x;
		file >> p.y;
		points[i] = p;
	}

	// Считаем расстояние между точками, берём самое большое
	for (int i{ 0 }; i < n; ++i) {
		for (int j{ i + 1 }; j < n; ++j) {
			dist = sqrt(pow(points[j].x - points[i].x, 2) + pow(points[j].y - points[i].y, 2));
			if (dist > max_dist) {
				max_dist = dist;
				pti1 = i;
				pti2 = j;
			}
		}
	}

	cout << "Наибольшее расстояние — " << max_dist << endl;
	cout << "Точки: (" << points[pti1].x << ", " << points[pti1].y << ") и (" << points[pti2].x << ", " << points[pti2].y << ")\n";
	delete[] points;
	return;
}


/// <summary>
/// Функция ищет две точки точки, наиболее удалённые друг от друга
/// </summary>
/// <param name="file_name"> — имя бинарного файла со списком точек; в первой строке
/// записано количество точек на плоскости, далее в каждой строке - координаты очередной точки</param>
void fun1_bin(string file_name)
{
	int n, pti1{ -1 }, pti2{ -1 };  // n – кол-во точек в файле, pti1 & pti2 – индексы наиболее удалённых друг от друга точек
	double dist, max_dist = DBL_MIN;

	fstream bfile(file_name + ".dat", ios::binary | ios::in);
	if (!bfile.is_open())
		cout << "Ошибка: не удалось открыть файл\n";
	else {
		bfile.read(reinterpret_cast<char*>(&n), sizeof(int));


		if (n < 2) {
			cout << "В файле недостаточно точек!\n";
			return;
		}

		// Заполяем список точек из файла
		point* points = new point[n];
		for (int i{ 0 }; i < n; ++i) {
			bfile.read(reinterpret_cast<char*>(&points[i]), sizeof(point));
		}

		// Считаем расстояние между точками, записываем самое большое
		for (int i{ 0 }; i < n; ++i) {
			for (int j{ i + 1 }; j < n; ++j) {
				dist = sqrt(pow(points[j].x - points[i].x, 2) + pow(points[j].y - points[i].y, 2));
				if (dist > max_dist) {
					max_dist = dist;
					pti1 = i;
					pti2 = j;
				}
			}
		}

		cout << "Наибольшее расстояние — " << max_dist << endl;
		cout << "Точки: (" << points[pti1].x << ", " << points[pti1].y << ") и (" << points[pti2].x << ", " << points[pti2].y << ")\n";
		delete[] points;
		bfile.close();
	}

	return;
}


void fun2(ofstream& output_file, person* employees_list, int size)
{
	// Функция записывает информацию про сотрудников в текстовый файл

	output_file << setw(30) << "ФИО сотрудника" << " | " << "Дата рождения" << " | " << "Пол" << '\n';
	for (int i{ 0 }; i < size; ++i) {
		output_file << setw(30) << employees_list[i].fullname << " | " << setw(13) << employees_list[i].birthday << " | " << employees_list[i].gender << '\n';
	}
	cout << "Сотрудники записаны в файл (см. сам файл)!\n";
	output_file.close();
}


void fun2_bin(string bfile_name, person* employees_list, int size)
{
	// Функция записывает информацию про сотрудников в бинарный файл

	fstream bfile(bfile_name + ".dat", ios::binary | ios::out);
	if (!bfile.is_open())
		cout << "Ошибка: не удалось открыть файл\n";
	else {
		for (int i{ 0 }; i < size; ++i) {
			bfile.write(reinterpret_cast<char*>(&employees_list[i]), sizeof(person));
		}
		cout << "Сотрудники записаны в файл!\n";
		bfile.close();
	}
	return;
}


/// <summary>
/// Функция создаёт бинарный файл с точками; ввод данных производит пользователь
/// </summary>
/// <param name="bfile_name"> — имя бинарного файла, в который записываются точки</param>
void create_dots_bin(string bfile_name)
{
	fstream bfile(bfile_name + ".dat", ios::binary | ios::out);
	if (!bfile.is_open())
		cout << "Ошибка: не удалось открыть файл\n";
	else {
		int n;
		cout << "Введите количество точек: ";
		cin >> n;
		bfile.write(reinterpret_cast<char*>(&n), sizeof(int));
		for (int i{ 0 }; i < n; ++i) {
			point p;
			cout << "x: "; cin >> p.x;
			cout << "y: "; cin >> p.y;
			bfile.write(reinterpret_cast<char*>(&p), sizeof(point));
		}

		bfile.close();
	}

	return;
}


/// <summary>
/// Функция переводит текстовый файл с точками в бинарный
/// </summary>
/// <param name="file_name"> — имя текстового файла с точками; имя нового бинарного файла</param>
void dots_from_txt_to_dat(string file_name)
{
	ifstream file(file_name + ".txt");
	if (!file.is_open())
		cout << "Не удалось открыть файл!\n";
	else {
		int n;
		file >> n;

		if (n < 2) {
			cout << "В файле недостаточно точек!\n";
			file.close();
			return;
		}

		fstream bfile(file_name + ".dat", ios::binary | ios::out);
		if (!bfile.is_open())
			cout << "Не удалось открыть файл!\n";
		else {
			bfile.write(reinterpret_cast<char*>(&n), sizeof(int));
			for (int i{ 0 }; i < n; ++i) {
				point p;
				file >> p.x;
				file >> p.y;
				bfile.write(reinterpret_cast<char*>(&p), sizeof(point));
			}

			bfile.close();
		}
		file.close();
	}

	return;
}


/// <summary>
/// Функция выводит список сотрудников из бинарного файла в консоль
/// </summary>
/// <param name="bfile_name"> — имя исходного бинарного файла</param>
void read_employees_from_file_bin(string bfile_name)
{
	fstream bfile(bfile_name + ".dat", ios::binary | ios::in);
	if (!bfile.is_open())
		cout << "Ошибка: не удалось открыть файл\n";
	else {
		cout << setw(30) << "ФИО сотрудника" << " | " << "Дата рождения" << " | " << "Пол" << '\n';
		person p;
		while (bfile.read(reinterpret_cast<char*>(&p), sizeof(person))) {
			cout << setw(30) << p.fullname << " | " << setw(13) << p.birthday << " | " << p.gender << '\n';
		}

		cout << "\n\n";
		bfile.close();
	}

	return;
}


/// <summary>
/// Функция создаёт бинарный файл с числами типа double; пользователь вводит числа в консоли
/// </summary>
/// <param name="bfile_name"> — имя исходного бинарного файла</param>
void create_double_file_bin(string bfile_name)
{
	double num;
	int k;
	fstream bfile(bfile_name + ".dat", ios::binary | ios::out);
	if (!bfile.is_open())
		cout << "Ошибка: не удалось открыть файл\n";
	else {
		cout << "Введите количество чисел для ввода: ";
		cin >> k;
		for (int i{ 1 }; i <= k; ++i) {
			cout << "Введите " << i << "-е число – ";
			cin >> num;
			bfile.write(reinterpret_cast<char*>(&num), sizeof(double));
		}


		bfile.close();
	}

	/*
	Неудачная реализация с вводом через строку. Почему то записывает, только целую часть от числа
	

	string num_s;
	double num_d;
	fstream bfile(bfile_name, ios::binary | ios::out);
	if (!bfile.is_open())
		cout << "Ошибка: не удалось открыть файл\n";
	else {
		cout << "Введите число (чтобы остановить ввод, введите \"-\")\n>> ";
		cin >> num_s;
		while (num_s != "-") {
			string::size_type sz;
			num_d = stod(num_s, &sz);
			cout << num_d;
			bfile.write(reinterpret_cast<char*>(&num_d), sizeof(double));
			cout << ">> ";
			cin >> num_s;
		}
		bfile.close();
	}
	*/

	return;
}


/// <summary>
/// Функция выводит в консоль числа типа double из бинарного файла
/// </summary>
/// <param name="bfile_name"> — имя исходного бинарного файла</param>
void read_double_file_bin(string bfile_name)
{
	double num;
	int i{ 0 };
	fstream bfile(bfile_name + ".dat", ios::binary | ios::in);
	if (!bfile.is_open())
		cout << "Ошибка: не удалось открыть файл\n";
	else {
		while (bfile.read(reinterpret_cast<char*>(&num), sizeof(double))) {
			cout << num << '\t';
			++i;

			// На одной строке не больше 8 чисел
			if (i % 8 == 0)
				cout << '\n';
		}
		cout << '\n';
		bfile.close();
	}

	return;
}


/// <summary>
/// Функция меняет первое и последнее числа в файле местами
/// </summary>
/// <param name="bfile_name"> — имя исходного бинарного файла</param>
void change_firts_and_last_nums(string bfile_name)
{
	double first_num{ 0 }, last_num{ 0 };
	fstream bfile(bfile_name + ".dat", ios::binary | ios::in | ios::out);
	if (!bfile.is_open())
		cout << "Ошибка: не удалось открыть файл\n";
	else {
		bfile.read(reinterpret_cast<char*>(&first_num), sizeof(double));
		bfile.seekg(-8, ios::end);
		bfile.read(reinterpret_cast<char*>(&last_num), sizeof(double));
		bfile.seekg(-8, ios::end);
		bfile.write(reinterpret_cast<char*>(&first_num), sizeof(double));
		bfile.seekg(0, ios::beg);
		bfile.write(reinterpret_cast<char*>(&last_num), sizeof(double));
		bfile.close();
	}
	return;
}