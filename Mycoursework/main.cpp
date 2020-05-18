#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;
//Запись в файл рандомных чисел
void file()
{
    int bb;
    cin>>bb;
    int b[bb];
    ofstream fout("input.txt");
    for(int i=0; i<bb; i++)
    {
        b[i]=rand()%10;
        fout<<b[i]<<endl;
    }
    fout.close();
}
//Сортировка массива чисел которые "вмещаются" в оперативную память
void sort(string *& arr, int n)
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
string* readFromFile(ifstream &fin, int n)
{
    string *arr = new string[n];
    string buff;
    for (int i = 0; !fin.eof() && i < n; i++)
    {
        getline(fin, buff);
        arr[i] = buff;
    }

    return arr;
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
//Функция  записи в один из файлов массива из "вмещающихся" элементов
void writeToFile(string *& arr, int n, ofstream &fout)
{
    for(int i=0;i<n;++i)
    {
    fout<<arr[i]<<" ";
    }
}
int main()
{

    //cout<<"Please inter the element in the file ";
    //file();
    //проверка на то, пустой ли файл или нет
    //const char filename[] = "input.txt";

    /*FILE* f = fopen(filename, "rb");
    if(!f)
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
    ifstream fin("input.txt");
    if (!fin)
    {
        cerr << "Uh oh, file could not be opened for reading!" << endl;
        return -1;
    }

    ofstream fout1("A.txt");
    ofstream fout2("B.txt");

    string *arr;

    cout<<"PLease enter the parametr for memory limit:  ";
    int N ;
    cin>>N;
    for (int i = 0; !fin.eof(); ++i)
    {

        arr = readFromFile(fin, N);
        sort(arr,N);
        print(arr, N);
        //Разбивка файла на части(на 2 файла меньшего размера поочередено записывая в них элементы из большого)
        if(i%2==0)
        {
            writeToFile(arr, N, fout2);
        }
        else
            writeToFile(arr, N, fout1);
    }
    delete[] arr;


    fin.close();
    fout1.close();
    fout2.close();
    return 0;
}
