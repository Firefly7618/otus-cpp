#pragma once
 
#include <cstdlib>
#include <memory>
 
 
template <typename T, typename Allocator = std::allocator<T>>
class simple_vector
{
public:
    simple_vector() = delete;
    explicit simple_vector(size_t capacity) 
    {
        m_begin = m_allocator.allocate(capacity);

        m_capacity = capacity;
        m_size = 0;
        m_end = m_begin;
    }
 
    ~simple_vector()
    {
        m_allocator.deallocate(m_begin, m_capacity);
    }
 
    T& operator[](size_t index)
    {
        return m_begin[index];
    }
 
    T* begin() noexcept
    {
        return m_begin;
    }

    T* end() noexcept
    {
        return m_end;
    }
 
    size_t size() const noexcept
    {
        return m_size;
    }

    size_t capacity() const noexcept
    {
         return m_capacity;
    }

    void push_back(const T& value)
    {
        if (m_size == m_capacity)
        {
            T* new_block = m_allocator.allocate(m_capacity*2);

            for (size_t i = 0; i <  m_size; ++i)
            {
                std::construct_at(new_block + i, m_begin[i]);
            }

            m_allocator.deallocate(m_begin, m_capacity);

            m_begin = new_block;
            m_capacity *= 2;
        }

        std::construct_at(m_begin + m_size, value);

        ++m_size;
 
        m_end = m_begin + m_size;
    }
 
private:
    T* m_begin = nullptr;
    T* m_end = nullptr;
 
    size_t m_capacity = 0;
    size_t m_size = 0;

    Allocator m_allocator;
  
    void copy(T* source, size_t count, T* destination)
    {
        for (size_t iter = 0; iter < count; ++iter)
        {
            destination[iter] = source[iter];
        }
    }
}; 
