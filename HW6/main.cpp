#include<iostream>
#include<string>
#include "GTUIterator.cpp"
#include "GTUSet.cpp"
#include "GTUSetBase.cpp"
#include "GTUMap.cpp"

using namespace SORMAN;

template <class T>
shared_ptr<GTUSetBase<T> > setIntersection(const GTUSetBase<T>&, const GTUSetBase<T>&);//Returns intersection of two set

template <class T>
void testPrint(GTUSetBase<T> &, GTUIterator<T> &);//Prints the set



template <class T>
shared_ptr<GTUSetBase<T> > setIntersection(const GTUSetBase<T> &firstSet,const GTUSetBase<T> &secondSet){

	//intersec set
	GTUSet<T> set;

	for(auto firstItr = firstSet.begin(); firstItr != firstSet.end(); ++firstItr)
		for(auto secondItr = secondSet.begin(); secondItr != secondSet.end(); ++secondItr)
			if(*firstItr == *secondItr)
				set.insert(*firstItr);//Insert the common elements to the intersection set
			
	//Memory allocation as size of intersection set for share ptr to be returned
	shared_ptr<GTUSet<T>> interSec(new GTUSet<T>[set.size()],default_delete<GTUSet<T>[]>());
	for(auto it = set.begin(); it != set.end(); ++it)//Inserts all common element from set to shared ptr;
		interSec.get()->insert(*it);
	
	return interSec;
}

template <class T>
void testPrint(GTUSetBase<T> &container, GTUIterator<T> &iterator){//Prints the set with iterator

	for(iterator = container.begin(); iterator != container.end(); ++iterator)
		cout<<*iterator<<' ';
	cout<<endl;
}

using namespace std;

