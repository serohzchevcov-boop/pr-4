#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <clocale>

using namespace std;

class User {
protected:
    string name;
    string email;

private:
    string password;

public:
    User(string n, string e, string p) {
        name = n;
        email = e;
        password = p;
    }

    virtual void showInfo() {
        cout << "Имя: " << name << endl;
        cout << "Email: " << email << endl;
    }

    string getName() {
        return name;
    }

    virtual ~User() {}
};

class Student : public User {
private:
    vector<int> courseIds;

public:
    Student(string n, string e, string p)
        : User(n, e, p) {}

    void enrollCourse(int id) {
        courseIds.push_back(id);
    }

    void showInfo() override {
        cout << "Студент: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Количество курсов: " << courseIds.size() << endl;
    }
};

class Teacher : public User {
private:
    vector<int> courseIds;

public:
    Teacher(string n, string e, string p)
        : User(n, e, p) {}

    void addCourse(int id) {
        courseIds.push_back(id);
    }

    void showInfo() override {
        cout << "Преподаватель: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Количество курсов: " << courseIds.size() << endl;
    }
};

class LearningMaterial {
protected:
    string title;

public:
    LearningMaterial(string t) {
        title = t;
    }

    virtual void showInfo() {
        cout << "Материал: " << title << endl;
    }

    virtual ~LearningMaterial() {}
};

class Lesson : public LearningMaterial {
public:
    Lesson(string t) : LearningMaterial(t) {}

    void showInfo() override {
        cout << "Урок: " << title << endl;
    }
};

class Assignment : public LearningMaterial {
public:
    Assignment(string t) : LearningMaterial(t) {}

    void showInfo() override {
        cout << "Задание: " << title << endl;
    }
};

class Course {
protected:
    int id;
    string title;
    string description;

public:
    vector<Lesson> lessons;
    vector<Assignment> assignments;

    Course(int i, string t, string d) {
        id = i;
        title = t;
        description = d;
    }

    int getId() {
        return id;
    }

    string getTitle() {
        return title;
    }

    virtual void showInfo() {
        cout << "Курс: " << title << endl;
        cout << "Описание: " << description << endl;
    }

    void addLesson(string name) {
        lessons.push_back(Lesson(name));
    }

    void addAssignment(string name) {
        assignments.push_back(Assignment(name));
    }

    virtual ~Course() {}
};

class OnlineCourse : public Course {
public:
    OnlineCourse(int i, string t, string d)
        : Course(i, t, d) {}

    void showInfo() override {
        cout << "Онлайн-курс: " << title << endl;
        cout << "Описание: " << description << endl;
    }
};

class PracticalCourse : public Course {
public:
    PracticalCourse(int i, string t, string d)
        : Course(i, t, d) {}

    void showInfo() override {
        cout << "Практический курс: " << title << endl;
        cout << "Описание: " << description << endl;
    }
};

class Enrollment {
private:
    int studentId;
    Course* course;

public:
    Enrollment(int s, Course* c) {
        studentId = s;
        course = c;
    }

    int getStudentId() {
        return studentId;
    }

    Course* getCourse() {
        return course;
    }

    void showInfo() {
        cout << "Студент ID: " << studentId << endl;
        cout << "Курс: " << course->getTitle() << endl;
    }
};

class AccessExample {
protected:
    int protectedValue;

public:
    AccessExample() {
        protectedValue = 10;
    }

    friend class SameModuleExample;
};

class SameModuleExample {
public:
    void showValue(AccessExample& obj) {
        cout << "Значение protected: "
             << obj.protectedValue << endl;
    }
};

