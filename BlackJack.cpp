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

void createDeck(card_deck* deck){
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
                int offset = random(theCards->size-1);
                cards* card = theCards->root;
                if(offset!=0){
                    for(int j=0;j<offset;j++){
                        card = card->next;
                    }
                }

                this->sum+=card->next->face;
                LL_add_cards(this->playerDeck, card->next->face, card->next->suit);
                card->next=card->next->next;
                theCards->size--;


            }

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
            //theCards->size--;
            theCards->size--;
            //this->theCards = this->theCards->next;
            free(temp);
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
        card_deck* getDeck(){
            return this->theCards;
        }
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

        void resetPlayer(){
            clearDeck(playerDeck);
            playerDeck = allocateDeck();
            this->sum = 0;
        }
};



int main() {
    srand(time(nullptr));

    cout << "creating deck\n";
    card_deck *deck = allocateDeck();
    createDeck(deck);
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
            clearDeck(deck);
            deck = allocateDeck();
            createDeck(deck);
            user.resetPlayer();
            comp.resetPlayer();


        }
        cout<<"you have "<<user.getMoney()<<" coins"<<endl;
        cout<<"enter number to bet"<<endl;
        cin>>bet;
        while(user.bet(stoi(bet))==-1){
            cout<<"you only have "<<user.getMoney()<<" coins to bet, try again"<<endl;
            cin>>bet;
        }
        cout<<"you have bet "<<bet<<"coins";

        cout << "\n\ngiving cards to user...\n";
        user.dealCards(); //give 2 cards
        user.printCards();

        print_deck(deck->root);
        cout<<"size "<<deck->size<<endl;
        cout << "\n user current sum = " << user.getSum() << endl;


        //comp.setCards(deck); //sync comp deck
        cout <<"\ngiving cards to computer...\n";
        comp.dealCards(); //give 2 cards
        comp.printCards();
        //clearCard(deck->root); //clear previous deck
        //deck = comp.getDeck(); // set deck from player deck
        print_deck(deck->root);
        cout<<"size "<<deck->size<<endl;

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
                //user.setCards(deck);
                user.addOneCard();
                user.printCards();
                //deck = user.getDeck();
                print_deck(deck->root);
                cout << "\ncurrent sum = " << user.getSum() << endl;
                if(user.getSum()>21){
                    cout<<"overdrew, you lose "<<bet<<" coins";
                    break;
                }else if (user.getSum()==21){ //exactly 21
                    cout<<"you win "<<bet<< " coins!";
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

                if(comp.getSum()<user.getSum()){
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
            clearDeck(deck);
            clearDeck(user.getDeck());
            clearDeck(comp.getDeck());
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

