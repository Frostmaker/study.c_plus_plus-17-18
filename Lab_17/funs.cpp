#include "funs.h"

using namespace std;

/// <summary>
/// ������� ������ ���� � �������
/// </summary>
void menu()
{
	cout << " ______________________ MENU ______________________\n";
	cout << "|   1 ���������� ���������� ����� �������          |\n";
	cout << "|   2 �������� ������ ����������� � ����           |\n";
	cout << "|__________________________________________________|\n";
	cout << "|   3 ����� (�������)                              |\n";
	cout << "|   4 ���������� (�������)                         |\n";
	cout << "|   5 ������ � �������� ���� ����� ���� double     |\n";
	cout << "|   6 �������� ������ � ��������� ����� �������    |\n";
	cout << "|   7 ������� �������� ���� � ������� �������      |\n";
	cout << "|   8 ������������ ��������� ���� � ��������       |\n";
	cout << "|  10 ������� �������� ���� � ������� double       |\n";
	cout << "|__________________________________________________|\n";
	cout << "|   9 ����                                         |\n";
	cout << "|   0 �����                                        |\n";
	cout << "|__________________________________________________|\n";
}


/// <summary>
/// ������� ���� ��� ����� �����, �������� �������� ���� �� �����
/// </summary>
/// <param name="file"> � �������� ����; � ������ ������
/// �������� ���������� ����� �� ���������, ����� � ������ ������ - ���������� ��������� �����
/// </param>
void fun1(ifstream& file)
{
	int n, pti1{ -1 }, pti2{ -1 };  // n � ���-�� ����� � �����, pti1 & pti2 � ������� �������� �������� ���� �� ����� �����
	double dist, max_dist = DBL_MIN;
	point p;
	file >> n;

	if (n < 2) {
		cout << "� ����� ������������ �����!\n";
		return;
	}

	// �������� ������ ����� �� �����
	point* points = new point[n];
	for (int i{ 0 }; i < n; ++i) {
		file >> p.x;
		file >> p.y;
		points[i] = p;
	}

	// ������� ���������� ����� �������, ���� ����� �������
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

	cout << "���������� ���������� � " << max_dist << endl;
	cout << "�����: (" << points[pti1].x << ", " << points[pti1].y << ") � (" << points[pti2].x << ", " << points[pti2].y << ")\n";
	delete[] points;
	return;
}


/// <summary>
/// ������� ���� ��� ����� �����, �������� �������� ���� �� �����
/// </summary>
/// <param name="file_name"> � ��� ��������� ����� �� ������� �����; � ������ ������
/// �������� ���������� ����� �� ���������, ����� � ������ ������ - ���������� ��������� �����</param>
void fun1_bin(string file_name)
{
	int n, pti1{ -1 }, pti2{ -1 };  // n � ���-�� ����� � �����, pti1 & pti2 � ������� �������� �������� ���� �� ����� �����
	double dist, max_dist = DBL_MIN;

	fstream bfile(file_name + ".dat", ios::binary | ios::in);
	if (!bfile.is_open())
		cout << "������: �� ������� ������� ����\n";
	else {
		bfile.read(reinterpret_cast<char*>(&n), sizeof(int));


		if (n < 2) {
			cout << "� ����� ������������ �����!\n";
			return;
		}

		// �������� ������ ����� �� �����
		point* points = new point[n];
		for (int i{ 0 }; i < n; ++i) {
			bfile.read(reinterpret_cast<char*>(&points[i]), sizeof(point));
		}

		// ������� ���������� ����� �������, ���������� ����� �������
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

		cout << "���������� ���������� � " << max_dist << endl;
		cout << "�����: (" << points[pti1].x << ", " << points[pti1].y << ") � (" << points[pti2].x << ", " << points[pti2].y << ")\n";
		delete[] points;
		bfile.close();
	}

	return;
}


void fun2(ofstream& output_file, person* employees_list, int size)
{
	// ������� ���������� ���������� ��� ����������� � ��������� ����

	output_file << setw(30) << "��� ����������" << " | " << "���� ��������" << " | " << "���" << '\n';
	for (int i{ 0 }; i < size; ++i) {
		output_file << setw(30) << employees_list[i].fullname << " | " << setw(13) << employees_list[i].birthday << " | " << employees_list[i].gender << '\n';
	}
	cout << "���������� �������� � ���� (��. ��� ����)!\n";
	output_file.close();
}


