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
#include <bits/c++config.h>
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

        int m_front {};
		int m_back {};
		std::size_t m_size {};
	    //std::size_t m_initCap{};
		std::size_t m_cap {};
        std::size_t m_initCap {};
		// Any private member functions
		//   - helper functions for resizing your array?
        Type* deque;
        void double_capacity();
        void half_capacity();

        
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
m_initCap(m_cap),
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
    if(!this->empty() && m_front > 0)
    	return deque[m_front];
    else 
        throw underflow();
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {
	// Enter your implementation here
    if(!this->empty() && m_back > 0)
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
    if(this->m_size == this->m_cap)
        /*array needs to be doubled*/
        this->double_capacity();


    this->m_front--;
    this->m_front = (this->m_size == 0)? 0 : this->m_cap - (this->m_front % this->m_cap);
    this->deque[this->m_front] = obj;
    

    this->m_size++;

}

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
	// Enter your implementation here
    if(this->m_size == this->m_cap)
        /*array needs to be doubled*/
        this->double_capacity();
    
    this->m_back++;
    this->m_back = (this->m_size == 0)? 0 : this->m_back % this->m_cap;
    this->deque[this->m_back] = obj;


    this->m_size++;


}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
	// Enter your implementation here
    
    if(this->empty()) throw underflow{};

    
    this->m_front = (this->m_front == this->m_cap-1)? 0 : this->m_front++;
    this->m_size--;

    if(this->m_size <= this->m_cap/4 && this->m_cap/2 >= this->m_initCap)
      /*half the array*/
      this->half_capacity();

}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
	// Enter your implementation here
    if(this->empty()) throw underflow{};

    
    this->m_back = (this->m_back == 0 )? this->m_cap - 1  : this->m_back--;
    this->m_size--;

    if(this->m_size <= this->m_cap/4 && this->m_cap/2 >= this->m_initCap)
      /*half the array*/
      this->half_capacity();

}

template <typename Type>
void Resizable_deque<Type>::clear() {
	// Enter your implementation here
    this->m_size = 0;
    this->m_back = 0;
    this->m_front = 0;

    if(this->m_initCap != this->m_cap){
      Type* deletion_ptr = this->deque;
      delete [] deletion_ptr;
      deletion_ptr = nullptr;
      this->deque = new Type[this->m_initCap];
      this->m_cap = this->m_initCap;
    }
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functions (helper functions) here

template<typename Type>
void Resizable_deque<Type>::double_capacity(){
     
    // allocate new array
    Type* new_array = new Type[this->m_cap*2];
    // elements [i] = old[(i+front)% old_capacity]

    for(std::size_t i{0}; i < this->m_size; i++){
        new_array[i] = deque[(i+this->m_front)%this->m_cap]; 
    }

    Type* deletion_ptr = this->deque;
    delete [] deletion_ptr;
    deletion_ptr = nullptr;

    this->deque = new_array;
    this->m_cap *= 2;

    this->m_back = this->m_size
     
}

template<typename Type>
void Resizable_deque<Type>::half_capacity(){

}

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
