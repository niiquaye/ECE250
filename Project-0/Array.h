/*
    This code has been modified.  The original version was written by Douglas Harder.  "Mad props"
    to Douglas for setting this all up
                                         - MCS
*/

#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>
#include <iostream>
#include <cmath>
#include "Exception.h"
#include "ece250.h"

template <typename Type>
class Array {
	 private:
		int array_capacity;
		Type *internal_array;
		int array_size;

	public:
		Array( int = 10 );
		~Array();

		int size() const;
		int capacity() const;
		bool empty() const;
		bool full() const;
        bool append(Type const &);

		Type operator[]( int ) const;

		void clear();

        void print(std::ostream &);
};

/*
 * Constructor
 *
 * Create a new array with a capacity of at least one.
 * The default value of the argument is 10.
 *
 * The array is initially empty, and
 * there is no need to zero out the entries of the array;
 */

template <typename Type>
Array<Type>::Array( int n ):
array_capacity( std::max( n, 1 ) ),
internal_array( new Type[capacity()] ),
array_size( 0 ) {
    std::cout << "heyyyyy" << std::endl;
}


/*
 * Destructor
 *
 * Deallocate the memory assigned to 'internal_array'
 */

template <typename Type>
Array<Type>::~Array() {
    delete [] internal_array;
}

/*
 * Size
 *
 * Return the number of objects currently stored in this array.
 */

template <typename Type>
int Array<Type>::size() const {
    return array_size;
}

/*
 * Capacity
 *
 * Return the capacity of this array (the maximum number of objects
 * this array can store).
 */

template <typename Type>
int Array<Type>::capacity() const {
    return array_capacity;
}

/*
 * Empty
 *
 * Returns true if the array is empty (the size is 0), and false otherwise.
 */

template <typename Type>
bool Array<Type>::empty() const {
	return (array_size == 0) ? true : false ;
}

/*
 * Full
 *
 * Returns true if the number of objects stored in the array (the size)
 * equals the capacity.
 */

template <typename Type>
bool Array<Type>::full() const {
	return (array_size == array_capacity) ? true : false;
}

/*
 * operator[]( int n )
 *
 * If n >= 0 and n < size(), return the object stored at index n of this array.
 * If n < 0, throw an underflow exception.
 * If n >= size(), throw an overflow exception.
 */

template <typename Type>
Type Array<Type>::operator[]( int n ) const {
    if( n >= 0 && n < Array<Type>::size()){
        return internal_array[n];
    }
    else if (n < 0){
        throw underflow();
    }
    else{
        throw overflow();
    }
}

/*
 * Append
 *
 * If the array is full, do nothing and return false.
 *
 * Otherwise, append the argument to the next available location
 * in the array, increment the array size, and return true.
 */

template <typename Type>
bool Array<Type>::append( Type const &obj ) {
   // check if array is full
    if(Array<Type>::full()){
        return false;
    }
    
    // add new element into array and increment array_size
    internal_array[array_size] = std::move(obj);
    array_size++;

    return true;

}

/*
 * Clear
 *
 * Empty the array; that is, set the array size to 0.
 *
 * Note:  nothing else has to be done here.  We do not have
 * to delete the array, we do not have to set the entries in
 * the array to 0, nullptr or anything else.
 */

template <typename Type>
void Array<Type>::clear() {
    if(array_size == 0) return;
	array_size = 0;
}

/*
 * Printing the array
 *
 * This is a helper function for you.  Determine how you want the array to print out.
 * We will NOT be testing this automatically, it's just for your debugging
 */
void print(std::ostream & outStream)
{
    outStream << "Nothing yet";
}

#endif
