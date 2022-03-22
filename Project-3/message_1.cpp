#include <iostream>
#include "Search_tree.h"
int maxHeight(int n);
int minHeight(int n);
int main() {
    Search_tree<int> tree;

    // for ( int i = 1; i <= 30; ++i ) {
    //     tree.insert( i );
    // }
    

    // std::cout << std::endl;

    

    // std::cout << std::endl;

    // std::cout << "Front:   " << tree.front()   << std::endl;
    // std::cout << "Back:    " << tree.back()    << std::endl;
    // std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

    // std::cout << "--> ";

    // for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
    //     std::cout << *itr << " ";
    // }

    // std::cout << std::endl;

    // std::cout << "--> ";

    // for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
    //     std::cout << *itr << " ";
    // }

    // std::cout << std::endl;

    

    // for ( int i = 1; i <= 15; ++i ) {
    //     tree.erase( (97*i) % 30 );
    // }

    // std::cout << "--> ";
    

    // for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
    //     std::cout << *itr << " ";
    // }
    // std::cout << std::endl;
    // std::cout << "Front:   " << tree.front()   << std::endl;
    // std::cout << "Back:    " << tree.back()    << std::endl;
    // std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

    

    std::cout << std::endl;

    for(int x = 0; x < 100; x++) {
        std::cout << x << std::endl;
        int n;
        int r1 = std::rand() % 80;
        int r2 = std::rand() % 10;
        int r3 = std::rand() % 10;
        for(int y = 0; y < r2; y++) {
            tree.insert(r1);
            r1 = std::rand() % 5000;
        }
        n = 0;
        std::cout << tree << std::endl;
        for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
            
            n++;
        }
        if(tree.height() > maxHeight(n)){
            std::cout << "Hi 1" << std::endl;
            std::cout << "ERROR" << std::endl;
            break;
        }
        if(tree.height() < minHeight(n)){
            std::cout << tree.height() << " " << minHeight(n) << " " << n << std::endl;
            std::cout << "Hi 2" << std::endl;
            std::cout << "ERROR" << std::endl;
            break;
        }
        std::cout << "Front:   " << tree.front()   << std::endl;
        std::cout << "Back:    " << tree.back()    << std::endl;
        std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

        for(int z = 0; z < r3; z++){
            tree.erase(r1);
            r1 = std::rand() % 5000;
        }
        n = 0;
        for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
            n++;
        }
        if(! (tree.height() <= maxHeight(n)) ){
            std::cout << "Hi 3" << std::endl;
            std::cout << "ERROR" << std::endl;
            break;
        }
        if(! (tree.height() >= minHeight(n))){
            std::cout << "Hi 4" << std::endl;
            std::cout << "ERROR" << std::endl;
            break;
        }

        std::cout << "Front:   " << tree.front()   << std::endl;
        std::cout << "Back:    " << tree.back()    << std::endl;
        std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

    }
    std::cout << "works" << std::endl;

    return 0;
}

int maxHeight(int n) {
    return std::floor(1.44*log2(n+2)-.3277) - 1;
}
int minHeight(int n) {
    return std::ceil(std::log2(n+1)) - 1;
}