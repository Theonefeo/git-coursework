#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
//Запись в файл рандомных чисел
void file()
{
   int bb;
   cin>>bb;
  int b[bb];
  ofstream fout("f.txt");
  for(int i=0;i<bb;i++)
  {
    b[i]=rand()%10;
    fout<<b[i];
  }
  fout.close();
}
void Vvod(int n, float* a)//создание массива
{
    int i;

    for(i=0; i<n; i++)//рандомное заполнение массива
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
 //fstream file("f.txt");
    //if (!file.is_open()) cout << "Not open\n"; // если не открылся
    //else if (file.peek() == EOF) cout << "Fail empty\n"; // если первый символ конец файла
    const char filename[] = "f.txt";

    FILE* f = fopen(filename, "rb");
    if(!f)
    {
        cout << "File is not exists" << endl;
        return 0;
    }

    char h;
    size_t readed = fread(&h, 1, 1, f);

    if(readed)
        cout << "File contains data" << endl;
    else
        cout << "File NOT contains data" << endl;



   //int bb;
   //cout<<"Please inter the element in the file ";
   //cin>>bb;
   //file();


    int n;
    float a[100];
    cout<<"Inter n ";
    cin>>n;
    cout<<endl;
    Vvod(n, a);
    Vyvod(n, a);
    cout<<"Sorted array "<<endl;
    Sortirovka(n, a);
    Vyvod(n, a);
    //double q;
    //cout<<"\n"<<"Inter q "<<"\n";
    //cin>>q;
    //cout<<endl;


  return 0;
}



//    srand(time(0));
    /*void Simple_Merging_Sort (

{
    char *name;
  int a1, a2, k, i, j, kol, tmp;
  ifstream fin("f.txt");

  FILE *f, *f1, *f2;

  kol = 0;
  if ( (f = fopen(name,"r")) == NULL )
    printf("\nИсходный файл не может быть прочитан...");
  else {
    while ( !feof(f) ) {
      fscanf(f,"%d",&a1);
      kol++;
    }
    fclose(f);
  }
  k = 1;
  while ( k < kol ){
    f = fopen(name,"r");
    f1 = fopen("smsort_1","w");
    f2 = fopen("smsort_2","w");
    if ( !feof(f) ) fscanf(f,"%d",&a1);
    while ( !feof(f) ){
      for ( i = 0; i < k && !feof(f) ; i++ ){
        fprintf(f1,"%d ",a1);
        fscanf(f,"%d",&a1);
      }
      for ( j = 0; j < k && !feof(f) ; j++ ){
        fprintf(f2,"%d ",a1);
        fscanf(f,"%d",&a1);
      }
    }
    fclose(f2);
    fclose(f1);
    fclose(f);

    f = fopen(name,"w");
    f1 = fopen("smsort_1","r");
    f2 = fopen("smsort_2","r");
    if ( !feof(f1) ) fscanf(f1,"%d",&a1);
    if ( !feof(f2) ) fscanf(f2,"%d",&a2);
    while ( !feof(f1) && !feof(f2) ){
      i = 0;
      j = 0;
      while ( i < k && j < k && !feof(f1) && !feof(f2) ) {
        if ( a1 < a2 ) {
          fprintf(f,"%d ",a1);
          fscanf(f1,"%d",&a1);
          i++;
        }
        else {
          fprintf(f,"%d ",a2);
          fscanf(f2,"%d",&a2);
          j++;
        }
      }
      while ( i < k && !feof(f1) ) {
        fprintf(f,"%d ",a1);
        fscanf(f1,"%d",&a1);
        i++;
      }
      while ( j < k && !feof(f2) ) {
        fprintf(f,"%d ",a2);
        fscanf(f2,"%d",&a2);
        j++;
      }
    }
    while ( !feof(f1) ) {
      fprintf(f,"%d ",a1);
      fscanf(f1,"%d",&a1);
    }
    while ( !feof(f2) ) {
      fprintf(f,"%d ",a2);
      fscanf(f2,"%d",&a2);
    }
    fclose(f2);
    fclose(f1);
    fclose(f);
    k *= 2;
  }
  remove("smsort_1");
  remove("smsort_2");
  fin.close();

return 0; */
