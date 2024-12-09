class Shape
{
    String name;
    Shape(String name)
    {
        this.name = name;
    }
    void print()
    {
        System.out.println(name + "() : " + Double.toString(area()));
    }
    void draw()
    {
        System.out.println("NULL");
    }
    double area()
    {
        return 0.0;
    }
}

class Circle extends Shape
{
    int radius;
    Circle(String name, int radius) 
    {
        super(name);
        this.radius = radius;
    }
    void print()
    {
        System.out.println(name + "(" + this.radius + ") : " + Double.toString(area()));
    }
    void draw()
    {
        System.out.println("   * *");
        System.out.println(" *     *");
        System.out.println("*       *");
        System.out.println(" *     *");
        System.out.println("   * *");
    }
    double area()
    {
        return this.radius*this.radius*3.14;
    }
}

class Triangle extends Shape
{
    int base;
    int height;
    Triangle(String name, int base, int height) 
    {
        super(name);
        this.base = base;
        this.height = height;
    }
    void print()
    {
        System.out.println(name + "(" + this.base + ", " + this.height + ") : " + Double.toString(area()));
    }
    void draw()
    {
        System.out.println("   *");
        System.out.println("  * *");
        System.out.println(" *   *");
        System.out.println("* * * *");
    }
    double area()
    {
        return (this.base * this.height)/2;
    }
}

class Square extends Shape
{
    int length;
    Square(String name, int length) 
    {
        super(name);
        this.length = length;
    }
    void print()
    {
        System.out.println(name + "(" + this.length + ") : " + Double.toString(area()));
    }
    void draw()
    {
        System.out.println("* * * *");
        System.out.println("*     *");
        System.out.println("*     *");
        System.out.println("* * * *");
    }
    double area()
    {
        return this.length*this.length;
    }
}

class Rectangle extends Square
{
    int width;
    Rectangle(String name, int length, int width) 
    {
        super(name, length);
        this.width = width;
    }
    void print()
    {
        System.out.println(name + "(" + this.length + ", " + this.width + ") : " + Double.toString(area()));
    }
    void draw()
    {
        System.out.println("* * * *");
        System.out.println("*     *");
        System.out.println("*     *");
        System.out.println("*     *");
        System.out.println("*     *");
        System.out.println("* * * *");
    }
    double area()
    {
        return this.length*this.width;
    }
}

class ListNode 
{
    Shape shape;
    ListNode next;
    ListNode(Shape shape, ListNode next) 
    {
        this.shape = shape;
        this.next = next;
    }
}


class Picture
{
    ListNode head;
    Picture()
    {
        this.head = null;
    }
    void add(Shape sh)
    {
        ListNode node = new ListNode(sh, head);
        this.head = node;
    }
    void printAll()
    {
        ListNode head_copy = head;
        while (true)
        {
            head_copy.shape.print();
            if (head_copy.next == null)
            {
                break;
            }
            head_copy = head_copy.next;
        }
    }
    void drawAll()
    {
        ListNode head_copy = head;
        while (true)
        {
            head_copy.shape.draw();
            if (head_copy.next == null)
            {
                break;
            }
            head_copy = head_copy.next;
        }
    }
    double totalArea()
    {
        ListNode head_copy = head;
        double total = 0;
        while (true)
        {
            total += head_copy.shape.area();
            if (head_copy.next == null)
            {
                break;
            }
            head_copy = head_copy.next;
        }
        return total;
    }
}

public class mainClass
{
    public static void main(String[] args)
    {
        int x = Integer.parseInt(args[0]);
        int y = Integer.parseInt(args[1]);

        Picture picture = new Picture();

        Shape triangle1 = new Triangle("FirstTriangle", x, y);
        Shape triangle2 = new Triangle("SecondTriangle", x-1, y-1);

        Shape circle1 = new Circle("FirstCircle", x);
        Shape circle2 = new Circle("SecondCircle", x-1);

        Shape square1 = new Square("FirstSquare", x);
        Shape square2 = new Square("SecondSquare", x-1);

        Shape rect1 = new Rectangle("FirstRectangle", x, y);
        Shape rect2 = new Rectangle("SecondRectangle", x-1, y-1);

        picture.add(triangle1);
        picture.add(triangle2);
        picture.add(circle1);
        picture.add(circle2);
        picture.add(square1);
        picture.add(square2);
        picture.add(rect1);
        picture.add(rect2);

        picture.printAll();
        picture.drawAll();
        System.out.println("Total : " + picture.totalArea());

    }
}