#pragma once

#include "IPrimitive.h"
#include "IObserver.h"
#include "IObservable.h"

#include <vector>
#include <list>
#include <memory>
#include <algorithm>
#include <iostream>

class EditorModel : public IObservable
{
public:

    ~EditorModel() = default;

    // store the primitive
    void add_primitive(std::shared_ptr<IPrimitive> primitive)
    {
        std::cout << "add a primitive" << std::endl;

        m_primitives.push_back(primitive);
        notify();
    }

    //remove the primitive from the storage
    void delete_primitive(std::shared_ptr<IPrimitive> primitive)
    {
        auto it = std::find(m_primitives.begin(), m_primitives.end(), primitive);
        if (it != m_primitives.end())
        {
            std::cout << "delete a primitive" << std::endl;

            m_primitives.erase(it);
            notify();
        }
    }

    auto get_primitives() const noexcept
    {
        return m_primitives;
    }

    void clear()
    {
        m_primitives.clear();
        notify();
    }

private:

    std::vector<std::shared_ptr<IPrimitive>> m_primitives;
    std::list<std::weak_ptr<IObserver>> m_subscribers;

    // notify about the change in a model
    void notify()
    {
        for (auto subscribersIter = m_subscribers.begin(); subscribersIter != m_subscribers.end();)
        {
            auto ptr = subscribersIter->lock();
            if (ptr)
            {
                ptr->update();
                subscribersIter++;
            }
            else
            {
                m_subscribers.erase(subscribersIter);
            }
        }
    }
};