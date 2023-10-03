//
// Created by Jackson Burns and Jose Juan Velasquez on 9/30/2023.
//

#include "Blackjack.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

//Open Structure
card_deck* allocateDeck(){
    auto* list = (card_deck*)calloc(1, sizeof(card_deck));
    return list;
}
cards* cards_node_create(int face, char suit){
    auto* node = (cards*)calloc(1,sizeof(cards));
    node->suit = suit;
    node->face = face;
    node->next = nullptr;
    return node;
}

void clearCard(cards* card){

    //Declare variables used within the function
    cards* temp = card;

    //Open while loop that loops until it reached the end of the list
    while (card != nullptr) {
        temp = card;
        //Make the current head point to the next card
        card = card->next;
        //De-allocate the previous card
        delete temp;
        //Point to the next card to repeat cycle

    }
}

void clearDeck(card_deck* deck){
    if(deck->root != nullptr){
        clearCard(deck->root);
    }
    delete deck;
}

void cards_add(cards* node, int face, char suit){
    if(node->next != nullptr){
        cards_add(node->next, face, suit);
    } else {
        cards* newNode = cards_node_create(face,suit);
        node->next = newNode;
    }
}

void LL_add_cards(card_deck * tree, int face, char suit){
    if(tree->root == nullptr){
        tree->root = cards_node_create(face,suit);
        tree->size++;
    } else{
        cards_add(tree->root,face,suit);
        tree->size++;
    }
}

void print_deck(cards* node){
    if(node->next != nullptr){
        cout << node->face << node->suit << " ";
        print_deck(node->next);
    }else{
        cout<<endl;
    }
}

void createDeck(card_deck* deck){
    for (int i = 3; i <= 6; i++) {
        for (int j = 1; j <= 13; j++) {
            LL_add_cards(deck ,j,i);
        }
    }
}
void SwapCards(cards *cardOne, cards *cardTwo) {
    //Declare variables used within the function
    cards temp;

    //Make the temp variable equal the random card created in the Shuffle function
    temp.suit = cardOne->suit;
    temp.face = cardOne->face;

    //Swap card1 and card2 using the temp variable
    cardOne->suit = cardTwo->suit;
    cardOne->face = cardTwo->face;
    cardTwo->suit = temp.suit;
    cardTwo->face = temp.face;
}

void shuffleDeck(cards *deck) {
    //Declare variables used within the function
    cards* card1, * card2;
    int i;
    srand((unsigned int) time(nullptr));

    //Open for loop in order to iterate the number of cards present, which is 52
    for (i = 0; i < 52; i++)
    {
        //Declare a variable that conatins the random number generator
        int randCard1 = rand() % 52;
        //Make one of the declared structure variables equal the head of the node
        card1 = deck;

        //Open for loop that iterates the random number generated that is stored within the variable
        for (int j = 0; j < randCard1; j++) {
            //Make the card1 variable equal the next card number until it iterates the number that was randomly generated
            card1 = card1->next;
        }
        //Declare a variable that conatins the random number generator
        int randCard2 = rand() % 52;
        //Make one of the declared structure variables equal the head of the node
        card2 = deck;

        //Open for loop that iterates the random number generated that is stored within the variable
        for (int k = 0; k < randCard2; k++) {
            //Make the card2 variable equal the next card number until it iterates the number that was randomly generated
            card2 = card2->next;
        }
        //Now that we have two random cards, we call the SwapCards function to swap their locations
        SwapCards(card1, card2);

    }

}

class Player{
    card_deck* playerDeck;
    card_deck* theCards;
    int sum;
    int money;

    public:
        explicit Player(card_deck* obj){
            this->playerDeck = allocateDeck();
            this->theCards = obj;
            this->sum = 0;
            this->money = 100;
        }

        //Open Hand function that will transfer 2 cards from the original deck's tail into another linked list
        void dealCards() {
            cards* temp = theCards->root;
            for(int i = 0; i < 2; i++) {
                this->sum+=temp->face;
                LL_add_cards(this->playerDeck, temp->face, temp->suit);
                temp = temp->next;
            }
            this->theCards->root = this->theCards->root->next->next;
        }

        void addOneCard(){
            cards *temp = this->theCards->root;
            this->sum+=temp->face;
            LL_add_cards(this->playerDeck, temp->face, temp->suit);
            this->theCards->root = this->theCards->root->next;
            //free(temp);
        }

