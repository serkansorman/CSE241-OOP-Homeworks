#ifndef GTUITERATOR_H
#define GTUITERATOR_H

#include <memory>
using namespace std;
namespace SORMAN{
	template<class T>
	class GTUIterator{
		public:
			GTUIterator(T *val = '\0');
			GTUIterator(const GTUIterator &gtuItr);//Copy constructor
			GTUIterator<T> &operator++(); //Operator overloading for increment
			GTUIterator<T> &operator--(); //Operator overloading for decrement
			GTUIterator<T> &operator=(const GTUIterator& rightSide); //Operator overloading for assignment
			bool operator==(const GTUIterator& rightSide)const; //Operator overloading for equal to
		    bool operator!=(const GTUIterator& rightSide)const; //Operator overloading for inequality
		    T& operator*()const; //Operator overloading for dereference
		    T* operator->()const;//Operator overloading for member access
		private:
			T *p;	//Iterator pointer
	};
}
#endif