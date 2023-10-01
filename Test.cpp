//
// Created by jaxru on 9/13/2023.
//

#include "Blackjack.h"
#include <iostream>
using namespace std;

//Open Structure
card_deck* Create_deck_list(){
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
    } else{
        cards_add(tree->root,face,suit);
    }
}

void print_deck(cards* node){
    if(node->next != nullptr){
        cout << node->face << node->suit << " ";
        print_deck(node->next);
    }
}

void CreateDeck(card_deck* deck){
    for (int i = 3; i <= 6; i++) {
        for (int j = 1; j <= 13; j++) {
            LL_add_cards(deck ,j,i);
        }
    }
}

class Player{
    card_deck* playerDeck;
    cards* theCards;
    int sum;

public:
    explicit Player(cards* obj){
        this->playerDeck = Create_deck_list();
        this->theCards = obj;
        this->sum = 0;
    }

    //Open Hand function that will transfer 2 cards from the original deck's tail into another linked list
    void dealCards() {
        cards* temp = theCards;
        for(int i = 0; i < 2; i++) {
            this->sum+=temp->face;
            LL_add_cards(this->playerDeck, temp->face, temp->suit);
            temp = temp->next;
        }
        temp = theCards;
        this->theCards = this->theCards->next;
        free(temp);
        temp = theCards;
        this->theCards = this->theCards->next;
        free(temp);
    }

    void addOneCard(){
        cards *temp = this->theCards;
        this->sum+=temp->face;
        LL_add_cards(this->playerDeck, temp->face, temp->suit);
        this->theCards = this->theCards->next;
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
        return this->theCards;
    }

    void setCards(cards* obj){
        this->theCards = obj;
    }

    int getSum(){
        return this->sum;
    }
};



int main() {
    cout << "creating deck\n";
    card_deck *deck = Create_deck_list();
    CreateDeck(deck);
    print_deck(deck->root);

    cout << "\n\ngiving cards to user...\n";
    Player user(deck->root);
    user.dealCards();
    user.printCards();
    deck->root = user.getCards();
    print_deck(deck->root);
    cout << "\ncurrent sum = " << user.getSum() << endl;

    cout <<"\ngiving cards to computer...\n";
    Player comp(deck->root);
    comp.dealCards();
    comp.printCards();
    deck->root = comp.getCards();
    print_deck(deck->root);
    cout << "\ncurrent sum = " << comp.getSum() << endl;

    cout <<"\ngiving user one card...\n";
    user.setCards(deck->root);
    user.addOneCard();
    user.printCards();
    deck->root = user.getCards();
    print_deck(deck->root);
    cout << "\ncurrent sum = " << user.getSum() << endl;

    cout <<"\ngiving comp one card...\n";
    comp.setCards(deck->root);
    comp.addOneCard();
    comp.printCards();
    deck->root = comp.getCards();
    print_deck(deck->root);
    cout << "\ncurrent sum = " << comp.getSum() << endl;

    return 0;

}

