// Online C++ compiler to run C++ program online
#include <iostream>
#include <cstdlib>
#include <stack>
#include <string>
#include <vector>
#include <list>
#include <time.h>
#include "Deck.h"

using namespace std;


const int HAND_SIZE = 6;

struct Card{
    int value;
    int run_value;
    string symbol;
    string suit;
};

class Deck {       // The class
    public:
        Deck();
        void Shuffle();
        void printDeck();
        void assignCustomHands(list<Card*> &hand1, list<Card*> &hand2);
        void dealHands(list<Card*> &hand1, list<Card*> &hand2);
        void returnCardsToDeck(list<Card*> &hand1, list<Card*> &hand2);
    private:
        vector<Card*> myDeck, shuffledDeck, shuffledTestDeck;;
        //stack<Card*> shuffledDeck, shuffledTestDeck;
        int num_hands;
        int cards_per_hand;
};

Deck::Deck(){
    Card* currCard;
    //using lists for the hands because they are doubly linked lists, placing
    //cards in descending order of value reduces time complexity of counting
    //points in the hand
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
            shuffledDeck.push_back(currCard);
        }
    }
    cout<<"Deck generated!\n";
}

void Deck::Shuffle(){
    //shuffle the deck
    myDeck = shuffledDeck;
    shuffledDeck.clear();
    shuffledTestDeck.clear();
    for(int i = 52; i > 0; i--){
        srand(time(NULL));
        int r = rand() % i;
        shuffledDeck.push_back(myDeck[r]);
        shuffledTestDeck.push_back(myDeck[r]);
        myDeck.erase(myDeck.begin() + r);
    }
    cout<<"Deck shuffled\n";
}

void Deck::printDeck(){
//test print the entire deck
    for(int i = 0; i < 52; i++){
        cout<<shuffledTestDeck.back()->symbol<<shuffledTestDeck.back()->suit<<'\n';
        shuffledTestDeck.pop_back();
    }
}

void Deck::assignCustomHands(list<Card*> &hand1, list<Card*> &hand2){
    hand1.push_back(myDeck[11]);
    hand1.push_back(myDeck[10]);
    hand1.push_back(myDeck[9]);
    hand1.push_back(myDeck[9]);
    hand1.push_back(myDeck[8]);

    hand2.push_back(myDeck[3]);
    hand2.push_back(myDeck[2]);
    hand2.push_back(myDeck[1]);
    hand2.push_back(myDeck[0]);
    hand2.push_back(myDeck[0]);
}

void Deck::dealHands(list<Card*> &hand1, list<Card*> &hand2){
   Card* currCard;
   list<Card*>::iterator it;
   while(hand1.size() < HAND_SIZE && hand2.size() < HAND_SIZE){
    if(hand1.empty()){
        hand1.push_back(shuffledDeck.back());
        shuffledDeck.pop_back();
        hand2.push_back(shuffledDeck.back());
        shuffledDeck.pop_back();
    }
    else {
        //first deal top card to my hand
        it=hand1.begin();
        //for some reason the iterator can't be de-referenced directly,
        //but the address can be copied to a pointer and that can be de-referenced
        currCard = *it; 
        while(it!=hand1.end() && shuffledDeck.back()->run_value < currCard->run_value){
            it++;
            currCard = *it; 
        }
        hand1.insert(it, shuffledDeck.back());
        shuffledDeck.pop_back();


        //then deal next card to opponent hand
        it=hand2.begin();
        //for some reason the iterator can't be de-referenced directly,
        //but the address can be copied to a pointer and that can be de-referenced
        currCard = *it; 
        while(it!=hand2.end() && shuffledDeck.back()->run_value < currCard->run_value){
            it++;
            currCard = *it; 
        }
        hand2.insert(it, shuffledDeck.back());
        shuffledDeck.pop_back();
    }
   }
}

void Deck::returnCardsToDeck(list<Card*> &hand1, list<Card*> &hand2){
    Card* currCard;
    list<Card*>::iterator it;
    it = hand1.begin();
    while(it != hand1.end()){
        currCard = *it;
        shuffledDeck.push_back(currCard);
        hand1.pop_front();
        it = hand1.begin();
    }

    it = hand2.begin();
    while(it != hand2.end()){
        currCard = *it;
        shuffledDeck.push_back(currCard);
        hand2.pop_front();
        it = hand2.begin();
    }
}

