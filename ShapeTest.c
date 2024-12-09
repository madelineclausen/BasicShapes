#include <malloc.h>
#include <iostream>

typedef double (*double_method_type)(void *);
typedef void (*void_method_type)(void *);

typedef union 
{
    double_method_type double_method;
    void_method_type void_method;
} VirtualTableEntry;

typedef VirtualTableEntry * VTableType;

VirtualTableEntry Shape_VTable[3];
VirtualTableEntry Circle_VTable[3];
VirtualTableEntry Triangle_VTable [3];
VirtualTableEntry Square_VTable [3];
VirtualTableEntry Rectangle_VTable [3];

struct Shape
{
    VTableType VPointer;
    std::string name;
};

Shape * Shape_Shape(Shape * _this, std::string name)
{
    _this->VPointer = Shape_VTable;
    _this->name = name;
    return _this;
}

struct Circle
{
    VTableType VPointer;
    std::string name;
    double radius;
};

Circle * Circle_Circle(Circle * _this, std::string name, double radius)
{
    Shape_Shape((Shape *)_this, name); 
    _this->VPointer = Circle_VTable; 
    _this->radius = radius;
    return _this;
}

struct Triangle
{
    VTableType VPointer;
    std::string name;
    double base;
    double height;
};

Triangle * Triangle_Triangle(Triangle * _this, std::string name, double base, double height)
{
    Shape_Shape((Shape *)_this, name);
    _this->VPointer = Triangle_VTable;
    _this->base = base;
    _this->height = height;
    return _this;
}

struct Square
{
    VTableType VPointer;
    std::string name;
    double length;
};

Square * Square_Square(Square * _this, std::string name, double length)
{
    Shape_Shape((Shape *)_this, name); 
    _this->VPointer = Square_VTable; 
    _this->length = length;
    return _this;
}

struct Rectangle
{
    VTableType VPointer;
    std::string name;
    double length;
    double width;
};

Rectangle * Rectangle_Rectangle(Rectangle * _this, std::string name, double length, double width)
{
    Square_Square((Square *)_this, name, length);
    _this->VPointer = Rectangle_VTable;
    _this->length = length;
    _this->width = width;
    return _this;
}

void printAll(Shape* shapes[8], int count)
{
    for (int i = 0; i<count; i++)
    {
        shapes[i]->VPointer[2].void_method(shapes[i]);
    }
}

void drawAll(Shape* shapes[8], int count)
{
    for (int i = 0; i<count; i++)
    {
        shapes[i]->VPointer[1].void_method(shapes[i]);
    }
}

double totalArea(Shape* shapes[8], int count)
{
    double total = 0;
    for (int i = 0; i<count; i++)
    {
        total += shapes[i]->VPointer[0].double_method(shapes[i]);
    }
    return total;
}

double areaCircle(Circle *_this)
{
    return _this->radius * _this->radius * 3.14;
}

void drawCircle(Circle *_this)
{
    std::cout << "   * *\n *     *\n*       *\n *     *\n   * *\n" << std::endl;
}

void printCircle(Circle *_this)
{
    std::cout << _this->name + "(" + std::to_string(_this->radius) + ") : " + std::to_string(Circle_VTable[0].double_method(_this)) << std::endl;
}

double areaTriangle(Triangle *_this)
{
    return (_this->base * _this->height) / 2;
}

void drawTriangle(Triangle *_this)
{
    std::cout << "   *\n  * *\n *   *\n* * * *\n" << std::endl;
}

void printTriangle(Triangle *_this)
{
    std::cout << _this->name + "(" + std::to_string(_this->base) + ", " + std::to_string(_this->height) + ") : " + std::to_string(Triangle_VTable[0].double_method(_this)) << std::endl;
}

double areaSquare(Square *_this)
{
    return _this->length * _this->length;
}

void drawSquare(Square *_this)
{
    std::cout << "* * * *\n*     *\n*     *\n* * * *\n" << std::endl;
}

void printSquare(Square *_this)
{
    std::cout << _this->name + "(" + std::to_string(_this->length) + ") : " + std::to_string(Square_VTable[0].double_method(_this)) << std::endl;
}

double areaRectangle(Rectangle *_this)
{
    return _this->length * _this->width;
}

void drawRectangle(Rectangle *_this)
{
    std::cout << "* * * *\n*     *\n*     *\n*     *\n*     *\n* * * *\n" << std::endl;
}

void printRectangle(Rectangle *_this)
{
    std::cout << _this->name + "(" + std::to_string(_this->length) + ", " + std::to_string(_this->width) + ") : " + std::to_string(Rectangle_VTable[0].double_method(_this)) << std::endl;
}

void populateVTable()
{
    Rectangle_VTable[0] = {.double_method=(double_method_type)areaRectangle};
    Rectangle_VTable[1] = {.void_method=(void_method_type)drawRectangle};
    Rectangle_VTable[2] = {.void_method=(void_method_type)printRectangle};
    Circle_VTable[0] = {.double_method=(double_method_type)areaCircle};
    Circle_VTable[1] = {.void_method=(void_method_type)drawCircle};
    Circle_VTable[2] = {.void_method=(void_method_type)printCircle};
    Triangle_VTable[0] = {.double_method=(double_method_type)areaTriangle};
    Triangle_VTable[1] = {.void_method=(void_method_type)drawTriangle};
    Triangle_VTable[2] = {.void_method=(void_method_type)printTriangle};
    Square_VTable[0] = {.double_method=(double_method_type)areaSquare};
    Square_VTable[1] = {.void_method=(void_method_type)drawSquare};
    Square_VTable[2] = {.void_method=(void_method_type)printSquare};
}


int main(int argc, char *argv[])
{
    populateVTable();
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    Shape* shapes [8] = {(Shape *)Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "FirstTriangle", x, y),
                        (Shape *)Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "SecondTriangle", x-1, y-1),
                        (Shape *)Circle_Circle((Circle *)malloc(sizeof(Circle)), "FirstCircle", x),
                        (Shape *)Circle_Circle((Circle *)malloc(sizeof(Circle)), "SecondCircle", x-1),
                        (Shape *)Square_Square((Square *)malloc(sizeof(Square)), "FirstSquare", x),
                        (Shape *)Square_Square((Square *)malloc(sizeof(Square)), "SecondSquare", x-1),
                        (Shape *)Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "FirstRectangle", x, y),
                        (Shape *)Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "SecondRectangle", x-1, y-1)
    };

    printAll(shapes, 8);
    drawAll(shapes, 8);
    std::cout << "Total : " + std::to_string(totalArea(shapes, 8)) << std::endl;
}