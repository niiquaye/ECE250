/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( new typename Double_sentinel_list<Type>::Double_node {} ),
list_tail( new typename Double_sentinel_list<Type>::Double_node {} ),
list_size(0)
{
    /**
     * Set head and tail to point to each other on construction
     */ 

    std::cout << "constructor" <<std::endl;
	list_head->next_node = list_tail;
    list_head->previous_node = nullptr;

    list_tail->next_node = nullptr;
    list_tail->previous_node = list_head;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( new typename Double_sentinel_list<Type>::Double_node {} ),
list_tail( new typename Double_sentinel_list<Type>::Double_node {} ),
list_size(list.size())
{
    std::cout << "copy constructor" << std::endl;
	list_head->next_node = list_tail;
    list_head->previous_node = nullptr;

    list_tail->next_node = nullptr;
    list_tail->previous_node = list_head;

    for(auto current = list.begin(); current != list.end(); current = current->next())
        this->push_back(current->value());
        
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	// Enter your implementation here
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {

    // iterate while not null, hence iterate until list_head points to list_tail
    while(list_head->next()){

        // get reference to node to be deleted
        typename Double_sentinel_list<Type>::Double_node* deletion_node = list_head;

        // iterate to next node in linked list
        list_head = list_head->next();

        // delete node
        delete deletion_node;
        deletion_node = nullptr;
    }

    // delete last node 
    if(list_head) delete list_head;
    list_head = nullptr;
    list_tail = nullptr;

}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	// Enter your implementation here
	return (list_size == 0);
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
    if(list_head->next()){ return list_head->next()->value();}
    else{ throw underflow(); } /*else clause not really needed but oh well*/
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    if(list_tail->previous()) {return list_tail->previous()->value();}
    else{ throw underflow(); }
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
    return list_head->next(); // return actual head of list ... aka the node after the head sentinel node
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	return list_tail; // return one past the end of the list ... aka the sentinel tail node itself
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	// Enter your implementation here
	return list_tail->previous(); // return actual end of the list ... aka previous node from the end sentinel node
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	return list_head; // return head sentinel node
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {

    // iterate through list with dummy 'current' node and find element  
    for(typename Double_sentinel_list<Type>::Double_node* current {this->begin()}; current != this->end(); current = current->next()){ /* 'current' node construction invokes copy constructor \
                                                                                                                                     - TODO: implement copy constructor*/
        // conduct santity check ensuring node is not null
        if(current){
            // check if current node value is equal to obj we are trying to find
            if(current->value() == obj){
                return current; // found object
            }

            continue; // continue to next iteration - not really necessary though
        }

    }
    return this->end(); // end of list reached - therefore return end of list
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {

    int count{0};
    // iterate throught list with dummy 'current' node and count occurences of 'obj'
    for(typename Double_sentinel_list<Type>::Double_node* current {this->begin()}; current != this->end(); current = current->next()){ /* 'current' node invokes copy constructor \
                                                                                                                                     - TODO: implement copy constructor*/
        // conduct santity check ensuring node is not null
        if(current){
            // check if current node value is equal to obj we are trying to find
            if(current->value() == obj){
                count++;
            }

            continue; // continue to next iteration - not really necessary though
        }

    }

    return count;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

    std::cout<<"copy assignment operator" << std::endl;

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {

     typename Double_sentinel_list<Type>::Double_node* temp { new Double_node{obj} };

     if(this->empty()){
         temp->previous_node = list_head;
         temp->next_node = list_tail;

         list_head->next_node = temp;
         list_tail->previous_node = temp;

         list_size++;
         return;
     }

     temp->next_node = list_head->next_node;
     temp->previous_node = list_head;

     list_head->next_node->previous_node = temp;
     list_head->next_node = temp;

     list_size++;

}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {

    typename Double_sentinel_list<Type>::Double_node* temp { new Double_node{obj} };

     if(this->empty()){
         temp->previous_node = list_head;
         temp->next_node = list_tail;

         list_head->next_node = temp;
         list_tail->previous_node = temp;

         list_size++;
         return;
     }
     
     temp->next_node = list_tail;
     temp->previous_node = list_tail->previous_node;

     list_tail->previous_node->next_node = temp;
     list_tail->previous_node = temp;

     list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {

    if(this->empty()) { throw underflow(); }

    typename Double_sentinel_list<Type>::Double_node* deletion_node { list_head->next() };

    list_head->next_node = list_head->next_node->next_node;
    list_head->next_node->previous_node = list_head;

    list_size--;

    delete deletion_node;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {

    if(this->empty()) { throw underflow(); }

    typename Double_sentinel_list<Type>::Double_node* deletion_node { list_tail->previous() };

    list_tail->previous_node = list_tail->previous_node->previous_node;
    list_tail->previous_node->next_node = list_tail;

    list_size--;

    delete deletion_node;
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {

    if(this->empty()) {return 0;}

    int deletion_count{0};

    /*
     * Simply pop back or pop front the node if data is in head or tail
     *
     * */
    bool value_in_head {false};
    bool value_in_tail{false};

    while( (list_head->next_node && (value_in_head = (list_head->next_node->value() == obj)))
            || (list_tail->previous_node && (value_in_tail = (list_tail->previous_node->value() == obj))) ){
         
        if(value_in_head){
           this->pop_front();
           deletion_count++;
        }

        if(value_in_tail){
           this->pop_back();
           deletion_count++;
        }
    }

    /*
     * Delete node if it is in the middle of the list
     *
     * */
    for(typename Double_sentinel_list<Type>::Double_node* current {this->begin()}; current != this->end(); current = current->next())
    {
        if(current){
            if(current->value() == obj){

              // found node to delete node
              
              typename Double_sentinel_list<Type>::Double_node* deletion_node {current};

              current->previous_node->next_node = current->next_node;
              current->next_node->previous_node = current->previous_node;

              delete deletion_node;
              deletion_count++;

            }

        }
       
    }

    return deletion_count;

}
/*
 * Double node implementation
 *
 */ 

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( nv ), // This assigns 'node_value' the default value of Type
previous_node( pn ),
next_node( nn )
{
	// Enter your implementation here
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	// Enter your implementation here
    return node_value;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	// Enter your implementation here
    return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	// Enter your implementation here
	return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
