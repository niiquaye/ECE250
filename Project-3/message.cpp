#include <iostream>
#include "Search_tree.h"
int maxHeight(int n);
int minHeight(int n);
int main() {
    Search_tree<int> tree;

    std::cout << std::endl;

    //correct number of iterations is done first
    bool correctIterations = true;
    for(int y = 0; y < 5; y++) {
        tree.insert(y);
    }
    int n = 0;
    for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
        n++;
    }
    if(n != 5) {
        correctIterations = false;
    }

    for(int y = 0; y < 3; y++) {
        tree.erase(y);
        n--;
    }
    if(n != 2) {
        correctIterations = false;
    }

    for(int y = 3; y < 5; y++) {
        tree.insert(y);
    }

    if(n != 2) {
        correctIterations = false;
    }
    if(!correctIterations) {
        std::cout << "counting items wrong" << std::endl;
    }
    
    else{
        for(int x = 0; x < 5000; x++) {
        std::cout << x + 1 << std::endl;
        std::cout << std::endl;
        int n = 0;
        int r1 =  (std::rand() - RAND_MAX / 2) % 200;
        int r2 = std::rand() % 30;
        for(int y = 0; y < r2; y++) {
            tree.insert(r1);
            r1 =  (std::rand() - RAND_MAX / 2) % 200;
        }
        n = 0;
        std::cout << tree << std::endl;
        int prev = -201;
        bool iteratorTest = true;
        for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
            
            if(*itr <= prev) {
                std::cout << "forward iterator fail" << std::endl;
                iteratorTest = false;
                break;
            }
            prev = *itr;
            n++;
        }
        if(!iteratorTest) {
            break;
        }

        prev = 201;
        iteratorTest = true;
        for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
            if(*itr >= prev) {
                std::cout << "backward iterator fail" << std::endl;
                iteratorTest = false;
                break;
            }
            prev = *itr;
            
        }

        if(!iteratorTest) {
            break;
        }
        if(tree.height() > maxHeight(n)){

            std::cout << "avl max height fail" << std::endl;;
            break;
        }
        if(tree.height() < minHeight(n)){
            std::cout << n << std::endl;
            std::cout << "avl min heigh fail" << std::endl;
            break;
        }
        

        for(int z = 0; z < 10000; z++){
            tree.erase(r1);
            r1 = (std::rand() - RAND_MAX / 2) % 200;
        }
        n = 0;
        prev = -201;
        iteratorTest = true;
        for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
            if(*itr <= prev) {
                std::cout << "forward iterator fail" << std::endl;
                iteratorTest = false;
                break;
            }
            prev = *itr;
            n++;
        }
        if(!iteratorTest) {
            break;
        }
        prev = 201;
        iteratorTest = true;
        for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
            if(*itr >= prev) {
                std::cout << "backward iterator fail" << std::endl;
                iteratorTest = false;
                break;
            }
            prev = *itr;
            
        }
        if(!iteratorTest) {
            break;
        }
        if(tree.height() > maxHeight(n)){
            std::cout  << "AVL max heigh fail" << std::endl;
            break;
        }
        if(tree.height() < minHeight(n)){
            std::cout << "AVL min height fail" << std::endl;
            break;
        }

    }

    }
    
    std::cout << "done" << std::endl;

    return 0;
}

int maxHeight(int n) {
    return std::floor(1.44*log2(n+2)-.328) - 1;
}
int minHeight(int n) {
    
    return std::ceil(std::log2(n+1)) - 1;
}