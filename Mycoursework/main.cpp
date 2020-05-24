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
    for(int i=0; i<n; ++i)
    {
        fout<<arr[i]<<endl;
    }
}
/////////////////2 этап алгоритма
//Чтение по 5 элементов из файла А в массив а
void readFromFileA(ifstream &finA, int n, string *a) //OBYAVLENIE
{
    //string *a = new string[n];

    string buffA;

    for (int i = 0; !finA.eof() && i < n; i++)
    {
        getline(finA, buffA);
        //finA>>buffA;
        a[i] = buffA;

    }

}
//Чтение по 5 элементов из файла Б в массив б
void readFromFileB(ifstream &finB, int n, string *b)
{
    //string *b = new string[n];
    string buffB;

    for (int i = 0; !finB.eof() && i < n; i++)
    {
        getline(finB, buffB);
        //finB>>buffB;
        b[i] = buffB;

    }

}
//Для тестирования
void printA(string a[], int nn)
{
    cout<<"Print massiv a: ";
    cout << "[";
    for (int i = 0; i < nn; i++)
    {
        cout << a[i] << " ";
    }
    cout << "]" << endl;
}
//Для тестирования
void printB(string b[], int nm)
{
    cout<<"Print massiv b: ";
    cout << "[";
    for (int i = 0; i < nm; i++)
    {
        cout << b[i] << " ";
    }
    cout << "]" << endl;
}
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


//Запись массива с в файл С
void writeToFileC(string * c, int n, ofstream &foutC)
{
    for(int i=0; i<n; ++i)
    {
        foutC<<c[i]<<endl;
    }
}
//Запись массива д в файл Д
void writeToFileD(string * c, int n, ofstream &foutD)
{
    for(int i=0; i<n; ++i)
    {
        foutD<<c[i]<<endl;
    }
}

//Функция слияния элементов массива а и б в результирующий с(д)

void merge(string *a, int &i, string *b, int &j, string *c, int &p, int n, int &NNp,bool &flag, int N, ofstream &foutC, ofstream &foutD) //, bool flag)
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
        else if(a[i] > b[j])
        {
            c[p] = b[j];
            j++;
            p++;
        }
        else if(a[i] == b[j])
        {
            c[p] = a[i];
            i++;
            p++;
            if(p == n*2)
            {
                if(flag == true && NNp<2)
                {
                    //writeFromFrrayC(foutC, foutD, c, N, a, i, b, j,p );
                    cout<<"writeToFileC: ";
                    printC(c, N);
                    cout<<endl;
                    writeToFileC(c, N, foutC); //чтение в файл С
                    p =0;
                    NNp++; //Пометка для того чтобы читать либо в файл С либо в файл Д
                    if(NNp==2)
                    {
                        flag = false;
                        merge(a, i, b,j, c, p, N/2, NNp, flag, N ,foutC, foutD);
                    }
                    else
                        merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
                }
                else if(flag == false && NNp<4)
                {
                    cout<<"writeToFileD: ";
                    printC(c, N);
                    cout<<endl;
                    writeToFileD(c, N, foutD);
                    p = 0;
                    NNp++;
                    if(NNp==4)
                    {
                        NNp = 0;
                        flag = true;
                        merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
                    }
                    else
                        merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
                }
            }
            else
            {
                c[p] = b[j];
                j++;
                p++;
                if(p == n*2)
                {
                    merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
                    //writeFromFrrayC(foutC, foutD, c, N, a, i, b, j,p );
                    if(flag == true && NNp<2)
                    {
                        //writeFromFrrayC(foutC, foutD, c, N, a, i, b, j,p );
                        cout<<"writeToFileC: ";
                        printC(c, N);
                        cout<<endl;
                        writeToFileC(c, N, foutC); //чтение в файл С
                        p =0;
                        NNp++; //Пометка для того чтобы читать либо в файл С либо в файл Д
                        if(NNp==2)
                        {
                            flag = false;
                            merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
                        }
                        else
                            merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
                    }
                    else if(flag == false && NNp<4)
                    {

                        cout<<"writeToFileD: ";
                        printC(c, N);
                        cout<<endl;
                        writeToFileD(c, N, foutD);
                        p = 0;
                        NNp++;
                        if(NNp==4)
                        {
                            NNp = 0;
                            flag = true;
                            merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
                        }
                        else
                            merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
                    }
                }
                else
                    merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
            }
        }
    }
}

