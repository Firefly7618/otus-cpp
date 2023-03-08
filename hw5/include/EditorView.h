#pragma once

#include "IObserver.h"
#include "EditorModel.h"
#include "IPrimitive.h"
#include "IController.h"
#include "Event.h"

#include <memory>
#include <list>
#include <iostream>

class EditorView : public IObserver
{
public:
    ~EditorView() = default;
    EditorView() = delete;

    EditorView(std::shared_ptr<EditorModel> model)
    : m_model(model)
    {
    }

    void add_controller(const std::shared_ptr<IController>& controller)
    {
        m_viewcontrollers.emplace_back(controller);
    }

    void user_added_primitive(std::shared_ptr<IPrimitive> primitive)
    {
        PrimitiveEvent event(EventType::AddPrimitive, primitive);
        send_event(event);
    }

    void user_deleted_primitive(std::shared_ptr<IPrimitive> primitive)
    {
        PrimitiveEvent event(EventType::DeletePrimitive, primitive);
        send_event(event);
    }

    void load_from_file(const std::string& filepath)
    {
        FileEvent event(EventType::LoadPrimitive, filepath);
        send_event(event);
    }

    void save_to_file(const std::string& filepath)
    {
        FileEvent event(EventType::SavePrimitive, filepath);
        send_event(event);
    }

    // redraw the picture after primitives are updated
    void update() override
    {
        std::cout << "View: draw" << std::endl;

        for (auto const& primitive: m_model->get_primitives())
        {
            primitive->draw();
        }
    }

private:
    std::shared_ptr<EditorModel> m_model;
    std::list<std::weak_ptr<IController>> m_viewcontrollers;

    void send_event(const Event& event)
    {
        for (auto contIter = m_viewcontrollers.begin(); contIter != m_viewcontrollers.end();)
        {
            auto ptr = contIter->lock();
            if (ptr)
            {
                ptr->onEvent(event);
                contIter++;
            }
            else
            {
                m_viewcontrollers.erase(contIter);
            }
        }
    }
};