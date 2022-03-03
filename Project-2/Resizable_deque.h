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

        int m_front {};            // head pointer
		int m_back {};             // tail pointer
        int m_head_index {};       // head index used to compute head pointer

		std::size_t m_size {};     // size of deque
		std::size_t m_cap {};      // capacity of deque
        std::size_t m_initCap {};  // initial capacity of deque

        Type* deque;               // deque pointer


		// Any private member functions
        void double_capacity();   // doubles deque capacity
        void half_capacity();     // halves deque capacity



        
	// Friends

    // std::cout operator overload
	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );

    // absolute value function
    template<typename T>
    friend T abs(T a); 
};
 

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////



// Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n /* = 16*/ ):
m_cap((n >= 16)? n : 16),
m_initCap(m_cap),
deque(new Type[m_cap]),
m_size(0),
m_front(0),
m_back(0),
m_head_index(m_front)
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
	// free allocated memory
    if(deque) delete [] deque;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {
	// return current size of deque  
	return static_cast<int>(this->m_size);
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	// return current capacity of deque
	return static_cast<int>(this->m_cap);
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
	// return true if size equals zero
	return (this->m_size == 0);
}

template <typename  Type>
Type Resizable_deque<Type>::front() const {
	// check if deque is not empty and ensure m_front ( aka deque head)
    // is non-negative value then return the front of the deque
    // else throw and underflow
    if(!this->empty() && m_front >= 0)
    	return deque[m_front];
    else 
        throw underflow();
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {
	// check if deque is not empty and ensure m_back  ( aka deque tail)
    // is non-negative value then return the back  of the deque
    // else throw and underflow
    if(!this->empty() && m_back >= 0)
	   return deque[m_back];
    else{
        throw underflow();

    }
}

template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
	// Swap the member variables
    std::swap(this->m_size, deque.m_size);
    std::swap(this->m_front, deque.m_front);
    std::swap(this->m_cap, deque.m_cap);
    std::swap(this->m_head_index, deque.m_head_index);

    std::swap(this->deque, deque.deque);

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
	// check if array is full, if so double capacity 
    if(this->m_size == this->m_cap)
        /*array needs to be doubled*/
        this->double_capacity();

    // if size is equal to zero reset head index counter to 0
    // if not decrement the head index counter
    if(m_size == 0)
        m_head_index = 0;
    else 
        m_head_index--;

    // calculate the head pointer location by taking the head index counter mod the capacity
    // head index counter will be negative thus the mod of a negative number is as follows
    // -n % k = k - n % k ; where n is head index counter and k is capacity
    this->m_front = (this->m_size == 0)? 0 : this->m_cap - (abs(this->m_head_index) % this->m_cap) ;

    // add element to the deque
    this->deque[this->m_front] = obj;
    
    // augment the size by 1
    this->m_size++;
}

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
	// check if array is full, is so double capacity
    if(this->m_size == this->m_cap)
        /*array needs to be doubled*/
        this->double_capacity();
    
    // increment tail pointer, if size is 0 ensure the tail pointer is 0,
    // else mod the location of the back pointer by the capacity
    this->m_back++;
    this->m_back = (this->m_size == 0)? 0 : this->m_back % this->m_cap;

    // add element to the deque
    this->deque[this->m_back] = obj;

    // augment the size by 1
    this->m_size++;

}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
	// check if deque is empty if so throw underflow
    if(this->empty()) throw underflow{};

    // increase head index to keep track of where 
    // the new head to be calculated will be
    this->m_head_index++;

    // pop of element from deque head by incrementing the
    // head pointer, if head pointer equal to capacity -1 
    // wrap back around to 0
    if(m_front == m_cap - 1)
        m_front = 0;
    else 
        m_front++;

    // decrease the size of the deque
    this->m_size--;

    // check if deque capacity needs to be halved
    if(this->m_size <= this->m_cap/4 && this->m_cap/2 >= this->m_initCap)
      /*half the deque capacity*/
      this->half_capacity();
    

}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
	// check if deque is empty if so throw underflow
    if(this->empty()) throw underflow{};

    
    // pop of element from deque tail by decrementing the
    // tail pointer, if tail pointer equal to 0 wrap back         
    // around to capacity -1 
    if(m_back == 0)
        m_back = m_cap - 1;
    else
        m_back--;

    // decrease the size of the deque
    this->m_size--;

    // check if the deque needs to be halved
    if(this->m_size <= this->m_cap/4 && this->m_cap/2 >= this->m_initCap)
      /*half the deque capacity*/
      this->half_capacity();

}

template <typename Type>
void Resizable_deque<Type>::clear() {
	// reset all deque members to 0
    this->m_size = 0;
    this->m_back = 0;
    this->m_front = 0;
    this->m_head_index = 0;

    // resize deque to intial capacity if it is not
    // equal to initial capacity
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

    // copy data from old array into newly allocated array
    for(std::size_t i{0}; i < this->m_size; i++){
        new_array[i] = deque[(this->m_front)%this->m_cap];
        this->m_front++;
    }

    // deallocate old deque
    Type* deletion_ptr = this->deque;
    delete [] deletion_ptr;
    deletion_ptr = nullptr;

    // set the deque pointing to the newly allocated array
    this->deque = new_array;

    // double the capacity
    this->m_cap *= 2;

    // set tail pointer to size - 1
    this->m_back = this->m_size - 1;

    // set head pointer and head index to 0
    this->m_front = 0; this->m_head_index = 0;
     
}

template<typename Type>
void Resizable_deque<Type>::half_capacity(){
    // allocate new array
    Type* new_array = new Type[this->m_cap/2];

    // copy data from old array into newly allocated array
    for(std::size_t i{0}; i < this->m_size; i++){
        new_array[i] = deque[(this->m_front)%this->m_cap];
        this->m_front++;
    }

    // dealloacate old deque
    Type* deletion_ptr = this->deque;
    delete [] deletion_ptr;
    deletion_ptr = nullptr;

    // set the deque pointing to the newly allocated array
    this->deque = new_array;

    // half the capacity
    this->m_cap /= 2;

    // set tail pointer to size -1
    this->m_back = this->m_size - 1;

    // set head pointer to 0 and head index to 0
    this->m_front = 0; this->m_head_index = 0;

}

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// friend that computes the magnitude of a given value
template <typename T>
T abs (T a) {return (a < 0)? a*-1: a;} 

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &list ) {

    for(auto i = 0; (list.m_front+i)%list.m_cap != list.m_back; ++i){
        
        out << list.deque[(list.m_front + i) % list.m_cap] << " ";
    
    }

	return out;
}

#endif
