#include "../include/Tree.h"
#include <iostream>

template <class T>

void FiveRuleTestTree() {
    std::cout << "\r\n-------------------------- Tree Checks -------------------------" << std::endl;
    std::cout << "Tree Type - " << typeid(T).name() << std::endl;
    std::cout << "----------------------------------------------------------------\r\n" << std::endl;
    T * test1      = new T(5);
    T * test2      = new T(3);
    test1->addChild(*test2);
    delete(test2);

    std::cout << "------Copy Test------" << std::endl;
    T test3 = *test1; //Tree Copy Constructor Tester, It shall choose the utilize the copy constructor since it is not initialized!
    delete(test1); 
    if(test3.getChildren()[0]->getRootLabel() == 3){
            std::cout << "Passed | Copy Constructor Test" << std::endl;
        }else
            std::cout << "Failed | Copy Constructor Test" << std::endl;
    std::cout << "\r\n------Assignment Test------" << std::endl;
    T      testAssignment(5);
    testAssignment = (test3); //Assignment Constructor
    if(testAssignment.getChildren()[0]->getRootLabel()  == 3)
        std::cout << "Passed | Assignment Constructor Test " << std::endl;
    else
        std::cout << "Failed | Assignment Constructor Test " << std::endl;
    std::cout << "\r\n------Move Tests------" << std::endl;

    T testMove1(6);
    T testMove2(5);
    test2 = new T(5);
    testMove1.addChild(*test2);
    delete(test2);
    testMove2 = std::move(testMove1);
    if(testMove2.getChildren()[0]->getRootLabel() == 5 && testMove1.getChildren().size() == 0)
        std::cout << "Passed | Tree Assignment Test "<< std::endl;
    else
        std::cout << "Failed | Tree Assignment Test " << std::endl;
    testMove2 = std::move(testMove2); // Sanity check -> shouldn't trigger
    if(testMove2.getChildren()[0]->getRootLabel() == 5 )
        std::cout << "Passed | Tree Assignment Test (Sanity)" << std::endl;
    else
        std::cout << "Failed | Tree Assignment Test (Sanity) " <<std::endl;
    T testMove3(std::move(T(1337)));
    if(testMove3.getRootLabel() == 1337)
        std::cout << "Passed | Tree Assignment Constructor Test" << std::endl;
    else
        std::cout << "Failed | Tree Assignment Constructor Test" << std::endl;
    std::cout << "-----------------------\r\n\r\n\n" << std::endl;
}
int main(int argc,char **argv){
    FiveRuleTestTree<MaxRankTree>();
    FiveRuleTestTree<RootTree>();
}

using namespace std;
