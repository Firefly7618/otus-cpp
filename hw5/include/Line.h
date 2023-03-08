#pragma once

#include "IPrimitive.h"
#include "Point.h"

class Line : public IPrimitive
{
public:
    Line(const Point& p1, const Point& p2)
        : m_p1{p1}
        , m_p2{p2}
    { }
    
    void draw() const override
    {}

private:
    Point m_p1;
    Point m_p2;

};