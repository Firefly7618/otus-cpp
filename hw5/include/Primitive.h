#pragma once

#include "PrimitiveParameters.h"

class Primitive
{
public:
    virtual ~Primitive() = default;

    Primitive() = delete;

    Primitive(PrimitiveParameters&& params)
    : m_params(params)
    {}

private:

    PrimitiveParameters m_params;

};