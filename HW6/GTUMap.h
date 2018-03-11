#ifndef GTUMAP_H
#define GTUMAP_H

#include "GTUSet.h"
#include <memory>

using namespace std;
namespace SORMAN{
	template<class K,class V>
	class GTUMap:public GTUSet<pair<K,V>>{//GTU map derived from GTUSet<pair<K,V>>
		public:
			GTUMap(int newSize = 0);
			GTUMap(const GTUMap &set);
			V& operator[] (const K& key) const;//index perator overloading for map	
			const GTUMap<K,V> &operator=(const GTUMap& rightSide);//Assignment operator
			void insert(const pair<K,V> &val) throw(invalid_argument);//Overloads the insertt function for map
	};
}
#endif