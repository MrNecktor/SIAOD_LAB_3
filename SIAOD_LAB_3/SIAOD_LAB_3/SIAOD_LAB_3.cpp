
#include <iostream>
#include <cstring>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int cmp_ptr(int lenpatt, int lenst, char st[80], char patt[80], int mas[256])
{
    int i, j, metka;
    metka = i = j = lenpatt - 1;
    while (i > 0 && j < lenst)
    {
        if (st[j] != patt[i])
        {
            metka = metka + mas[st[metka]];
            i = lenpatt - 1;
            j = metka;
        }
        else
        {
            i = i--;
            j = j--;
        }

    }
    if (j >= lenst)
        return -1;
    else
        return j;
}

using namespace std;
//const char* string = "eeeeeejjjjjjffffggg";
//const char* substring = "ej";
int KMPSearch(char* string, char* substring) //в качестве параметров в функцию передается строка и субстрока
{
    int  sl, ssl;
    int res = -1;
    sl = strlen(string);                                            //присваивается длина строки
    ssl = strlen(substring);                                      //присваивается длина субстроки
    if (sl == 0)                                                    //проверка строки
        cout << "Неверно задана строка\n";
    else if (ssl == 0)                                            //проверка субстроки
        cout << "Неверно задана подстрока\n";
    else                                                            //Если все нормально - поехали
    {
        int  i, j = 0, k = -1;
        int* d;
        d = new int[1000];                                         //создали динамический одномерный массив
        d[0] = -1;                                                    //первый элемент делаем равным -1
        while (j < ssl - 1)
        {                                      //пока  j < кол-ва эл-тов строки
            while (k >= 0 && substring[j] != substring[k])          /*пока k больше или равно 0 и j-тый элемент субстроки не равен  k-тому присваиваем k k-тый элемент динамического массива*/
            {
                k = d[k];
            }
            j++;                                                         //увеличиваем j
            k++;
            if (substring[j] == substring[k])                   //если j-ый элемент субстроки равен k-тому
                d[j] = d[k];                                             //присваиваем j-тому элементу динамического массива k-тый
            else                                                         //иначе
                d[j] = k;                                                 //присваиваем k
        }
        i = 0;
        j = 0;                                                         //обнулили i, j
        while (j < ssl && i < sl)
        {                                                               //пока j < длины субстроки и i < длины строки
            while (j >= 0 && string[i] != substring[j])                 // пока j >= 0 и i-ый элемент субстроки не равен j-ому
            {
                j = d[j];                                                       //j присваивается j-ый элемент динамического массива
            }
            i++;
            j++;                                                         //увеличиваем i и j
        }


        delete[] d;                                                 //удаляем динам. массив                                                
        res = j == ssl ? i - ssl : -1;                           // результатом будет i-ssl если j = ssl и -1 в противном случае
    }
    return res;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    int A;
    int B;
    cout << "выбор задачи ";
    cin >> A;
    
    switch (A)
    {
        case 1:
        {
            char* string = _strdup("eeeeeejjjjjjffffggg");
            char* substring = _strdup("ej");
            cout << endl;
            

            cout << endl << "результат " << KMPSearch(string, substring) << endl;
            return 0;
        }
        case 2:
        {
            char st[80] = { "iiiooorrrttt" }, patt[80] = { "io" };
            int i, j, lenst, lenpatt, mas[256], metka;
            



            lenst = strlen(st);
            lenpatt = strlen(patt);
            for (i = 0; i < 256; i++)
                mas[i] = lenpatt;
            for (i = lenpatt - 2; i >= 0; i--)
                if (mas[patt[i]] == lenpatt)
                    mas[patt[i]] = (lenpatt - 1 - i);
            i = cmp_ptr(lenpatt, lenst, st, patt, mas);
            if (i > 0)
                printf("Результат %d", i);
            else
                printf("Слово не найдено");
            return 0;
        }
        
    }
    
    
}