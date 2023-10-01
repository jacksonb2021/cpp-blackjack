//
// Created by josej on 9/30/2023.
//

#ifndef PROJECT_1_BLACKJACK_H
#define PROJECT_1_BLACKJACK_H

#endif //PROJECT_1_BLACKJACK_H

typedef struct cards {
    char suit;
    int face;
    struct cards* next;
} cards;

//The structure in charge of the root node of a tree.
typedef struct card_deck{
    cards* root; //Will be the pointer pointing to the root node of a tree.
}card_deck;


card_deck* Create_deck_list();

cards* cards_node_create(int face, char suit);

void cards_add(cards* node, int face, char suit);

void LL_add_cards(card_deck * tree, int face, char suit);

void print_deck(cards* node);
