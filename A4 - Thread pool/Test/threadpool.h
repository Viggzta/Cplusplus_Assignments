
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <utility>
#include <future>
#include <cstdint>

class ThreadPool
{ /* todo */
private:
	class WorkItem
	{
	private:
		ThreadPool* _ownerThreadpool;
	public:
		WorkItem(ThreadPool* ownerPool)
		{
			_ownerThreadpool = ownerPool;
		}

		void operator()()
		{
			std::function<void()> func;
			while (_ownerThreadpool->_running)
			{
				// Behövs det mutex?
				std::unique_lock<std::mutex> lock(_ownerThreadpool->_mutex);
				if (_ownerThreadpool->_queue.empty())
				{
					_ownerThreadpool->_conditionLock.wait(lock);
				}
				func = _ownerThreadpool->_queue.front();
				_ownerThreadpool->_queue.pop();
				func();
			}
		}
	};

	bool _running;
	std::vector<std::thread> _threads;
	std::queue<std::function<void()>> _queue;
	std::mutex _mutex;
	std::condition_variable _conditionLock;

public:
	ThreadPool(unsigned int n)
	{
		_threads = std::vector<std::thread>(n);
		_running = true;
		for (size_t i = 0; i < n; i++)
		{
			_threads[i] = std::thread(WorkItem(this));
		}
	}

	ThreadPool(const ThreadPool &) = delete;
	ThreadPool(ThreadPool &&) = delete;

	ThreadPool & operator=(const ThreadPool &) = delete;
	ThreadPool & operator=(ThreadPool &&) = delete;

	template <class F, class ... Args>
	auto enqueue(F f, Args ... args)
	{
		std::function<F(args...)> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
		auto task = std::make_shared<std::packaged_task<F()>>(func);
		// Add task to queue
	}
};

#endif
