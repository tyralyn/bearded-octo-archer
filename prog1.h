#include<iostream>
#include<sstream>
#include<string>
#include <stdlib.h>
#include "binaryTree.h"
//#include "eval.h"

#define MAX_SIZE 500000

using namespace std;

void parse (string query, binaryTree*& tree)
{
  istringstream iss(query);
  string token[1000];
  int i, numtokens;
  i=0; numtokens=0;
  do {
    iss >> token[i];
    i++;
    numtokens++;
  } while (iss);
  i=0;
  while (i < numtokens)    {
    i = i+1;
  }
  int value;
  const char * ptr;
  if (numtokens>1) {
    //ptr=token[1].length._str();
    string k=token[1];
    value=atoi(k.c_str());
    //value=atoi(token[1]);
  }
  if (token[0]=="insert") {
    tree->insert(value);
  }
  else if (token[0]=="delete") {
    tree->Delete2(value);
  }
  else if (token[0]=="access") {
    tree->access(value);
  }
  else if (token[0]=="print") {
    tree->print();
  }
}

int main() {
  string line;
  binaryTree* myTree=new binaryTree();
  while(getline(cin, line)) {
    parse(line, myTree);
  }
}
/*

int main(){
  string query, result[MAX_SIZE], line;
  stringstream linestream;
  int i,size;
  binaryTree* myTree=new binaryTree();
  
  while(cin.getline(fin, line)) {
    cout << "Expression:(op1 operator op2); where op1/op1 is Integer or Expression and operators +, -, *, /" << endl;
    cout<<"Enter the Expression or 'DONE': ";
    cin.getline(result,256);
    parse(query, myTree); 
  }
  return 0;
}
*/

