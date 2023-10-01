//
// Created by jaxru on 9/13/2023.
//

#include "Test.h"
#include <iostream>
using namespace std;
#define S 6 //Spades symbol
#define H 3 //Hearts symbol
#define D 4 //Diamond symbol
#define C 5 //Club symbol

//Define necessary paramters for the deck of cards and string
#define CARDS 52
#define SSIZE 50
//Open Structure

class cards{
public:
    char suit;
    int face;
    cards* next;

    cards(){
        suit = 0;
        face = 0;
        next = nullptr;
    }
    cards(int face, char suit){
        this->face = face;
        this->suit = suit;
        this->next = nullptr;
    }

};

class Deck{
    cards* deck;

public:
    Deck(){this->deck = nullptr;}

    void CreateDeck(){
        for (int i = 3; i <= 6; i++) {
            for (int j = 1; j <= 13; j++) {
                addCard(j,i);
            }
        }
    }

    void addCard(int face, char suit){
        auto* card = new cards(face, suit);
        card->next = deck;
        deck = card;
    }
    cards* getCards(){
        return this->deck;
    }

    void printDeck(){
        cards* temp = this->deck;
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

};

class Player{
    cards* playerDeck;
    cards* theCards;

public:
    explicit Player(Deck* obj){
        this->playerDeck = nullptr;
        this->theCards = obj->getCards();
    }

    //Open Hand function that will transfer 2 cards from the original deck's tail into another linked list
    void dealCards() {
        cards* temp=nullptr;
        //Set the new linked list equal to the head of the original linked list containing the deck
        cards* currDeck = this->theCards;

        for (int i = 0; i < 2; i++) {
            if (temp == nullptr) {//make hand point to the location that temp points to
                this->playerDeck = currDeck;
            } else {
                //make next pointer member of tail point to temp
                temp->next = currDeck;
            }
            temp = currDeck;// updating tail
            currDeck = currDeck->next;// setting next pt. of tail to null.
        }

        //Update the shuffled deck so that the cards are now within the player's hand and not within the original linked list
        temp->next = nullptr;
        this->theCards = currDeck;

        //Checks the number of cards in the Deck
        //If done correctly, number should be 52 - 2*(number of players)
        //If one player was dealt, should be 52-2 cards
        //If two players, should be 52 - 4 cards

    }

    void countDeckCardsRemaining(){
        int count = 0;
        cards* current = this->theCards;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        cout << "current amount of cards in the deck is "<< count << endl;
    }

    void addOneCard(){
        cards* temp=this->playerDeck;
        cards* currDeck = this->theCards;
        //Set the new linked list equal to the head of the original linked list containing the deck
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = currDeck;
        currDeck = currDeck->next;
        temp->next->next = nullptr;
        this->theCards = currDeck;
    }

