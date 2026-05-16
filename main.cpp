#include <iostream>
#include "AVL.hpp"
#include "AVLNode.hpp"
#include "AVLDictionary.hpp"

int main(){

    //=========================== AVL TESTS ===========================
    AVL* avlsrch = new AVL;

    //Initilization
    avlsrch->insert(5,6.93);
    avlsrch->insert(3,22.7);
    avlsrch->insert(4,99.3);
    avlsrch->insert(10,46.9);
    avlsrch->insert(11,34.7);
    avlsrch->insert(2,9.09);
    avlsrch->insert(7,37.32);
    avlsrch->insert(12,42.44);
    avlsrch->insert(1,1.2);
    avlsrch->insert(6,6.57);

    //Test for Insert & Search
    std::cout << "***Test for Insert & Search***" << std::endl;
    std::cout << "Should output 46.9: " << avlsrch->search(10).value() << std::endl;
    std::cout << "Should output 99.3: " << avlsrch->search(4).value() << std::endl;
    std::cout << "Should output 0 (key 99 not found): " << avlsrch->search(99).has_value() << std::endl;
    avlsrch->insert(2,10.3); //duplicate key, should be ignored
    std::cout << "Should output 9.09 (duplicate insert ignored): " << avlsrch->search(2).value() << std::endl;

    //Test for contains
    std::cout << "***Test for contains***" << std::endl;
    std::cout << "Should output 1: " << avlsrch->contains(7) << std::endl;
    std::cout << "Should output 0: " << avlsrch->contains(42) << std::endl;

    //Tests for all three traversals
    std::cout << "***Test for in_order traversal*** (should be sorted by key)" << std::endl;
    avlsrch->inorder_traversal();
    std::cout << "***Test for pre_order traversal***" << std::endl;
    avlsrch->preorder_traversal();
    std::cout << "***Test for post_order traversal***" << std::endl;
    avlsrch->postorder_traversal();

    //Test for size/height
    std::cout << "***Test for Size***" << std::endl;
    std::cout << "Should output 10: " << avlsrch->size() << std::endl;
    std::cout << "***Test for Height***" << std::endl;
    std::cout << "Should output 4 (tree stays balanced): " << avlsrch->height() << std::endl;

    //Test for remove
    std::cout << "***Test for remove***" << std::endl;
    avlsrch->remove(7);
    std::cout << "Should output 0 (key 7 removed): " << avlsrch->contains(7) << std::endl;
    std::cout << "Should output 9: " << avlsrch->size() << std::endl;
    avlsrch->remove(1);
    avlsrch->remove(2);
    std::cout << "Should output 7: " << avlsrch->size() << std::endl;
    std::cout << "In order after removals: " << std::endl;
    avlsrch->inorder_traversal();

    //Test that the tree stays balanced under many ordered inserts
    std::cout << "***Test for balancing (1000 ascending inserts)***" << std::endl;
    AVL* big = new AVL;
    for(int i = 1; i <= 1000; i++){
        big->insert(i, i * 1.5);
    }
    std::cout << "Should output 1000: " << big->size() << std::endl;
    std::cout << "Should output 10 (NOT 1000, tree is balanced): " << big->height() << std::endl;
    delete big;

    //Test for Copy Constructor and assignment operator
    std::cout << "***Test for Copy Constructor***" << std::endl;
    AVL avlsrch2 = *avlsrch;
    std::cout << "Copied tree printed out (should match original): " << std::endl;
    avlsrch2.inorder_traversal();
    avlsrch2.remove(5);
    std::cout << "Should output 0 (copy modified): " << avlsrch2.contains(5) << std::endl;
    std::cout << "Should output 1 (original untouched): " << avlsrch->contains(5) << std::endl;

    std::cout << "***Test for assignment operator***" << std::endl;
    AVL avlsrch3;
    avlsrch3 = *avlsrch;
    std::cout << "Should output 1: " << avlsrch3.contains(5) << std::endl;
    std::cout << "Should output 7: " << avlsrch3.size() << std::endl;

    //Test for is_empty and clear
    std::cout << "***Test for is_empty and clear***" << std::endl;
    std::cout << "Should output 0: " << avlsrch->is_empty() << std::endl;
    avlsrch->clear();
    std::cout << "Should output 1: " << avlsrch->is_empty() << std::endl;

    delete avlsrch;


    //======================= AVLDICTIONARY TESTS =======================
    std::cout << std::endl;
    AVLDictionary* diction = new AVLDictionary;

    diction->insert(8,22.31);
    diction->insert(52,48.52);
    diction->insert(42,61.62);
    diction->insert(31,57.99);  //Initilization
    diction->insert(12,23.67);
    diction->insert(11,0.12);
    diction->insert(10,1.6);
    diction->insert(67,33.2);

    //Test for insert (duplicate keys rejected)
    std::cout << "***Test for insert***" << std::endl;
    std::cout << "Should output 1 (new key): " << diction->insert(99,5.5) << std::endl;
    std::cout << "Should output 0 (duplicate key): " << diction->insert(8,1.0) << std::endl;
    diction->remove(99); //clean up so later counts stay tidy

    //Test for get
    std::cout << "***Test for get***" << std::endl;
    std::cout << "Should output 23.67: " << diction->get(12) << std::endl;
    std::cout << "Should output -1 (key not found): " << diction->get(1) << std::endl;

    //Test for remove
    std::cout << "***Test for remove***" << std::endl;
    std::cout << "Should output 1: " << diction->remove(31) << std::endl;
    std::cout << "Should output 0: " << diction->remove(1) << std::endl;

    //Test for get_range
    std::cout << "***Test for get_range***" << std::endl;
    std::cout << "Range from 8 to 42:" << std::endl;
    std::vector<Pair<int,double>> testt = diction->get_range(8,42);
    for(int i = 0; i < (int)testt.size(); i++){
        std::cout << "(" << testt[i].first << "," << testt[i].second << ")" << std::endl;
    }

    //Test for keys, values, and entries
    std::cout << "***Test for keys, values, and entries***" << std::endl;
    std::cout << "Here are the keys: " << std::endl;
    std::vector<int> k = diction->keys();
    for(int i = 0; i < diction->size(); i++){
        std::cout << k[i] << ",";
    }
    std::cout << std::endl;

    std::cout << "Here are the values: " << std::endl;
    std::vector<double> v = diction->values();
    for(int i = 0; i < diction->size(); i++){
        std::cout << v[i] << ",";
    }
    std::cout << std::endl;

    std::cout << "Here are the entries: " << std::endl;
    std::vector<Pair<int,double>> e = diction->entries();
    for(int i = 0; i < diction->size(); i++){
        std::cout << "(" << e[i].first << "," << e[i].second << ")" << std::endl;
    }

    //Test for size, is_empty, and clear
    std::cout << "***Test for size, is_empty, and clear***" << std::endl;
    std::cout << "Here is size: " << diction->size() << std::endl;
    std::cout << "Is it empty? (should output 0): " << diction->is_empty() << std::endl;
    std::cout << "Clearing..." << std::endl;
    diction->clear();
    std::cout << "Here is new size (should output 0): " << diction->size() << std::endl;
    std::cout << "Is it empty? (should output 1): " << diction->is_empty() << std::endl;

    delete diction;

    std::cout << std::endl << "All tests finished." << std::endl;
}
