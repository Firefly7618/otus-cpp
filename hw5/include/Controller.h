#pragma once

#include "EditorModel.h"
#include "EditorView.h"
#include "PrimitiveParameters.h"

#include <memory>
#include <string_view>

class Controller
{
public:
    virtual ~Controller() = default;

    Controller(std::shared_ptr<EditorModel> model, std::unique_ptr<EditorView>&& view)
    : m_model(model)
    , m_view(std::move(view))
    { } 

    virtual void addPrimitive(PrimitiveParameters&&) {}
    virtual void deletePrimitive(PrimitiveParameters&&) {}

    // Load the model from filePath
    virtual void LoadModel(const std::string_view) {}
    
    // Save the model to file
    virtual void SaveMode(const std::string_view) {}

private:

    std::shared_ptr<EditorModel> m_model;
    std::unique_ptr<EditorView> m_view;
};