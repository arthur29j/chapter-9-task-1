#include <iostream>
#include <string>



using namespace std;



class Player
{
	friend ostream& operator<<(ostream& os, const Player* aPlayer);

public:
	static int s_Total;
	static int GetTotal();
	Player(const string& name = ""); // Constructor
	~Player();
	string GetName() const;
	Player* GetNext() const;
	void SetNext(Player* next);

private:
	string m_Name;
	Player* m_pNext; // Pointer to the next player in the lobby
};
int Player::s_Total = 0; // Initializing a static member variable
Player::Player(const string& name): // Constructor
	m_Name(name),
	m_pNext(0)
{
	++s_Total;
}
Player::~Player() // Destructor
{
	--s_Total;
}
int Player::GetTotal() // Getter for a static member variable
{
	return s_Total;
}
string Player::GetName() const
{
	return m_Name;
}
Player* Player::GetNext() const
{
	return m_pNext;
}
void Player::SetNext(Player* next)
{
	m_pNext = next;
}



class Lobby
{
	friend ostream& operator<<(ostream& os, const Lobby& aLobby);
	
public:
	Lobby();
	~Lobby();
	void AddPlayer();
	void RemovePlayer();
	void Clear();
	void GetPlayerByNumber();

private:
	Player* m_pHead; // Pointer to the first player in the lobby
};
Lobby::Lobby(): // Constructor
	m_pHead(0)
{}
Lobby::~Lobby() // Destructor
{
	Clear();
}
void Lobby::AddPlayer()
{
	// Create a new player
	cout << "Please enter the name of the new player: ";
	string name;
	cin >> name;

	Player* pNewPlayer = new Player(name);

	if (m_pHead == 0) // If the list is empty, put the pNewPlayer at the beginning of it
	{
		m_pHead = pNewPlayer;
	}
	else // Otherwise, find the end of the list and add the pNewPlayer there
	{
		Player* pIter = m_pHead;

		while (pIter->GetNext() != 0)
		{
			pIter = pIter->GetNext();
		}
		pIter->SetNext(pNewPlayer);
	}
}
void Lobby::RemovePlayer()
{
	if (m_pHead == 0)
	{
		cout << "The game lobby is empty!\n";
	}
	else
	{
		Player* pTemp = m_pHead;

		m_pHead = m_pHead->GetNext();

		delete pTemp;
	}
}
void Lobby::Clear()
{
	while (m_pHead != 0)
	{
		RemovePlayer();
	}
}
void Lobby::GetPlayerByNumber()
{
	cout << m_pHead;
}



ostream& operator<<(ostream& os, const Lobby& aLobby) // ostream& operator<< for class Lobby
{
	Player* pIter = aLobby.m_pHead;
	os << "\nHere's who's in the game lobby:\n";

	if (pIter == 0)
	{
		os << "The lobby is empty!\n";
	}
	else
	{
		while (pIter != 0)
		{
			os << pIter->GetName() << "\n";
			pIter = pIter->GetNext();
		}
	}

	return os;
}
ostream& operator<<(ostream& os, const Player* pPlayer) // ostream& operator<< for class Player
{	
	if (pPlayer == 0)
	{
		os << "The lobby is empty.\n";
	}
	else
	{
		// Get the first one
		//os << pPlayer->GetName();


		// Get the player by number
		os << "Now there are " << Player::GetTotal() << " players in the lobby\n";
		os << "Choose the number of the player you want to display: ";

		int choice;

		do
		{
			cin >> choice;
			if ((choice > Player::GetTotal()) || (choice <= 0))
			{
				os << "Your choice must less than or equal to " << Player::GetTotal() << ", but greater than 0.\n";
			}
		}
		while ((choice > Player::GetTotal()) || (choice <= 0));

		if (choice == 1)
		{
			os << "\nHere's the player you have choosen:\n";
			os << pPlayer->GetName();
		}
		else
		{
			Player* pTemp = pPlayer->GetNext();

			for (int i = 1; i < (choice - 1); i++)
			{
				pTemp = pTemp->GetNext();
			}

			os << "\nHere's the player you have choosen:\n";
			os << pTemp->GetName();
		}
	}

	return os;
}



int main()
{
	// Test for operator<< for class Player
	//Player* player = new Player("Arthur");
	//cout << player;

	Lobby myLobby;
	int choice;

	do
	{
		cout << myLobby;
		cout << "\nGAME LOBBY\n";
		cout << "0 - Exit the program.\n";
		cout << "1 - Add a player to the lobby.\n";
		cout << "2 - Remove a player from the lobby.\n";
		cout << "3 - Clear the lobby.\n";
		cout << "4 - Display a specific player by number in the lobby.\n";
		cout << "\nEnter choice: ";
		cin >> choice;

		switch (choice)
		{
		case 0:
			cout << "\n\nGood-bye!\n";
			break;
		case 1:
			myLobby.AddPlayer();
			break;
		case 2:
			myLobby.RemovePlayer();
			break;
		case 3:
			myLobby.Clear();
			break;
		case 4:
			myLobby.GetPlayerByNumber();
			break;
		default:
			cout << "That was not a valid choice!\n";
		}
	}
	while (choice != 0);

	return 0;
}