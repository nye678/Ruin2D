#ifndef __RUIN2D_SINGLETON_H_
#define __RUIN2D_SINGLETON_H_

#include <memory>
#include "Assert.h"

namespace Ruin2D
{
	/* Singleton
	   Templated Singleton pattern implementation. To use create an
	   instance with the class you want to singletonize. If you want
	   you can make that class' constructor private and add the
	   Singleton class as a friend. */
	template<typename T>
	class Singleton
	{
		static std::shared_ptr<T> Instance;

	public:
		/* Create 
		   Creates the singleton instance. */
		inline static std::shared_ptr<T> Create()
		{
			if (Instance == nullptr)
			{
				Instance = std::shared_ptr<T>(new T());
			}

			return Instance;
		}

		/* Get
		   Gets a shared pointer to the singleton object. */
		inline static std::shared_ptr<T> Get()
		{
			Assert(Instance != nullptr, "Tried to get a singleton instance that has not been created yet.");
			return Instance;
		}

	private:
		Singleton() {};
		Singleton(const Singleton &) = delete;
		Singleton &operator= (const Singleton &) = delete;
	};

	template<typename T>
	std::shared_ptr<T> Singleton<T>::Instance = nullptr;
}

#endif