int main()
{

    //cout<<"Please inter the element in the file ";
    //file();
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

    string *arr;

    cout<<"PLease enter the parametr for memory limit:  ";
    int N ;
    cin>>N;
    for (int i = 0; !fin.eof(); ++i)
    {

        arr = readFromFile(fin, N); //Чтение в массив из большого файла с учетом ограничений заданных в начале
        sort(arr,N); //Сортировка выбранных из большого файла 10 элементов
        print(arr, N); //Вывод массивов для проверки
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
    fout2.close();*/
//////////////////////////////// 2 этап реализации алгоритма
    //ifstream finA("A.txt"); //Открытие файла А для чтения
    //ifstream finB("B.txt"); //Открытие файла Б для чтения

    ifstream finA("A.txt");
    if (!finA)
    {
        cerr << "Uh oh, file could not be opened for reading!" << endl;
        return -1;
    }

    ifstream finB("B.txt");
    if (!finB)
    {
        cerr << "Uh oh, file could not be opened for reading!" << endl;
        return -1;
    }
    ofstream foutC("C.txt"); //Открытие файла С для записи
    ofstream foutD("D.txt"); //Открытие файла Д для записи

    //string *a;
    //string *b;
    //string *c;

    //
    cout<<"enter the limit  ";
    int N;
    cin>>N;

    string a[N/2];
    string b[N/2];
    string c[N];

    readFromFileA(finA, N/2, a);
    readFromFileB(finB, N/2, b);
    int n = N/2;
    int i = 0, j= 0, p=0;
    //int Np=0;
    int NNp = 0;
    bool flag = true;
    //в цикле
//Попеременное чтение из файлов А и В отрезков длиною 5(в массив а-5эл и в-5эл) и дальнейшее копирование слиянием в результирующие массивы с и d с записью их в соответсвующие файлы
    for(int pi=0; !finA.eof() && !finB.eof(); ++pi)

    {

        merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);

        //Если количество элементов массива с равно 10 (ограничение на оп.память) то записываем  его в файл С
        if(p == n*2)
        {

            if(flag == true && NNp<2)
            {
                //writeFromFrrayC(foutC, foutD, c, N, a, i, b, j,p );
                cout<<"writeToFileC: ";
                printC(c, N);
                cout<<endl;
                writeToFileC(c, N, foutC); //чтение в файл С
                p =0;
                NNp++; //Пометка для того чтобы читать либо в файл С либо в файл Д
                if(NNp==2)
                {
                    flag = false;
                    merge(a, i, b,j, c, p, N/2, NNp, flag, N ,foutC, foutD);
                }
                else
                    merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
            }
            else if(flag == false && NNp<4)
            {
                cout<<"writeToFileD: ";
                printC(c, N);
                cout<<endl;
                writeToFileD(c, N, foutD);
                p = 0;
                NNp++;
                if(NNp==4)
                {
                    NNp = 0;
                    flag = true;
                    merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
                }
                else
                    merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
            }
            //Последующие логические выборы - средство для достижения поочередной записи(2 раза подряд в один и тот же файл) массивов в файлы С и Д
            //Функция записывания отрезка размером 5 в файлы С и Д
            //writeFromFrrayC(foutC, foutD, c, N, a, i, b, j,p );
            //Функция выгрузки массива с в файлы С и Д
//void writeFromFrrayC(ofstream &foutC, ofstream &foutD, string *c,int N, string *a, int &i, string *b, int &j,int &p )
        }
        //если указатель дошел до конца массива а(то есть i указывает на последний элемент)-значит массив полностью прочитан и его надо перезаписать
        else if(i == n)
        {
            //перезапись массива а
            readFromFileA(finA, N/2, a);
            i = 0;
            merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
        }
        //если указатель дошел до конца массива б-значит массив полностью прочитан и его надо перезаписать
        else if(j == n)
        {
            //перезапись массива b
            readFromFileB(finA, N/2, b);
            j = 0;
            merge(a, i, b,j, c, p, N/2, NNp, flag, N, foutC, foutD);
        }


        //delete[] a;
        //delete[] b;
        //delete[] c;
    }



    finA.close();
    finB.close();
    foutC.close();
    foutD.close();
////////////
    return 0;
}