int main(){

	using namespace SORMAN;

	GTUSet<int> myIntSet;
	GTUIterator<int> intptr;


	cout<<"-------------------------------------"<<endl;
	//First block tests Integer set
	try{
		myIntSet.insert(4);//Inserts elements to set
		myIntSet.insert(2);
		myIntSet.insert(1);
		myIntSet.insert(5);
		myIntSet.insert(3);
		myIntSet.insert(1);
	}
	catch(invalid_argument param){//Catch the exception
		cout<<"Invalid argument:"<<param.what()<<endl;
	}

	cout<<"Integer set => ";	//Prints the set
	testPrint(myIntSet,intptr);

	cout<<"Size of Integer set is "<<myIntSet.size()<<endl;
	cout<<"Number of '8' in int set is "<<myIntSet.count(8)<<endl;//Tests count function and finds number of searched element 
	cout<<"Number of '4' in int set is "<<myIntSet.count(4)<<endl;

	intptr = myIntSet.find(2);	//Tests find function 
	if(*intptr == 2)
		cout<<"Integer set contains "<<*intptr<<endl;
	else
		cout<<"Integer set does not contain 2"<<endl;

	myIntSet.erase(2);//Erase element 
	cout<<"2 is deleted"<<endl;

	cout<<"Integer set => ";
	testPrint(myIntSet,intptr);//Prints new set
	cout<<"Size of Integer set is "<<myIntSet.size()<<endl;//Shows new size after deleting process

	intptr = myIntSet.find(2);//Checks element after deleted
	if(*intptr == 2)
		cout<<"Integer set contains "<<*intptr<<endl;
	else
		cout<<"Integer set does not contain 2"<<endl;


	myIntSet.clear();//Clear all elements in set
	cout<<"Integer set is cleaning..."<<endl;
	if(myIntSet.empty())//Checks is empty after cleared
		cout<<"Set is empty !!!"<<endl;

	cout<<"-------------------------------------"<<endl;
	//Second block test string set


	GTUSet<string> myStrSet;							//******************************************************   									 
	GTUIterator<string> Strptr;							//                						  			   *
														//  In this block, All tests are same with first block *
	try{												//										  			   *
		myStrSet.insert("Ankara");						//******************************************************
		myStrSet.insert("Mersin");
		myStrSet.insert("Zonguldak");
		myStrSet.insert("Rize");
		myStrSet.insert("Izmir");
		myStrSet.insert("Bolu");
		myStrSet.insert("Adana");
		myStrSet.insert("Bolu");
	}
	catch(invalid_argument param){
		cout<<"Invalid argument:"<<param.what()<<endl;
	}

	cout<<"String set => ";
	testPrint(myStrSet,Strptr);

	cout<<"Size of String set is "<<myStrSet.size()<<endl;
	cout<<"Number of Manisa in str set is "<<myStrSet.count("Manisa")<<endl;
	cout<<"Number of Mersin in str set is "<<myStrSet.count("Mersin")<<endl;

	Strptr = myStrSet.find("Rize");
	if(*Strptr == "Rize")
		cout<<"String set contains "<<*Strptr<<endl;
	else
		cout<<"String set does not contain Rize"<<endl;

	myStrSet.erase("Rize");
	cout<<"Rize is deleted"<<endl;

	Strptr = myStrSet.find("Rize");
	cout<<"String set => ";
	testPrint(myStrSet,Strptr);
	cout<<"Size of String set is "<<myStrSet.size()<<endl;
	if(*Strptr == "Rize")
		cout<<"String set contains "<<*Strptr<<endl;
	else
		cout<<"String set does not contain Rize"<<endl;

	myStrSet.clear();
	cout<<"String set is cleaning..."<<endl;
	if(myStrSet.empty())
		cout<<"Set is empty !!!"<<endl;

	cout<<"-------------------------------------"<<endl;
 //Third block tests Map

	GTUMap<string,string> myMap;
 	GTUIterator<pair<string,string> > mapPtr;

	try{
		myMap.insert(make_pair("Amasya","Elma")); //Insert pairs to the map
		myMap.insert(make_pair("Diyarbakir","Karpuz"));
		myMap.insert(make_pair("Adana","Kebap"));
		myMap.insert(make_pair("Mersin","Tantuni"));
		myMap.insert(make_pair("Mersin","Portakal"));
	}
	catch(invalid_argument param){
		cout<<"Invalid argument:"<<param.what()<<endl;//Catch exception
	}

	cout<<"myMap[Mersin] = "<<myMap["Mersin"]<<endl;
	myMap["Mersin"] = "Portakal";
	cout<<"Map: ";
	for(mapPtr = myMap.begin(); mapPtr != myMap.end(); ++mapPtr)//Prints map keys and values
		cout<<mapPtr->first<<"=>"<<mapPtr->second<<"  ";
	cout<<endl;

	cout<<"Size of Map is "<<myMap.size()<<endl;//Shows size of map
	cout<<"Number of [Adana] = Kebap in map is "<<myMap.count(make_pair("Adana","Kebap"))<<endl;//Find pair occurence in map
	cout<<"Number of [Istanbul] = Tantuni in map is "<<myMap.count(make_pair("Istanbul","Tantuni"))<<endl;

	mapPtr = myMap.find(make_pair("Amasya","Elma"));
	if(mapPtr->first == "Amasya")
		cout<<"Map contains "<<mapPtr->first<<endl;			//Checks whether pair is in element or not
	else
		cout<<"Map does not contain Amasya"<<endl;

	myMap.erase(make_pair("Amasya","Elma"));	//Delete chosen pair
	cout<<"Amasya is deleted"<<endl;

	mapPtr = myMap.find(make_pair("Amasya","Elma"));
	cout<<"Map: ";
	
	for(mapPtr = myMap.begin(); mapPtr != myMap.end(); ++mapPtr)//Prints map keys and values
		cout<<mapPtr->first<<"=>"<<mapPtr->second<<"  ";
	cout<<endl;

	cout<<"Size of Map is "<<myMap.size()<<endl; //Shows size after pair deleted
	if(mapPtr->first == "Amasya")							//Checks whether pair is in element or not
		cout<<"Map contains "<<mapPtr->first<<endl;
	else
		cout<<"Map does not contain Amasya"<<endl;

	myMap.clear();//Clear all contents of map
	cout<<"Map is cleaning..."<<endl;	
	if(myMap.empty())				//Checks is map empty
		cout<<"Map is empty !!!"<<endl;

	cout<<"-------------------------------------"<<endl;
	//This block tests intersection of two SETS
	GTUSet<int> myIntSet2;

	try{
		myIntSet.insert(9);	//Inserts elements to first set
		myIntSet.insert(2);
		myIntSet.insert(3);
		myIntSet.insert(5);
		myIntSet.insert(7);


		myIntSet2.insert(9); //Inserts elements to second set
		myIntSet2.insert(2);
		myIntSet2.insert(5);
		myIntSet2.insert(4);
		myIntSet2.insert(12);
		myIntSet2.insert(8);
	}
	catch(invalid_argument param){
		cout<<"Invalid argument:"<<param.what()<<endl;
	}

	//Prints first and second set respectively
	cout<<"First Integer set => ";
	testPrint(myIntSet,intptr);
	cout<<"Second Integer set => ";
	testPrint(myIntSet2,intptr);

	shared_ptr<GTUSetBase<int> > interSec;
	interSec = setIntersection(myIntSet,myIntSet2);//Calculate intersection of these two set

	cout<<"Intersection Set: ";
	for(auto it = interSec->begin(); it != interSec->end(); ++it)//Print intersection of two sets
		cout<<*it<<" ";
	cout<<endl;

	cout<<"-------------------------------------"<<endl;

	//This block tests intersection of two MAPS
	GTUMap<string,string> myMap2;

	try{
		myMap.insert(make_pair("Amasya","Elma")); //Insert pairs to the map1
		myMap.insert(make_pair("Diyarbakir","Karpuz"));
		myMap.insert(make_pair("Adana","Kebap"));
		myMap.insert(make_pair("Mersin","Tantuni"));

		myMap2.insert(make_pair("Adana","Kebap"));//Insert pairs to the map2
		myMap2.insert(make_pair("Mersin","Tantuni"));
		myMap2.insert(make_pair("Malatya","Kayisi"));
		myMap2.insert(make_pair("Ordu","Findik"));
	}
	catch(invalid_argument param){
		cout<<"Invalid argument:"<<param.what()<<endl;//Catch exceptions
	}

	cout<<"First map => ";											
	for(mapPtr = myMap.begin(); mapPtr != myMap.end(); ++mapPtr)	//Prints map1 key and values
		cout<<mapPtr->first<<"=>"<<mapPtr->second<<"  ";
	cout<<endl;

	cout<<"Second map => ";
	for(mapPtr = myMap2.begin(); mapPtr != myMap2.end(); ++mapPtr)     //Prints map2 key and values
		cout<<mapPtr->first<<"=>"<<mapPtr->second<<"  ";
	cout<<endl;

	auto interSecMap = setIntersection(myMap,myMap2);	//Calculate intersection of these two map

	cout<<"Intersection Map: ";
	for(auto it = interSecMap->begin(); it != interSecMap->end(); ++it)//Print intersection map
		cout<<(*it).first<<"=>"<<(*it).second<<"  ";
	cout<<endl;

	cout<<"-------------------------------------"<<endl;
	

	return 0;
}
