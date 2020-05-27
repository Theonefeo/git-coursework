#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

//Запись в файл рандомных чисел
void file(int SizeOfTheSourceArray)
{
    int b[SizeOfTheSourceArray];
    ofstream fout("input.txt");
    for(int i=0; i<SizeOfTheSourceArray; i++)
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
}
//Чтение из большого файла элементов в массив строк(размер массива - количество "вмещающихся элементов")
int readFromFile(ifstream &fin, int n, string *arr)
{
    string buff;
    int i = 0;
    for (; !fin.eof() && i < n; i++)
    {
        getline(fin, buff);
        if (buff == "")
        {
            i--; //Если осталось 3 элемента а мы читаем по 5 из файла то следовательно пустые строки надо убрать - для этого и нужна эта доп ветка
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
/////////////////2 этап алгоритма
void printC(string *c, int N)
{
    cout<<"Print massiv c: ";
    cout << "[";
    for (int i = 0; i < N; i++)
    {
        cout << c[i] << " ";
    }
    cout << "]" << endl;
}
//Функция слияния элементов массива а и б в результирующий с(д)
void merge(string *a, int &i, int &n_i, string *b, int &j, int &n_j, string *c, int &p, int n) //n_i, n_j - для случая, если в a и b записалось меньше чем n элементов
{

    if (n_i == 0) // считываем и записываем в с хвост оставшегося файла, без слияния
    {
        while (j < n_j && p < n*2)
        {
            c[p] = b[j];
            j++;
            p++;
        }
    }
    else if (n_j == 0)
    {
        while (i < n_i && p < n*2)
        {
            c[p] = a[i];
            i++;
            p++;
        }
    }

//Слияние: идем по массивам а и b сравнивая элемемнты и заполняя массив с(д) который потом запишим в файл С(Д)
    while ( !(i == n_i && j == n_j && p == n*2))
    {

        if (j!=n_j)
        {
            if(i!=n_i)
            {
            if(a[i] < b[j])
            {
                c[p] = a[i];
                i++;
                p++;
            }
            else if(a[i]>=b[j])
            {
                c[p] = b[j];
                j++;
                p++;
            }
            }
        }
        if(i==n_i && p!=n*2)
        {
            c[p] = b[j];
            j++;
            p++;
        }
        else if(j==n_j && p!=n*2)
        {
            c[p]=a[i];
            i++;
            p++;
        }

    }
    /*while (i < n_i && j < n_j && p < n)
    {

    	if ((p == 0 ? true : c[p - 1] < a[i]) && a[i] < b[j])
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
    }*/

}
//Функция выполняющая 2 часть алгоритма - попеременное записи и чтение то файлов А и В то файлов С  и Д
void sortControl(/*лимит буффера. 5 по умолчанию*/int n = 5, /*количество сортируемых данных*/
        int M = 100)
{

    int currentAmountOfPortionsToWrite = 1;
    bool read_fileA_and_fileB = true;

    string a[n];
    string b[n];
    string c[n*2];
    int i = 0, j = 0, p = 0;
    int n_i = n, n_j = n;

    do
    {


        ifstream fin1;
        ifstream fin2;
        ofstream fout1;
        ofstream fout2;

        /*int i = 0, j = 0, p = 0;*/
        n_i = n, n_j = n; //записываем элементы от i до n_i и от j до n_j
//	int Cnt = 0; //Сколько раз подряд записали в один файлов 10(количество вмещающихся элементов в оп.память) порций

//	int ccc = 100;

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

        readFromFile(fin1, n, a); //Так как мы заходим в функцию с массивыми пустыми то мы должны их заполнить соотсветсвенно элементами
        readFromFile(fin2, n, b);

//		ofstream *curFout = &fout1;

//		Cnt = 0; //Сколько раз подряд записали в один файлов 10(количество вмещающихся элементов в оп.память) порций
        bool writeElementsToFout1 = true;
        int writePortionCount = 0;

        if (fin1.eof() || fin2.eof())
            cout << "один из файлов A,B,C,D пуст" << endl;
        do
        {

            if (writePortionCount >= currentAmountOfPortionsToWrite)
            {
                writeElementsToFout1 = !writeElementsToFout1;
                writePortionCount = 0;
            }

            /*cout << "Print massv a  ";
            print(a, n_i);
            cout << "Print massv b ";
            print(b, n_j);
            cout << "Print massv c ";
            print(c, n*2);
            cout << endl << endl;*/

            merge(a, i, n_i, b, j, n_j, c, p, n);

            cout << "Print massv a  ";
            print(a, n_i);
            cout << "Print massv b ";
            print(b, n_j);
            cout << "Print massv c ";
            print(c, n*2);
            cout << endl << endl;

            if (p >= n*2) //Если количество элементов массива с равно 10 (ограничение на оп.память) то записываем его в файл С
            {
                cout << "writeToFileC: ";
                printC(c, n*2);
                cout << endl;

                if (writeElementsToFout1 == true)
                {
                    writeToFile(fout1, p, c);
                }
                else
                {
                    writeToFile(fout2, p, c);
                }
                p = 0;
                writePortionCount++;
            }
            //если указатель дошел до конца массива а(то есть i указывает на последний элемент)-значит массив полностью прочитан и его надо перезаписать
            if (i >= n_i && p==0)
            {
                //перезапись массива а
                n_i = readFromFile(fin1, n, a);
                i = 0;
            }
            //если указатель дошел до конца массива б-значит массив полностью прочитан и его надо перезаписать
            if (j >= n_j && i==0 && p==0)
            {
                //перезапись массива b
                n_j = readFromFile(fin2, n, b);
                j = 0;
            }

        }while (n_i + n_j >= n*2);   //выйдем из цикла, когда в 2 массива запишется меньше, чем n элементов

        if (p > 0)
        {
            //записываем хвост файла
            if (writeElementsToFout1 == true)
                writeToFile(fout1, p, c);
            else
                writeToFile(fout2, p, c);
            cout << "tail. array c ";
            print(c, p);
        }

//close streams
        fin1.close();
        fin2.close();
        fout1.close();
        fout2.close();

    }
    while (currentAmountOfPortionsToWrite * 10 < M);   // для M=100 выйдем из цикла, когда будет 16 * 10 >=100
}
int main()
{

    //cout<<"Please inter the element in the file ";
    //int SizeOfTheSourceArray;
    //cin>>SizeOfTheSourceArray;
    //file(SizeOfTheSourceArray);
    //проверка на то, пустой ли файл или нет
    //const char filename[] = "input.txt";

    /*FILE* f = fopen(filename, "rb");
    if(!file)
    {
        cout << "File is not exists" << endl;// файл не найден

    }

    char h;
    size_t readed = fread(&h, 1, 1, f);

    if(readed)
        cout << "File contains data" << endl; // в файле находятся данные
    else
        cout << "File NOT contains data" << endl; //в файле не находятся данные - файл пустой
     */
////////////////
    /*      ifstream fin("input.txt");
    if (!fin)
    {
    	cerr << "Uh oh, file could not be opened for reading!" << endl;
    	return -1;
    }

    ofstream fout1("A.txt");
    ofstream fout2("B.txt");

    cout << "PLease enter the parametr for memory limit:  ";
    int N;
    //	cin >> N;
    N = 10;
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
    */
//////////////////////////////// 2 этап реализации алгоритма

    cout << "enter the limit  ";
//	int N;
//	cin >> N;

    int n = 5;		//вместимость буффера
    int M = 100;		//сколько записей в хранилище

    sortControl(n, M);
    return 0;
}
/*else if(a[i]==b[j] && (i!=n_i || i!=n_j))
		{
		     if(i!=n_i)
		     {
              c[p] = a[i];
              i++;
              p++;
             }
             else if(j!=n_j)
             {
                c[p] = b[j];
                j++;
                p++;
             }
        }
    */

