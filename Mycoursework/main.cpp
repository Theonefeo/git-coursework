#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;
//Запись в файл рандомных чисел
void file()
{
    int bb;
    cin>>bb;
    int b[bb];
    ofstream fout("f.txt");
    for(int i=0; i<bb; i++)
    {
        b[i]=rand()%10;
        fout<<b[i]<<endl;
    }
    fout.close();
}
//Функция разделения "большого" файла на массивы
void Splitting_a_File()
{
    int s[50];
    int ss[100];
    //Запись содержимого файла в массив для того,чтобы потом из массивa распределить элементы по файлам
    ifstream fin("f.txt");
    //vector<int>v;
    //пока файл не пуст проходим по нему
    while(!fin.eof())
    {

        for(int i=0; i<50; i++)
        {
            //string s;
            //getline(ifs, s);
            fin>>s[i];
        }
        for(int i=50; i<100; i++)
        {
            //string s;
            //getline(ifs, s);
            fin>>ss[i];
        }
    }
    fin.close();
    cout<<endl;
    //cout<<"f2"<<endl;
    //int sf2[50];
    vector<int>v;
    int as;
    //Копирование полунормального массива в нормальный
    for (int i = 50; i <100; i++)
    {

        as = ss[i];
       v.push_back(as);
    }
    int sf2[50];
    for (int i = 0; i <50; i++)
    {


       sf2[i] = v.at(i);
    }

    //перенос элементов из массива в доп файл f1
    ofstream fout("f1.txt");
    for(int i = 0; i<50; i++)
    {

        fout<<s[i]<<" ";


    }
    fout.close();
    //перенос элементов из массива в доп файл f2
    ofstream fout1("f2.txt");
    for(int i = 0; i<50; i++)
    {

        //fout1<<ss[i]<<" ";
        fout1<<sf2[i]<<" ";
        //v.pop_back();
    }

    fout1.close();

}
void Vvod(int n, float* a)//создание массива
{
    for(int i=0; i<n; i++)//рандомное заполнение массива
    {
        a[i]=rand()%10;
    }
}

void Vyvod(int n, float* a)//вывод массива
{
    int i;
    for(i=0; i<n; i++)
    {
        cout<<a[i]<<" ";

    }
    cout<<"\n";
}

void Sortirovka(int n, float* a)///сортировка выборочная
{
    int i;
    int imin = 0;

    for(i=0; i<n-1; i++)//цикл в цикле
    {

        imin = i;
        for(int j=i+1; j<n; j++)
        {
            if(a[j]<a[imin])///если текущий элемент меньше минимума
            {
                imin = j;
            }
        }

        swap(a[i], a[imin]);///меняем местами текущий элемент с минимальным


    }
}
int main()
{
    //cout<<"Please inter the element in the file ";
    //file();
    //проверка на то, пустой ли файл или нет
    const char filename[] = "f.txt";

    FILE* f = fopen(filename, "rb");
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



    //int n;
    //float a[100];
    //cout<<"Inter n ";
    //cin>>n;
    //cout<<endl;
    //Vvod(n, a);
    //Vyvod(n, a);
    //Разбивка файла на части(на другие файлы меньшего размера)
    Splitting_a_File();
    /*int d[10];

    //cout<<"Sorted array "<<endl;
    //Sortirovka(n, a);
    //Vyvod(n, a);*/
    return 0;
}
