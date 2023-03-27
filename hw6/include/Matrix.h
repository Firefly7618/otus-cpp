#pragma once

#include <map>
#include <iostream>

template <typename T, T DefaultValue>
class Matrix
{
public:

    class Row
    {
    public:

        Row()
        : m_default{DefaultValue}
        {}

        const T& operator[](std::size_t column) const
        {
            auto it = m_values.find(column);
            if (it != m_values.end())
            {
                return it->second;
            }
            else
            {
                
                return m_default;
            }
        }

        std::size_t size()const 
        {
            return m_values.size();
        }

        auto begin() const
        {
            return m_values.begin();
        }

        auto end() const
        {
            return m_values.end();
        }

        void set(std::size_t column, T value)
        {
            if (m_default == value)
            {
                return;
            }
            m_values[column] = value;
        }

    private:
        std::map<std::size_t, T> m_values;
        const T m_default;
    };

    Matrix()
    : m_default{}
    {}

    const Row& operator[](std::size_t column) const
    {
        auto it = m_matrix.find(column);
        if (it != m_matrix.end())
        {
            return it->second;
        }
        else
        {
            return m_default;
        }
    }

    std::size_t size() const
    {
        std::size_t matrix_size = 0;
        for (auto const& [key, rows]: m_matrix)
        {
            matrix_size += rows.size();
        }

        return matrix_size;
    }

    auto begin() const
    {
        return m_matrix.begin();
    }

    auto end() const
    {
        return m_matrix.end();
    }

    void set(std::size_t raw, std::size_t column, T value)
    {
        if (value == DefaultValue)
        {
            return;
        }

        m_matrix[raw].set(column, value);
    }

private:
    // map row index to Rows
    std::map<std::size_t, Row> m_matrix;
    Row m_default;
};