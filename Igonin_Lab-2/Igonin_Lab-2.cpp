// Lab-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "CSs.h"
#include "Pipes.h"
#include "SubFunc.h"

using namespace std;

int Menu() {
    std::cout << "1. Add pipe \n2. Add CS \n3. View pipes \n4. View CS \n5. Edit pipe \n6. Edit CS \n7. Save \n8. Load \n9. Exit";
    int number = tryChoose(1, 9);
    return number;
}

void Save(Pipes& pipes, CSs& Stations)
{
    ofstream fout("Saves.txt", ios_base::out | ios_base::trunc);// out - открыте для записи, trunc - удаление содержимого, ios_base - класс для всех потоковых классов ввода-вывода
    if (fout.is_open())
    {
        if (pipes.isExist() || Stations.isExist())
        {
            if (pipes.isExist())
            {
                pipes.PipesDataOut(fout);
            }
            else
                fout << 0 << endl;
            if (Stations.isExist())
            {
                Stations.CSDataOut(fout);
            }
            else
                fout << 0 << endl;
            cout << "Save completed" << endl;
        }
        else
            cout << "Nothing to save" << endl;
        cout << endl;
        fout.close();
    }
    else
        cout << "Error: save was failed";
}

void Load(Pipes& pipes, CSs& Stations) // Несостыковочка сохр. и загр.
{
    ifstream fin("Saves.txt");
    if (fin.is_open())
    {
        pipes.PipeDataIn(fin);
        Stations.CSDataIn(fin);
        fin.close();
        cout << "Load completed" << endl;
    }
    else
        cout << "Error: can't find save file" << endl;
    cout << endl;
}

int main()
{
    Pipes pipes;
    CSs Stations;
    while (true) {
        int number = Menu();
        switch (number)
        {
        case 1:
            pipes.addPipe();
            break;
        case 2:
            Stations.addCS();
            break;
        case 3:
            pipes.ViewPipes();
            break;
        case 4:
            Stations.ViewStations();
            break;
        case 5:
            pipes.editPipes();
            break;
        case 6:
            Stations.editCS();
            break;
        case 7:
            Save(pipes, Stations);
            break;
        case 8:
            Load(pipes, Stations);
            break;
        case 9:
            return 0;
            break;
        default:
            break;
        }
    };
    return 0;
}