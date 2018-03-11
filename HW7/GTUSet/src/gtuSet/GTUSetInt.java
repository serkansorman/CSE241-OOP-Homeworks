package gtuSet;

import java.security.InvalidParameterException;
/**
 * Interface class
 * 
 * @author Serkan Sorman
 * @param <T> Type of Set
 * 
 */
public interface GTUSetInt<T>{

    /**
     * Test whether container is empty
     * @return size equals to 0 or not
     */
    boolean empty();

    /**
     * Return maximum size
     * @return maximum size
     */
    int max_size();

    /**
     * Erase element from set
     * @param val is element that will be erased
     */
    void erase(Object val);

    /**
     * Clear all content
     */
    void clear();

    /**
     * Get iterator to element
     * @param val is element that will be searched in set
     * @return GTUIterator of searched element
     */
    GTUSet.GTUIterator find(Object val);

   /** Count elements with a specific value
     * @param val is element that will be count in set
     * @return counter is number's of element
     */
    int count(Object val);

    /**
     * Return iterator to beginning
     * @return GTUIterator of begin
     */
    GTUSet.GTUIterator begin();

    /**
     * Return iterator to end
     * @return GTUIterator of end
     */
    GTUSet.GTUIterator end();//

    /**
     * Return container size
     * @return setSize
     */
    int size();//Return container size

    /**
     * Insert element to the set
     * @param val is element that will be inserted to the set
     * @throws InvalidParameterException if the element is already in the set
     */
    void insert(T val)throws InvalidParameterException ;

    /**
     *Sorts all element in set
     */
    void sort();

    /**
     * Finds intersection of two sets.
     * @param other is set that will be compared to the another set
     * @return intersection of two set
     */
    GTUSetInt<T> intersection(GTUSetInt<T> other);//Intersections of two set


}
		