        void printCards(){
            //cout<<endl;
            cards* temp = this->playerDeck->root;
            while(temp != nullptr) {
                if (temp->face == 13) {
                    cout << "K";
                    cout << temp->suit;
                } else if (temp->face == 12) {
                    cout << "Q";
                    cout << temp->suit;
                }
                else if (temp->face == 11) {
                    cout << "J";
                    cout << temp->suit;
                }
                else if (temp->face == 1) {
                    cout << "A";
                    cout << temp->suit;
                }
                else{
                    cout << temp->face;
                    cout << temp->suit;
                }
                temp = temp->next;
            }
            cout<<endl;
        }
//        card_deck* getDeck(){
//            return this->theCards;
//        }
//
//        void setCards(card_deck * obj){
//            clearDeck(theCards);
//            this->theCards = obj;
//        }

        int getSum(){
            return this->sum;
        }

        int getMoney(){
            return this->money;
        }

        //bets money. if there is enough money, the bet will be returned.
        // if not enough money, it will return -1
        int bet(int val){
            if(this->money<val){
                return -1;
            }
            else{
                this->money-=val;
                return val;
            }
        }

        void addMoney(int val){
            this->money+=val;
        }

        void resetPlayer(card_deck * deck){
            clearDeck(playerDeck);
            playerDeck = allocateDeck();
            this->sum = 0;
            this->theCards = deck;
        }
};

int main() {
    srand(time(nullptr));

    cout << "creating deck\n";
    card_deck *deck = allocateDeck();
    createDeck(deck);
    shuffleDeck(deck->root);
    print_deck(deck->root);
    cout<<deck->size;

    Player user(deck);
    Player comp(deck);
    string str;
    cout<<"welcome to blackjack"<<endl;
    string bet;
    //main program loop
    bool firstRun = true;
    while(true){
        if(!firstRun){
            print_deck(deck->root);
            clearDeck(deck);
            deck = allocateDeck();
            createDeck(deck);
            shuffleDeck(deck->root);
            user.resetPlayer(deck);
            comp.resetPlayer(deck);
        }
        cout<<"you have "<<user.getMoney()<<" coins"<<endl;
        cout<<"enter number to bet"<<endl;
        cin>>bet;
        while(user.bet(stoi(bet))==-1){
            cout<<"you only have "<<user.getMoney()<<" coins to bet, try again"<<endl;
            cin>>bet;
        }
        cout<<"you have bet " <<bet<< " coins";

        cout << "\n\ngiving cards to user...\n";
        user.dealCards(); //give 2 cards
        user.printCards();

        cout << "\n user current sum = " << user.getSum() << endl;

        cout <<"\ngiving cards to computer...\n";
        comp.dealCards(); //give 2 cards
        comp.printCards();

        cout << "\n computer current sum = " << comp.getSum() << endl;

        while(true){
            cout<<"hit(h/H) or stay(s/S)"<<endl;
            cin>>str;
            while(str!="h"&&str!="H"&&str!="s"&&str!="S"){
                cout<<"invalid input, try again"<<endl;
                cin>>str;
            }
            if(str=="h"||str=="H"){
                cout <<"\ngiving user one card...\n";
                user.addOneCard();
                user.printCards();
                cout << "current sum = " << user.getSum() << endl;
                if(user.getSum()>21){
                    cout<<"overdrew, you lose "<<bet<<" coins"<<endl;
                    break;
                }else if (user.getSum()==21){ //exactly 21
                    cout<<"you win "<<bet<< " coins!"<<endl;
                    user.addMoney(2*(stoi(bet)));
                    firstRun=false;
                    break;

                }
                else{
                    continue;
                }
            }
            else { //stay
                while(comp.getSum()<17){
                    cout<<"computer is drawing"<<endl;
                    //comp.setCards(deck);
                    comp.addOneCard();
                    comp.printCards();

                }
                //win condition

                if(comp.getSum()>21||comp.getSum()<user.getSum()){
                    cout<<"YOU WIN "<<bet<<" COINS"<<endl;
                    user.addMoney(2*stoi(bet));
                }
                else if (comp.getSum()==user.getSum()){
                    cout<<"TIE. returning your money"<<endl;
                    user.addMoney(stoi(bet));
                }
                else{
                    cout<<"YOU LOST "<<bet<<" COINS"<<endl;

                }
                break;
            }

        }

        cout<<"play again? (y/n)"<<endl;
        cin>>str;
        if(str=="n"||str=="N"){
            cout<<"You have "<<user.getMoney()<<" coins"<<endl;
            print_deck(deck->root);
            clearDeck(deck);
            return 0;
        }
        else{
            firstRun=false;
            continue;
        }


    }

//    for(int i=0;i<30;i++){
//        cout<<random(10)<<" ";
//    }





    //Pending Jackson: Freeing memory after a game ends, adding coin system, win/lose conditions (must count A as either 1 or 11 depending on current sum), shuffle cards
    //Pending JJ: Improve printing, creating console game after everything is done, more?

    return 0;

}



