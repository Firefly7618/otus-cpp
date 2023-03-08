#pragma once

#include "Event.h"
#include "IObserver.h"
#include "EditorModel.h"

class IController
{
public:
    virtual ~IController() = default;

    IController(std::shared_ptr<EditorModel> model)
    : m_model(model)
    {
    }

    virtual void onEvent(const Event& event) = 0;

protected:
    std::shared_ptr<EditorModel> m_model;
};