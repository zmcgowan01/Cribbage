// Online C++ compiler to run C++ program online
#include <fstream>
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
    int i_suit;   //for easier processing
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
        vector<Card*> myDeck, myDeckCustomHand, shuffledDeck, shuffledTestDeck;
        //stack<Card*> shuffledDeck, shuffledTestDeck;
        int num_hands;
        int cards_per_hand;
};

//constructor
//creates the Deck
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
                    currCard->i_suit = 0;
                    break;
                case 1:
                    currCard->suit = "club";
                    currCard->i_suit = 1;
                    break;
                case 2:
                    currCard->suit = "heart";
                    currCard->i_suit = 2;
                    break;
                case 3:
                    currCard->suit = "diamond";
                    currCard->i_suit = 3;
                    break;
            }
            myDeck.push_back(currCard);
            myDeckCustomHand.push_back(currCard); //keep this one in chronological order for custom hand making
            shuffledDeck.push_back(currCard);
        }
    }
    cout<<"Deck generated!\n";
}

//randomly shuffles the deck
//uses on internal class members
//shuffledDeck is the object to use
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

//test function
//prints the shuffled deck
void Deck::printDeck(){
//test print the entire deck
    for(int i = 0; i < 52; i++){
        cout<<shuffledTestDeck.back()->symbol<<shuffledTestDeck.back()->suit<<'\n';
        shuffledTestDeck.pop_back();
    }
}


//test function... print the hand
void print_hand(list<Card*> hand){
    Card* currCard;    
    list<Card*>::iterator it;
    for (it=hand.begin(); it!=hand.end(); ++it){
        currCard = *it;
        cout<<currCard->symbol<<currCard->suit<<'\n';
    }
    cout<<'\n';
}

//test function
//can create custom hands for each player
void Deck::assignCustomHands(list<Card*> &hand1, list<Card*> &hand2){
    hand1.push_back(myDeckCustomHand[11]);
    hand1.push_back(myDeckCustomHand[10]);
    hand1.push_back(myDeckCustomHand[9]);
    hand1.push_back(myDeckCustomHand[9]);
    hand1.push_back(myDeckCustomHand[8]);

    hand2.push_back(myDeckCustomHand[3]);
    hand2.push_back(myDeckCustomHand[2]);
    hand2.push_back(myDeckCustomHand[1]);
    hand2.push_back(myDeckCustomHand[0]);
    hand2.push_back(myDeckCustomHand[0]);
}

//deals cards to each player
//from the member object shuffledDeck
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

//this needs to be to return cards back to the deck
//it's helpful to have the cards physically removed
//from the deck for the duration of the hand
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

bool is_hand_sorted(list<Card*> hand){
    int prev_val = 15;  //arbitrary # larger than largest card value
    Card* currCard;    
    list<Card*>::iterator it;
    for (it=hand.begin(); it!=hand.end(); ++it){
        currCard = *it;
        if(currCard->run_value > prev_val);
            return false;
    }
    return true;
}

// comparison function for sorting list of type *Card
bool compare_cardvalue (const Card *first, const Card *second)
{
    if(first->run_value >= second->run_value)
        return true;
    else
        return false;
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

//trimming unnecessary checks by detecting when the end of
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
            if(currCard1->run_value == currCard2->run_value)
                count++;
            else
                break;
        }
    }
    return count;
}

//returns the number of points in the hand
//awarded to the player due to runs
//takes into account runs of different sizes
//and multiple runs in one hand
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

//used in calculating the optimal score of a hand
//specifically used to weight the possibility of scoring knobs
int count_cards_of_suit(list<Card*> hand, int suit){
    Card* currCard;    
    list<Card*>::iterator it;
    int suit_count = 0;
    it = hand.begin();
    while(it != hand.end()){
        currCard = *it;
        if(currCard->i_suit == suit)
            suit_count++;
        it++;
    }
    return suit_count;
}

//used in calculating the optimal score of a hand
//specifically used to weight the possibility of scoring knobs
//used to check for the number of Jacks for nobs
int count_cards_by_symbol(list<Card*> hand, int card_val){
    Card* currCard;    
    list<Card*>::iterator it;
    int card_count = 0;
    it = hand.begin();
    while(it != hand.end()){
        currCard = *it;
        if(currCard->run_value == card_val)
            card_count++;
        it++;
    }
    return card_count;
}

//calculates the weighted point value of nobs for
//a given hand, given the unknown of the cut card
float count_weighted_points_nobs(list<Card*> hand,list<Card*> discard_hand){
    Card* currCard;    
    list<Card*>::iterator it1;
    list<int>::iterator it2;
    list<int> jack_suits;
    int currSuit = 0;
    float weighted_nobs_score = 0.0;
    it1 = hand.begin();
    if(count_cards_by_symbol(hand, 11) > 0){
        while(it1 != hand.end()){
            currCard = *it1;
            if(currCard->run_value == 11)
                jack_suits.push_front(currCard->i_suit);
            it1++;
        }
        it2 = jack_suits.begin();
        while(it2 != jack_suits.end()){
            currSuit = *it2;
            weighted_nobs_score += (13.0 - (float) count_cards_of_suit(hand, currSuit) - (float) count_cards_of_suit(discard_hand, currSuit))/46.0;
            it2++;
        }
    }
    return weighted_nobs_score;
}

