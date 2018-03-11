#include<iostream>
#include "GTUMap.h"

using namespace std;

namespace SORMAN{
	template<class K,class V>
	GTUMap<K,V>::GTUMap(int newSize)//Calls GTUSet constructor
		:GTUSet<pair<K,V>>::GTUSet(newSize)
	{

	}

	template<class K,class V>
	GTUMap<K,V>::GTUMap(const GTUMap &set)//Calls GTUSet copy constructor
		:GTUSet<pair<K,V>>::GTUSet(set)
	{
		
	}

	template<class K,class V>
	const GTUMap<K,V> &GTUMap<K,V>::operator=(const GTUMap<K,V>& rightSide){//Calls GTUSet assignment operator

		GTUSet<pair<K,V>>::operator=(rightSide);

	}

	template<class K,class V>
	V& GTUMap<K,V>::operator[] (const K& key)const{//index operator for access element of map with unique key

		GTUIterator<pair<K,V>> itr;

		for(itr = this->begin(); itr != this->end(); ++itr)//Finds the key and returns the value which has this key
			if(itr->first == key)
				return itr->second;
	}

	template<class K,class V>
	void GTUMap<K,V>::insert(const pair<K,V> &val) throw(invalid_argument){//Insert pair to the map

		for(int i = 0;i< this->size_;++i)//if key has already in map,pair is not inserted because each key must be unique
			if(get<0>(this->sharedData.get()[i]) == val.first)
				throw(invalid_argument("This element is already in the set!!!"));//Throws exception
		

		shared_ptr<pair<K,V>> tempData = this->sharedData;//Gets backup of map
		shared_ptr <pair<K,V>> temp(new pair<K,V>[++this->size_],default_delete<pair<K,V>[]>());//Creates a shared ptr for allocating memory and assigns to map
		this->sharedData = temp;
		
	    for (int i = 0; i < this->size_ - 1; ++i)//Copies elements from the backup to the data
	        	this->sharedData.get()[i] = tempData.get()[i];  
	    
	    this->sharedData.get()[this->size_-1] = val;//Insert the element to the end of data;

	    this->sort();//Sort map's key
	}
}