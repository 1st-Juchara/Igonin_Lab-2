// Lab-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "CPipe.h"
#include "SubFunc.h"

using namespace std;

vector <int> filterPipes(const vector <Pipe>& pipes)
{
    vector <int> index;
    string name;
    int status = -1;
    cout << "1. Choose by filter \n2. Display all";
    if (tryChoose(1, 2) == 1)
    {
        cout << "1. Search by name \n2. All names";
        if (tryChoose(1, 2) == 1)
        {
            cout << "Name: ";
            inputString(cin, name);
            cout << endl;
        }

        cout << "1. Search by status \n2. Any status";
        if (tryChoose(1, 2) == 1)
        {
            cout << "1. EXPLOITED \n2. IN REPAIR";
            status = tryChoose(1, 2) - 1;
        }

        for (int i = 0; i < pipes.size(); i++)
            if (inString(pipes[i].name, name) and ((pipes[i].inRepare == bool(status)) or (status == -1)))
                index.push_back(i);
    }
    else
        for (int i = 0; i < pipes.size(); i++)
            index.push_back(i);
    return index;
}

vector <int> filterCS(const vector <CS>& Stations)
{
    vector <int> index;
    string name;
    int workshops = -1;
    cout << "1. Choose by filter \n2. Display all";
    if (tryChoose(1, 2) == 1)
    {
        cout << "1. Search by name \n2. All names";
        if (tryChoose(1, 2) == 1)
        {
            cout << "Name: ";
            inputString(cin, name);
            cout << endl;
        }

        cout << "1. Search by worksops status \n2. Any status";
        if (tryChoose(1, 2) == 1)
        {
            cout << "Choose percantage of online ws (0%..100%)";
            workshops = tryChoose(0, 100);
        }

        for (int i = 0; i < Stations.size(); i++)
            if (inString(Stations[i].name, name) and ((Stations[i].WSOn/Stations[i].WSCnt*100 == workshops) or (workshops == -1)))
                index.push_back(i);
    }
    else
        for (int i = 0; i < Stations.size(); i++)
            index.push_back(i);
    return index;
}

int Menu() {
    std::cout << "1. Add pipe \n2. Add CS \n3. View pipes \n4. View CS \n5. Edit pipe \n6. Edit CS \n7. Save \n8. Load \n9. Exit";
    int number = tryChoose(1, 9);
    return number;
}

void ViewPipe(const Pipe& pipe)
{
    cout << "\t\t" << "Name: " << pipe.name << endl;
    cout << "\t\t" << "Length: " << pipe.length << endl;
    cout << "\t\t" << "Diameter: " << pipe.diameter << endl;
    if (pipe.inRepare)
        cout << "\t\t" << "Status: IN REPAIR" << endl;
    else
        cout << "\t\t" << "Status: EXPLOITED \n" << endl;
}

void ViewCS(const CS& Stations)
{
    cout << "\t\t" << "Name: " << Stations.name << endl;
    cout << "\t\t" << "Number of workshops: " << Stations.WSCnt << endl;
    cout << "\t\t" << "Workshops online: " << Stations.WSOn << endl;
    cout << "\t\t" << "Payoff: " << Stations.payoff << endl;
    cout << endl;
}

void ViewPipes(const vector <Pipe> &pipes) { //+
    if (isExist(pipes))
    {
        vector <int> index = filterPipes(pipes);
        cout << "Pipes:" << endl;
        for (int i = 0; i < index.size(); i++)
            ViewPipe(pipes[index[i]]);
    }
    cout << endl;
}

void ViewStations(const vector <CS>& Stations) {
    if (isExist(Stations))
    {
        vector <int> index = filterCS(Stations);
        cout << "Stations:" << endl;
        for (int i = 0; i < index.size(); i++)
            ViewCS(Stations[index[i]]);
    }
    cout << endl;
}

void addPipe(vector <Pipe> &pipes) { // +
    int id = rand() % 9000000 + 1000000;
    cout << "Enter pipe name:\n\n> ";
    string name;
    inputString(cin, name);
    cout << endl;
    cout << "Enter pipe length:";
    float length = tryInputNum(0, INT_MAX);
    cout << "Enter pipe diameter: ";
    float diameter = tryInputNum(0, INT_MAX);
    pipes.push_back({id, name, length, diameter , false});
}

void addCS(vector <CS> &Stations) { // +
    int wsOn = 0;
    int id = rand() % 9000000 + 1000000;
    std::cout << "Enter CS name:\n\n> ";
    string name;
    inputString(cin, name);
    cout << endl;
    std::cout << "Enter count of workshops: ";
    int workshops = tryChoose(1, 10000);
    std::cout << "Enter station productivity (1..100): ";
    int prod = tryChoose(1, 100);
    Stations.push_back({id, name, workshops, 0, prod });
}

void changePipe(vector <Pipe>& pipes, const vector <int>& index) {
    cout << "1. Change pipe status\n2. Delete pipe";
    int number = tryChoose(1, 2);
    if (number == 1)
    {
        cout << "Pipe status:" << endl;
        cout << "\t1. UNDER REPAIR \n\t2. IS FUNCTIONING";
        bool status = tryChoose(1, 2) == 1;
        for (int i = 0; i < index.size(); i++)
            pipes[index[i]].inRepare = status;
    } 
    else
        for (int i = index.size() - 1; i >= 0; i--)
            pipes.erase(pipes.begin() + index[i]);
}

