#include<iostream>
#include <ostream>
#include<vector>
#include <algorithm>
#include <random>
using namespace std;




 class Card
{
    public:
    enum rank
    {ACE = 1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING,Last};
    enum type{CLUBS,DIAMONDS,HEARTS,SPADES,Last};
    Card(rank, type);
    int getValue();
    void displayCard();
    private:
        rank r;
        type t;
};
Card::Card(rank rank,type type){
    r = rank;
    t = type;
}
int Card::getValue(){
    int value;
    value = r;
    if (value >10){
        value =10;
    }return value;
}
void Card::displayCard(){
    cout<<r<<t;
}

class Hand{
    public:
    void add(Card);
    void clear();
    int getTotal();
    private:
    std::vector<Card> Cards;

};
void Hand::add(Card newCard){
    Cards.push_back(newCard);
}
void Hand::clear(){
    Cards.clear();
}
/* 
 add numbers in the hand, Ace take the value one if total +11 exceed 21
*/
int Hand::getTotal(){
    int total=0;
    int Ace =0;

    for ( Card c: Cards){
        if (c.getValue!=1){
            total +=c.getValue;
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

    
}
class Deck{
    public:
    // enum rank
    // {ACE = 1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};
    // enum type{CLUBS,DIAMONDS,HEARTS,SPADES};
    void populate();
    void shuffle();
    Card deal();
    private:
        std::vector<Card> Deck;

};

void Deck::populate(){
    for (Card::rank r= Card::ACE; r!=Card::Last;r= (Card::rank)(r+1)){
        for (Card::type t = Card::CLUBS; t!=Card::Last;t = (Card::type)(t+1)){
            Deck.push_back(Card(r,t));
        }
    }
}
Card Deck::deal(){  
    Card card= Deck.back();
    Deck.pop_back();
    return card;
}
void Deck::shuffle(){

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(Deck), std::end(Deck), rng);
}

class AbstractPlayer :public Hand{
    virtual bool isDrawing()const=0;
    bool isBusted();
};

bool AbstractPlayer::isBusted(){
    return getTotal()>21;
}

int main(){
}