int main() {
    setlocale(LC_ALL, "");

    vector<Student> students;
    vector<Teacher> teachers;
    vector<Course*> courses;
    vector<Enrollment> enrollments;

    int choice;

    do {
        cout << "\n===== СИСТЕМА ДИСТАНЦИОННЫХ КУРСОВ =====" << endl;
        cout << "1. Добавить студента" << endl;
        cout << "2. Добавить преподавателя" << endl;
        cout << "3. Создать онлайн-курс" << endl;
        cout << "4. Создать практический курс" << endl;
        cout << "5. Записать студента на курс" << endl;
        cout << "6. Показать студентов" << endl;
        cout << "7. Показать преподавателей" << endl;
        cout << "8. Показать курсы" << endl;
        cout << "9. Показать записи на курсы" << endl;
        cout << "10. Добавить урок" << endl;
        cout << "11. Добавить задание" << endl;
        cout << "12. Показать материалы курса" << endl;
        cout << "13. Проверка доступа" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string name, email, password;

            cout << "Введите имя: ";
            getline(cin, name);

            cout << "Введите email: ";
            getline(cin, email);

            cout << "Введите пароль: ";
            getline(cin, password);

            students.push_back(Student(name, email, password));
            cout << "Студент добавлен!" << endl;
        }
        else if (choice == 2) {
            string name, email, password;

            cout << "Введите имя: ";
            getline(cin, name);

            cout << "Введите email: ";
            getline(cin, email);

            cout << "Введите пароль: ";
            getline(cin, password);

            teachers.push_back(Teacher(name, email, password));
            cout << "Преподаватель добавлен!" << endl;
        }
        else if (choice == 3 || choice == 4) {
            string title, description;
            int id = courses.size() + 1;

            cout << "Введите название курса: ";
            getline(cin, title);

            cout << "Введите описание курса: ";
            getline(cin, description);

            if (choice == 3) {
                courses.push_back(
                    new OnlineCourse(id, title, description)
                );
            }
            else {
                courses.push_back(
                    new PracticalCourse(id, title, description)
                );
            }

            cout << "Курс создан!" << endl;
        }
        else if (choice == 5) {
            if (students.empty() || courses.empty()) {
                cout << "Сначала добавьте студента и курс." << endl;
            }
            else {
                cout << "Список студентов:" << endl;

                for (int i = 0; i < students.size(); i++) {
                    cout << i + 1 << ". "
                         << students[i].getName() << endl;
                }

                int studentNumber;
                cout << "Выберите студента: ";
                cin >> studentNumber;

                cout << "Список курсов:" << endl;

                for (int i = 0; i < courses.size(); i++) {
                    cout << i + 1 << ". "
                         << courses[i]->getTitle() << endl;
                }

                int courseNumber;
                cout << "Выберите курс: ";
                cin >> courseNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (studentNumber > 0 &&
                    studentNumber <= students.size() &&
                    courseNumber > 0 &&
                    courseNumber <= courses.size()) {

                    Course* selectedCourse = courses[courseNumber - 1];
                    bool alreadyEnrolled = false;

                    for (int i = 0; i < enrollments.size(); i++) {
                        if (enrollments[i].getStudentId() == studentNumber - 1 &&
                            enrollments[i].getCourse() == selectedCourse) {
                            alreadyEnrolled = true;
                            break;
                        }
                    }

                    if (!alreadyEnrolled) {
                        students[studentNumber - 1].enrollCourse(
                            selectedCourse->getId()
                        );

                        enrollments.push_back(
                            Enrollment(studentNumber - 1, selectedCourse)
                        );

                        cout << "Студент записан на курс!" << endl;
                    }
                    else {
                        cout << "Студент уже записан на этот курс." << endl;
                    }
                }
                else {
                    cout << "Неверный номер." << endl;
                }
            }
        }
        else if (choice == 6) {
            for (int i = 0; i < students.size(); i++) {
                students[i].showInfo();
                cout << endl;
            }
        }
        else if (choice == 7) {
            for (int i = 0; i < teachers.size(); i++) {
                teachers[i].showInfo();
                cout << endl;
            }
        }
        else if (choice == 8) {
            for (int i = 0; i < courses.size(); i++) {
                courses[i]->showInfo();
                cout << endl;
            }
        }
        else if (choice == 9) {
            for (int i = 0; i < enrollments.size(); i++) {
                enrollments[i].showInfo();
                cout << endl;
            }
        }
        else if (choice == 10 || choice == 11 || choice == 12) {
            if (courses.empty()) {
                cout << "Сначала создайте курс." << endl;
            }
            else {
                for (int i = 0; i < courses.size(); i++) {
                    cout << i + 1 << ". "
                         << courses[i]->getTitle() << endl;
                }

                int courseNumber;
                cout << "Выберите курс: ";
                cin >> courseNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (courseNumber > 0 && courseNumber <= courses.size()) {
                    Course* selectedCourse = courses[courseNumber - 1];

                    if (choice == 10) {
                        string lessonName;

                        cout << "Введите название урока: ";
                        getline(cin, lessonName);

                        selectedCourse->addLesson(lessonName);
                        cout << "Урок добавлен!" << endl;
                    }
                    else if (choice == 11) {
                        string assignmentName;

                        cout << "Введите название задания: ";
                        getline(cin, assignmentName);

                        selectedCourse->addAssignment(assignmentName);
                        cout << "Задание добавлено!" << endl;
                    }
                    else {
                        cout << "Уроки:" << endl;

                        for (int i = 0; i < selectedCourse->lessons.size(); i++) {
                            selectedCourse->lessons[i].showInfo();
                        }

                        cout << "Задания:" << endl;

                        for (int i = 0; i < selectedCourse->assignments.size(); i++) {
                            selectedCourse->assignments[i].showInfo();
                        }
                    }
                }
                else {
                    cout << "Неверный номер курса." << endl;
                }
            }
        }
        else if (choice == 13) {
            AccessExample example;
            SameModuleExample access;

            access.showValue(example);
        }
        else if (choice == 0) {
            cout << "Программа завершена." << endl;
        }
        else {
            cout << "Неверный пункт меню." << endl;
        }

    } while (choice != 0);

    for (int i = 0; i < courses.size(); i++) {
        delete courses[i];
    }

    return 0;
}