#pragma once

#include "IController.h"
#include "EditorModel.h"
#include "Event.h"


#include <memory>
#include <string_view>

class Controller final : public IController
{
public:
    ~Controller() = default;

    Controller(std::shared_ptr<EditorModel> model)
    : IController(model)
    {} 

    void onEvent(const Event& event) override
    {
        if (EventType::AddPrimitive == event.getType())
        {
            const auto& primEvent = static_cast<const PrimitiveEvent&>(event);
            m_model->add_primitive(primEvent.get_primitive());
        }
        else if (EventType::DeletePrimitive == event.getType())
        {
            const auto& primEvent = static_cast<const PrimitiveEvent&>(event);
            m_model->delete_primitive(primEvent.get_primitive());
        }
        else if (EventType::LoadPrimitive == event.getType())
        {
            const auto& fileEvent = static_cast<const FileEvent&>(event);
            LoadModel(fileEvent.get_filepath());
        }
        else if (EventType::SavePrimitive == event.getType())
        {
            const auto& fileEvent = static_cast<const FileEvent&>(event);
            SaveModel(fileEvent.get_filepath());
        }
    }

private:

    // Load the model from filePath
    void LoadModel(const std::string_view /*filePath */)
    {
        m_model->clear();

        /**
         * for primitives in a file m_model->add_primitive();
        */
    }
    
    // Save the model to file
    void SaveModel(const std::string_view /*filePath */)
    {
        /**
         * m_model->get_primitives();
         * for primitive in primitives serialize and save to file
        */
    }

};