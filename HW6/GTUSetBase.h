#ifndef GTUSETBASE_H
#define GTUSETBASE_H

#include "GTUIterator.h"

using namespace std;

namespace SORMAN{
	template<class T>
	class GTUSetBase{//Abstract GTUSetBase class
		public:
			GTUSetBase(int newSize = 0);
			GTUSetBase(const GTUSetBase & container);//copy constructor
			virtual bool empty() const = 0;//Test whether container is empty
			virtual int max_size()const = 0;//Return maximum size
			virtual void erase(const T &val) = 0;//Erase element
			virtual void clear() = 0;//Clear all content
			virtual const GTUIterator<T> find(const T &val) const = 0;//Get iterator to element
			virtual int count(const T &val) const = 0;//Count elements with a specific value
			virtual const GTUIterator<T> begin() const noexcept = 0;//Return iterator to beginning
			virtual const GTUIterator<T> end() const noexcept = 0;//Return iterator to end
			virtual int size()const = 0;//Return container size
			virtual void insert(const T &val) throw(invalid_argument) = 0;//Insert element,throws exception std::invalid_argument if the element is already in the set
			const GTUSetBase<T> &operator=(const GTUSetBase& rightSide);//Overload assignment operator
		protected:
			virtual void sort() = 0;//Sorts all element in set
			shared_ptr<T> sharedData;//Keeps set element using dynamic memory techniques
			int size_;//Set size
	};
}
#endif