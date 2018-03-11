#ifndef GTUSET_H
#define GTUSET_H

#include "GTUSetBase.h"
#include "GTUIterator.h"
#include <memory>

using namespace std;

namespace SORMAN{
template<class T>
	class GTUSet:public GTUSetBase<T>{//Derived from GTUSetBase<T>
		public:
			GTUSet(int newSize = 0);
			GTUSet(const GTUSet &set);
			/*All functions below overriding from GTUSetBase end their tasks are same as base class and explained in GTUSetBase.h
			All functions implementations are in GTUSet.cpp*/
			virtual bool empty() const;
			virtual int max_size()const;
			virtual void erase(const T &val);
			virtual void clear();
			virtual const GTUIterator<T> find(const T &val) const;
			virtual int count(const T &val) const;
			virtual const GTUIterator<T> begin() const noexcept;
			virtual const GTUIterator<T> end() const noexcept;
			virtual int size()const;
			virtual void insert(const T &val) throw(invalid_argument);
			const GTUSet<T> &operator=(const GTUSet& rightSide);
		protected:
			virtual void sort();		
	};
}
#endif