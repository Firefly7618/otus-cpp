#pragma once

#include "IPrimitive.h"

class Point : public IPrimitive
{
public:
    Point(int x, int y)
        : m_x{x}
        , m_y{y}
    {}
    
    void draw() const override
    {}

private:
    int m_x;
    int m_y;

};