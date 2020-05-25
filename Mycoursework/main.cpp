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
void readFromFile(ifstream &fin, int n, string *arr)
{
    string buff;

    for (int i = 0; !fin.eof() && i < n; i++)
    {
        getline(fin, buff);
        arr[i] = buff;
    }

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
    for(int i=0; i<n; ++i)
    {
        fout <<arr[i] <<endl;
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
void merge(string *a, int &i, string *b, int &j, string *c, int &p, int n) //, bool flag)
{

//Слияние: идем по массивам а и b сравнивая элемемнты и заполняя массив с(д) который потом запишим в файл С(Д)
    while (!(i == n || j == n || p == n*2))
    {
        if (a[i] < b[j])
        {
            c[p] = a[i];
            i++;
            p++;
        }
        else if(a[i]>b[j])
        {
            c[p] = b[j];
            j++;
            p++;
        }
        else if(a[i]==b[j])
        {
            c[p] = a[i];
            i++;
            p++;
        }
    }
}
//Функция выполняющая 2 часть алгоритма - попеременное записи и чтение то файлов А и В то файлов С  и Д
void sortControl(int n, int N, string *a, string *b, string *c, int SizeOfTheSourceArray/*количество частей для считывания из файла А и файла В*//*5, если размер буффера = 10*/)
{
    ifstream fin1;
    ifstream fin2;
    ofstream fout1;
    ofstream fout2;
//SizeOfTheSourceArray - количество элементов в исходном не отсортированном файле
    int currentAmountOfDataToWrite = 1;
    bool read_fileA_and_fileB = true;
    bool LastBatchOfEnteriesInTheFile = true;//Когда мы запишем в один файл 10 раз подряд по 10 элементов - то есть в один файл все отсортированные элементы, то этот флаг будет фолс и мы выходим из цикла вайл
    int i = 0, j= 0, p=0;
    int Cnt = 0; //Сколько раз подряд записали в один файлов 10(количество вмещающихся элементов в оп.память) порций
    while(LastBatchOfEnteriesInTheFile == true/* То есть пока мы не достигли того что в один файл 10 раз подряд записали по 10 элементов и в итоге не получили один файл отсортированных 100 элементов*/)
    {
        if(currentAmountOfDataToWrite == 1)
            currentAmountOfDataToWrite *=2;
        else
            currentAmountOfDataToWrite = currentAmountOfDataToWrite + 2;

        if (read_fileA_and_fileB)
        {
            fin1.open("A.txt");
            fin2.open("B.txt");
            fout1.open("C.txt");
            fout2.open("D.txt");
            read_fileA_and_fileB = false;
            readFromFile(fin1, n, a);//Так как мы заходим в функцию с массивыми пустыми то мы должны их заполнить соотсветсвенно элементами
            readFromFile(fin2, n, b);//Так как мы заходим в функцию с массивыми пустыми то мы должны их заполнить соотсветсвенно элементами
        }
        else
        {
            fin1.open("C.txt");
            fin2.open("D.txt");
            fout1.open("A.txt");
            fout2.open("B.txt");
            read_fileA_and_fileB = true;
            readFromFile(fin1, n, a);//Так как мы заходим в функцию с массивыми пустыми то мы должны их заполнить соотсветсвенно элементами
            readFromFile(fin2, n, b);//Так как мы заходим в функцию с массивыми пустыми то мы должны их заполнить соотсветсвенно элементами
        }

        ofstream *curFout = &fout1;

        Cnt = 0; //Сколько раз подряд записали в один файлов 10(количество вмещающихся элементов в оп.память) порций
        bool writeElementsToFout1 = true;
        for(int writeElementsCount = 1; !(fin1.eof() && fin2.eof()); writeElementsCount++)
        {
            if (writeElementsCount>currentAmountOfDataToWrite)
            {
                writeElementsToFout1 = !writeElementsToFout1;
                writeElementsCount = 1;
            }

            if(writeElementsToFout1 == true)
            {
                if(Cnt*N >= SizeOfTheSourceArray)
                {
                    LastBatchOfEnteriesInTheFile = false;
                }
                else
                {
                    curFout = &fout1;
                    Cnt++;
                }
            }
            else
            {
                curFout = &fout2;
                Cnt = 0;
            }
            if(LastBatchOfEnteriesInTheFile == true)
                merge(a, i, b, j, c, p, n);

//Если количество элементов массива с равно 10 (ограничение на оп.память) то записываем его в файл С
            if(p == n*2 && LastBatchOfEnteriesInTheFile == true)
            {
                cout<<"writeToFileC: ";
                printC(c, N);
                cout<<endl;
                writeToFile(*curFout, N, c);
                p = 0;
            }
//если указатель дошел до конца массива а(то есть i указывает на последний элемент)-значит массив полностью прочитан и его надо перезаписать
            if(i == n && LastBatchOfEnteriesInTheFile == true)
            {
//перезапись массива а
                cout<<"Print massv a  ";
                print(a, n);
                readFromFile(fin1, n, a);
                i = 0;
            }
//если указатель дошел до конца массива б-значит массив полностью прочитан и его надо перезаписать
            if(j == n && LastBatchOfEnteriesInTheFile == true)
            {
//перезапись массива b
                cout<<"Print massv b ";
                print(b, n);
                readFromFile(fin2, n, b);
                j = 0;
            }
            /*if(fin1.eof)
            {

            }*/
        }
//close streams
        fin1.close();
        fin2.close();
        fout1.close();
        fout2.close();
    }
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
    /*ifstream fin("input.txt");
    if (!fin)
    {
        cerr << "Uh oh, file could not be opened for reading!" << endl;
        return -1;
    }

    ofstream fout1("A.txt");
    ofstream fout2("B.txt");

    //string *arr;

    cout<<"PLease enter the parametr for memory limit:  ";
    int N ;
    cin>>N;
    string arr[N];
    for (int i = 0; !fin.eof(); ++i)
    {

        //arr = readFromFile(fin, N); //Чтение в массив из большого файла с учетом ограничений заданных в начале
        readFromFile(fin, N, arr);
        sort(arr,N); //Сортировка выбранных из большого файла 10 элементов
        print(arr, N); //Вывод массивов для проверки
        //Разбивка файла на части(на 2 файла меньшего размера поочередено записывая в них элементы из большого)
        if(i%2==0)
        {
            writeToFile(fout2, N, arr);
        }
        else
            writeToFile(fout1, N, arr);
    }
    //delete[] arr;

    fin.close();
    fout1.close();
    fout2.close();
    */
//////////////////////////////// 2 этап реализации алгоритма
    cout<<"Please inter the element in the file ";
    int SizeOfTheSourceArray;
    cin>>SizeOfTheSourceArray;

    cout<<"enter the limit  ";
    int N;
    cin>>N;

    string a[N/2];
    string b[N/2];
    string c[N];
    int n = 5;

    sortControl(n, N, a, b ,c, SizeOfTheSourceArray);

    return 0;
}
