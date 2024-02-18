// Author: Chris Kau
// CECS 325-02
// WAR (Prog 2 - MORE WAR)
// Due 02/27/2024
// I certify that this program is my own original work. I did not copy any part of this program from any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <array>
#include <map>
#include <string>
using namespace std;
class Card
{
	private:
		map<char, int> cvals = {{'A', 1},{'2', 2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9},{'T',10},{'J',11},{'Q',12},{'K',13}};
	public:
		char rank;
		char suit;
		Card(){}	//Have to create the empty constructor first, then we can specify its attributes
		Card(char r, char s)
		{
			rank = r;
			suit = s;
		}

		void display()
		{
			//Displays each card in a readable format subsituting 'T' for 10
        		if (rank == 'T'){
                		cout << "10" << suit;
        		}else{
        	        	cout << rank << suit;
        		}
		}

		int compare(Card other)
		{
			//Uses maps to get the values of each rank char to make comparing much easier
        		if(cvals[rank] < cvals[other.rank])
        		{
                		return -1;
        		}else if(cvals[rank] > cvals[other.rank])
        		{
        		        return 1;
        		}
        		return 0;
		}

};

class Deck
{
	private:
		//deckidx is used for the deal() function to simulate the cards from the deck being used.
		int cardidx = 0;
		char suits[4] = {'C','S','D','H'};
		char ranks[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
		Card deck[52];
	public:
		Deck()
		{
			int idx = 0;
			for(char suit : suits)
			{
				for(char rank : ranks)
				{
					deck[idx] = Card(rank, suit);
					idx++;	
				}
			}	
		}
		
		void display()
		{
			//Because sizeof() returns the size in bytes, we divide it by one element to get the num of elements in the array
			for(int k = 0; k < sizeof(deck)/sizeof(deck[0]); k++)
			{	
				//Makes a new line every 13 cards that are displayed
				if(k%13 == 0)
				{
					cout << endl;
				}
				//displays the card
				deck[k].display();
				//prints out and gets rid of last comma
				if (k < (sizeof(deck)/sizeof(deck[0])) - 1)
				{
					cout << ", ";
				}
			}
			cout << endl;
		}
		
		void shuffle()
		{
			srand(time(0));
			for (int i = 0; i < sizeof(deck)/sizeof(deck[0]);i++)
			{
				int seed = rand();
				swap(deck[i+ (seed%(52 - i))], deck[i]);
			}
		}

		Card deal()
		{
			if (isEmpty())
			{
				throw logic_error("the deck is empty");
			}else
			{
			Card card = deck[cardidx];
			//Use 'n' to represent that card being gone
			deck[cardidx] = Card('n','n');
			cardidx++;
			return card;
			}
		}

		bool isEmpty()
		{
			if(cardidx == 52)
			{
				return true;
			}
			return false;
		}
};

int main()
{
	string player1;
        string player2;
	string gameCount;
        cout << "Enter the name of the first player: ";
        getline(cin, player1);
        cout << "Enter the name of the second player: ";
        getline(cin, player2);
	cout << "How many games will they play? ";
	getline(cin, gameCount);
        Deck deck;
        cout << "Original Deck" << endl;
        deck.display();
        deck.shuffle();
        cout << "Shuffled Deck" <<endl;
        deck.display();
	int p1wins = 0;
        int p1losses = 0;
        int p2wins = 0;
        int p2losses = 0;
        int ties = 0;
        int gameCounter = 1;
	for(int i = 0; i < stoi(gameCount); i++)
	{
		try
		{
		Card p1card = deck.deal();
		Card p2card = deck.deal();
		cout << "Game " << gameCounter << endl << "--------" << endl;
		cout << player1 << "=>";
                p1card.display();
                cout << endl;
                cout << player2 << "=>";
                p2card.display();
                cout << endl;
		int comparison = p1card.compare(p2card);
                //Checks to see who wins
                if (comparison == 1)
                {
                        p1wins++;
                        p2losses++;
                        cout << player1 << "=> " << "Winner" << endl;
                }else if (comparison == -1)
                {
                        p1losses++;
                        p2wins++;
                        cout << player2 << "=> " << "Winner" << endl;
                }else if (comparison == 0)
                {
                        ties++;
                        cout << "Tie Game" << endl;
                }
                gameCounter++;
                cout << endl;
		} catch(logic_error)
		{
		cout << "Error - Deck is empty" << endl;		
		break;
		}
	}
	//Coverts to string for formatting
	string p1winsString = to_string(p1wins);
	string p1lossesString = to_string(p1losses);
        string tiesString = to_string(ties);
	cout << "------Final Stats------" << endl << string(7, ' ') << player1 << " vs. " << player2 << endl;
        cout << "Wins   " << p1wins << string(player1.length() + 5 - p1winsString.length(), ' ') << p2wins << endl;
        cout << "Losses " << p1losses << string(player1.length() + 5 - p1lossesString.length(), ' ') << p2losses << endl;
        cout << "Ties   " << ties << string(player1.length() + 5 - tiesString.length(), ' ') << ties << endl;
};
