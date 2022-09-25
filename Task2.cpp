#include <iostream> // консоль - cout

// классы
class Figura
{
private:
    unsigned int qtySide;       // число сторон фигуры

protected:  // теперь к этим полям можно обращаться из производных классов
    bool figInit;               // false - объект не действителен
    unsigned int* lenght;
    unsigned short* angle;

public:
    Figura()                    // конструктор по умолчанию
    {
        setQtySide(0);
    }
    Figura(int n)               // конструктор с параметрами
    { 
        setQtySide(n);
    }
    ~Figura()   // деструктор, не уверен, что правильно освобождаю память?!
    {
        if (lenght) delete lenght;
        if (angle) delete angle;
    }

    void setQtySide(int n)
    {
        if (n <= 0)
        {
            qtySide = 0;
            lenght = nullptr;
            angle = nullptr;
        }
        else
        {
            qtySide = static_cast<unsigned int>(n);
            lenght = new unsigned int[n](); // длины в кол-ве "n"
            angle = new unsigned short[n](); // углы в кол-ве "n"
        }
        figInit = false;
    }
    bool isAvailable() { return figInit; }
    unsigned int getQtySide() { return qtySide; }
    // не сущ. стророна фигуры имеет длину/угол = 0
    unsigned int getLen(int num)
    {
        if (num < 0 || num >= qtySide) return 0;
        else return lenght[num];
    }
    unsigned short getAng(int num)
    {
        if (num < 0 || num >= qtySide) return 0;
        else return angle[num];
    }
};

class Triangle : public Figura
{
private:
protected:
public:
    // конструктор по умолчанию, запускает конструктор родителя с параметрами
    Triangle() : Figura(3) { ; }
    void setLengh(int a, int b, int c)
    {
        if (!getQtySide() || a <= 0 || b <= 0 || c <= 0) figInit = false;
        else
        {
            lenght[0] = static_cast<unsigned int>(a);
            lenght[1] = static_cast<unsigned int>(b);
            lenght[2] = static_cast<unsigned int>(c);
            if (angle[0] && angle[1] && angle[2]) figInit = true;
            else figInit = false;
        }
    }
    void setAngle(short a, short b, short c)
    {
        if (!getQtySide() || a <= 0 || b <= 0 || c <= 0) figInit = false;
        else
        {
            angle[0] = static_cast<unsigned short>(a);
            angle[1] = static_cast<unsigned short>(b);
            angle[2] = static_cast<unsigned short>(c);
            if (lenght[0] && lenght[1] && lenght[2]) figInit = true;
            else figInit = false;
        }
    }
};
class TriRight : public Triangle    // прямоугольный треугольник
{
public:
    TriRight(int lenA, int lenB, int lenC, short angA, short angB)
    {
        setLengh(lenA, lenB, lenC);
        setAngle(angA, angB, 90);
    }
};
class TriIsos : public Triangle    // равнобедренный треугольник
{
public:
    TriIsos(int lenA, int lenB, short angA, short angB)
    {
        setLengh(lenA, lenB, lenA);
        setAngle(angA, angB, angA);
    }
};
class TriEquil : public Triangle    // равносторонний треугольник
{
public:
    TriEquil(int lengh)
    {
        setLengh(lengh, lengh, lengh);
        setAngle(60, 60, 60);
    }
};

class Quad : public Figura
{
private:
protected:
public:
    Quad()  // конструктор по умолчанию
    { 
        setQtySide(4);  // создаю четырехугольник
    }
    void setLengh(int a, int b, int c, int d)
    {
        if (!getQtySide() || a <= 0 || b <= 0 || c <= 0 || d <= 0) figInit = false;
        else
        {
            lenght[0] = static_cast<unsigned int>(a);
            lenght[1] = static_cast<unsigned int>(b);
            lenght[2] = static_cast<unsigned int>(c);
            lenght[3] = static_cast<unsigned int>(d);
            if (angle[0] && angle[1] && angle[2] && angle[3]) figInit = true;
            else figInit = false;
        }
    }
    void setAngle(short a, short b, short c, short d)
    {
        if (!getQtySide() || a <= 0 || b <= 0 || c <= 0 || d <= 0) figInit = false;
        else
        {
            angle[0] = static_cast<unsigned short>(a);
            angle[1] = static_cast<unsigned short>(b);
            angle[2] = static_cast<unsigned short>(c);
            angle[3] = static_cast<unsigned short>(d);
            if (lenght[0] && lenght[1] && lenght[2] && lenght[3]) figInit = true;
            else figInit = false;
        }
    }
};
class Rectangle : public Quad    // прямоугольник
{
public:
    Rectangle(int lenA, int lenB)
    {
        setLengh(lenA, lenB, lenA, lenB);
        setAngle(90, 90, 90, 90);
    }
};
class Square : public Quad    // квадрат
{
public:
    Square(int lengh)
    {
        setLengh(lengh, lengh, lengh, lengh);
        setAngle(90, 90, 90, 90);
    }
};
class Parall : public Quad    // параллелограмм
{
public:
    Parall(int lenA, int lenB, short angA, short angB)
    {
        setLengh(lenA, lenB, lenA, lenB);
        setAngle(angA, angB, angA, angB);
    }
};
class Rhombus : public Quad    // ромб
{
public:
    Rhombus(int lengh, short angA, short angB)
    {
        setLengh(lengh, lengh, lengh, lengh);
        setAngle(angA, angB, angA, angB);
    }
};

// объявления функций
void print_info(const std::string, Figura*);

