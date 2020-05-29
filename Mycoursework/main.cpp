#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

//Запись в файл рандомных чисел
void file(int M)
{
    int b[M];
    ofstream fout("input.txt");
    for(int i=0; i<M; i++)
    {
        b[i]=rand()%10;
        fout<<b[i]<<endl;
    }
    fout.close();
}
//Сортировка массива чисел которые "вмещаются" в оперативную память
void sort(string *arr, int n)
{
    //Сортировка Шeлла
    int d = n / 2; //Длина промежутков между элементами

    while (d > 0)
    {
        for (int i = 0; i < n - d; i++)
        {
            int j = i;
            while (j >= 0 && arr[j] > arr[j + d])
            {
                string temp = arr[j];
                arr[j] = arr[j + d];
                arr[j + d] = temp;

                j--;
            }
        }
        d = d/2;
    }
}//Чтение из большого файла элементов в массив строк(размер массива - количество "вмещающихся элементов")
int readFromFile(ifstream &fin, int n, string *arr)
{
	string buff;
	int i = 0;
	for (; !fin.eof() && i < n; i++)
	{
		getline(fin, buff);
		if (buff == "")
		{
			i--;
			continue; // пустые строки не записываем в массив и счетчик не увеличиваем
		}
		arr[i] = buff;
	}
	return i; //возвращаем, сколько элементов было записано в массив

}
//Печатаем массивы на экране - проверяем их содержимое
void print(string arr[], int N)
{

	cout << "[";
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << " ";
	}
	cout << "]" << endl;
}

//Функция записи в один из файлов массива из "вмещающихся" элементов
void writeToFile(ofstream &fout, int n, string *arr)
{
	for (int i = 0; i < n; ++i)
	{
		string buff = arr[i];
		if (buff != "")
			fout << buff << endl;
	}
}

void printC(string *c, int N)
{
	cout << "Print massiv c: ";
	cout << "[";
	for (int i = 0; i < N; i++)
	{
		cout << c[i] << " ";
	}
	cout << "]" << endl;
}
void merge(ifstream &fin1, ifstream &fin2, ofstream &fout1, ofstream &fout2, int n/*размер буффера*/, int currentAmountOfPortionsToWrite/*сколько частей записываем в каждый fout1/fout2*/)
{
	string a[n];
	string b[n];
	string c[n];
	int i = n, n_i = n, j = n, n_j = n, p = 0;
	bool writeElementsToFout1 = true;
	int writePortionCount = 0;

	int readPortionsFromFin1 = 0;
	int readPortionsFromFin2 = 0;

	do
	{
		if (p == n)
		{
			if (writeElementsToFout1 == true)
			{
				writeToFile(fout1, n, c);
			}
			else
			{
				writeToFile(fout2, p, c);
			}
			p = 0;
			writePortionCount++;
		}

		if (writePortionCount >= currentAmountOfPortionsToWrite)
		{
			writeElementsToFout1 = !writeElementsToFout1;
			writePortionCount = 0;
			readPortionsFromFin1 = 0;
			readPortionsFromFin2 = 0;
		}

		if (i == n_i)
		{
			if (readPortionsFromFin1 < currentAmountOfPortionsToWrite / 2) //дело в том, что мы читаем файл по порциям и мы можем залезть на следующую порцию, которая по плану должна сливаться в следующий массив с
			{
				n_i = readFromFile(fin1, n, a);
				readPortionsFromFin1++;
			}
			else
				n_i = 0;
			i = 0;
		}
		if (j == n_j)
		{
			if (readPortionsFromFin2 < currentAmountOfPortionsToWrite / 2)
			{
				n_j = readFromFile(fin2, n, b);
				readPortionsFromFin2++;
			}
			else
				n_j = 0;
			j = 0;
		}

		// начало ф-ии merge
		if (n_i == 0) // считываем и записываем в с хвост оставшегося файла, без слияния
		{
			while (j < n_j && p < n)
			{
				c[p] = b[j];
				j++;
				p++;
			}
		}
		else if (n_j == 0)
		{
			while (i < n_i && p < n)
			{
				c[p] = a[i];
				i++;
				p++;
			}
		}
		else

			while (i < n_i && j < n_j && p < n)
			{

				if (a[i] < b[j])
				{
					c[p] = a[i];
					i++;
				}
				else
				{
					c[p] = b[j];
					j++;
				}
				p++;
			}
		//конец merge

		if (writePortionCount >= currentAmountOfPortionsToWrite)
		{
			writeElementsToFout1 = !writeElementsToFout1;
			writePortionCount = 0;
			readPortionsFromFin1 = 0;
			readPortionsFromFin2 = 0;
		}
	} while (n_i != 0 || n_j != 0);

	if (p > 0) //если остался незаписанный хвост массива с, записываем его
	{
		if (writeElementsToFout1 == true)
			writeToFile(fout1, p, c);
		else
			writeToFile(fout2, p, c);
	}

}

//Функция выполняющая 2 часть алгоритма - попеременное записи и чтение то файлов А и В то файлов С  и Д
void sortControl(/*лимит буффера*/int n, /*количество сортируемых данных*/ int M)
{
	int currentAmountOfPortionsToWrite = 1;
	bool read_fileA_and_fileB = true;
	ifstream fin1;
	ifstream fin2;
	ofstream fout1;
	ofstream fout2;

	do
	{
		currentAmountOfPortionsToWrite = currentAmountOfPortionsToWrite * 2;

		if (read_fileA_and_fileB)
		{
			fin1.open("A.txt");
			fin2.open("B.txt");
			fout1.open("C.txt");
			fout2.open("D.txt");
			read_fileA_and_fileB = false;
		}
		else
		{
			fin1.open("C.txt");
			fin2.open("D.txt");
			fout1.open("A.txt");
			fout2.open("B.txt");
			read_fileA_and_fileB = true;
		}
		if (!fin1 || !fin2)
			cerr << "Uh oh, file could not be opened for reading!" << endl;

		merge(fin1, fin2, fout1, fout2, n, currentAmountOfPortionsToWrite);

		//close streams
		fin1.close();
		fin2.close();
		fout1.close();
		fout2.close();

	} while (currentAmountOfPortionsToWrite * n < M); // для M=100 выйдем из цикла, когда будет 16 * 10 >=100

}
int main()
{

   cout << "PLease enter the parametr for memory limit:  ";
	int N;
	cin >> N;

	cout << "сколько записей в хранилище?";
	int M;
	cin >> M;
	file(M);

	ifstream fin("input.txt");
	if (!fin)
	{
		cerr << "Uh oh, file could not be opened for reading!" << endl;
		return -1;
	}

	ofstream fout1("A.txt");
	ofstream fout2("B.txt");

	string arr[N];
	for (int i = 0; !fin.eof(); i++)
	{

		//arr = readFromFile(fin, N); //Чтение в массив из большого файла с учетом ограничений заданных в начале
		N = readFromFile(fin, N, arr);
		sort(arr, N); //Сортировка выбранных из большого файла 10 элементов
		print(arr, N); //Вывод массивов для проверки
		//Разбивка файла на части(на 2 файла меньшего размера поочередено записывая в них элементы из большого)
		if (i % 2 == 0)
		{
			writeToFile(fout1, N, arr);
		}
		else
			writeToFile(fout2, N, arr);
	}

	fin.close();
	fout1.close();
	fout2.close();

//////////////////////////////// 2 этап реализации алгоритма
    cout<<"Vvedite eshe ras rasmer byfera ";
    cin>>N;
	sortControl(N, M);

	cout<<"смотрите файл A.txt или C.txt, в одном из них все отсортированные записи!";

 return 0;
}
