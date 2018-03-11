#include<iostream>
#include "GTUSetBase.h"

using namespace std;

namespace SORMAN{
	template<class T>
	GTUSetBase<T>::GTUSetBase(int newSize)//Assigns new size
		:size_(newSize)
	{

	}

	template<class T>
	GTUSetBase<T>::GTUSetBase(const GTUSetBase<T> & container){//Copy constructor

		this->size_ = container.size_;//Copy size to new set

		for(int i=0; i<size_; ++i)//Copy content to new set
			this->sharedData.get()[i] = container.sharedData.get()[i];
	}


	template<class T>
	const GTUSetBase<T> &GTUSetBase<T>::operator=(const GTUSetBase<T>& rightSide){

		if(this == &rightSide)//if assigned same object each other return one of these
			return *this;
		else{

			this->size_ = rightSide.size_;//Copy size to set

			shared_ptr<T> tempData(new T[size_],default_delete<T[]>());//Memory allocation for data
			sharedData = tempData;


			for(int i=0; i<size_; ++i)//Copy content to set
				this->sharedData.get()[i] = rightSide.sharedData.get()[i];

			return *this;
		}
	}
}
