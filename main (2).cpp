#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

// Структура задачі
struct Task {
    string text;      // Назва задачі
    int priority;     // Пріоритет
    bool completed;   // Статус виконання
};

// Завантаження задач із файлу
void loadTasks(vector<Task>& tasks) {

    ifstream file("tasks.txt");

    if (!file.is_open())
        return;

    string line;

    while (getline(file, line)) {

        stringstream ss(line);

        Task task;

        string priorityStr;
        string completedStr;

        getline(ss, task.text, '|');
        getline(ss, priorityStr, '|');
        getline(ss, completedStr);

        task.priority = stoi(priorityStr);
        task.completed = (completedStr == "1");

        tasks.push_back(task);
    }

    file.close();
}

// Збереження задач у файл
void saveTasks(vector<Task>& tasks) {

    ofstream file("tasks.txt");

    for (Task task : tasks) {

        file << task.text << "|"
             << task.priority << "|"
             << task.completed << endl;
    }

    file.close();
}

// Додавання нової задачі
void addTask(vector<Task>& tasks) {

    Task task;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nВведіть назву задачі: ";
    getline(cin, task.text);

    do {
        cout << "Введіть пріоритет (1-5): ";
        cin >> task.priority;

        if (cin.fail() || task.priority < 1 || task.priority > 5) {

            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Невірний пріоритет.\n";
        }

    } while (task.priority < 1 || task.priority > 5);

    task.completed = false;

    tasks.push_back(task);

    cout << "Задачу додано.\n";
}

// Виведення всіх задач
void showAll(vector<Task>& tasks) {

    if (tasks.empty()) {

        cout << "Список задач порожній.\n";
        return;
    }

    cout << "\n===== ВСІ ЗАДАЧІ =====\n";

    for (int i = 0; i < tasks.size(); i++) {

        cout << i + 1 << ". "
             << tasks[i].text
             << " | Пріоритет: "
             << tasks[i].priority
             << " | ";

        if (tasks[i].completed)
            cout << "Виконано";
        else
            cout << "Активна";

        cout << endl;
    }
}

// Виведення тільки активних задач
void showActive(vector<Task>& tasks) {

    bool found = false;

    cout << "\n===== АКТИВНІ ЗАДАЧІ =====\n";

    for (int i = 0; i < tasks.size(); i++) {

        if (!tasks[i].completed) {

            cout << i + 1 << ". "
                 << tasks[i].text
                 << " | Пріоритет: "
                 << tasks[i].priority << endl;

            found = true;
        }
    }

    if (!found)
        cout << "Активних задач немає.\n";
}

// Позначення задачі виконаною
void completeTask(vector<Task>& tasks) {

    if (tasks.empty()) {
        cout << "Список порожній.\n";
        return;
    }

    showAll(tasks);

    int number;

    cout << "\nНомер задачі: ";
    cin >> number;

    if (number >= 1 && number <= tasks.size()) {

        tasks[number - 1].completed = true;

        cout << "Задачу виконано.\n";
    }
    else {
        cout << "Неправильний номер.\n";
    }
}

// Видалення задачі
void deleteTask(vector<Task>& tasks) {

    if (tasks.empty()) {
        cout << "Список порожній.\n";
        return;
    }

    showAll(tasks);

    int number;

    cout << "\nНомер задачі для видалення: ";
    cin >> number;

    if (number >= 1 && number <= tasks.size()) {

        tasks.erase(tasks.begin() + number - 1);

        cout << "Задачу видалено.\n";
    }
    else {
        cout << "Неправильний номер.\n";
    }
}

// Виведення головного меню
void menu() {

    cout << "\n========== МЕНЕДЖЕР ЗАДАЧ ==========\n";
    cout << "1. Додати задачу\n";
    cout << "2. Показати всі задачі\n";
    cout << "3. Показати активні задачі\n";
    cout << "4. Позначити виконаною\n";
    cout << "5. Видалити задачу\n";
    cout << "0. Зберегти і вийти\n";
}

// Головна функція програми
int main() {

    vector<Task> tasks;

    // Завантаження задач із файлу
    loadTasks(tasks);

    int choice;

    do {

        menu();

        cout << "Ваш вибір: ";
        cin >> choice;

        if (cin.fail()) {

            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Помилка вводу.\n";

            continue;
        }

        switch (choice) {

            case 1:
                addTask(tasks);
                break;

            case 2:
                showAll(tasks);
                break;

            case 3:
                showActive(tasks);
                break;

            case 4:
                completeTask(tasks);
                break;

            case 5:
                deleteTask(tasks);
                break;

            case 0:
                saveTasks(tasks);
                cout << "Дані збережено у tasks.txt\n";
                break;

            default:
                cout << "Невірний вибір.\n";
        }

    } while (choice != 0);

    return 0;
}