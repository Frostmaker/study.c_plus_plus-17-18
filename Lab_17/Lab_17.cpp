#include "funs.h"

int main()
{
	setlocale(LC_ALL, "rus");

	bool tf = true;
	int o;
	menu();
	while (tf) {

		cout << "Выберите пункт меню: ";
		cin >> o;

		switch (o) {
		case 1:
		{
			ifstream file("TestFile_2.txt");  // TestFile_1.txt
			if (!file.is_open())
				cout << "Не удалось открыть файл!\n";
			else {
				fun1(file);
				file.close();
			}
			break;
		}
		case 2:
		{
			ofstream file("TestFile_3.txt");
			if (!file.is_open())
				cout << "Не удалось открыть файл!\n";
			else {
				const int size{ 5 };
				person employees_list[size];
				person human0{ "Казаков Владислав Богданович", "16.09.1957", 'M' };
				person human1{ "Суворова Злата Ивановна", "01.09.1980", 'F' };
				person human2{ "Козлов Артём Иванович", "13.11.1980", 'M' };
				person human3{ "Осипова Злата Максимовна", "18.01.1940", 'F' };
				person human4{ "Соколова Виктория Матвеевна", "30.04.1991", 'F' };

				employees_list[0] = human0;
				employees_list[1] = human1;
				employees_list[2] = human2;
				employees_list[3] = human3;
				employees_list[4] = human4;


				fun2(file, employees_list, size);
			}
			break;
		}
		case 3:
		{
			string file_name;
			cout << "Введите название нового файла (без расширения): ";  // DotsFile_2 | DotsFile_1
			cin >> file_name;
			fun1_bin(file_name);
			break;
		}
		case 4:
		{
			string bfile_name;
			const int size{ 5 };
			person employees_list[size];
			person human0{ "Казаков Владислав Богданович", "16.09.1957", 'M' };
			person human1{ "Суворова Злата Ивановна", "01.09.1980", 'F' };
			person human2{ "Козлов Артём Иванович", "13.11.1980", 'M' };
			person human3{ "Осипова Злата Максимовна", "18.01.1940", 'F' };
			person human4{ "Соколова Виктория Матвеевна", "30.04.1991", 'F' };

			employees_list[0] = human0;
			employees_list[1] = human1;
			employees_list[2] = human2;
			employees_list[3] = human3;
			employees_list[4] = human4;
			cout << "Введите название нового файла (без расширения): ";
			cin >> bfile_name;
			fun2_bin(bfile_name, employees_list, 5);
			read_employees_from_file_bin(bfile_name);
			break;
		}
		case 5:
		{
			string bfile_name;
			cout << "Введите название нового файла (без расширения): ";
			cin >> bfile_name;

			create_double_file_bin(bfile_name);
			cout << "Файл успешно создан!\n";
			read_double_file_bin(bfile_name);
			break;
		}
		case 6:
		{
			string bfile_name;
			cout << "Введите название файла (без расширения): ";
			cin >> bfile_name;
			change_firts_and_last_nums(bfile_name);
			cout << "Числа перемещены!\n";
			read_double_file_bin(bfile_name);
			break;
		}
		case 7:
		{
			string file_name;
			cout << "Введите название нового файла (без расширения): ";
			cin >> file_name;
			create_dots_bin(file_name);
			cout << "Файл успешно создан!\n";

			break;
		}
		case 8:
		{
			// Можно написать .txt файл ручками и сделать его бинарную копию с этой функцией

			string file_name;
			cout << "Введите название текстового файла (без расширения): ";
			cin >> file_name;
			dots_from_txt_to_dat(file_name);
			cout << "Файл успешно перезаписан!\n";
			break;
		}
		case 10:
		{
			string bfile_name;
			cout << "Введите название файла (без расширения): ";
			cin >> bfile_name;
			read_double_file_bin(bfile_name);  // DoubleNumsFile_1
		}
		case 9:
			menu();
			break;
		case 0:
			tf = false;
			break;
		default:
			cout << "Нет такого пункта меню!\n";
		}
	}

	//system("pause");
	return 0;
}