#pragma once

#include <mutex>
#include <thread>
#include <queue>

namespace gp1
{
template <typename T>
class ProducerConsumerQueue
{
public:
	ProducerConsumerQueue() {};
	~ProducerConsumerQueue() {};

	void push(T element)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_cv.wait(lock, [this]() { return true; });

		m_queue.push(element);

		lock.unlock();
		m_cv.notify_all();
	}

	T pop()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_cv.wait(lock, [this]()
		{
			return !m_queue.empty();
		});

		T element = m_queue.front();
		m_queue.pop();

		lock.unlock();
		m_cv.notify_all();

		return element;
	}

private:
	std::mutex m_mutex;
	std::condition_variable m_cv;
	std::queue<T> m_queue;
};

}
