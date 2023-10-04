//
// Created by Jackson Burns and Jose Juan Velasquez on 9/30/2023.
//


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

typedef struct cards {
    char suit;
    int face;
    struct cards* next;
} cards;

//The structure in charge of the root node of a tree.
typedef struct card_deck{
    cards* root; //Will be the pointer pointing to the root node of a tree.
    int size;
}card_deck;


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
    if(card== nullptr){
        free(card);
        return;
    } else{
        clearCard(card->next);
    }
    free(card);
}

void clearDeck(card_deck* deck){
    if(deck->root != nullptr){
        clearCard(deck->root);
    }
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
void SwapCards(cards *cardOne, cards *cardTwo) {
    cards temp;
    temp.suit = cardOne->suit;
    temp.face = cardOne->face;

    cardOne->suit = cardTwo->suit;
    cardOne->face = cardTwo->face;
    cardTwo->suit = temp.suit;
    cardTwo->face = temp.face;
}

void shuffleDeck(cards *deck) {
    cards* card1, * card2;
    srand( time(nullptr));

    for (int i = 0; i < 52; i++){
        int randCard1 = rand() % 52;
        card1 = deck;

        for (int j = 0; j < randCard1; j++) {
            card1 = card1->next;
        }

        int randCard2 = rand() % 52;
        card2 = deck;

        for (int k = 0; k < randCard2; k++) {
            card2 = card2->next;
        }
        SwapCards(card1, card2);
    }
}

class Player{
    card_deck* playerDeck;
    card_deck* theCards;
    int sum;
    int money;
    bool firstDeal;

public:
    explicit Player(card_deck* obj){
        this->playerDeck = allocateDeck();
        this->theCards = obj;
        this->sum = 0;
        this->money = 100;
        this->firstDeal = true;
    }

    //Open Hand function that will transfer 2 cards from the original deck's tail into another linked list
    void dealCards() {
        cards* temp = theCards->root;
        for(int i = 0; i < 2; i++) {
            if(temp->face > 10){
                this->sum+=10;
            } else{
                this->sum+=temp->face;
            }
            LL_add_cards(this->playerDeck, temp->face, temp->suit);
            temp = temp->next;
        }
        if(this->sum > 21 && this->firstDeal){
            this->playerDeck->root = this->playerDeck->root->next->next;
            temp = theCards->root;
            for(int i = 0; i < 2; i++) {
                if(temp->face > 10){
                    this->sum+=10;
                } else{
                    this->sum+=temp->face;
                }
                LL_add_cards(this->playerDeck, temp->face, temp->suit);
                temp = temp->next;
            }
        }
        temp = this->theCards->root;
        this->theCards->root = this->theCards->root->next;
        free(temp);
        temp = this->theCards->root;
        this->theCards->root = this->theCards->root->next;
        free(temp);
        this->firstDeal=false;
    }

    void addOneCard(){
        cards *temp = this->theCards->root;
        if(temp->face > 10){
            this->sum+=10;
        } else{
            this->sum+=temp->face;
        }
        LL_add_cards(this->playerDeck, temp->face, temp->suit);
        temp = this->theCards->root;
        this->theCards->root = this->theCards->root->next;
        free(temp);
    }

    void printCardsTop(cards* temp){
        for (int j = 0; j < this->playerDeck->size; j++) {
            if (temp->face == 11) {//If the face value is a eleven, print the Jack symbol and its corresponding suit
                cout << "|J"<<temp->suit << "       |\t";
            }
            else if (temp->face == 12) {//If the face value is a twelve, print the Queen symbol and its corresponding suit
                cout << "|Q"<<temp->suit << "       |\t";
            }
            else if (temp->face == 13) {//If the face value is a thirteen, print the King symbol and its corresponding suit
                cout << "|K"<<temp->suit << "       |\t";
            }
            else if (temp->face == 1) {//If the face value is a one, print the Ace symbol and its corresponding suit
                cout << "|A"<<temp->suit << "       |\t";
            }
            else if (temp->face == 10) {//If the face value is a ten, print the number ten with its adjusted spaces and its corresponding suit
                cout << "|"<<temp->face<<temp->suit << "      |\t";
            }
            else {//If the face value is between two to nine, print the numbers with their adjusted spaces and its corresponding suit
                cout << "|"<<temp->face<<temp->suit << "       |\t";
            }
            //After loop makes one cycle, make the list (temp) point to the next card
            temp = temp->next;
        }
        cout << endl;
    }

    void printCardsBottom(cards* temp2){
        //Open for loop for the last part of the cards with the face and suit
        for (int j = 0; j < this->playerDeck->size; j++) {

            if (temp2->face == 11) {//If the face value is a eleven, print the Jack symbol and its corresponding suit
                cout<< "|_______J"<< temp2->suit<<"|\t";
            }
            else if (temp2->face == 12) {//If the face value is a twelve, print the Queen symbol and its corresponding suit
                cout<<"|_______Q"<< temp2->suit<<"|\t";
            }
            else if (temp2->face == 13) {//If the face value is a thirteen, print the King symbol and its corresponding suit
                cout<<"|_______K"<< temp2->suit<<"|\t";;
            }
            else if (temp2->face == 1) {//If the face value is a one, print the Ace symbol and its corresponding suit
                cout<<"|_______A"<< temp2->suit<<"|\t";;
            }
            else if (temp2->face == 10) {//If the face value is a ten, print the number ten with its adjusted spaces and its corresponding suit
                cout<<"|_______" <<temp2->face<<temp2->suit<<"|\t";;
            }
            else {//If the face value is between two to nine, print the numbers with their adjusted spaces and its corresponding suit
                cout<<"|_______"<< temp2->face<< temp2->suit<<"|\t";;
            }
            //Make the third pointer (temp2) point to the next card
            temp2 = temp2->next;
        }
        cout << endl;
    }

    void printLines(){
        for (int j = 0; j < this->playerDeck->size; j++) {
            cout << "|         |\t";
        }
        cout << endl;
    }

    void printCards() {
        cards *temp = this->playerDeck->root;
        for (int j = 0; j < this->playerDeck->size; j++) {
            cout << " _________\t";
        }
        cout << endl;
        printCardsTop(temp);
        printLines();
        printLines();
        temp = this->playerDeck->root;
        for (int j = 0; j < this->playerDeck->size; j++) {
            cout << "|    " << temp->suit << "    |\t";
            temp = temp->next;
        }
        cout << endl;
        printLines();
        printLines();
        temp = this->playerDeck->root;
        printCardsBottom(temp);
    }

    int getSum() {
        return this->sum;
    }

    int getMoney() {
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
        this->playerDeck = allocateDeck();
        this->sum = 0;
        this->theCards = deck;
    }

    void clearPlayer(card_deck *pDeck) {
        clearDeck(playerDeck);
    }
};

int main() {
    srand(time(nullptr));
    card_deck *deck = allocateDeck();
    createDeck(deck);
    shuffleDeck(deck->root);

    Player user(deck);
    Player comp(deck);
    string str;
    cout<<"********** Welcome to Blackjack! **********"<<endl;
    string bet;
    //main program loop
    bool firstRun = true;
    while(true){
        if(!firstRun){
            clearDeck(deck);
            deck = allocateDeck();
            createDeck(deck);
            shuffleDeck(deck->root);
            user.resetPlayer(deck);
            comp.resetPlayer(deck);
        }
        cout<<"***** You have "<<user.getMoney()<<" coins. *****"<<endl;
        cout<<"***** Enter number to bet. *****"<<endl;
        cin>>bet;
        while(user.bet(stoi(bet))==-1){
            cout<<"***** You only have "<<user.getMoney()<<" coins to bet, try again. *****"<<endl;
            cin>>bet;
        }
        cout<<"** You have bet " <<bet<< " coins. **";

        cout << "\n\n* giving cards to user... *\n";
        user.dealCards(); //give 2 cards
        user.printCards();

        cout << "\nuser current sum = " << user.getSum() << endl;

        cout <<"\n* giving cards to computer... *\n";
        comp.dealCards(); //give 2 cards

        while(true){
            cout<<"hit(h/H) or stay(s/S)"<<endl;
            cin>>str;
            while(str!="h"&&str!="H"&&str!="s"&&str!="S"){
                cout<<"invalid input, try again"<<endl;
                cin>>str;
            }
            if(str=="h"||str=="H"){
                cout <<"\n* giving user one card... *\n";
                user.addOneCard();
                user.printCards();
                cout << "user current sum = " << user.getSum() << endl;
                if(user.getSum()>21){
                    cout<<"*** overdrew, you lose "<<bet<<" coins ***"<<endl;
                    break;
                }else if (user.getSum()==21){ //exactly 21
                    cout << "Computer's hand:\n";
                    comp.printCards();
                    cout << "computer's final sum = " << comp.getSum() << endl;
                    cout<<"*** You win "<<bet<< " coins! ***"<<endl;
                    user.addMoney(2*(stoi(bet)));
                    //firstRun=false;
                    break;
                }
                else{
                    continue;
                }
            }
            else { //stay
                while(comp.getSum()<17){
                    cout<<"* computer is drawing *"<<endl;
                    comp.addOneCard();
                }
                //win condition

                if(comp.getSum()>21||comp.getSum()<user.getSum()){
                    cout << "Computer's hand:\n";
                    comp.printCards();
                    cout << "computer's final sum = " << comp.getSum() << endl;
                    cout<<"*** YOU WIN "<<bet<<" COINS ***"<<endl;
                    user.addMoney(2*stoi(bet));
                }
                else if (comp.getSum()==user.getSum()){
                    cout << "Computer's hand:\n";
                    comp.printCards();
                    cout << "computer's final sum = " << comp.getSum() << endl;
                    cout<<"*** TIE. returning your money ***"<<endl;
                    user.addMoney(stoi(bet));
                }
                else{
                    cout << "Computer's hand:\n";
                    comp.printCards();
                    cout << "computer's final sum = " << comp.getSum() << endl;
                    cout<<"*** YOU LOST "<<bet<<" COINS ***"<<endl;
                }
                break;
            }

        }
        cout<<"play again? (y/n)"<<endl;
        cin>>str;
        while(str!="n"&&str!="N"&&str!="y"&&str!="Y"){
            cout<<"You entered an invalid option";
            cin>>str;
        }
        if(str=="n"||str=="N"){
            cout<<"***** Goodbye. *****"<<endl;
            clearDeck(deck);
            user.clearPlayer(deck);
            comp.clearPlayer(deck);
            return 0;
        }
        else{
            firstRun=false;
            continue;
        }
    }
    //Pending Jackson: Freeing memory after a game ends, adding coin system, win/lose conditions (must count A as either 1 or 11 depending on current sum), shuffle cards
    //Pending JJ: Improve printing, creating console game after everything is done, more?

}