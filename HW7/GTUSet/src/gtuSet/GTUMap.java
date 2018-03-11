package gtuSet;
import javafx.util.Pair;
import java.security.InvalidParameterException;
import java.lang.reflect.Array;  

/**
 * This class extends the GTUSet
 * 
 * @author Serkan Sorman
 * @param <K> is key of pair
 * @param <V> is value of pair
 * 
 */
public class GTUMap<K,V> extends GTUSet<Pair <K, V> >{
    /**
     * @param cls indicate the class type 
     */
    public GTUMap(Class<Pair<K,V>[]> cls){   
        super(cls);
    }
    
    /**
     * @param newSize new size of map
     * @param cls indicate the class type
     */
    public GTUMap(int newSize,Class<Pair<K,V>[]> cls){
         super(newSize,cls);
    }
    
    /** 
     * Access data with unique key
     * @param key is index of map
     * @return value of key.if key is not in map @return null
     */
    public V at(K key){
        for(int i=0; i<setSize; ++i)//Finds the key and returns the value which has this key
            if(data[i].getKey().equals(key))
                return data[i].getValue();
        return null;
    }
    /**
     * @param val is key that will be searched in map
     * @return GTUIterator of searched element of map
     */
    @Override
    public  GTUIterator find(Object val){//Get iterator to element
        for (int i = 0; i < setSize; ++i) {
            if (val.equals(data[i].getKey())) {
                return new GTUIterator(data[i]);
            }
        }
        return end();
    }
    /** 
     * @param val is key that will be erased it's pair
     */
    @Override
    public void erase(Object val){
        Pair []tempData = (Pair<K,V>[])(Array.newInstance(Pair.class,setSize));
        for (int i = 0,j = 0; i < setSize; ++i) {//Finds the key and erase pair which has this key
            if( ! val.equals(data[i].getKey()) ) {//Copies all elements except for val to data
                tempData[j] = data[i];
                ++j;  
            }
        }
        --setSize; 
        System.arraycopy(tempData, 0, data, 0, setSize);//Copies all elements to data
    } 
    /**
     * @param val is element that will be count in set
     * @return counter is number's of element
     */
    @Override
    public int count(Object val){
        int counter = 0;
        for (int i = 0; i < setSize; ++i) {
            if (val.equals(data[i].getKey())) 
                ++counter;
        }
        return counter;
    }
    /** 
     * @param val is element that will be inserted tp the set
     *  @throws InvalidParameterException if the key is already in the set
     */    
    @Override
    public void insert(Pair<K,V> val) throws InvalidParameterException{
        for(int i=0; i<setSize; ++i)//Throws exception if element has already in the set
            if(data[i].getKey().equals(val.getKey()))
                throw new InvalidParameterException("This element is already in the set!!!");
        
        
        Pair<K,V>[] tempData = data;
        
        if(setSize == capacity){//if there is not enough place left increments the capacity
           capacity += setSize;
           data = type.cast(Array.newInstance(type.getComponentType(),capacity));//New memory allocation for data
        }
        
        
        ++setSize;
        for(int i = 0; i<setSize-1; ++i)//Copies all elements to data
            data[i] = tempData[i];

        data[setSize - 1] = val;//Add elements to the tail of data
        sort();
    }
    /**
     * Finds intersection of two maps
     * @param other is set that will be compared to the another set
     * @return  intersection of two map
     */
    @Override
    public GTUSetInt<Pair<K,V>> intersection(GTUSetInt<Pair<K,V>> other){

        GTUMap<K,V> otherMap = (GTUMap) other;//Down casting to the GTUMap class
        GTUMap<K,V> intersec = new GTUMap(type);

        //Finds the elements which are both in first set and second set
        for(int i=0; i<setSize; ++i)
            for(int j=0; j<otherMap.setSize; ++j)
                if(data[i].equals(otherMap.data[j]))
                    intersec.insert(data[i]);

        return intersec;

    }
     /**
     * Sorts all element in set
     */
    @Override
    public void sort(){//Sorts all element in set
        Pair<K,V> temp;
        for(int i=0; i<setSize;++i){
            for(int j=i+1;j<setSize;++j){
                Comparable left = (Comparable)data[j].getKey();//Cast comparable to compare
                Comparable right = (Comparable)data[i].getKey();
                if(left.compareTo(right) < 0){
                    temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }
        }
    }
}
