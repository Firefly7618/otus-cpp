#pragma once

#include "IPrimitive.h"

#include <memory>
#include <string>
#include <string_view>
#include <utility>

enum class EventType
{
    AddPrimitive,
    DeletePrimitive,
    LoadPrimitive,
    SavePrimitive
};

class Event
{
public:
    virtual ~Event() = default;
    Event() = delete;

    explicit Event(EventType eventType)
    : m_eventType(eventType)
    {}

    EventType getType() const noexcept
    {
        return m_eventType;
    }

private:
    EventType m_eventType;
};


class PrimitiveEvent : public Event
{
public:
    virtual ~PrimitiveEvent() = default;
    PrimitiveEvent() = delete;

    PrimitiveEvent(EventType eventType, std::shared_ptr<IPrimitive> primitive)
    : Event(eventType)
    , m_primitive(std::move(primitive))
    {}

     std::shared_ptr<IPrimitive> get_primitive() const noexcept
    {
        return m_primitive;
    }

private:
    std::shared_ptr<IPrimitive> m_primitive; 
};


class FileEvent : public Event
{
public:
    virtual ~FileEvent() = default;
    FileEvent() = delete;

    FileEvent(EventType eventType, std::string_view filePath)
    : Event(eventType)
    , m_filepath(filePath)
    {}

    std::string_view get_filepath() const noexcept
    {
        return m_filepath;
    }

private:
    std::string m_filepath;
};