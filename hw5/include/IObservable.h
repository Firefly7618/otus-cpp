#pragma once

#include "IObserver.h"

#include <memory>

class IObservable
{
public:
    virtual ~IObservable() = default;

    virtual void add_observer(const std::shared_ptr<IObserver>& obs) = 0;

private:

    virtual void notify() = 0;
};