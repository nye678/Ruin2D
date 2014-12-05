#ifndef __RUIN2D_SCOPESTACK_H_
#define __RUIN2D_SCOPESTACK_H_

#include "LinearAllocator.h"

namespace Ruin2D
{
	/* Scope Stack class */
	/* A scope stack is a scoped linear memory allocator which automatically
	   frees memory when destructed. Object destructors will even be called
	   automatically by the ScopeStack. */
	class ScopeStack
	{
		// All allocations are made on 16 byte boundries.
		static const size_t Alignment = 16;

		// Object headers are allocated along with objects. Headers form a
		// linked list whose order reflects the order that object destructors
		// are called in.
		struct ObjectHeader
		{
			// Pointer to the next object header.
			ObjectHeader* chain;

			// Function pointer to a function that will destroy the object.
			void(*destroyObject)(void *ptr);
			
			// The number of allocated objects. Will equal 1 for single objects.
			// Arrays of objects will share a single header.
			size_t count;

			// The size of the object in bytes.
			size_t size;
		};

		// Returns a pointer to the object (or first object) from a header.
		static void* ObjectPointerFromHeader(ObjectHeader* header);

		// Returns a pointer to the header of an allocated object.
		// Don't use on PODs!!
		static ObjectHeader* HeaderFromObjectPointer(void* pointer);

		// Calls the destructor for type T objects.
		template <typename T> static void DestructorCall(void *ptr);

		// Calls the destructor for every object in the array.
		template <typename T> static void ArrayDestructorCall(void *ptr);

	private:
		LinearAllocator& _allocator;
		void* _rewindPoint;
		ObjectHeader* _headerChain;

	public:
		// Allocates a raw chunk of memory.
		void* Alloc(size_t size);

		// Constructs a new object.
		template <typename T> T* NewObject();

		// Constructs a new object with the given parameters.
		template <typename T, typename... Args> T* NewObject(Args... args);

		// Constructs a new object array.
		template <typename T> T* NewObjectArray(size_t count);

		// Constructs a new POD object. Destructors will not be
		// called for POD objects.
		template <typename T> T* NewPOD();
		
	private:
		ObjectHeader* AllocWithHeader(size_t size);
		ObjectHeader* AllocWithHeader(size_t size, size_t count);

	public:
		ScopeStack(LinearAllocator &allocator);
		~ScopeStack();
	};

	template <typename T>
	T* ScopeStack::NewObject()
	{
		ObjectHeader* header = AllocWithHeader(sizeof(T));
		T* result = new (ObjectPointerFromHeader(header)) T;

		header->destroyObject = &ScopeStack::DestructorCall<T>;
		header->chain = _headerChain;
		_headerChain = header;

		return result;
	}

	template <typename T, typename... Args>
	T* ScopeStack::NewObject(Args... args)
	{
		ObjectHeader* header = AllocWithHeader(sizeof(T));
		T* result = new (ObjectPointerFromHeader(header)) T(args...);

		header->destroyObject = &ScopeStack::DestructorCall<T>;
		header->chain = _headerChain;
		_headerChain = header;

		return result;
	}

	template <typename T>
	T* ScopeStack::NewObjectArray(size_t count)
	{
		size_t b = sizeof(T[5]);
		size_t c = count * sizeof(T);

		ObjectHeader* header = AllocWithHeader(sizeof(T), count);
		T* result = new (ObjectPointerFromHeader(header)) T[count];

		header->destroyObject = &ScopeStack::ArrayDestructorCall<T>;
		header->chain = _headerChain;
		_headerChain = header;

		return result;
	}

	template <typename T>
	T* ScopeStack::NewPOD()
	{
		void* podPtr = Alloc(sizeof(T));
		return new (podPtr) T;
	}

	template <typename T>
	void ScopeStack::DestructorCall(void *ptr)
	{
		static_cast<T*>(ptr)->~T();
	}

	template <typename T>
	void ScopeStack::ArrayDestructorCall(void *ptr)
	{
		auto header = HeaderFromObjectPointer(ptr);
		auto arrayPtr = static_cast<T*>(ptr);
		
		for (size_t i = 0; i < header->count; ++i)
		{
			arrayPtr[i].~T();
		}
	}
}

#endif