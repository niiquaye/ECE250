/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"
#include <cstddef>
#include <iostream>

template <typename Type>
class Resizable_deque {
	public:
		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();

	private:
		// Your member variables

        std::size_t m_front {};
		std::size_t m_back {};
		std::size_t m_size {};
	    //std::size_t m_initCap{};
		std::size_t m_cap {};

		// Any private member functions
		//   - helper functions for resizing your array?
        Type* deque;

        
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};
/***
 * elements [i] = old[(i+front)% old_capacity]
 *
 **/ 

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n = 16 ):
m_cap((n >= 16)? n : 16),
deque(new Type[m_cap]),
m_size(0),
m_front(0),
m_back(0)
{

}

// Copy Constructor (OPTIONAL)
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque )
// Your initalization list
{
	// Enter your implementation here
}

// Move Constructor (OPTIONAL)
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque )
// Your initalization list
{
	// Enter your implementation here
}

// Destructor
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
	// Enter your implementation here
    if(deque) delete [] deque;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {
	// Enter your implementation here
	return static_cast<int>(this->m_size);
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	// Enter your implementation here
	return static_cast<int>(this->m_cap);
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
	// Enter your implementation here
	return (this->m_size == 0);
}

template <typename  Type>
Type Resizable_deque<Type>::front() const {
	// Enter your implementation here
    if(!this->empty() && m_front >= 0)
    	return deque[m_front];
    else 
        throw underflow();
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {
	// Enter your implementation here
    if(!this->empty() && m_back >= 0)
	   return deque[m_back];
    else 
        throw underflow();
}

template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
	// Swap the member variables
	//     std::swap( variable, deque.variable );

	// Enter your implementation here
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {
	// This is done for you...
	Resizable_deque<Type> copy( rhs );
	swap( copy );

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {
	// This is done for you...
	swap( rhs );

	return *this;
}

template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
	// Enter your implementation here
    if(this->m_size == this->m_cap){
        // array needs to be doubled
   }

    this->m_size++;
    deque[this->m_size] = obj;
    m_front = m_size;
}

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
	// Enter your implementation here
    if(this->m_size == this->m_cap){
        // array needs to be doubled
    }

    this->m_size++;
    deque[this->m_size] = obj;
    m_back = m_size;


}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
	// Enter your implementation here
}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
	// Enter your implementation here
}

template <typename Type>
void Resizable_deque<Type>::clear() {
	// Enter your implementation here
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functions (helper functions) here


/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &list ) {
	out << "not yet implemented";

	return out;
}

#endif
