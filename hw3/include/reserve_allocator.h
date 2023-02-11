#pragma once

#include <cstring>
#include <iostream>
#include <cassert>
#include <utility>


template <typename T>
struct reserve_allocator
{
	using value_type = T;

	using pointer = T *;
	using const_pointer = const T *;
	using reference = T &;
	using const_reference = const T &;

	reserve_allocator()
    : m_pointer{nullptr}
	, m_size{10}
	, m_used{0}

    {
		std::cout << __PRETTY_FUNCTION__ << std::endl;

		assert(m_size > 0);
		assert(sizeof(T) > 0);
		
        m_pointer = reinterpret_cast<T*>(std::malloc(m_size * sizeof(T)));
		if (!m_pointer)
		{
			throw std::bad_alloc();
		}
    }

    ~reserve_allocator()
    {
		std::cout << __PRETTY_FUNCTION__ << std::endl;

		if (m_pointer)
		{
        	std::free(m_pointer);
			m_pointer = nullptr;
		}
    }

	template <typename U>
	reserve_allocator(const reserve_allocator<U>& other)
		: m_pointer{nullptr}
		, m_size{other.getSize()}
		, m_used{0}
	{
		construct();
	}

	reserve_allocator(const reserve_allocator& other)
		: m_pointer{nullptr}
		, m_size{other.getSize()}
		, m_used{0}
	{
		construct();
	}

	template <typename U>
	reserve_allocator& operator=(const reserve_allocator<U>& other)
	{
		m_size = other.getSize();
		m_used = 0;

		construct();
	}

	reserve_allocator& operator=(const reserve_allocator& other)
	{
		m_size = other.getSize();
		m_used = 0;

		construct();
	}

	reserve_allocator(reserve_allocator&& other) noexcept
	{
		std::cout << __PRETTY_FUNCTION__ <<  std::endl;

		takeOwnership(std::move(other));
	}

	reserve_allocator& operator=(reserve_allocator&& other) noexcept
	{
		std::cout << __PRETTY_FUNCTION__  << std::endl;

		takeOwnership(std::move(other));
	}

	T *allocate(std::size_t n)
    {
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;

		if (n + m_used > m_size)
		{
			throw std::bad_alloc();
		}
	
		auto* out_p = m_pointer + m_used;
		m_used += n;

		return out_p;
	}

	void deallocate(T*, std::size_t n) noexcept
     {
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args)
    {
		std::cout << __PRETTY_FUNCTION__ << std::endl;

		new (p) U(std::forward<Args>(args)...);
	}

	template <typename U>
	void destroy(U *p)
    {
		std::cout << __PRETTY_FUNCTION__ << std::endl;

		p->~U();
	}

	T* getPtr() const noexcept
	{
		return m_pointer;
	}

	std::size_t getSize() const noexcept
	{
		return m_size;
	}

	std::size_t getUsed() const noexcept
	{
		return m_used;
	}

	void clear() noexcept
	{
		m_pointer = nullptr;
		m_size = 0;
		m_used= 0;
	}

private:

	void takeOwnership(reserve_allocator&& other) noexcept
	{
		m_pointer = other.getPtr();
		m_size = other.getSize();
		m_used = other.getUsed();

		other.clear();
	}

	void construct()
	{
		assert(m_size > 0);
		assert(sizeof(T) > 0);

		std::cout << __PRETTY_FUNCTION__ << std::endl;

		m_pointer = reinterpret_cast<T*>(std::malloc(m_size * sizeof(T)));
		if (!m_pointer)
		{
			throw std::bad_alloc();
		}
	}

	T* m_pointer;

    std::size_t m_size;
	std::size_t m_used;
};