//benchmarking function
//arguments must be a deck and an already dealt hand
//function will print the hand of each player, number of points,
//and the time it took to calculate the score of each hand
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

//returns the weighted value of the hand
//this doesnt account for flushes yet?
float calculate_weighted_hand_value(list<Card*> hand){
    Card* currCard;
    currCard = new Card;
    list<Card*>::iterator it;
    int numCalcs = 0;
    float weighted_value = 0.0;
    int cumulative_score = 0;
    for(int i = 1; i <=13; i++){
        currCard->value = i;
        currCard->run_value = i;
        if(currCard->value > 10)
            currCard->value = 10;
        switch(i){
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
        hand.push_back(currCard);
        hand.sort(compare_cardvalue);
        //print_hand(hand);
        it = hand.begin();
        cumulative_score += 2*count_fifteens_trim(numCalcs,0, hand, it) + 2*count_pairs(hand) + count_runs(hand);
        
        //remove the hypothetical cut card
        it = hand.begin();
        while(it != hand.end()){
            currCard = *it;
            if(currCard->suit.empty())
                break;
            it++;
        }
        hand.remove(currCard);
    }

    weighted_value = (float)cumulative_score / 13.0;

    return weighted_value;
}

//optimal hand and discard hand should come in empty and will be populated by the function
//hand is the 6 card hand dealt to the player
//there should be some quality check of arguments for this function
//the hand will have cards ordered 1-2-3-4-5-6, for future comments
void choose_optimal_hand(list<Card*> hand, list<Card*> *optimal_hand, list<Card*> *discard){
    list<Card*> discard_stage, optimal_hand_stage;
    float highest_score = 0.0, current_score = 0.0;
    int suit_count = 0, suit = -1;

    //trimming effort, check if there is a flush possibility
    //with 6 cards, there can't be more than one suit with
    //possible flush
    for(int i=0; i < 4; i++){
        suit_count = count_cards_of_suit(hand, i);
        if(suit_count >= 4){
            suit = i;
            break;
        }
    }

    int factorial_iterator =   HAND_SIZE - 1;
    list<Card*>::iterator it;
    it = hand.begin();
    while(it != hand.end()){
        optimal_hand_stage.push_back(*it);
        it++;
    }

    discard_stage.push_back(optimal_hand_stage.front());
    optimal_hand_stage.pop_front();
    discard_stage.push_back(optimal_hand_stage.front());
    optimal_hand_stage.pop_front();

    //the first discard/hand combination tried is 1-2 / 3-4-5-6 
    //each outer loop will switch the first card of the discard combo
    //the inner loop swaps out the other discard until all combos are checked
    //the inner loop uses factorial to prevent repeating a hand/discard combination
    for(int i=0; i<(HAND_SIZE-1); i++){
        current_score = calculate_weighted_hand_value(optimal_hand_stage);
        current_score += count_weighted_points_nobs(optimal_hand_stage, discard_stage);
        if(suit!=-1){
            if(count_cards_of_suit(optimal_hand_stage, suit) == 4)
                current_score += 4 + ((13-suit_count) / 52);
        }
        if(current_score > highest_score){
            highest_score = current_score;
            optimal_hand->clear();
            discard->clear();
            it = optimal_hand_stage.begin();
            while(it != optimal_hand_stage.end()){
                optimal_hand->push_back(*it);
                it++;
            }

            it = discard_stage.begin();
            while(it != discard_stage.end()){
               discard->push_back(*it);
                it++;
            }
        }
        //print_hand(discard_stage);

        //now we rotate the card combinations without changing order
        //on the first iteration of the outer loop, these 5 combos are checked:
        //1-2 / 3-4-5-6 (already checked above)
        //1-3 / 4-5-6-2
        //1-4 / 5-6-2-3
        //1-5 / 6-2-3-4
        //1-6 / 2-3-4-5
        for(int j=0; j<(factorial_iterator-1); j++){
            //this is where we would calculate the scoring potential
            //of each combination
            optimal_hand_stage.push_back(discard_stage.back());
            discard_stage.pop_back();
            discard_stage.push_back(optimal_hand_stage.front());
            optimal_hand_stage.pop_front();
            current_score = calculate_weighted_hand_value(optimal_hand_stage);
            current_score += count_weighted_points_nobs(optimal_hand_stage, discard_stage);
            if(suit!=-1){
                if(count_cards_of_suit(optimal_hand_stage, suit) == 4)
                    current_score += 4 + ((13-suit_count) / 52);
            }
            if(current_score > highest_score){
                highest_score = current_score;
                optimal_hand->clear();
                discard->clear();
                it = optimal_hand_stage.begin();
                while(it != optimal_hand_stage.end()){
                    optimal_hand->push_back(*it);
                    it++;
                }

                it = discard_stage.begin();
                while(it != discard_stage.end()){
                    discard->push_back(*it);
                    it++;
                }
            }
            //print_hand(discard_stage);
        }
        optimal_hand_stage.push_back(discard_stage.back());
        discard_stage.pop_back();

        //at this point your discard_stage should only have the master
        //discard card used for this outer loop, and optimal hand will have
        //the other cards in order

        for(int k = 0; k < (HAND_SIZE - 1 - factorial_iterator); k++){
            optimal_hand_stage.push_back(optimal_hand_stage.front());
            optimal_hand_stage.pop_front();
        }



        optimal_hand_stage.push_back(discard_stage.back());
        discard_stage.pop_back();

        //now all cards are in optimal_hand_stage, in order,
        //the front card will be the next master discard card
        //after the first iteration of outer loop, the order 
        //is 2-3-4-5-6-1, for example

        discard_stage.push_back(optimal_hand_stage.front());
        optimal_hand_stage.pop_front();
        discard_stage.push_back(optimal_hand_stage.front());
        optimal_hand_stage.pop_front();

        //ready for the next iteration... at this point, in order,
        //for successive loop iterations the lists will look like this:
        //2-3 / 4-5-6-1
        //3-4 / 5-6-1-2
        //4-5 / 6-1-2-3
        //5-6 / 1-2-3-4
        //... we don't need 6 as the master card, because it's already
        //been combined with every other possible card in the discard

        factorial_iterator--;
    }
    
}

//Ignore flushes, because the possibility of a flush is so low for the crib
//create all combinations of 5 cards that exist, minus the case where all
//5 cards match because it doesn't exist (13^5 - 13)
//We are interested in weighting the scoring potential of 13^2 = 169
//different discard combinations, so print in CSV format the first two
//cards in the combo followed by the weighting score of all 13^3 = 2197
//combos of the other 3 cards (opponents discarded cards and cut card)
void calculate_discard_lookup_table(void){
    
    Card* currCard;
    list<Card*> hand, sorted_hand;
    list<Card*>::iterator it; 
    int prev_value = 0; //for checking for impossible situations to skip
    int numCalcs = 0;
    float weighted_score = 0.0, fifteens = 0.0, pairs = 0.0, runs = 0.0, nobs = 0.0;

    const float NUM_COMBOS = 2196.0; 13^3 - 1;
    //create the cards and hand array

    ofstream myFile("crib_lookup.csv");
    for(int i =0;i<5;i++){
            currCard = new Card;
            hand.push_back(currCard);
    }

    
    for(int a=1; a <=13; a++){
        it = hand.begin();
        currCard = *it;
        currCard->value = a;
        currCard->run_value = a;
        if(a > 10)
            currCard->value = 10;
        
        for(int b=1; b <=13; b++){
            it = hand.begin();
            it++;
            currCard = *it;
            currCard->value = b;
            currCard->run_value = b;
            if(b > 10)
                currCard->value = 10;            
            weighted_score = 0.0;
            
            for(int c=1; c <=13; c++){
                it = hand.begin();
                it++; it++;
                currCard = *it;
                currCard->value = c;
                currCard->run_value = c;
                if(c > 10)
                    currCard->value = 10;
                
                for(int d=1; d <=13; d++){
                    it = hand.begin();
                    it++; it++; it++;
                    currCard = *it;
                    currCard->value = d;
                    currCard->run_value = d;
                    if(d > 10)
                        currCard->value = 10;
                    
                    for(int e=1; e <=13; e++){
                        it = hand.begin();
                        it++; it++; it++; it++;
                        currCard = *it;
                        currCard->value = e;
                        currCard->run_value = e;
                        if(e > 10)
                            currCard->value = 10;
                        prev_value = e;
                        it = hand.begin();
                        while(it != hand.end()){
                            currCard = *it;
                            if(currCard->run_value != prev_value)
                                break;
                            else
                                it++;
                        }
                        if(it == hand.end())
                            continue;   //all cards have the same value, i.e. this hand contains 5 cards of the same type which doesn't exist
                        
                        sorted_hand = hand;
                        sorted_hand.sort(compare_cardvalue);
                        it = sorted_hand.begin();
                        fifteens = 2.0*count_fifteens_trim(numCalcs,0, sorted_hand, it);
                        pairs = 2.0*count_pairs(sorted_hand);
                        runs = (float)count_runs(sorted_hand);
                        nobs = 0.25*count_cards_by_symbol(sorted_hand,11);    //not going to count flushes because they are so rare in the crib
                        weighted_score += fifteens + pairs + runs + nobs;
                    }// end of 5th card
                }//end of 4th card
            }//end of 3rd card
            weighted_score = weighted_score / NUM_COMBOS;
            myFile<<a<<","<<b<<","<<weighted_score<<"\n";
        }//end of 2nd card
    }//end of 1st card  
    myFile.close();                
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

    /*
    count_points_benchmark(&deck, myHand, opponentHand);

    print_hand(myHand);

    choose_optimal_hand(myHand,&optimal_hand, &discard);

    cout<<"Optimal hand: \n";
    print_hand(optimal_hand);

    cout<<"Discard cards: \n";
    print_hand(discard);
    */

    //calculate_discard_lookup_table();

    //start gameplay:

    return 0;
}