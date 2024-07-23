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
    int run_value;
    string symbol;
    string suit;
};

const int HAND_SIZE = 5;

//count the number of different card combinations
//can be added up to equal 15 (for point scoring)
//needs to be recursive
//returns the number combos to make 15
int count_fifteens(int &numCalcs, int sum, list<Card*> &hand, list<Card*>::iterator it){
    Card* currCard;

    int count = 0;
    int internal_sum = sum;

    if(it == hand.end())
        return 0;

    while(it != hand.end()){
        currCard = *it;
        internal_sum += currCard->value;
        it++;
        if(internal_sum == 15)
            count++;
        else if(internal_sum < 15){
            count += count_fifteens(numCalcs, internal_sum, hand, it);
        }
        internal_sum -= currCard->value;
        numCalcs++;
    }
    return count;
}

//trimming unnecessary checks by detecting when the end
//the highest level recursive call reaches the end of 
//the hand and the running sum is too low to reach 15.
//At that point, there is no need to go further into the
//recursive call stack with lower numbers
int count_fifteens_trim(int &numCalcs, int sum, list<Card*> &hand, list<Card*>::iterator it){
    Card* currCard;

    int count = 0;
    int temp = 0;
    int internal_sum = sum;

    if(it == hand.end())
        return -1;

    while(it != hand.end()){
        currCard = *it;
        internal_sum += currCard->value;
        it++;
        if(internal_sum == 15)
            count++;
        else if(internal_sum < 15){
            temp = count_fifteens_trim(numCalcs, internal_sum, hand, it);
            if(temp == -1)
                break;
            else
                count += temp;
        }
        internal_sum -= currCard->value;
        numCalcs++;
    }
    return count;
}

//function to count the number of pairs in the hand
//this includes 3 of a kind (3 pairs) and 4 of a kind
//(six pairs)
//O(2n) time complexity
int count_pairs(list<Card*> &hand){
    Card *currCard1, *currCard2;
    int count = 0;
    list<Card*>::iterator it1, it2;

    for (it1=hand.begin(); it1!=hand.end(); it1++){
        currCard1 = *it1;
        it2=it1;
        for (it2++; it2!=hand.end(); it2++){
            currCard2 = *it2;
            if(currCard1->symbol == currCard2->symbol)
                count++;
            else
                break;
        }
    }
    return count;
}

int count_runs(list<Card*> hand){
    list<Card*> pair_cards, no_pair_hand;
    Card *currCard1, *currCard2;
    int count = 0;
    int current_run_length = 1;
    int previous_card= 0;
    int multiplier = 1;
    bool double_run = false;
    list<Card*>::iterator it1, it2, it3;
    it1 = hand.begin();
    it2=it1;
    it2++;
    //separate the cards into one hand with no repeats
    //and another hand with all duplicate cards
    while(it2 != hand.end()){
        currCard1 = *it1;
        currCard2 = *it2;        
        if(currCard1->run_value == currCard2->run_value){
            pair_cards.push_back(currCard1);
        }
        else{
            no_pair_hand.push_back(currCard1);
        }
        hand.pop_front();
        it1 = hand.begin();
        it2 = it1;
        it2++;
    }

    //there is one card left
    currCard1 = *it1;
    no_pair_hand.push_back(currCard1);


    //check the non-repeat hand for runs, if a run exists,
    //check the duplicate cards for double runs
    for (it1=no_pair_hand.begin(); it1!=no_pair_hand.end(); it1++){
        currCard1 = *it1;
        it2=it1;
        it2++;
        previous_card = currCard1->run_value;
        while(it2!=no_pair_hand.end()){
            currCard2 = *it2;
            if(previous_card == (currCard2->run_value+1)){
                current_run_length++;
                previous_card = currCard2->run_value;
            }
            else
                break;
            it2++;
        }
        it2--;  //now it2 points to the last number in the run
        it1 = it2; //avoids double counting runs longer than 3
        if(current_run_length >=3){
            for(int i=0; i<current_run_length; i++){
                currCard2 = *it2;
                it3 = pair_cards.begin();
                while(it3 != pair_cards.end()){
                    currCard1 = *it3;
                    if(currCard1->run_value == currCard2->run_value){
                        if(double_run)
                            multiplier = 4; //double double run detected
                        else
                            multiplier++;   //should work for double and triple runs
                    }
                    it3++;
                }
                if(multiplier > 1){
                    double_run = true; //saves the information for a double double run
                                        //in which case incrementing the multiplier will
                                        //not suffice, multiplier should be doubled
                }
                it2--;
            }
            count += current_run_length * multiplier;
        }
        current_run_length = 1;
    }
    return count;
}


