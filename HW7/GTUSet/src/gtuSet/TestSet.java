package gtuSet;
import java.security.InvalidParameterException;
import javafx.util.Pair;
/**
 * This class lets you test GTUSet and GTUMap with many types
 *
 * @author Serkan Sorman
 * @version 1.0
 */
public class TestSet{
     /**
     * Prints Set elements
     * @param itr is GTUIterator for printing set
     */
    public static void testPrint(GTUSet.GTUIterator itr){

        while(itr.hasNext())
            System.out.printf(itr.next()+" ");
        System.out.println();
    }
    
    public static void main(String Arg[]){
        System.out.println("------------< IntegerSet Test >-------------------------");
        //First block tests Integer set

        GTUSet<Integer> myIntSet = new GTUSet(Integer[].class);
        GTUSet<Integer>.GTUIterator itrInt = myIntSet.new GTUIterator();
        try{
            myIntSet.insert(4);//Inserts elements to set
            myIntSet.insert(2);
            myIntSet.insert(1);
            myIntSet.insert(5);
            myIntSet.insert(3);
            myIntSet.insert(1);
        }
        catch(InvalidParameterException e){//Catch the exception
            System.out.println("Invalid Parameter:" + e.getMessage());
        }

        System.out.printf("Integer set => ");    //Prints the set
        testPrint(itrInt);
        
        System.out.println("Size of Integer set is " + myIntSet.size());
        System.out.println("Number of '8' in Integerset is " + myIntSet.count(8));//Tests count function and finds number of searched element 
        System.out.println("Number of '4' in Integerset is " + myIntSet.count(4));

        itrInt = myIntSet.find(2);  //Tests find function 
        if(itrInt.getElement().equals(2))
            System.out.println("Integer set contains " + itrInt.getElement());
        else
            System.out.println("Integer set does not contain 2");

        myIntSet.erase(2);//Erase element 
        System.out.println("2 is deleted");

        System.out.printf("Integer set => "); //Prints new set
        System.out.println(myIntSet);//Tests toString

        System.out.println("Size of Integer set is " + myIntSet.size());//Shows new size after deleting process

        itrInt = myIntSet.find(2);//Checks element after deleted
        if(itrInt.getElement().equals(2))
            System.out.println("Integer set contains " + itrInt.getElement());
        else
            System.out.println("Integer set does not contain 2");


        myIntSet.clear();//Clear all elements in set
        System.out.println("Integer set is cleaning...");
        if(myIntSet.empty())//Checks is empty after cleared
            System.out.println("Set is empty !!!");

        System.out.println("------------< StringSet Test >-------------------------");
        //Second block test string set
        

        GTUSet<String> myStrSet = new GTUSet(String[].class);             //******************************************************                                     
        GTUSet.GTUIterator itrStr = myStrSet.new GTUIterator();           //                                                     *
                                                                          //  In this block, All tests are same with first block *
        try{                                                              //                                                     *
            myStrSet.insert("Ankara");                                    //******************************************************
            myStrSet.insert("Mersin");
            myStrSet.insert("Zonguldak");
            myStrSet.insert("Rize");
            myStrSet.insert("Izmir");
            myStrSet.insert("Bolu");
            myStrSet.insert("Adana");
            myStrSet.insert("Bolu");
        }
         catch(InvalidParameterException e){//Catch the exception
            System.out.println("Invalid Parameter:" + e.getMessage());
        }

        System.out.printf("String set => ");
        testPrint(itrStr);

        System.out.println("Size of String set is " + myStrSet.size());
        System.out.println("Number of Manisa in str set is " + myStrSet.count("Manisa"));
        System.out.println("Number of Mersin in str set is " + myStrSet.count("Mersin"));

        itrStr = myStrSet.find("Rize");
        if(itrStr.getElement().equals("Rize"))
            System.out.println("String set contains " + itrStr.getElement());
        else
            System.out.println("String set does not contain Rize");

        myStrSet.erase("Rize");
        System.out.println("Rize is deleted");

        itrStr = myStrSet.find("Rize");
        System.out.printf("String set => ");
        System.out.println(myStrSet);//Tests toString
        
        System.out.println("Size of String set is " + myStrSet.size());
        if(itrStr.getElement().equals("Rize"))
            System.out.println("String set contains " + itrStr.getElement());
        else
            System.out.println("String set does not contain Rize");

        myStrSet.clear();
        System.out.println("String set is cleaning...");
        if(myStrSet.empty())
            System.out.println("Set is empty !!!");

        System.out.println("--------------< Map Test >-----------------------");
     //Third block tests Map
        
        GTUMap<String,String> myMap = new GTUMap(Pair[].class);
        GTUMap<String,String>.GTUIterator itrMap = myMap.new GTUIterator();
        
        try{
            myMap.insert(new Pair("Amasya","Elma")); //Insert pairs to the map
            myMap.insert(new Pair("Diyarbakir","Karpuz"));
            myMap.insert(new Pair("Adana","Kebap"));
            myMap.insert(new Pair("Mersin","Tantuni"));
            myMap.insert(new Pair("Mersin","Portakal"));
        }
         catch(InvalidParameterException e){//Catch the exception
            System.out.println("Invalid Parameter:" + e.getMessage());
        }
        
        System.out.printf("Map: ");
        while(itrMap.hasNext())//Prints map keys and values
            System.out.printf("%s  ",itrMap.next());
        System.out.println();

        System.out.println("myMap[Mersin] = " + myMap.at("Mersin"));//Tests accessing value with at

        System.out.println("Size of Map is " + myMap.size());//Shows size of map
        System.out.println("Number of Adana is " + myMap.count("Adana"));//Find pair occurence in map
        System.out.println("Number of Bolu is " + myMap.count("Bolu"));
        
        itrMap = myMap.find("Amasya");
       
        if(itrMap.getElement().getKey().equals("Amasya"))//Checks whether pair is in element or not
            System.out.println("Map contains " + itrMap.getElement().getKey());
        else
            System.out.println("Map does not contain Amasya");
        
        myMap.erase("Amasya");    //Delete chosen pair
        System.out.println("Amasya is deleted");

        itrMap = myMap.find("Amasya");
        System.out.printf("Map: ");

        System.out.println(myMap);//Tests toString
        
        System.out.println("Size of Map is " + myMap.size()); //Shows size after pair deleted
        if(itrMap.getElement().getKey().equals("Amasya"))
            System.out.println("Map contains " + itrMap.getElement().getKey());//Checks whether pair is in element or not
        else
            System.out.println("Map does not contain Amasya");
        
        myMap.clear();//Clear all contents of map
        System.out.println("Map is cleaning...");   
        if(myMap.empty())               //Checks is map empty
            System.out.println("Map is empty !!!");
                                                   
        System.out.println("-------------------------------------");
        //This block tests intersection of two SETS
        GTUSet<Integer> myIntSet2 = new GTUSet(Integer[].class);
        
        try{
            myIntSet.insert(9); //Inserts elements to first set
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
        catch(InvalidParameterException e){//Catch the exception
            System.out.println("Invalid Parameter:" + e.getMessage());
        }

        //Prints first and second set respectively
        System.out.printf("First Integer set => ");
        testPrint(itrInt);
        itrInt = myIntSet2.begin();
        System.out.printf("Second Integer set => ");
        testPrint(itrInt);

        GTUSet<Integer> interSec = (GTUSet) myIntSet.intersection(myIntSet2);//Finds intersection of these two set
       
        System.out.printf("Intersection Set: ");
        System.out.println(interSec);//PrIntegerintersection of two sets
        
        System.out.println("-------------------------------------");
        //This block tests intersection of two MAPS
        GTUMap<String,String> myMap2 = new GTUMap(Pair[].class);
      
        try{
            myMap.insert(new Pair("Amasya","Elma")); //Insert pairs to the map1
            myMap.insert(new Pair("Diyarbakir","Karpuz"));
            myMap.insert(new Pair("Adana","Kebap"));
            myMap.insert(new Pair("Mersin","Tantuni"));

            myMap2.insert(new Pair("Adana","Kebap"));//Insert pairs to the map2
            myMap2.insert(new Pair("Mersin","Tantuni"));
            myMap2.insert(new Pair("Malatya","Kayisi"));
            myMap2.insert(new Pair("Ordu","Findik"));
        }
        catch(InvalidParameterException e){//Catch the exception
            System.out.println("Invalid Parameter:" + e.getMessage());
        }
        
        itrMap = myMap.begin();
        System.out.printf("First map => ");                                          
        while(itrMap.hasNext())//Prints map keys and values
            System.out.printf("%s  ",itrMap.next());
        System.out.println();
        itrMap = myMap2.begin();
        System.out.printf("Second map => ");
        while(itrMap.hasNext())//Prints map keys and values
            System.out.printf("%s  ",itrMap.next());
        System.out.println();

        GTUMap<String,String> intersecMap = (GTUMap)myMap.intersection(myMap2);//Finds intersection of these two map
        
        System.out.printf("Intersection Map: ");
        System.out.println(intersecMap);//Tests toString

        System.out.println("-------------------------------------");
        }
}