
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <utility>
#include <future>

template <class T>
class ThreadPool
{ /* todo */
private:
	class WorkItem
	{

	};

	bool _running;
	std::vector<std::thread> _threads;
	std::queue<T> _queue;
	std::mutex _mutex;
public:
	ThreadPool(int n)
	{
		_threads = std::vector<std::thread>(n);
		_running = true;
		for (size_t i = 0; i < n; i++)
		{
			_threads[i] = std::thread();
		}
	}

	template <class T, class ... Args>
	enqueue(T f, Args ... args)
	{
		std::function<T(f(args...))()> func = std::bind(std::forward<T>(f), std::forward<Args>(args)...);
		auto task = std::make_shared<std::packaged_task<T(f(args...))()>>(func);
	}
};

#endif
