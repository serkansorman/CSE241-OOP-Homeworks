#include<iostream>
#include "GTUSet.h"

using namespace std;

namespace SORMAN{
	template<class T>
	GTUSet<T>::GTUSet(int newSize)//Calls GTUSetBase constructor
		:GTUSetBase<T>::GTUSetBase(newSize)
	{

	}

	template<class T>
	GTUSet<T>::GTUSet(const GTUSet &set)//Calls GTUSetBase copy constructor
		:GTUSetBase<T>::GTUSetBase(set)
	{

	}

	template<class T>
	const GTUSet<T> &GTUSet<T>::operator=(const GTUSet<T>& rightSide){//Calls GTUSetBase assignment operator

		GTUSetBase<T>::operator=(rightSide);

	}

	template<class T>
	const GTUIterator<T> GTUSet<T>::begin() const noexcept{//Return iterator to beginning
		
		T *tempData = this->sharedData.get(); //Create a temp pointer for callıng GTUIterator with normal pointer argument

		return  GTUIterator<T>(tempData);//Indıcate beginnning
	}
			

	template<class T>
	const GTUIterator<T> GTUSet<T>::end() const noexcept{//Return iterator to end

		T *tempData = this->sharedData.get();//Create a temp pointer for callıng GTUIterator with normal pointer argument

		return  GTUIterator<T>(tempData + this->size_ );//Shit to the pointer to the end
	}


	template<class T>
	int GTUSet<T>::size()const{//Return container size
		return this->size_;
	}

	template<class T>
	void GTUSet<T>::insert(const T &val) throw(invalid_argument) {//Insert element to the set

		for(int i = 0;i< this->size_;++i)//if element has already in set throws exception
			if(this->sharedData.get()[i] == val)
				throw(invalid_argument("This element is already in the set!!!"));
		
		shared_ptr<T> tempData = this->sharedData;//Gets backup of data
		shared_ptr <T> temp(new T[++this->size_],default_delete<T[]>());//Creates a shared ptr for allocating memory and assigns to data
		this->sharedData = temp;
		
	    for (int i = 0; i < this->size_ - 1; ++i)//Copies elements from the backup to the data
	        	this->sharedData.get()[i] = tempData.get()[i];  
	    
	    this->sharedData.get()[this->size_-1] = val;//Insert the element to the end of data;

	    sort();//Sorts all elements in data	
	    
	}

	template<class T>
	int GTUSet<T>::count(const T &val) const{//Count elements with a specific value

		int counter = 0;

		for(int i = 0; i<this->size_; ++i)//Calculate number of specific element
			if(this->sharedData.get()[i] == val)
				++counter;

		return counter;

	}

	template<class T>
	const GTUIterator<T> GTUSet<T>::find(const T &val)const{//Gets iterator to element

		GTUIterator<T> p;

		for(p = begin();p != end();++p)//Searchs the element in data
			if(*p == val)
				return p;//if element find return iterator

		return end();
	}


	template<class T>
	void GTUSet<T>::clear(){//Clear all contents of set
		
		this->sharedData = nullptr;

		this->size_ = 0;//Set size 0
	}

	template<class T>
	void GTUSet<T>::erase(const T &val){
		
		GTUIterator<T> itr;
		itr = find(val);

		if(*itr == val){//if element to be deleted is in set

			shared_ptr<T> temp(new T[this->size_],default_delete<T[]>());//Allocates memory for copies

			for(int i = 0,j = 0; i< this->size_; ++i){//Copies all elements except for element to be deleted
				if(this->sharedData.get()[i] != val){
					temp.get()[j] = this->sharedData.get()[i];
					++j;
				}
			}
						
			this->sharedData = temp;//recopies elements to the data
			
			--this->size_;//decrements  size by one
		}

	}

	template<class T>
	int GTUSet<T>::max_size()const{//Return max size
		return 1000000;
	}

	template<class T>
	bool GTUSet<T>::empty() const{//Checks whether set is empty or not

		return this->size_ == 0;

	}


	template<class T>
	void GTUSet<T>::sort(){//Sorts the elements with bubble sort

		T temp;
		for(int i=0; i<this->size_;++i){
			for(int j=i+1;j<this->size_;++j){
				if(this->sharedData.get()[j]<this->sharedData.get()[i]){
					temp = this->sharedData.get()[i];
					this->sharedData.get()[i] = this->sharedData.get()[j];
					this->sharedData.get()[j] = temp;
				}
			}
		}
	}
}