void print_hand(list<Card*> hand){
    Card* currCard;    
    list<Card*>::iterator it;
    for (it=hand.begin(); it!=hand.end(); ++it){
        currCard = *it;
        cout<<currCard->symbol<<currCard->suit<<'\n';
    }
    cout<<'\n';
}

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

void count_points_benchmark(Deck *deck, list<Card*> hand1, list<Card*> hand2){
    Card* currCard;    
    list<Card*>::iterator it;
    clock_t start, end; 
    int numCalcs = 0;
    int total_points = 0;
    float time_complexity = 0.0; //ns

    for(int i = 0; i < 100; i++){
        //test print my hand
        cout << "\nmy hand: \n";
        print_hand(hand2);

        numCalcs = 0;
        it=hand1.begin();
        start = clock();
        total_points = 2*count_fifteens_trim(numCalcs,0, hand1, it) + 2*count_pairs(hand1) + count_runs(hand1);
        end = clock();
        time_complexity += ((float)end-(float)start);
        cout<<"total points: "<<total_points<<"\n\n";

        //test print opponent's hand
        cout << "opponent's hand: \n";
        print_hand(hand2);

        numCalcs = 0;
        it=hand2.begin();
        start = clock();
        total_points = 2*count_fifteens_trim(numCalcs,0, hand2, it) + 2*count_pairs(hand2) + count_runs(hand2);
        end = clock();
        time_complexity += ((float)end-(float)start);
        cout<<"total points: "<<total_points<<"\n\n";
    
        deck->returnCardsToDeck(hand1, hand2);
        deck->Shuffle();
        deck->dealHands(hand1, hand2);
    }
    time_complexity = time_complexity / 200.0;
    cout<<"Average time of each search in ns: "<<time_complexity<<"\n";
}


void choose_optimal_hand(list<Card*> hand, list<Card*> *optimal_hand, list<Card*> *discard){
    optimal_hand->clear();
    discard->clear();

    int factorial_iterator =   HAND_SIZE - 1;
    list<Card*>::iterator it;
    it = hand.begin();
    while(it != hand.end()){
        optimal_hand->push_back(*it);
        it++;
    }

    optimal_hand = &hand;
    discard->push_back(optimal_hand->front());
    optimal_hand->pop_front();
    discard->push_back(optimal_hand->front());
    optimal_hand->pop_front();
    for(int i=0; i<(HAND_SIZE-1); i++){
        print_hand(*discard);
        for(int j=0; j<(factorial_iterator-1); j++){
            //this is where we would calculate the scoring potential
            //of each combination
            optimal_hand->push_back(discard->back());
            discard->pop_back();
            discard->push_back(optimal_hand->front());
            optimal_hand->pop_front();
            print_hand(*discard);
        }
        optimal_hand->push_back(discard->back());
        discard->pop_back();

        for(int k = 0; k < (HAND_SIZE - 1 - factorial_iterator); k++){
            optimal_hand->push_back(optimal_hand->front());
            optimal_hand->pop_front();
        }

        optimal_hand->push_back(discard->back());
        discard->pop_back();

        discard->push_back(optimal_hand->front());
        optimal_hand->pop_front();
        discard->push_back(optimal_hand->front());
        optimal_hand->pop_front();

        factorial_iterator--;
    }
    
}

int main() {
    Deck deck;
    Card* currCard;
    list<Card*> myHand, opponentHand, discard, optimal_hand;
    list<Card*>::iterator it;
    clock_t start, end; 
    //assign specific cards to hands for unit testing
    //deck.assignCustomHands(myHand, opponentHand);

    deck.Shuffle();
    
    //deck.printDeck();

    //deal the cards, order the cards in descending order
    deck.dealHands(myHand, opponentHand);

    //count_points_benchmark(&deck, myHand, opponentHand);

    print_hand(myHand);

    choose_optimal_hand(myHand,&optimal_hand, &discard);

    return 0;
}