package gtuSet;
import java.lang.reflect.Array;
import java.security.InvalidParameterException;
import java.util.Arrays;
/**
* This class implements the GTUSetInt
*
* @param <T> Type of Set
* @version 1.0
* @author Serkan Sorman
*/
public class GTUSet<T> implements GTUSetInt<T>{
    /** Holds set's elements*/
    protected T []data;
    /** Size of Set*/
    protected int setSize;
    /**Capacity of Set*/
    protected int capacity;
    /**Holds the type which is type of set */
    protected Class<T[]> type;
    
    /** 
     * @param cls indicate the class type
     */
    public GTUSet(Class<T[]> cls){
        this(0,cls);
        
    }
    /**
     * @param newSize indicate the new size of set
     * @param cls indicate the class type
     */
    public GTUSet(int newSize,Class<T[]> cls){
       setSize = newSize;
       capacity = newSize + 10;
       data = cls.cast(Array.newInstance(cls.getComponentType(),capacity));
       type = cls;
    }
    /**
     * @return size equals to 0 or not
     */
    @Override
    public boolean empty(){ 
       return setSize == 0;
    }
    /**
     * @return maximum size
     */
    @Override
    public int max_size(){
        return 1000000;
    }	
    
    /**
     * Erase element from set
     * @param val is element that will be erased
     */
    @Override
    public void erase(Object val){
        
        T []tempData = type.cast(Array.newInstance(type.getComponentType(),setSize));//Create temp array

        for (int i = 0,j = 0; i < setSize; ++i) {//Copies all elements except for val to data
            if( ! val.equals(data[i]) ) {
                     tempData[j] = data[i];
                     ++j;  
             }
        }
        --setSize; //Decrements size by one
        System.arraycopy(tempData, 0, data, 0, setSize);//Copy all elements to data
    }
    /**
     * Clear all content and assigns to size 0
     */
    @Override
    public void clear(){
            setSize = 0;
    }
    /**
     * Get iterator to element
     * @param val is element that will be searched in set
     * @return GTUIterator of searched element
     */
    @Override
    public  GTUIterator find(Object val){//Get iterator to element
        for (int i = 0; i < setSize; ++i) {
            if (val.equals(data[i])){
                return new GTUIterator(data[i]);
            }
        }
        return end();//if element can not found return end ıterator of the set
    }
    /**
     * Count elements with a specific value
     * @param val is element that will be count in set
     * @return counter is number's of element
     */
    @Override
    public int count(Object val){
        int counter = 0;
        for (int i = 0; i < setSize; ++i) {
            if (val.equals(data[i])) 
                ++counter;
        }
        return counter;
    }
    /**
     * @return the iterator of beginning
     */
    @Override
    public  GTUIterator begin(){
        return new GTUIterator(data[0]);
    }
    /**
     * @return the iterator of end
     */
    @Override
    public  GTUIterator end(){
        return new GTUIterator(data[setSize]);
    }
    /**
     * @return set size
     */
    @Override
    public int size(){
        return setSize;
    }
    /**
     * Insert element to the set
     * @param val element that will be inserted to the set
     * @throws InvalidParameterException if the element is already in the set
     */
    @Override
    public void insert(T val)throws InvalidParameterException{

        for(int i=0; i<setSize; ++i)//Throws exception if element has already in the set
            if(data[i].equals(val))
                throw new InvalidParameterException("This element is already in the set!!!");
        
        T[] tempData = data;
        if(setSize == capacity){//if there is not enough place left increments the capacity
           capacity += setSize;
           data = type.cast(Array.newInstance(type.getComponentType(),capacity));//New memory allocation for data
        }
        ++setSize;
        for(int i = 0; i<setSize-1; ++i)//Copies all elements to data
            data[i] = tempData[i];

        data[setSize - 1] = val;//Add elements to the tail of data
        sort();//Sorts all elements
    }
    /**
     * Finds intersection of two sets.
     * @param other is set that will be compared to the another set
     * @return intersec is intersection of two set
     */
    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> other){

        GTUSet<T> otherSet = (GTUSet) other;//Down casting to the GTUSet class
        GTUSet<T> intersec = new GTUSet(type);

        //Finds the elements which are both in first set and second set
        for(int i=0; i<setSize; ++i)
           for(int j=0; j<otherSet.setSize; ++j)
                if(data[i] == otherSet.data[j])
                   intersec.insert(data[i]);//insert common elements to set
        return intersec;
    }
    /**
     * Sorts all element in set
     */
    @Override
    public void sort(){

        T temp;
        for(int i=0; i<setSize;++i){
            for(int j=i+1;j<setSize;++j){
                Comparable left = (Comparable)data[j];//Cast comparable for comparing
                Comparable right = (Comparable)data[i];
                if(left.compareTo(right) < 0){
                        temp = data[i];
                        data[i] = data[j];
                        data[j] = temp;
                }
            }
        }
    }
    /**
     * Convert all set elements to string
     * @return result is string of all data elements
     */
    @Override
    public String toString(){
        String result="";
        for (int i = 0; i < setSize; i++)
            result += data[i] + " ";
        
        return result;
    }
    /**
     * Compare two GTUSet objects
     * @param o is a GTUSet object that will be compared to another object
     * @return equal or not
     */
    @Override
    public boolean equals(Object o){
        if(o == this)//if object is same with itself @return true
            return true;
        if (!(o instanceof GTUSet))//if object is not intance of super class @return false
            return false;
       
        GTUSet set = (GTUSet) o;//Casts object fort the access member data
        if(set.setSize == setSize){//Compares each elements in data
            for(int i=0; i<setSize; ++i){
                if(data[i] != set.data[i])
                    return false;
            }
        }
        return true;
    }
    
    /**
     * Iterator of GTUSet class
     */
    public class GTUIterator{
       /** index of GTUSet data*/
        protected int index;
        /** Holds one element of data*/
        protected T element;
        
        public 	GTUIterator(){
            index = 0;
        }
        /**
         * @param newElement is sets the element
         */
        public 	GTUIterator(T newElement){
            index = 0;
            element = newElement;
        }
       /**
        * Returns true if this list iterator has more elements when traversing the list in the forward direction.
        * @return data has next or not
        */
        public boolean hasNext() {
            return index < setSize;
        }
        /**
         * Returns true if this list iterator has more elements when traversing the list in the reverse direction.
         * @return data has previous or not
         */
        public boolean hasPrevious(){
            return setSize > 1;
        };
        /**
         * Returns the previous element in the list and moves the cursor position backwards.
         * @return the previous element
         */
        public T previous(){
            return data[index--];
        };
        /**
         * Returns the next element in the list and advances the cursor position.
         * @return the next element
         */
        public T next() {
            return data[index++];
        }
        /**
         * Gets current element
         * @return the current Element
         */
        public  T getElement(){
            return element;
        }
    }
}