void assignCustomHands(list<Card*> &hand1, list<Card*> &hand2,vector<Card*> &deck){
    hand1.push_back(deck[11]);
    hand1.push_back(deck[10]);
    hand1.push_back(deck[9]);
    hand1.push_back(deck[9]);
    hand1.push_back(deck[8]);

    hand2.push_back(deck[3]);
    hand2.push_back(deck[2]);
    hand2.push_back(deck[1]);
    hand2.push_back(deck[0]);
    hand2.push_back(deck[0]);
}

int main() {
    // Write C++ code here
    
    Card* currCard;
    vector<Card*> myDeck, testDeck;
    stack<Card*> shuffledDeck, shuffledTestDeck;
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
            currCard->run_value = j;
            if(currCard->value > 10)
                currCard->value = 10;
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
            testDeck.push_back(currCard);
            //cout<<arrayIndex<<'\n';
        }
    }
    cout<<"Deck generated!\n";
    
    //assign specific cards to hands for unit testing
    assignCustomHands(myHand, opponentHand, testDeck);

    //shuffle the deck
    for(int i = 52; i > 0; i--){
        srand(time(NULL));
        int r = rand() % i;
        shuffledDeck.push(myDeck[r]);
        shuffledTestDeck.push(myDeck[r]);
        //cout<<myDeck[r]->symbol<<"  "<<myDeck[r]->suit<<'\n';
        myDeck.erase(myDeck.begin() + r);
    }

    cout<<"Deck shuffled\n";
    
    //test print the entire deck
    for(int i = 0; i < 52; i++){
        cout<<shuffledTestDeck.top()->symbol<<shuffledTestDeck.top()->suit<<'\n';
        shuffledTestDeck.pop();
    }

   //deal the cards, order the cards in descending order
/*
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
        while(it!=myHand.end() && shuffledDeck.top()->run_value < currCard->run_value){
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
        while(it!=opponentHand.end() && shuffledDeck.top()->run_value < currCard->run_value){
            it++;
            currCard = *it; 
        }
        opponentHand.insert(it, shuffledDeck.top());
        shuffledDeck.pop();
    }
   }
*/

    //test print my hand
    cout << "\nmy hand: \n";
    for (it=myHand.begin(); it!=myHand.end(); ++it){
        currCard = *it;
        cout<<currCard->symbol<<currCard->suit<<'\n';
    }
    int numCalcs = 0;
    numCalcs = 0;
    it=myHand.begin();
    int fifteens_points = 2*count_fifteens_trim(numCalcs,0, myHand, it);
    int pairs_points = 2*count_pairs(myHand);
    int runs_points = count_runs(myHand);
    cout<<"number of fifteens: "<< fifteens_points<< "\nnumber of pairs: "<<pairs_points<<"\n";
    cout<<"number of runs: "<< runs_points<< "\ntotal points: "<<(fifteens_points+pairs_points+runs_points)<<"\n";
    cout<<"\nNumCalcs: "<<numCalcs<<"\n";

    //test print opponent's hand
    cout << "opponent's hand: \n";
    for (it=opponentHand.begin(); it!=opponentHand.end(); ++it){
        currCard = *it;
        cout<<currCard->symbol<<currCard->suit<<'\n';
    }
    numCalcs = 0;
    it=opponentHand.begin();
    fifteens_points = 2*count_fifteens_trim(numCalcs,0, opponentHand, it);
    pairs_points = 2*count_pairs(opponentHand);
    runs_points = count_runs(opponentHand);
    cout<<"number of fifteens: "<< fifteens_points<< "\nnumber of pairs: "<<pairs_points<<"\n";
    cout<<"number of runs: "<< runs_points<< "\ntotal points: "<<(fifteens_points+pairs_points+runs_points)<<"\n";
    cout<<"\nNumCalcs: "<<numCalcs<<"\n";

    return 0;
}