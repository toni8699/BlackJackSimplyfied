#ifndef BLACKJACK_H_
#define BLACKJACK_H_
#include <vector>
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


class Hand{
    public:
    void add(Card);
    void clear();
    int getTotal()const;
    void printCards();
    private:
    std::vector<Card> Cards;

};

class Deck{
    public:
    // enum rank
    // {ACE = 1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};
    // enum type{CLUBS,DIAMONDS,HEARTS,SPADES};
    void populate();
    void shuffle();
    Card deal();
    private:
        vector<Card> Deck;

};

class AbstractPlayer :public Hand{
    public:
    virtual bool isDrawing()const=0;
    bool isBusted();
    private:
};
class ComputerPlayer: public AbstractPlayer{
    public:
    bool isDrawing()const override;
};
class HumanPlayer: public AbstractPlayer{
    public:
    bool isDrawing() const override;
    void announce(ComputerPlayer);
};


class BlackJackGame{
    private:
    Deck m_deck;
    ComputerPlayer m_casino;
    public:
    void play();
};


#endif