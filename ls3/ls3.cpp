#include <iostream>
#include <cstring>
#include <Windows.h>
using namespace std;

class Data {
public:
    int dayy;
    int monthh;
    int yearr;
    Data() : dayy{ 0 }, monthh{ 0 }, yearr{ 0 } {}
    Data(int day, int month, int year) : dayy{ day }, monthh{ month }, yearr{ year } {}
    void print() const { cout << dayy << "|" << monthh << "|" << yearr << endl; }
};

class Human {
    int index;
    char* Surname;
    char* name;
    char* Fathername;
    Data birth;
    static int plus;

public:
    Human() : index{ 0 }, Surname{ nullptr }, name{ nullptr }, Fathername{ nullptr }, birth{ 0,0,0 } {
        plus += 1;
    }

    Human(int ind, const char* Surn, const char* nam, const char* Fname, int day, int month, int year)
        : index{ ind }, birth{ day, month, year } {
        Fathername = new char[strlen(Fname) + 1];
        Surname = new char[strlen(Surn) + 1];
        name = new char[strlen(nam) + 1];
        strcpy(Fathername, Fname);
        strcpy(Surname, Surn);
        strcpy(name, nam);
        plus += 1;
    }

    Human(Human&& human)
        : index{ human.index }, birth{ human.birth } {
        Surname = human.Surname;
        name = human.name;
        Fathername = human.Fathername;

        human.index = 0;
        human.Surname = nullptr;
        human.name = nullptr;
        human.Fathername = nullptr;
    }

    Human& operator=(Human&& human) {
        if (this != &human) {
            delete[] Surname;
            delete[] name;
            delete[] Fathername;

            index = human.index;
            Surname = human.Surname;
            name = human.name;
            Fathername = human.Fathername;
            birth = human.birth;

            human.index = 0;
            human.Surname = nullptr;
            human.name = nullptr;
            human.Fathername = nullptr;
        }
        return *this;
    }

    void Print() const {
        cout << index << " , " << Surname << " , " << name << " , " << Fathername << " , ";
        birth.print();
    }

    ~Human() {
        delete[] Surname;
        delete[] name;
        delete[] Fathername;
        plus -= 1;
    }

    int Count() const {
        return plus;
    }
};

int Human::plus = 0;

class Flat {
    int kil;
    Human* Kvart;

public:
    Flat() : kil{ 0 }, Kvart{ nullptr } {}

    Flat(Human humans[], int num) : kil{ num } {
        Kvart = new Human[kil];
        for (int i = 0; i < kil; i++) {
            Kvart[i] = humans[i];
        }
    }

    Flat(Flat&& flatt) : kil{ flatt.kil }, Kvart{ flatt.Kvart } {
        flatt.kil = 0;
        flatt.Kvart = nullptr;
    }

    Flat& operator=(Flat&& flatt) {
        if (this != &flatt) {
            delete[] Kvart;
            kil = flatt.kil;
            Kvart = flatt.Kvart;
            flatt.kil = 0;
            flatt.Kvart = nullptr;
        }
        return *this;
    }

    ~Flat() {
        delete[] Kvart;
    }

    void Prrint() const {
        for (int i = 0; i < kil; i++) {
            Kvart[i].Print();
        }
    }
};

class Building {
    int num;
    Flat* flats;

public:
    Building(Flat* flatss, int numm) : num{ numm } {
        flats = new Flat[num];
        for (int i = 0; i < num; i++) {
            flats[i] = std::move(flatss[i]);
        }
    }

    ~Building() {
        delete[] flats;
    }

    void printBuilding() const {
        for (int i = 0; i < num; i++) {
            cout << endl << "Flat " << i + 1 << ": " << endl;
            flats[i].Prrint();
        }
    }
};

int main() {
    Human Humans1[] = { {48, "Иванов", "Иван", "Петрович", 28, 1, 1978} };
    Human Humans2[] = { {28, "Сидоров", "Дмитрий", "Алексеевич", 2, 3, 1996},
                        {31, "Петров", "Алексей", "Игоревич", 6, 9, 1992} };
    Human Humans3[] = { {24, "Кузнецова", "Ольга", "Владимировна", 4, 6, 2001},
                        {24, "Кузнецов", "Антон", "Владимирович", 15, 10, 2000},
                        {3, "Кузнецова", "Анна", "Антоновна", 25, 7, 2021} };
    Human Humans4[] = { {57, "Михайлова", "Мария", "Геннадьевна", 17, 8, 1967},
                        {68, "Михайлов", "Сергей", "Александрович", 21, 4, 1958},
                        {36, "Михайлов", "Артем", "Сергеевич", 25, 7, 1988},
                        {29, "Михайлова", "Елена", "Сергеевна", 25, 7, 1995} };
    Human Humans5[] = { {26, "Николаева", "Светлана", "Ивановна", 3, 2, 1998},
                        {30, "Николаев", "Владислав", "Михайлович", 21, 4, 1993},
                        {6, "Николаев", "Александр", "Владиславович", 4, 12, 2018},
                        {4, "Николаева", "Дарья", "Владиславовна", 13, 11, 2020},
                        {4, "Николаев", "Павел", "Владиславович", 13, 11, 2020} };

    Flat Kvar1{ Humans1, 1 };
    Flat Kvar2{ Humans2, 2 };
    Flat Kvar3{ Humans3, 3 };
    Flat Kvar4{ Humans4, 4 };
    Flat Kvar5{ Humans5, 5 };

    Flat flats[] = { Kvar1, Kvar2, Kvar3, Kvar4, Kvar5 };

    Building home{ flats, 5 };
    home.printBuilding();

    return 0;
}
