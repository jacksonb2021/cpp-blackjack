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
    auto* node = (cards*)malloc(sizeof(cards)*1);
    node->suit = suit;
    node->face = face;
    node->next = nullptr;
    return node;
}

void clearCard(cards* card){
    if(card== nullptr){
        return;
    }
    clearCard(card->next);
    free(card);

}
void clearDeck(card_deck* deck){
    clearCard(deck->root);
    free(deck);

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

void CreateDeck(card_deck* deck){
    for (int i = 3; i <= 6; i++) {
        for (int j = 1; j <= 13; j++) {
            LL_add_cards(deck ,j,i);
        }
    }
}

int random(int max){
    return rand()%max;
}

cards* seekRandom(cards* node, int random){
    if(random == 0){
        return node;
    } else {
        return seekRandom(node->next, random-1);
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

            for(int i = 0; i < 2; i++) {
                int offset = random(theCards->size);
                cards* card = theCards->root;
                if(offset!=0){
                    for(int j=0;j<offset;j++){
                        card = card->next;
                    }
                }

                this->sum+=card->next->face;
                LL_add_cards(this->playerDeck, card->next->face, card->next->suit);
                card->next=card->next->next;


//                cards* temp = theCards->root;
//                int offset = random(theCards->size);
//                cards*card = nullptr;
//                //root card
//                if(offset==0){
//                    card = temp->next;
//                    theCards->root = card;
//                    free(temp);
//
//                }
//                else{
//                    for(int j=0;j<offset-1;j++){
//                        temp = temp->next;
//                    }
//                    card = temp->next;
//                }
//
//                this->sum+=card->face;
//                LL_add_cards(this->playerDeck, card->face, card->suit);
//                temp->next = card->next;
//                theCards->size--;
//                free(card);
//                //temp = temp->next;
            }
//            temp = theCards;
//            this->theCards = this->theCards->next;
//            free(temp);
//            temp = theCards;
//            this->theCards = this->theCards->next;
//            free(temp);
        }

        void addOneCard(){
            cards *temp = this->theCards->root;
            int offset = random(theCards->size);
            for(int j=0;j<offset-1;j++){
                temp = temp->next;
            }
            cards* card = temp->next;
            this->sum+=card->face;
            LL_add_cards(this->playerDeck, card->face, card->suit);
            temp->next = card->next;
            theCards->size--;
            //this->theCards = this->theCards->next;
            free(temp);
        }

        void printCards(){
            cout<<endl;
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
        cards* getCards(){
            return this->theCards->root;
        }

        void setCards(card_deck * obj){
            this->theCards = obj;
        }

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
};



int main() {
    srand(time(nullptr));

    cout << "creating deck\n";
    card_deck *deck = allocateDeck();
    CreateDeck(deck);
    print_deck(deck->root);
    cout<<deck->size;

    Player user(deck);
    Player comp(deck);
    //main program loop
    while(true){
        string str;
        cout<<"welcome to blackjack. Press p to play, or e to exit"<<endl;
        cout<<"you have "<<user.getMoney()<<" coins"<<endl;
        cin>>str;
        if(str=="e"||str=="E"){
            break;
        }
        //TODO betting


        cout << "\n\ngiving cards to user...\n";
        user.dealCards(); //give 2 cards
        user.printCards();
        clearCard(deck->root); //clear previous cards
        deck->root = user.getCards(); // update main deck from player deck
        deck->size-=2; //decrease size by 2 for main deal
        print_deck(deck->root);
        cout << "\ncurrent sum = " << user.getSum() << endl;


        cout <<"\ngiving cards to computer...\n";
        comp.dealCards(); //give 2 cards
        comp.printCards();
        clearCard(deck->root); //clear previous deck
        deck->root = comp.getCards(); // set deck from player deck
        print_deck(deck->root);
        cout << "\ncurrent sum = " << comp.getSum() << endl;


        cout<<"hit(h/H) or stay(s/S)"<<endl;
        cin>>str;
        while(str!="h"||str!="H"||str!="s"||str!="S"){
            cout<<"invalid input, try again"<<endl;
            cin>>str;
        }
        if(str=="h"||str=="H"){

        }
        else (str=="s"||str=="S"){

        }

    }

//    for(int i=0;i<30;i++){
//        cout<<random(10)<<" ";
//    }



    cout <<"\ngiving user one card...\n";
    user.setCards(deck);
    user.addOneCard();
    user.printCards();
    deck->root = user.getCards();
    print_deck(deck->root);
    cout << "\ncurrent sum = " << user.getSum() << endl;

    cout <<"\ngiving comp one card...\n";
    comp.setCards(deck);
    comp.addOneCard();
    comp.printCards();
    deck->root = comp.getCards();
    print_deck(deck->root);
    cout << "\ncurrent sum = " << comp.getSum() << endl;

    //Pending Jackson: Freeing memory after a game ends, adding coin system, win/lose conditions (must count A as either 1 or 11 depending on current sum), shuffle cards
    //Pending JJ: Improve printing, creating console game after everything is done, more?

    return 0;

}

