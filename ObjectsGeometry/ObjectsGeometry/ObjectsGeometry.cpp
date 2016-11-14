#pragma once
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

class Figure {
public:
    virtual void  Draw() = 0;
    virtual float Area() = 0;
    virtual float Perimiter() = 0;
};

void Draw_Circle(double a,double x, double y, double z);
void Draw_cRectangle(double a,double x, double y, double z);
void Draw_Square(double a,double x, double y, double z);
void Draw_Triangle(double a,double x, double y, double z);

class cRectangle : public Figure {
public:
    cRectangle(float width, float height)
        : width_(width), height_(height) {}
    virtual float Width() const { return width_; }
    virtual float Height() const { return height_; }
    virtual void  Width(float value) { width_ = value; }
    virtual void  Height(float value) { height_ = value; }
    virtual float Area() { return Width() * Height(); };
    virtual float Perimiter() { return (Width() + Height()) * 2; };
    virtual void  Draw() {
		Draw_cRectangle(4, (double)(width_ / 5 + 3), 
			(double)(height_/ 5 + 2), 5.0f);
        printf("Rectangle. Width: %.3f, height: %.3f, area: %.3f, perimiter: %.3f;\n",
               Width(), Height(), Area(), Perimiter());
    }
private:
    float width_;
    float height_;
};


class Square : public cRectangle {
public:
    explicit Square(float side) : cRectangle(side, side) {}
    virtual float Width() const { return cRectangle::Width(); }
    virtual float Height() const { return cRectangle::Height(); }
    virtual void  Width(float value)  {
        cRectangle::Width(value);
        cRectangle::Height(value);
    }
    virtual void  Height(float value) {
        cRectangle::Width(value);
        cRectangle::Height(value);
    }
    virtual void  Draw() {
		Draw_Square(4, (double)((int)(cRectangle::Width()) % 3 + 1), 
			(double)((int)(cRectangle::Width()) % 3 + 1), 5.0f);
        printf("Square. Side: %.3f, area: %.3f, perimiter: %.3f;\n",
           cRectangle::Width(), Area(), Perimiter());
    }
};

class Circle : public Figure {
public:
    static const float PI;
    explicit Circle(float radius) : radius_(radius) {}
    virtual float Radius() const { return radius_; }
    virtual void  Radius(float value) { radius_ = value; }
    virtual float Area() { return PI * pow(Radius(), 2.); };
    virtual float Perimiter() { return 2 * PI * Radius(); };
    virtual void  Draw() {
		Draw_Circle(4, (double)((int)(Radius())% 5 + 3), 
			(double)((int)(Radius())%5 + 3), 5.0f);
        printf("Circle. Radius: %.3f, area: %.3f, perimiter: %.3f;\n",
               Radius(), Area(), Perimiter());
    }
private:
    float radius_;
};

class Triangle : public cRectangle {
public:
    explicit Triangle(float width, float height) : 
		cRectangle(width, height) {}
    virtual float Width() const { return cRectangle::Width(); }
    virtual float Height() const { return cRectangle::Height(); }
	virtual float Area() { return cRectangle::Area() / 2; };
    virtual void  Width(float value)  {
        cRectangle::Width(value);
    }
    virtual void  Height(float value) {
        cRectangle::Height(value);
    }
    virtual void  Draw() {
		Draw_Triangle(4, (double)((int)(cRectangle::Width()) % 5), 
			(double)((int)(cRectangle::Height())% 5), 5.0f);
        printf("Triangle. Width: %.3f, height: %.3f, area: %.3f\n",
           cRectangle::Width(), Height(), Area());
    }
};