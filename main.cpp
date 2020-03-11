#include<iostream>
#include <ostream>
#include<vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

 class Card
{
    public:
    enum rank
    {ACE = 1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};
    enum type{CLUBS,DIAMONDS,HEARTS,SPADES};
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
void Card::displayCard()
{
    char rank;
    char type;
    switch(r)
    {
        case ACE:
            rank='1';
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
    if (rank != 'T')
        std::cout<<rank<<type<<"\t";
    else
        std::cout<<"10"<<type<<"\t";
}

class Hand{
    public:
    void add(Card);
    void clear();
    int getTotal()const;
    void getCards();

    private:
    std::vector<Card> Cards;

};
void Hand::getCards() {
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
    Deck.clear();
    for (Card::rank r= Card::ACE; r<=Card::KING;r= (Card::rank)(r+1)){
        for (Card::type t = Card::CLUBS; t<=Card::SPADES;t = (Card::type)(t+1)){
            Deck.push_back(Card(r,t));
        }
    }
}
Card Deck::deal(){  
    // for ( Card c : Deck){
    //     c.displayCard();
    // }
    Card card= Deck.back();
    Deck.pop_back();
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

class AbstractPlayer :public Hand{
    public:
    virtual bool isDrawing()const=0;
    bool isBusted();
    private:
   // std::vector<Card> Cards;
};

bool AbstractPlayer::isBusted(){
    return getTotal()>21;
}
class ComputerPlayer: public AbstractPlayer{
    public:
    bool isDrawing()const override;
    private:
   // std::vector<Card> cCards;
};
class HumanPlayer: public AbstractPlayer{
    public:
    bool isDrawing() const override;
    void announce(ComputerPlayer);
    private:
      //  std::vector<Card> pCards;
};

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
    if (Computer.getTotal() >getTotal()){
        cout<<"Computer win"<<endl;
    }
    if (Computer.getTotal() < getTotal()){
        cout<<"You win"<<endl;
    }
    }

bool ComputerPlayer::isDrawing()const{
    return getTotal()<=16;
}
class BlackJackGame{
    private:
    Deck m_deck;
    ComputerPlayer m_casino;
    public:
    void play();
};
void BlackJackGame::play(){
    m_deck.populate();
    m_deck.shuffle();
    m_casino.clear();
    HumanPlayer human;
    human.clear();
    bool cont;
    m_casino.add(m_deck.deal());
    human.add(m_deck.deal());
    human.add(m_deck.deal());
    cout<<"Casino: ";
    m_casino.getCards();
   cout<<"["<<m_casino.getTotal()<<"]"<<std::endl;
    cout<<"Player: ";
    human.getCards();
    cout<<"["<<human.getTotal()<<"]"<<std::endl;
   
}

int main(){
    BlackJackGame game;
    game.play();
    return 0;
}