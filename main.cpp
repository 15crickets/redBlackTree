#include <iostream>
#include <cstring>
#include "Node.h"
#include <vector>
#include <fstream>
using namespace std;

void add(Node* &root, Node* current, Node* newNode);
void print(Node* current, int count);
bool search(Node* current, int value);
void remove(int direction, Node* current, int value);

int main(){
    Node* root = NULL;

    bool stillRunning = true;
    while(stillRunning == true){
        cout << "What would you like to do? ADD, REMOVE, SEARCH, PRINT, or QUIT " << endl;
        char choice[50];
        cin.get(choice, 50);
        cin.get();
        if(strcmp(choice, "ADD") == 0){
            char input[50];
            char method;
            cout << "Would you like to enter by file (f) or by console (c)? " << endl;
            cin >> method;
            cin.get();
            if(method == 'c'){
                cout << "How many numbers will you be entering? " << endl;
                int numNums;
                cin >> numNums;
                cin.get();
                cout << "Enter your string of numbers: " << endl;
                for(int i = 0; i < numNums; i++){
                    int tempInt;
                    cout << "INSIDE?" << endl;
                    cin >> tempInt;
                    cout << tempInt << endl;
                    cout << "HI" << endl;
                    cin.get();
                    Node* newNode = new Node();
                    newNode->setInformation(tempInt);
                    add(root, root, newNode);
                }  
            
            }
            else if(method == 'f'){
                vector<int> nums;
                fstream first_stream;
                first_stream.open("nums.txt");
                int num;
                while(first_stream >> num){
                    nums.push_back(num);
                }
                vector <int> ::iterator iter = nums.begin();
                for(iter = nums.begin(); iter < nums.end(); iter++){
                    Node* newNode = new Node();
                    newNode->setInformation(*iter);
                    add(root, root, newNode);
                }


            }
        }
        else if(strcmp(choice, "REMOVE") == 0){
            int value;
            cout << "What number would you like to remove? " << endl;
            cin >> value;
            cin.get();
            remove(0, root, value);
        }
        else if(strcmp(choice, "SEARCH") == 0){
            int value;
            cout << "What number would you like to search for? " << endl;
            cin >> value;
            cin.get();
            if(search(root, value) == true){
                cout << "That value exists in the tree" << endl;
            }
            else{
                cout << "That value doesn't exist in the tree" << endl;
            }
        }
        else if(strcmp(choice, "PRINT") == 0){
            print(root, 0);
        }
        else if(strcmp(choice, "QUIT") == 0){
            stillRunning = false;
        }

    }
    
}

bool search(Node* current, int value){
    if(value > current->getInformation()){
        if(current->getRight() != NULL){
            return search(current->getRight(), value);
        }
    }
    else if(value < current->getInformation()){
        if(current->getLeft() != NULL){
            return search(current->getLeft(), value);
        }
    }
    else if(value == current->getInformation()){
        return true;
    }
    return false;
}

void remove(int direction, Node* current, int value){
    if(current->getInformation() == value){
        if(current->getRight() == NULL && current->getLeft() == NULL){
            if(current->getParent() != NULL){
                if(direction == 0){
                    current->getParent()->setLeft(NULL);
                }
                else if(direction == 1){
                    current->getParent()->setRight(NULL);
                }
            }
            delete current;
        }
        else if(current->getLeft() == NULL){
            cout << "1" << endl;
            if(direction == 0){
                current->getParent()->setLeft(current->getRight());
            }
            else if(direction == 1){
                current->getParent()->setRight(current->getRight());
            }
            current->getRight()->setParent(current->getParent());
            delete current;
        }
        else if(current->getRight() == NULL){
            cout << current->getParent()->getInformation() << endl;
            if(direction == 0){
                current->getParent()->setLeft(current->getLeft());
            }
            else if(direction == 1){
                current->getParent()->setRight(current->getLeft());
            }
            current->getLeft()->setParent(current->getParent());
            delete current;
        }
        else{
            Node* tempNode = current->getRight();
            int counter = 0;
            while(tempNode->getLeft() != NULL){
                tempNode = tempNode->getLeft();
                counter++;
            }
            current->setInformation(tempNode->getInformation());
            if(counter == 0){
                current->setRight(tempNode->getRight());
                tempNode->getParent()->setRight(tempNode->getRight());
            }
            else{
                tempNode->getParent()->setLeft(tempNode->getLeft());
            }
            delete tempNode;
        }
    }
    else if(current->getInformation() > value){
        remove(0, current->getLeft(), value);
    }
    else if(current->getInformation() < value){
        remove(1, current->getRight(), value);
    }

}

void add(Node* &root, Node* current, Node* newNode){
    if(root == NULL){
        root = newNode;
    }
    else if(current->getInformation() >= newNode->getInformation()){
        if(current->getLeft() == NULL){
            current->setLeft(newNode);
            newNode->setParent(current);
        }
        else{
            add(root, current->getLeft(), newNode);
        }
    }
    else if(current->getInformation() < newNode->getInformation()){
        if(current->getRight() == NULL){
            current->setRight(newNode);
            newNode->setParent(current);
        }
        else{
            add(root, current->getRight(), newNode);
        }
    }

}

void print(Node* current, int count){
    if(current->getLeft() != NULL){
        print(current->getLeft(), count + 1);
    }
    for(int i = 0; i < count; i++){
        cout << '\t';
    }
    cout << current->getInformation() << endl;
    if(current->getRight() != NULL){
        print(current->getRight(), count + 1);
    }

}