void fun2_bin(string bfile_name, person* employees_list, int size)
{
	// ������� ���������� ���������� ��� ����������� � �������� ����

	fstream bfile(bfile_name + ".dat", ios::binary | ios::out);
	if (!bfile.is_open())
		cout << "������: �� ������� ������� ����\n";
	else {
		for (int i{ 0 }; i < size; ++i) {
			bfile.write(reinterpret_cast<char*>(&employees_list[i]), sizeof(person));
		}
		cout << "���������� �������� � ����!\n";
		bfile.close();
	}
	return;
}


/// <summary>
/// ������� ������ �������� ���� � �������; ���� ������ ���������� ������������
/// </summary>
/// <param name="bfile_name"> � ��� ��������� �����, � ������� ������������ �����</param>
void create_dots_bin(string bfile_name)
{
	fstream bfile(bfile_name + ".dat", ios::binary | ios::out);
	if (!bfile.is_open())
		cout << "������: �� ������� ������� ����\n";
	else {
		int n;
		cout << "������� ���������� �����: ";
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
/// ������� ��������� ��������� ���� � ������� � ��������
/// </summary>
/// <param name="file_name"> � ��� ���������� ����� � �������; ��� ������ ��������� �����</param>
void dots_from_txt_to_dat(string file_name)
{
	ifstream file(file_name + ".txt");
	if (!file.is_open())
		cout << "�� ������� ������� ����!\n";
	else {
		int n;
		file >> n;

		if (n < 2) {
			cout << "� ����� ������������ �����!\n";
			file.close();
			return;
		}

		fstream bfile(file_name + ".dat", ios::binary | ios::out);
		if (!bfile.is_open())
			cout << "�� ������� ������� ����!\n";
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
/// ������� ������� ������ ����������� �� ��������� ����� � �������
/// </summary>
/// <param name="bfile_name"> � ��� ��������� ��������� �����</param>
void read_employees_from_file_bin(string bfile_name)
{
	fstream bfile(bfile_name + ".dat", ios::binary | ios::in);
	if (!bfile.is_open())
		cout << "������: �� ������� ������� ����\n";
	else {
		cout << setw(30) << "��� ����������" << " | " << "���� ��������" << " | " << "���" << '\n';
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
/// ������� ������ �������� ���� � ������� ���� double; ������������ ������ ����� � �������
/// </summary>
/// <param name="bfile_name"> � ��� ��������� ��������� �����</param>
void create_double_file_bin(string bfile_name)
{
	double num;
	int k;
	fstream bfile(bfile_name + ".dat", ios::binary | ios::out);
	if (!bfile.is_open())
		cout << "������: �� ������� ������� ����\n";
	else {
		cout << "������� ���������� ����� ��� �����: ";
		cin >> k;
		for (int i{ 1 }; i <= k; ++i) {
			cout << "������� " << i << "-� ����� � ";
			cin >> num;
			bfile.write(reinterpret_cast<char*>(&num), sizeof(double));
		}


		bfile.close();
	}

	/*
	��������� ���������� � ������ ����� ������. ������ �� ����������, ������ ����� ����� �� �����
	

	string num_s;
	double num_d;
	fstream bfile(bfile_name, ios::binary | ios::out);
	if (!bfile.is_open())
		cout << "������: �� ������� ������� ����\n";
	else {
		cout << "������� ����� (����� ���������� ����, ������� \"-\")\n>> ";
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
/// ������� ������� � ������� ����� ���� double �� ��������� �����
/// </summary>
/// <param name="bfile_name"> � ��� ��������� ��������� �����</param>
void read_double_file_bin(string bfile_name)
{
	double num;
	int i{ 0 };
	fstream bfile(bfile_name + ".dat", ios::binary | ios::in);
	if (!bfile.is_open())
		cout << "������: �� ������� ������� ����\n";
	else {
		while (bfile.read(reinterpret_cast<char*>(&num), sizeof(double))) {
			cout << num << '\t';
			++i;

			// �� ����� ������ �� ������ 8 �����
			if (i % 8 == 0)
				cout << '\n';
		}
		cout << '\n';
		bfile.close();
	}

	return;
}


/// <summary>
/// ������� ������ ������ � ��������� ����� � ����� �������
/// </summary>
/// <param name="bfile_name"> � ��� ��������� ��������� �����</param>
void change_firts_and_last_nums(string bfile_name)
{
	double first_num{ 0 }, last_num{ 0 };
	fstream bfile(bfile_name + ".dat", ios::binary | ios::in | ios::out);
	if (!bfile.is_open())
		cout << "������: �� ������� ������� ����\n";
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