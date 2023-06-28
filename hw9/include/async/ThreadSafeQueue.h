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
    void push(T value);

    std::optional<T> pop();

    void stop();

private:

    // Indicates that there will be no more items pushed to the queue
    bool m_stopped = false;

    std::queue<T> m_queue;

    std::mutex m_mutex;
    std::condition_variable m_queue_notification;
};

} // namespace async::helpers
