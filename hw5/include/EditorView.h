#pragma once

#include "EditorModel.h"

#include <memory>

class EditorView
{

public:

    virtual ~EditorView() = default;

    explicit EditorView(std::shared_ptr<EditorModel> model)
    : m_model(model)
    {}

    virtual void draw() {} // draw the model

private:

    std::shared_ptr<EditorModel> m_model;

};