// программа
int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");   // задаём русский текст
    system("chcp 1251");            // настраиваем кодировку консоли
    std::system("cls");

    std::cout << "Задача 2. Фигуры. Стороны и углы\n"
              << "--------------------------------\n\n";

    Figura* fig = nullptr;    // указатель на объект типа Figura

    // треугольники ----------------------
    Triangle triangle;
    triangle.setLengh(10, 20, 30);
    triangle.setAngle(50, 60, 70);
    print_info("Треугольник", &triangle);

    fig = new TriRight (10, 20, 30, 50, 60);   // вот тут я присваиваю указателю динамически выделенный объект
    print_info("Прямоугольный треугольник", fig);
    //delete tri;     // тут его нужно удалять? Или в классе нужно делать деструктор (и как делать)?

    fig = new TriIsos (10, 20, 50, 60);
    print_info("Равнобедренный треугольник", fig);

    fig = new TriEquil (30);
    print_info("Равносторонний треугольник", fig);

    fig = new TriEquil(-10);  // ошибка инициализации, длина стороны = -10 !!!
    print_info("Еще равносторонний треугольник", fig);

    // четырехугольники ----------------------
    Quad quad;
    quad.setLengh(10, 20, 30, 40);
    quad.setAngle(50, 60, 70, 80);
    print_info("Четырёхугольник", &quad);
    
    fig = new Rectangle(10, 20);
    print_info("Прямоугольник", fig);

    fig = new Square(20);
    print_info("Квадрат", fig);
    
    fig = new Parall(20, 30, 30, 40);;
    print_info("Параллелограмм", fig);

    fig = new Rhombus(30, 30, 40);;
    print_info("Ромб", fig);
    delete fig;     // а тут его нужно удалять? Или в классе нужно делать деструктор (и как делать)?
    fig = nullptr;


    return 0;
}

// функция, принимает строку и базовый класс
// выводит информацию на консоль
void print_info(const std::string str, Figura* tr)
{
    using namespace std;

    cout << str << ":" << std::endl;
    if (tr->isAvailable())
    {
        int temp = 0;
        cout << "Стороны:";
        if (temp = tr->getLen(0)) cout << " а=" << temp;
        if (temp = tr->getLen(1)) cout << " b=" << temp;
        if (temp = tr->getLen(2)) cout << " c=" << temp;
        if (temp = tr->getLen(3)) cout << " d=" << temp;
        cout << std::endl << "Углы:";
        if (temp = tr->getAng(0)) cout << " A=" << temp;
        if (temp = tr->getAng(1)) cout << " B=" << temp;
        if (temp = tr->getAng(2)) cout << " C=" << temp;
        if (temp = tr->getAng(3)) cout << " D=" << temp;
        cout << std::endl;
    }
    else cout << "Фигура не определена!" << std::endl;
    cout << std::endl;
}


/*
В этом задании вы усложните иерархию классов для усложнённой предметной области.

У вас появляется информация о длине сторон и углах ваших фигур, а также несколько более конкретных фигур.
Теперь в треугольнике вы должны хранить информацию о длине всех его трёх сторон (a, b, c) и значениях его
трёх углов (A, B, C). В четырёхугольнике вы храните информацию о длине его четырёх сторон (a, b, c, d)
и значениях его четырёх углов (A, B, C, D).

Также у вас появляются более конкретные фигуры:

прямоугольный треугольник (угол C всегда равен 90);
равнобедренный треугольник (стороны a и c равны, углы A и C равны);
равносторонний треугольник (все стороны равны, все углы равны 60);
прямоугольник (стороны a,c и b,d попарно равны, все углы равны 90);
квадрат (все стороны равны, все углы равны 90);
параллелограмм (стороны a,c и b,d попарно равны, углы A,C и B,D попарно равны);
ромб (все стороны равны, углы A,C и B,D попарно равны).

Вы должны иметь возможность узнать у каждой фигуры длины её сторон и значения её углов, но извне вы не должны
быть способны изменить длины сторон и углы.

Не должно быть возможности создать фигуры, не удовлетворяющие перечисленным условиям. Например, нельзя создать
квадрат с разными углами. Геометрические соотношения проверять не нужно. Например, сумма углов в треугольнике
может быть не равна 180.

Задача: спроектировать и реализовать классы, описывающие предметную область. Продемонстрируйте их работу:
создайте по одному экземпляру каждой фигуры и выведите на экран информацию о длинах её сторон и величине
её углов. Значения используйте произвольные.

Инициализацию длин сторон и величин углов нужно выполнить с помощью вызова базовых конструкторов.

Для вывода информации о фигуре создайте функцию print_info, которая будет принимать в качестве аргумента
указатель на базовый класс фигуры.

Пример работы программы
Консоль
Треугольник:
Стороны: a=10 b=20 c=30
Углы: A=50 B=60 C=70

Прямоугольный треугольник:
Стороны: a=10 b=20 c=30
Углы: A=50 B=60 C=90

Равнобедренный треугольник:
Стороны: a=10 b=20 c=10
Углы: A=50 B=60 C=50

Равносторонний треугольник:
Стороны: a=30 b=30 c=30
Углы: A=60 B=60 C=60

Четырёхугольник:
Стороны: a=10 b=20 c=30 d=40
Углы: A=50 B=60 C=70 D=80

Прямоугольник:
Стороны: a=10 b=20 c=10 d=20
Углы: A=90 B=90 C=90 D=90

Квадрат:
Стороны: a=20 b=20 c=20 d=20
Углы: A=90 B=90 C=90 D=90

Параллелограмм:
Стороны: a=20 b=30 c=20 d=30
Углы: A=30 B=40 C=30 D=40

Ромб:
Стороны: a=30 b=30 c=30 d=30
Углы: A=30 B=40 C=30 D=40
*/