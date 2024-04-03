#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <locale>
#include <windows.h>
#include <list> // Добавляем заголовочный файл для работы со списками

using namespace std;

// Структура для хранения информации о детали
struct Detail {
    string name;
    float cost = 0;
    float size = 0;
    float weight = 0;
};

// Функция для ввода данных о детали
void enter(Detail& detail) {
    cout << "Введите название детали: ";
    cin >> detail.name;
    cout << "Введите стоимость детали: ";
    cin >> detail.cost;
    cout << "Введите размер детали: ";
    cin >> detail.size;
    cout << "Введите вес детали: ";
    cin >> detail.weight;
}

// Функция для сортировки списка деталей по стоимости 
void sortDetails(list<Detail>& results) {
    results.sort([](const Detail& a, const Detail& b) {
        return a.cost < b.cost;
        });
}

// Функция для вывода списка деталей в виде таблицы с нумерацией
void printDetails(const list<Detail>& results) {
    if (!results.empty()) {
        cout << "----------------------------------------------------------------------------------------------------------\n";
        cout << setw(5) << "№" << setw(20) << "Название детали" << setw(20) << "Стоимость" << setw(20) << "Размер" << setw(20) << "Вес" << endl;
        cout << "----------------------------------------------------------------------------------------------------------\n";
        int i = 0;
        for (const auto& detail : results) {
            cout << setw(5) << ++i << setw(20) << detail.name << setw(20) << detail.cost << setw(20) << detail.size << setw(20) << detail.weight << endl;
        }
        cout << "----------------------------------------------------------------------------------------------------------\n";
    }
    else {
        cout << "\nНет информации о деталях для вывода.\n";
    }
}

// Функция для сохранения информации о деталях в файл
void saveDetails(const list<Detail>& results) {
    if (!results.empty()) {
        ofstream outFile("details.txt");
        if (outFile.is_open()) {
            for (const auto& detail : results) {
                outFile << "Название детали: " << detail.name << "\nСтоимость детали: " << detail.cost << "\nРазмер детали: " << detail.size << "\nВес детали: " << detail.weight << endl;
            }
            outFile.close();
            cout << "Информация о деталях сохранена в файле 'details.txt'.\n";
        }
        else {
            cout << "Невозможно открыть файл для записи.\n";
        }
    }
    else {
        cout << "\nНет информации о деталях для сохранения.\n";
    }
}

// Функция для удаления данных о детали
void removeDetail(list<Detail>& results) {
    if (results.empty()) {
        cout << "Нет информации о деталях для удаления.\n";
        return;
    }

    cout << "Список деталей:\n";
    cout << "0. Отмена удаления\n";
    int i = 1;
    for (const auto& detail : results) {
        cout << i++ << ". " << detail.name << endl;
    }

    cout << "Введите номер детали для удаления (от 1 до " << results.size() << "), или введите 0 для отмены: ";
    int detailNumber;
    do {
        cin >> detailNumber;
        if (detailNumber == 0) {
            cout << "Отмена удаления.\n";
            return;
        }
        else if (detailNumber < 1 || detailNumber > results.size()) {
            cout << "Некорректный номер детали. Пожалуйста, введите корректный номер или 0 для отмены: ";
        }
    } while (detailNumber < 0 || detailNumber > results.size());

    auto iter = results.begin();
    advance(iter, detailNumber - 1);
    cout << "Деталь '" << iter->name << "' удалена.\n";
    results.erase(iter);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Rus");

    list<Detail> details; // Список структур Detail для хранения данных о деталях
    int choice;

    do {
        cout << "\nМеню выбора:\n";
        cout << "1. Ввести данные о детали\n";
        cout << "2. Удалить данные о детали\n";
        cout << "3. Вывести информацию о деталях\n";
        cout << "4. Отсортировать детали по стоимости\n";
        cout << "5. Сохранить информацию о деталях в файл\n";
        cout << "6. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
        {
            Detail newDetail;
            cout << "\nВведите данные о новой детали:\n";
            enter(newDetail);
            details.push_back(newDetail); 
            break;
        }
        case 2:
        {
            removeDetail(details);
            break;
        }
        case 3:
        {
            printDetails(details);
            break;
        }
        case 4:
            sortDetails(details);
            cout << "\nДетали отсортированы по стоимости.\n";
            break;
        case 5:
        {
            saveDetails(details);
            break;
        }
        case 6:
        {
            cout << "Выход.\n";
            break;
        }
        default:
        {
            cout << "Неверный выбор.\n";
            break;
        }

        }
    } while (choice != 6);

    return 0;
}