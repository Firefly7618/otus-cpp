#pragma once

#include <optional>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace async::helpers
{

/*
* Allows thread safe access to queue elements
* If queue is empty pop will block the exeuting thread
* All pushes after stop() are ignored
*/
template<class T>
class ThreadSafeQueue
{
public:

    ThreadSafeQueue() = default;

    ThreadSafeQueue(ThreadSafeQueue&&) = delete;
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue& operator=(ThreadSafeQueue&&) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    // TODO: think about copying
    void push(T value)
    {
        std::lock_guard<std::mutex> lg(m_mutex);

        if (m_stopped)
        {
            return;
        }

	    m_queue.push(std::move(value));
	    m_queue_notification.notify_one();
    }

    std::optional<T> pop()
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

    void stop()
    {
        {
            std::lock_guard<std::mutex> lock{m_mutex};
            m_stopped = true;
        }
    
        m_queue_notification.notify_all();
    }

private:

    // Indicates that there will be no more items pushed to the queue
    bool m_stopped = false;

    std::queue<T> m_queue;

    std::mutex m_mutex;
    std::condition_variable m_queue_notification;
};

} // namespace async::helpers
