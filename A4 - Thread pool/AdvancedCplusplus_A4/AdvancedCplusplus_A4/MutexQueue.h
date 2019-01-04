#ifndef MUTEX_QUEUE_H
#define MUTEX_QUEUE_H

#include <queue>
#include <mutex>

template <class T>
class MutexQueue
{
private:
	std::queue<T> _queue;
	std::mutex _mutex;

public:
	MutexQueue()
	{
	}

	bool empty()
	{
		std::unique_lock<std::mutex> lock(_mutex);
		return _queue.empty();
	}

	void enqueue(T& t)
	{
		std::unique_lock<std::mutex> lock(_mutex);
		_queue.push(t);
	}

	T dequeue()
	{
		std::unique_lock<std::mutex> lock(_mutex);
		if (_queue.empty())
		{
			return NULL;
		}
		T temp = std::move(_queue.front());
		_queue.pop();
		return temp;
	}
};
#endif
