// Online C++ compiler to run C++ program online
#include <iostream>
#include <cstdlib>
#include <stack>
#include <string>
#include <vector>
#include <list>
#include <time.h>

using namespace std;

struct Card{
    int value;
    string symbol;
    string suit;
};

const int HAND_SIZE = 5;

int main() {
    // Write C++ code here
    
    Card* currCard;
    vector<Card*> myDeck;
    stack<Card*> shuffledDeck, testDeck;
    //using lists for the hands because they are doubly linked lists, placing
    //cards in descending order of value reduces time complexity of counting
    //points in the hand
    list<Card*> myHand, opponentHand;
    list<Card*>::iterator it; 

    //create the deck from scratch. Poof!
    int arrayIndex;
    for(int i =0;i<4;i++){
        for(int j = 1;j<14; j++){
            currCard = new Card;
            //cout<<currCard<<"\n";
            currCard->value = j;
            switch(j){
                case 1:
                    currCard->symbol = "A";
                    break;
                case 2:
                    currCard->symbol = "2";
                    break;
                case 3:
                    currCard->symbol = "3";
                    break;
                case 4:
                    currCard->symbol = "4";
                    break;
                case 5:
                    currCard->symbol = "5";
                    break;
                case 6:
                    currCard->symbol = "6";
                    break;
                case 7:
                    currCard->symbol = "7";
                    break;
                case 8:
                    currCard->symbol = "8";
                    break;
                case 9:
                    currCard->symbol = "9";
                    break;
                case 10:
                    currCard->symbol = "10";
                    break;
                case 11:
                    currCard->symbol = "J";
                    break;
                case 12:
                    currCard->symbol = "Q";
                    break;
                case 13:
                    currCard->symbol = "K";
                    break;
            }
            switch(i){
                case 0:
                    currCard->suit = "spade";
                    break;
                case 1:
                    currCard->suit = "club";
                    break;
                case 2:
                    currCard->suit = "heart";
                    break;
                case 3:
                    currCard->suit = "diamond";
                    break;
            }
            myDeck.push_back(currCard);
            //cout<<arrayIndex<<'\n';
        }
    }
    cout<<"Deck generated!\n";
    
    //shuffle the deck
    for(int i = 52; i > 0; i--){
        srand(time(NULL));
        int r = rand() % i;
        shuffledDeck.push(myDeck[r]);
        testDeck.push(myDeck[r]);
        //cout<<myDeck[r]->symbol<<"  "<<myDeck[r]->suit<<'\n';
        myDeck.erase(myDeck.begin() + r);
    }

    cout<<"Deck shuffled\n";
    
    //test print the entire deck
    for(int i = 0; i < 52; i++){
        cout<<testDeck.top()->symbol<<testDeck.top()->suit<<'\n';
        testDeck.pop();
    }

   //deal the cards, order the cards in descending order
   
   
   /*cout<<"Test of iterator object\n";
   myHand.push_back(shuffledDeck.top());
   it=myHand.begin();
   cout<<"shuffledDeck.top: "<<shuffledDeck.top()->value<<"\n";
   //cout<<"*it: "<<*it<<"\n";

   currCard = *it;
   cout<<"currCard value: "<<currCard->value<<"\n";*/

   while(myHand.size() < HAND_SIZE && opponentHand.size() < HAND_SIZE){
    if(myHand.empty()){
        myHand.push_back(shuffledDeck.top());
        shuffledDeck.pop();
        opponentHand.push_back(shuffledDeck.top());
        shuffledDeck.pop();
    }
    else {
        //first deal top card to my hand
        it=myHand.begin();
        //for some reason the iterator can't be de-referenced directly,
        //but the address can be copied to a pointer and that can be de-referenced
        currCard = *it; 
        while(it!=myHand.end() && shuffledDeck.top()->value < currCard->value){
            it++;
            currCard = *it; 
        }
        myHand.insert(it, shuffledDeck.top());
        shuffledDeck.pop();


        //then deal next card to opponent hand
        it=opponentHand.begin();
        //for some reason the iterator can't be de-referenced directly,
        //but the address can be copied to a pointer and that can be de-referenced
        currCard = *it; 
        while(it!=opponentHand.end() && shuffledDeck.top()->value < currCard->value){
            it++;
            currCard = *it; 
        }
        opponentHand.insert(it, shuffledDeck.top());
        shuffledDeck.pop();
    }
   }

    //test print my hand
    std::cout << "my hand: \n";
    for (it=myHand.begin(); it!=myHand.end(); ++it){
        currCard = *it;
        cout<<currCard->symbol<<currCard->suit<<'\n';
    }
    std::cout << '\n';

    //test print opponent's hand
    std::cout << "opponent's hand: \n";
    for (it=opponentHand.begin(); it!=opponentHand.end(); ++it){
        currCard = *it;
        cout<<currCard->symbol<<currCard->suit<<'\n';
    }
    std::cout << '\n';

    return 0;
}