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
void caseThree(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void caseFour(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void caseFive(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void fixTree(Node* &root, Node* current);


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
	  /*
	  int value;
            cout << "What number would you like to remove? " << endl;
            cin >> value;
            cin.get();
            
	    remove(0, root, value);
	  */
	  cout << "Temporarily out of service, please try again later" << endl;
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

/*
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
*/

void caseThree(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode){
  parent->setColor('b');
  uncle->setColor('b');
  grandparent->setColor('r');
  fixTree(root, grandparent);
}

void caseFour(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode){



}

void caseFive(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode){


}

void fixTree(Node* &root, Node* current){
  if(root != NULL){
    if(root->getColor() == 'r'){
      cout << "Case1" << endl;
      root->setColor('b');
    }
    if(current->getParent() != NULL){
      if(current->getParent()->getColor() == 'b'){
	cout << "Case2" << endl;
	return;
      }
      if(current->getParent()->getParent() != NULL){
	if(current->getParent()->getUncle() != NULL){
	  if(current->getParent()->getColor() == 'r' && current->getParent()->getUncle()->getColor() == 'r'){
	    cout << "Case3" << endl;
	    caseThree(root, current->getParent()->getParent(), current->getParent(), current->getParent()->getUncle(), current);
	  }
	  if(current->getParent()->getColor() == 'r' && current->getParent()->getUncle()->getColor() == 'b'){
	    if(current->getParent()->getInformation() < current->getParent()->getParent()->getInformation() && current->getParent()->getInformation() < current->getInformation()){
	      caseFour(root, current->getParent()->getParent(), current->getParent(), current->getParent()->getUncle(), current);
	      cout << "Case4" << endl;
	    }
	    else if(current->getParent()->getInformation() >= current->getParent()->getParent()->getInformation() && current->getParent()->getInformation() >= current->getInformation()){
	      cout << "Case4" << endl;
	      caseFour(root, current->getParent()->getParent(), current->getParent(), current->getParent()->getUncle(), current);
	    }
	    
	    if(current->getParent()->getInformation() < current->getParent()->getParent()->getInformation() && current->getInformation() < current->getParent()->getInformation()){
	      cout << "Case5" << endl;
	      caseFive(root, current->getParent()->getParent(), current->getParent(), current->getParent()->getUncle(), current);
	    }
	    else if(current->getParent()->getInformation() >= current->getParent()->getParent()->getInformation() && current->getInformation() >= current->getParent()->getInformation()){
	      cout << "Case5" << endl;
	      caseFive(root, current->getParent()->getParent(), current->getParent(), current->getParent()->getUncle(), current);
	    }
	    
	  }
	}
      }
    }
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
    fixTree(root, newNode);

}

//pretty sure this add is useless

/*
void add(Node* &root, Node* current, Node* newNode){
    if(root == NULL){
        root = newNode;
	root->setColor('b');
    }
    else if(current->getInformation() >= newNode->getInformation()){
        if(current->getLeft() == NULL){
            current->setLeft(newNode);
	    newNode->setParent(current);
	    if(current->getColor() != 'b'){
	      if(current->getUncle()->getColor() == 'r'){
		caseThree(root, current->getParent(), current, current->getUncle(), newNode);
	      }
	      else if(current->getUncle()->getColor() == 'b' && current->getParent()->getInformation() <= current->getInformation()){
		caseFour(root, current->getParent(), current, current->getUncle(), newNode);
	      }
	      else if(current->getUncle()->getColor() == 'b' && current->getParent()->getInformation() > current->getInformation()){
		caseFive(root, current->getParent(), current, current->getUncle(), newNode);
	      }
	      
	    }
        }
        else{
            add(root, current->getLeft(), newNode);
        }
    }
    else if(current->getInformation() < newNode->getInformation()){
        if(current->getRight() == NULL){
            current->setRight(newNode);
            newNode->setParent(current);
	    if(current->getColor() != 'b'){
              if(current->getUncle()->getColor() == 'r'){
                caseThree(root, current->getParent(), current, current->getUncle(), newNode);
              }
              else if(current->getUncle()->getColor() == 'b' && current->getParent()->getInformation() >= current->getInformation()){
                caseFour(root, current->getParent(), current, current->getUncle(), newNode);
              }
              else if(current->getUncle()->getColor() == 'b' && current->getParent()->getInformation() < current->getInformation()){
                caseFive(root, current->getParent(), current, current->getUncle(), newNode);
              }

            }
        }
        else{
            add(root, current->getRight(), newNode);
        }
    }

  

}
*/
void print(Node* current, int count){
    if(current->getLeft() != NULL){
        print(current->getLeft(), count + 1);
    }
    for(int i = 0; i < count; i++){
        cout << '\t';
    }
    cout << current->getInformation() << " " << current->getColor() << endl;
    if(current->getRight() != NULL){
        print(current->getRight(), count + 1);
    }

}
