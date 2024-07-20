// Online C++ compiler to run C++ program online
#include <iostream>
#include <cstdlib>
#include <stack>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

struct Card{
    int value;
    string symbol;
    string suit;
};


int main() {
    // Write C++ code here
    Card* currCard;
    vector<Card*> myDeck;
    stack<Card*> shuffledDeck;
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
    
    for(int i = 52; i > 0; i--){
        srand(time(NULL));
        int r = rand() % i;
        shuffledDeck.push(myDeck[r]);
        //cout<<myDeck[r]->symbol<<"  "<<myDeck[r]->suit<<'\n';
        myDeck.erase(myDeck.begin() + r);
    }

    cout<<"Deck shuffled\n";
    
    for(int i = 0; i < 52; i++){
        cout<<shuffledDeck.top()->symbol<<shuffledDeck.top()->suit<<'\n';
        shuffledDeck.pop();
    }
    
    return 0;
}