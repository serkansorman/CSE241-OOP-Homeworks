#include<iostream>
#include "GTUIterator.h"

using namespace std;

namespace SORMAN{

	template<class T>
	GTUIterator<T>::GTUIterator(T *val)
		:p(val)
	{
	}

	template<class T>
	GTUIterator<T>::GTUIterator(const GTUIterator &gtuItr)
		:p(gtuItr.p)
	{	
	}

	template<class T>
	GTUIterator<T> &GTUIterator<T>::operator++(){//Operator overloading for increment
		++p;
		return *this;
	}

	template<class T>
	GTUIterator<T> &GTUIterator<T>::operator--(){//Operator overloading for decrement
		--p;
		return *this;
	}

	template<class T>
	GTUIterator<T> &GTUIterator<T>::operator=(const GTUIterator& rightSide){//Operator overloading for assignmnet

		if(this == &rightSide)
			return *this;
		else{
			
			p = rightSide.p;
			return *this;
		}
	}

	template<class T>
	bool GTUIterator<T>::operator==(const GTUIterator& rightSide)const{//Operator overloading for equality
		return p == rightSide.p;
	}

	template<class T>
	bool GTUIterator<T>::operator!=(const GTUIterator& rightSide)const{//Operator overloading for inequality
		return p != rightSide.p;
	}

	template<class T>
	T &GTUIterator<T>::operator*()const{//Operator overload for dereference
		return *p;
	}

	template<class T>
	T* GTUIterator<T>::operator->()const{//Operator overload for access member
		return p;
	}
}