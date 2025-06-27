#include<iostream>
#include<cassert>
#include<cmath>
#include<SFML/Graphics.hpp>

class Shape {
protected:
    int id;
    std::pair<int, int> coordinates;
public:
    Shape(int id, int X, int Y) : id(id), coordinates(X, Y) {}
    int getShape() const {
        return id;
    }
    std::pair<int, int> getCoordinates() const {
        return coordinates;
    }
    void setCoordinates(int X, int Y) {
        coordinates.first = X;
        coordinates.second = Y;
    }
    virtual void draw(sf::RenderWindow& window) const = 0;
};

class Rectangle : public Shape {
private:
    int length;
    int width;
public:
    Rectangle(int l = 0, int w = 0, int X = 0, int Y = 0) : Shape(0, X, Y), length(l), width(w) {
        assert(l >= 0 && w >= 0);
    }
    int getLength() const {
        return length;
    }
    int getWidth() const {
        return width;
    }
    int getPerimeter() const {
        return 2 * (length + width);
    }
    int getArea() const {
        return length * width;
    }
    int isSquare() const {
        return length == width;
    }
    void draw(sf::RenderWindow& window) const override {
        sf::RectangleShape rect(sf::Vector2f(length, width));
        rect.setPosition(coordinates.first, coordinates.second);
        rect.setFillColor(sf::Color::Green);
        window.draw(rect);
    }
};

class Square : public Rectangle {
public:
    Square(int side = 0, int X = 0, int Y = 0) : Rectangle(side, side, X, Y) {
        assert(side >= 0);
        id = 1;
    }
    int getLength() const {
        return Rectangle::getLength();
    }
    int getPerimeter() const {
        return 4 * getLength();
    }
    int getArea() const {
        return getLength() * getLength();
    }
    void draw(sf::RenderWindow& window) const override {
        sf::RectangleShape square(sf::Vector2f(getLength(), getLength()));
        square.setPosition(coordinates.first, coordinates.second);
        square.setFillColor(sf::Color::Blue);
        window.draw(square);
    }  
};

class Circle : public Shape {
private:
    int radius;
public:
    Circle(int r = 0, int X = 0, int Y = 0) : Shape(2, X, Y), radius(r) {
        assert(r >= 0);
    }
    int getRadius() const {
        return radius;
    }
    double getPerimeter() const {
        return 2 * M_PI * radius;
    }
    double getArea() const {
        return M_PI * radius * radius;
    }
    void draw(sf::RenderWindow& window) const override {
        sf::CircleShape circle(radius);
        circle.setPosition(coordinates.first - radius, coordinates.second - radius);
        circle.setFillColor(sf::Color::Red);
        window.draw(circle);
    }
};

class Ellipse : public Shape {
private:
    int semi_major;
    int semi_minor;
public:
    Ellipse(int a = 0, int b = 0, int X = 0, int Y = 0) : Shape(3, X, Y), semi_major(a), semi_minor(b) {
        assert(a >= 0 && b >= 0);
    }
    int getXLength() const {
        return semi_major;
    }
    int getYLength() const {
        return semi_minor;
    }
    double getArea() const {
        return M_PI * semi_major * semi_minor;
    }
    void draw(sf::RenderWindow& window) const override {
        sf::CircleShape ellipse(semi_major);
        ellipse.setScale(1.0f, static_cast<float>(semi_minor) / semi_major);
        ellipse.setPosition(coordinates.first - semi_major, coordinates.second - semi_minor);
        ellipse.setFillColor(sf::Color::Yellow);
        window.draw(ellipse);
    }
};

class Canvas {
private:
    std::vector<Shape*> shapes;
public:
    void addShape(Shape* shape) {
        shapes.push_back(shape);
    }
    void displayShapes() const {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Shapes Canvas");
        while(window.isOpen()) {
            sf::Event event;
            while(window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            window.clear(sf::Color::White);
            for(const auto& shape : shapes) {
                assert(shape != nullptr);
                shape->draw(window);
            }
            window.display();
        }
    }
};

// Testcase
int main() {
    Canvas canvas;

    Rectangle* rect = new Rectangle(120, 60, 50, 50);
    canvas.addShape(rect);

    Square* square = new Square(80, 250, 100);
    canvas.addShape(square);

    Circle* circle = new Circle(70, 400, 300);
    canvas.addShape(circle);

    Ellipse* ellipse = new Ellipse(90, 40, 600, 400);
    canvas.addShape(ellipse);

    canvas.displayShapes();

    return 0;
}