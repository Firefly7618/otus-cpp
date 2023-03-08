#pragma once

#include "PrimitiveParameters.h"
#include "Primitive.h"

#include <map>

class EditorModel
{

public:

    virtual ~EditorModel() = default;

    // construct primitive from params and store it
    virtual void addPrimitive(PrimitiveParameters&&) {}

    // find the primitive by params and remove from hte storage
    virtual void deletePrimitive(PrimitiveParameters&&) {}

private:

    std::map<PrimitiveParameters, Primitive> m_primitives;
};