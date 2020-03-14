#include"blackjack.h"
#include<iostream>
#include <ostream>
#include<vector>
#include <algorithm>
#include <random>
#include <chrono>

Card::Card(rank rank,type type){
    r = rank;
    t = type;
}
int Card::getValue(){
    int value;
    value = this->r;
    if (value >10){
        value =10;
    }
    return value;
}
void Card::displayCard()
{
    char rank;
    char type;
    switch(r)
    {
        case ACE:
            rank='A';
            break;
        case TWO:
            rank='2';
            break;
        case THREE:
            rank='3';
            break;
        case FOUR:
            rank='4';
            break;
        case FIVE:
            rank='5';
            break;
        case SIX:
            rank='6';
            break;
        case SEVEN:
            rank='7';
            break;
        case EIGHT:
            rank='8';
            break;
        case NINE:
            rank='9';
            break;
        case TEN:
            rank='T';
            break;
        case JACK:
            rank='J';
            break;
        case QUEEN:
            rank='Q';
            break;
        case KING:
            rank='K';
            break;
    }
    switch (t)
    {
        case CLUBS:
            type = 'C';
            break;
        case DIAMONDS:
            type = 'D';
            break;
        case HEARTS:
            type = 'H';
            break;
        default:
            type = 'S';
            break;
    }
    if (rank == 'T')
        cout<<10<<type<<" ";
    else{
        cout<<rank<<type<<" ";
    }
    // if ( this -> r <=10 ){
    //     cout<<r<<type<<" ";
    // }else{
    //     switch (r){
    //              case JACK:
    //         rank='J';
    //         break;
    //     case QUEEN:
    //         rank='Q';
    //         break;
    //     case KING:
    //         rank='K';
    //         break;
    // }
    //     }
    //     cout<<
    // }
}
void Hand::printCards() {
    for (Card c: Cards)
        c.displayCard();
}
void Hand::add(Card newCard){
    Cards.push_back(newCard);
}
void Hand::clear(){
    Cards.clear();
}
/* 
 add numbers in the hand, Ace take the value one if total +11 exceed 21
*/
int Hand::getTotal() const{
    int total=0;
    int Ace =0;

    for ( Card c: Cards){
        if (c.getValue()!=1){
            total +=c.getValue();
        }else{
            Ace++;                 // counting Aces
        }
    }
    while (Ace >0){
        if ( (total +11) >21){
                total+=1;
                Ace--;
        }else{
            total +=11;
            Ace--;
        }
    }
    return total;
    
}
void Deck::populate(){
    Deck.clear();
    for (Card::rank r= Card::ACE; r<=Card::KING;r= (Card::rank)(r+1)){
        for (Card::type t = Card::CLUBS; t<=Card::SPADES;t = (Card::type)(t+1)){
         //   cout<<"this is added "<<r<<" "<<t<<endl;
            Deck.push_back(Card(r,t));
        }
    }
    // for (Card c: Deck){
    //     c.displayCard();
    // }
    
}
Card Deck::deal(){  
    // for( Card c : Deck){
    //     c.displayCard();
    // }
    Card card= Deck.back();
    Deck.pop_back();
   // cout<<"Dealing this card"<<endl;
   // card.displayCard();
   // cout<<"value is "<<card.getValue()<<endl;
    card.getValue();
    return card;
}
void Deck::shuffle()
{
    srand(time(NULL));
    for (int k = 0; k < 54; k++) {
    int r = k + rand() % (54 - k);
    swap(Deck[k], Deck[r]);
}
}
bool AbstractPlayer::isBusted(){
    return getTotal()>21;
}


bool HumanPlayer::isDrawing()const{
    char yes;
    cout<<"Do you wanna draw another card? Y/N"<<endl;
    cin>>yes;
    if (yes =='Y' || yes=='y'){
        return true;
    }else{
        return false;
    }

}
void HumanPlayer::announce(ComputerPlayer Computer){
    if (Computer.getTotal() == getTotal() ){
        cout<<"Draw"<<endl;
    }
    if (Computer.getTotal() >getTotal() && !(Computer.isBusted())){
        cout<<"Computer win"<<endl;
    }
    if (Computer.getTotal() < getTotal() &&!(this -> isBusted())){
        cout<<"You win"<<endl;
    }
    }

bool ComputerPlayer::isDrawing()const{
    return getTotal()<=16;
}
void BlackJackGame::play(){
    bool cont = false; // continue drawing
    m_deck.populate();
    m_deck.shuffle();
    m_casino.clear();
    HumanPlayer player;
    player.clear();
    m_casino.add(m_deck.deal());
    player.add(m_deck.deal());
    player.add(m_deck.deal());
    cout<<"Casino: ";
    m_casino.printCards();
   cout<<"["<<m_casino.getTotal()<<"]"<<endl;
    cout<<"Player: ";
    player.printCards();
    cout<<"["<<player.getTotal()<<"]"<<endl;
   cont= player.isDrawing();
   while (cont){
       player.add(m_deck.deal());
       cout<<"Player: ";
       player.printCards();
       cout<<"["<<player.getTotal()<<"]"<<endl;
       if (player.isBusted()){
           cout<<"player busts"<<endl;
           cout<<"Casino wins"<<endl;
           return;
       }
        cont= player.isDrawing();
   }
   cont = m_casino.isDrawing();
   while(cont){
       m_casino.add(m_deck.deal());
       m_casino.printCards();
       cout<<"["<<m_casino.getTotal()<<"]"<<endl;
       if(m_casino.isBusted()){
        cout<<"Casino busts"<<endl;
        cout<<"player wins"<<endl;
        return;
       }
        cont = m_casino.isDrawing();
   }
    cout<<"Casino: ";
    m_casino.printCards();
    cout<<"["<<m_casino.getTotal()<<"]"<<endl;
    cout<<"Player: ";
    player.printCards();
    cout<<"["<<player.getTotal()<<"]"<<endl;
    player.announce(m_casino);


    
}