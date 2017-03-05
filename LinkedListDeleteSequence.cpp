#include <iostream>
#include <stdlib.h>
using namespace std;

struct Node{
    struct Node * next;
    int data;
    Node(){}
};

int main(){
ios::sync_with_stdio(false); //faster is better.
int nodeCount;
std::cin>>nodeCount; //Size of linked list.
struct Node* header = new Node(); //allocate for header
Node *previous = header;
for(int i=0; i<nodeCount; i++){ //Declare the linkedlist.
    struct Node* current = new Node();
    std::cin>>current->data;
    current->next = header->next; //This should be changed on the next loop iteration, but we want to point back to the start.
    previous->next = current;
    previous = current;//increment the previous pointer.
}

int deletions;
std::cin>>deletions; //How many sequences of deletion
if(deletions == 0)
    return(0);
int * delarr = new int[deletions*3];
for(int k=0; k<=3*deletions -1; k++){//Popluate del array.
    std::cin>>delarr[k];
}
int delCounter=0; //Actual deletion algorithm starts
for(int m=0; m<deletions; m++){
    int starter = delarr[3*m];
    int ender = delarr[3*m+1];
    int step = delarr[3*m+2];
    Node * beforeStart = NULL;
    Node * beforeEnd = NULL;
    int slowPointerCondition = 0;
    Node * current = header;
    Node * slowPointer = new Node(); //A preheader-node of sorts.  Needs to start behind the header.
        slowPointer->next = header; //Slow pointer should move at 3/4 speed of fast pointer.
    //std::cout<<"starting deletion search on "<<current->next->data<<", "<<current->next->next->data<<"..."<<endl; //TODO debug remove.
    while(current!=slowPointer || (slowPointerCondition==0 && current != NULL) && (beforeStart==NULL || beforeEnd==NULL)){ //step through the linkedlist, looking for
        slowPointerCondition++;
        if(current->next->data == starter && beforeStart == NULL) //Only if we haven't already found the starter.
            beforeStart = current;
        if(current->next->data == ender && current->next != beforeStart && beforeStart!=NULL)//We can't start and end on the same value because we will already have deleted it.  Also the end value must be found after the start value.
            beforeEnd = current;
        if(slowPointerCondition % 3 != 0){  //Increment our slow pointer, but only 3/4 or half of the time.
            slowPointer = slowPointer->next;
        }
        current = current->next; //increment our other beloved pointer.
    }
    if(beforeStart != NULL && beforeEnd != NULL && beforeEnd!=beforeStart){
        current = beforeStart;
        Node * afterDelete;
        int stopOn = beforeEnd->next->data;
        bool firstTime = true;
        int stepSinceDelete =0;
        while((current->next->data != stopOn && current->next!=NULL && current!=NULL) || firstTime){
            stepSinceDelete++;
            if(stepSinceDelete == step){
                stepSinceDelete=0;
                afterDelete = current->next->next;
                delCounter++;
                //std::cout<<"deleted value! "<<current->next->data<<endl; //TODO debug remove.
                if(current->next == header->next){ //If we try to delete a header node.
                    header->next = afterDelete;
                }
                //free(current->next);
                current->next = afterDelete;
            }
            else{
                current = current->next;
            }
            //std::cout<<"on "<<current->data<<" waiting for "<<stopOn<<endl; //TODO debug remove
            firstTime = false; //This ensures we don't stop prematurely when the starting and stopping values are identical.
        }
        //std::cout<<"found stop value!"<<stopOn<<endl; //TODO debug remove
        stepSinceDelete++;
        if(stepSinceDelete == step){
            stepSinceDelete=0;
            afterDelete = current->next->next; //Must delete one additional node.
            delCounter++;
            //std::cout<<"deleted value! "<<current->next->data<<endl; //TODO debug remove.
            if(current->next == header->next){ //If we try to delete a header node.
                    header->next = afterDelete;
            }
            //free(current->next);
            current->next = afterDelete;
        }
    }
}
free(delarr);
Node * now = header;
if(header->next == header || header->next == NULL || header->next->next == NULL)
{
    //Do nothing, this is a trap.
}
else for(int j=0; j<nodeCount - delCounter; j++){ //just prints the list values.
    now = now->next;
    cout<<now->data<<" ";
}
}