    void printCards(){
        cards* temp = this->playerDeck;
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


};

//void LL::printCards(LL* head) {
//    //Declare variables used within the function
//    cards* temp;
//    cards* temp1;
//    cards* temp2;
//    int count = 0;
//    //Make temp equal the head of the node
//    temp = head;
//    temp1 = head;
//    temp2 = head;
//
//    //Iterate while loop untill temp2 has reached the end of the linked list
//    while (temp2 != nullptr) {
//
//        //Open for loop to print the cards
//        for (int i = 0; i < 5; i++) {
//
//            if (count == 0) {//If the counter is zero, print the first line of the cards
//
//                //Open for loop to print all the top parts of the five cards within the same line
//                for (int j = 0; j < 5; j++) {
//                    cout << " _________     ";
//                }
//            }
//            else if (count == 1) {//If the counter is one, print second line of the cards
//
//                //Open another for loop for the first part of the cards with the face and suit
//                for (int j = 0; j < 5; j++) {
//                    if (temp->face == 11) {//If the face value is a eleven, print the Jack symbol and its corresponding suit
//                        cout << "|J" << temp->suit << "       |    ";
//                    }
//                    else if (temp->face == 12) {//If the face value is a twelve, print the Queen symbol and its corresponding suit
//                        cout << "|Q" << temp->suit << "       |    ";
//                    }
//                    else if (temp->face == 13) {//If the face value is a thirteen, print the King symbol and its corresponding suit
//                        cout << "|K" << temp->suit << "       |    ";
//
//                    }
//                    else if (temp->face == 1) {//If the face value is a one, print the Ace symbol and its corresponding suit
//                        cout << "|A" << temp->suit << "       |    ";
//
//                    }
//                    else if (temp->face == 10) {//If the face value is a ten, print the number ten with its adjusted spaces and its corresponding suit
//                        cout << "|"<<temp->face << temp->suit << "       |    ";
//
//                    }
//                    else {//If the face value is a ten, print the number ten with its adjusted spaces and its corresponding suit
//                        cout << "|"<<temp->face << temp->suit << "        |    ";
//
//                    }
//                    //After loop makes one cycle, make the list (temp) point to the next card
//                    temp = temp->next;
//                }
//            }
//            else if (count == 2 || count == 3) {//If the counter is a either two or three, print the third and fourth part of the card
//
//                //Open for loop to print the first part of the body of the five cards within the same line
//                for (int j = 0; j < 5; j++) {
//                    cout << "|         |    ";
//                }
//            }
//            else if (count == 4) {//If the counter is a four, print the middle of the card
//
//                //Open for loop to print the middle of the cards and their corresponding suit within the same line
//                for (int j = 0; j < 5; j++) {
//                    cout << "|    " << temp->suit << "    |    ";
//                    //Make the second pointer (temp1) point to the next card
//                    temp1 = temp1->next;
//                }
//            }
//            else if (count == 5 || count == 6) {//If the counter is either a five or six, print the sixth and seventh part of the card
//
//                //Open for loop to print the second part of the body of the five cards within the same line
//                for (int j = 0; j < 5; j++) {
//                    cout << "|         |    ";
//                }
//            }
//            else if (count == 7) {//If counter is seven, print the last part of the cards
//                //Open for loop for the last part of the cards with the face and suit
//                for (int j = 0; j < 5; j++) {
//                    if (temp2->face == 11) {//If the face value is a eleven, print the Jack symbol and its corresponding suit
//                        cout << "|_______J"<< temp2->suit << "|    ";
//                    }
//                    else if (temp2->face == 12) {//If the face value is a twelve, print the Queen symbol and its corresponding suit
//                        cout << "|_______Q"<< temp2->suit << "|    ";
//                    }
//                    else if (temp2->face == 13) {//If the face value is a thirteen, print the King symbol and its corresponding suit
//                        cout << "|_______K"<< temp2->suit << "|    ";
//                    }
//                    else if (temp2->face == 1) {//If the face value is a one, print the Ace symbol and its corresponding suit
//                        cout << "|_______A"<< temp2->suit << "|    ";
//                    }
//                    else if (temp2->face == 10) {//If the face value is a ten, print the number ten with its adjusted spaces and its corresponding suit
//                        cout << "|_______"<<temp2->face << temp2->suit << "|    ";
//                    }
//                    else {//If the face value is between two to nine, print the numbers with their adjusted spaces and its corresponding suit
//                        cout << "|_______"<<temp2->face << temp2->suit << "|    ";
//                    }
//                    //Make the third pointer (temp2) point to the next card
//                    temp2 = temp2->next;
//                }
//            }
//            //Iterate counter
//            count++;
//            //Print Newline in order to move into the next row of the lines
//            printf("\n");
//        }
//    }
//
//}

int main() {
    Deck *deck = new Deck();
    deck->CreateDeck();
//    deck->addCard(1,3);
//    deck->addCard(13,4);
//    deck->addCard(12,5);
//    deck->addCard(11,6);
//    deck->addCard(1,3);
//    deck->addCard(13,4);
    auto *player1 = new Player(deck);
    auto *player2 = new Player(deck);
    player1->countDeckCardsRemaining();
    deck->printDeck();
    cout << "adding cards..." << endl;
    player1->dealCards();
    cout << "Player 1's hand" << endl;
    player1->printCards();
    player1->countDeckCardsRemaining();
    deck->printDeck();

////    deck->removeCard();
////    deck->removeCard();
//
//    cout << "adding cards..." << endl;
//    player2->dealCards();
//    cout << "Player 2's hand" << endl;
//    player2->printCards();
//    player2->countDeckCardsRemaining();
//    player2->printDeck();
//
////    deck->removeCard();
////    deck->removeCard();
//
//    cout << "adding cards..." << endl;
//    player1->addOneCard();
//    cout << "Player 1's hand" << endl;
//    player1->printCards();
//    player1->countDeckCardsRemaining();
//    deck->printDeck();
////    deck->removeCard();
//
//    cout << "adding cards..." << endl;
//    player2->addOneCard();
//    cout << "Player 2's hand" << endl;
//    player2->printCards();
//    player2->countDeckCardsRemaining();
//    player2->printDeck();
////    deck->removeCard();
//
//    cout << "adding cards..." << endl;
//    player1->addOneCard();
//    cout << "Player 1's hand" << endl;
//    player1->printCards();
//    player1->countDeckCardsRemaining();
//    player1->printDeck();
////    deck->removeCard();
//
//    cout << "adding cards..." << endl;
//    player2->addOneCard();
//    cout << "Player 2's hand" << endl;
//    player2->printCards();
//    player2->countDeckCardsRemaining();
//    player2->printDeck();
//    deck->removeCard();
    return 0;

}

