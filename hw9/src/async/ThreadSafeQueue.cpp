#include "async/ThreadSafeQueue.h"

#include <mutex>
#include <optional>

namespace async::helpers
{

template <class T>
void  ThreadSafeQueue<T>::push(T value)
{
	std::lock_guard<std::mutex> lg(m_mutex);

    if (m_stopped)
    {
        return;
    }

	m_queue.push(value);
	m_queue_notification.notify_one();
}

template <class T>
std::optional<T> ThreadSafeQueue<T>::pop()
{
    std::unique_lock<std::mutex> ul(m_mutex);
	m_queue_notification.wait(ul, [this]()
    {
		return (m_stopped or (not m_queue.empty()));
	});

    // can only happen if stopped == true
    if (m_queue.empty())
    {
        return std::nullopt;
    }

    // if stop() was called but queue is not empty -> continue exectution

    std::optional<T> value {std::move(m_queue.front())};
	m_queue.pop();

    return value;
}

template <class T>
void ThreadSafeQueue<T>::stop()
{
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        m_stopped = true;
    }
    
    m_queue_notification.notify_all();
}

} // namespace async::helpers