// Lab-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Pipe {
    int id = 0;
    string name = "";
    float length = 0;
    float diameter = 0;
    bool inRepare = false;
};

struct CS {
    int id = 0;
    string name = "";
    vector <bool> WS;
    int payoff = 0;
};

bool isExist(const vector <Pipe>& pipes)
{
    return pipes.size() > 0 ? true : false;
}

bool isExist(const vector <CS>& Stations)
{
    return Stations.size() > 0 ? true : false;
}

void inputString(istream& in, string& str)
{
    in.ignore(10000, '\n');
    getline(in, str);
}

float tryInputNum(float min, float max) {
    float num;
    cout << "\n\n> ";
    while ((cin >> num).fail() || (num < min) || (num > max)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n\n> ";
    }
    cout << endl;
    return num;
}

int tryChoose(int min, int max) {
    int num;
    cout << "\n\n> ";
    while ((cin >> num).fail() || (num < min) || (num > max)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n> ";
    }
    cout << endl;
    return num;
}

int Menu() {
    std::cout << "1. Add pipe \n2. Add CS \n3. Objects \n4. Edit pipe \n5. Edit CS \n6. Save \n7. Load \n8. Exit";
    int number = tryChoose(1, 8);
    return number;
}

void ViewPipe(const Pipe& pipe)
{
    cout << "Pipe" << endl;
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
    cout << "Stations" << endl;
    cout << "\t\t" << "Name: " << Stations.name << endl;
    cout << "\t\t" << "Number of workshops: " << Stations.WS.size() << endl;
    cout << "\t\t" << "Payoff: " << Stations.payoff << endl;
    for (int j = 0; j < Stations.WS.size(); j++)
        if (Stations.WS[j])
            cout << "\t\t WS " << j + 1 << ". ON" << endl;
        else
            cout << "\t\t WS " << j + 1 << ". OFF" << endl;
}

void View(const vector <Pipe> &pipes, const vector <CS> &Stations) { //+
    if (isExist(pipes))
        for (int i = 0; i < pipes.size(); i++)
                ViewPipe(pipes[i]);
    if (isExist(Stations))
        for (int i = 0; i < Stations.size(); i++)
                ViewCS(Stations[i]);
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
    vector <bool> wsStatus;
    wsStatus.resize(workshops);
    fill(wsStatus.begin(), wsStatus.end(), true);
    std::cout << "Enter station productivity (1..100): ";
    int prod = tryChoose(1, 100);
    Stations.push_back({id, name, wsStatus, prod });
}

void editPipe(vector <Pipe> &pipes) { // ?
    if (pipes.size() > 0) {
        cout << pipes[0].name << endl;
        cout << "\tPipe status:" << endl;
        cout << "\t\t1. UNDER REPAIR \n\t\t2. IS FUNCTIONING";
        pipes[0].inRepare = tryChoose(1, 2) == 1;
    }
}

void editCS(vector <CS> &Stations) { // ?
    if (Stations.size() > 0)
    {
        cout << Stations[0].name << endl;
        cout << "\tPayoff: " << Stations[0].payoff << endl;
        cout << "\tWorkshops: " << Stations[0].payoff << endl;
        for (int i = 0; i < Stations[0].WS.size(); i++)
            if (Stations[0].WS[i])
                cout << "\t\t" << i + 1 << ". WS is ON" << endl;
            else
                cout << "\t\t" << i + 1 << ". WS is OFF" << endl;
        cout << endl;
        cout << "";
        cout << "Number of WS for editing:";
        int WScount = tryChoose(1, Stations[0] .WS.size());
        for (int i = 0; i < WScount; i++)
        {
            cout << "Enter index of WS for editing:";
            int WSindex = tryChoose(1, Stations[0].WS.size());
            Stations[0].WS[WSindex - 1] = !Stations[0].WS[WSindex - 1];
        }
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
        fout << Stations[i].payoff << ' ' << Stations[i].WS.size();
        for (int j = 0; j < Stations[i].WS.size(); j++)
        {
            fout << ' ' << Stations[i].WS[j];
        }
        fout << endl;
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
        CS Station;
        getline(in, Station.name);
        in >> Station.payoff;
        int WScount = 0;
        in >> WScount;
        Station.WS.resize(WScount);
        for (int j = 0; j < WScount; j++)
        {
            bool ws = true;
            in >> ws;
            Station.WS[j] = ws;
        }
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
            View(pipes, Stations);
            break;
        case 4:
            editPipe(pipes);
            break;
        case 5:
            editCS(Stations);
            break;
        case 6:
            Save(pipes, Stations);
            break;
        case 7:
            Load(pipes, Stations);
            break;
        case 8:
            return 0;
            break;
        default:
            break;
        }
    };
    return 0;
}