void changeCS(vector <CS>& Stations, const vector <int>& index) {

    cout << "1. Change WS status\n2. Delete CS";
    int number = tryChoose(1, 2);
    if (number == 1)
    {
        cout << "1. Turn off workshops" << endl << "2. Turn on workshops";
        int inst = tryChoose(1, 2) == 1;
        cout << "How many?";
        int delta = tryChoose(0, 999999);
        for (int i = 0; i < index.size(); i++)
        {
            Stations[index[i]].WSOn = inst ? delta > Stations[index[i]].WSOn ? 0 : Stations[index[i]].WSOn - delta :
                delta + Stations[index[i]].WSOn > Stations[index[i]].WSCnt ? Stations[index[i]].WSCnt : delta + Stations[index[i]].WSOn;
        }
    }
    else
        for (int i = index.size() - 1; i >= 0; i--)
            Stations.erase(Stations.begin() + index[i]);
}

void editPipes(vector <Pipe> &pipes) { // +
    if (isExist(pipes)) {
        vector <int> index = filterPipes(pipes);
        for (int i = 0; i < index.size(); i++)
        {
            cout << "pipe " << i+1 << endl;
            ViewPipe(pipes[index[i]]);
        }
        vector <int> index_ch;
        choosingElements(index, index_ch);
        changePipe(pipes, index_ch);
    }
}

void editCS(vector <CS> &Stations) { // ?
    if (isExist(Stations)) {
        vector <int> index = filterCS(Stations);
        for (int i = 0; i < index.size(); i++)
        {
            cout << "Station " << i + 1 << endl;
            ViewCS(Stations[index[i]]);
        }
        cout << "1. Choose interval of CS" << endl << "2. Choose several CS" << endl << "3. Choose a single CS";
        vector <int> index_ch;
        int number = tryChoose(1, 3);
        choosingElements(index, index_ch);
        changeCS(Stations, index_ch);
    }
}

void PipesDataOut(ofstream& fout, const vector <Pipe>& pipes) //+
{
    fout << pipes.size() << endl;
    for (int i = 0; i < pipes.size(); i++)
    {
        fout << pipes[i].name << endl;
        fout << pipes[i].id << ' ' << pipes[i].length << ' ' << pipes[i].diameter << ' ' << pipes[i].inRepare << endl;
    }
}

void CSDataOut(ofstream& fout, const vector <CS>& Stations) //+
{
    fout << Stations.size() << endl;
    for (int i = 0; i < Stations.size(); i++)
    {
        fout << Stations[i].name << endl;
        fout << Stations[i].id << ' ' << Stations[i].WSCnt << ' ' << Stations[i].WSOn << ' ' << Stations[i].payoff << endl;
    }
}

void Save(const vector <Pipe>& pipes, const vector <CS>& Stations)
{
    ofstream fout("Saves.txt", ios_base::out | ios_base::trunc);// out - открыте для записи, trunc - удаление содержимого, ios_base - класс для всех потоковых классов ввода-вывода
    if (fout.is_open())
    {
        if (isExist(pipes) || isExist(Stations))
        {
            if (isExist(pipes))
            {
                PipesDataOut(fout, pipes);
            }
            else
                fout << 0 << endl;
            if (isExist(Stations))
            {
                CSDataOut(fout, Stations);
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

void PipeDataIn(ifstream& in, vector <Pipe>& pipes)
{
    int pipesCnt = 0;
    in >> pipesCnt;
    for  (int i = 0; i < pipesCnt; i++)
    {
        in.ignore(10000, '\n');
        Pipe pipe;
        getline(in, pipe.name);
        in >> pipe.id;
        in >> pipe.length;
        in >> pipe.diameter;
        in >> pipe.inRepare;
        pipes.push_back(pipe);
    }
}

void CSDataIn(ifstream& in, vector <CS>& Stations)
{
    int StationsCnt = 0;
    in >> StationsCnt;
    for (int i = 0; i < StationsCnt; i++)
    {
        in.ignore(10000, '\n');
        CS Station;
        getline(in, Station.name);
        in >> Station.id;
        in >> Station.payoff;
        in >> Station.WSCnt;
        in >> Station.WSOn;
        Stations.push_back(Station);
    }
}

void Load(vector <Pipe>& pipes, vector <CS>& Stations) // Несостыковочка сохр. и загр.
{
    ifstream fin("Saves.txt");
    if (fin.is_open())
    {
        PipeDataIn(fin, pipes);
        CSDataIn(fin, Stations);
        fin.close();
        cout << "Load completed" << endl;
    }
    else
        cout << "Error: can't find save file" << endl;
    cout << endl;
}

int main()
{
    vector <Pipe> pipes;
    vector <CS> Stations;
    while (true) {
        int number = Menu();
        switch (number)
        {
        case 1:
            addPipe(pipes);
            break;
        case 2:
            addCS(Stations);
            break;
        case 3:
            ViewPipes(pipes);
            break;
        case 4:
            ViewStations(Stations);
            break;
        case 5:
            editPipes(pipes);
            break;
        case 6:
            editCS(Stations);
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