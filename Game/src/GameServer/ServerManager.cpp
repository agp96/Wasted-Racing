#include "ServerManager.h"
#include <iostream>

//Function provided by RakNet
unsigned char ServerManager::GetPacketIdentifier(RakNet::Packet *p)
{
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	else
		return (unsigned char) p->data[0];
}

void ServerManager::init()
{
    //First we get the instance of the peer
	peer=RakNet::RakPeerInterface::GetInstance();
	//Then we initialize the socket and set his socketFamily (for default communication, use AF_INET)
	RakNet::SocketDescriptor socket(PORT, 	0);
	socket.socketFamily = AF_INET;

	peer->Startup(MAXCLIENTS, &socket, 1);
	peer->SetMaximumIncomingConnections(MAXCLIENTS);

	nPlayers=0;
	started=false;
}

void ServerManager::run()
{
	//We run the server until we decide to close it, we should change the condition later
	while(true)
	{
		update();

		//After the update, we should use a clock to make the system sleep until the next update
	}
}

//Function to start the game when we are at the lobby
void ServerManager::startGame()
{
	if(!started && nPlayers > 2)
	{
		started=true;
		std::cout << "Starting game" << std::endl;
	}
}

void ServerManager::update()
{
	//identifier of the packet
	unsigned char identifier;

	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
	{
		identifier=GetPacketIdentifier(packet);
		switch(identifier)
		{
			case ID_REMOTE_CONNECTION_LOST:
				nPlayers--;
				std::cout << "Client disconnected from the server" << std::endl;
				std::cout << "Number of players: " << nPlayers << std::endl;
				break;
			case ID_CONNECTION_LOST:
				nPlayers--;
				std::cout << "Client disconnected from the server" << std::endl;
				std::cout << "Number of players: " << nPlayers << std::endl;
				break;
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				nPlayers--;
				std::cout << "Client disconnected from the server" << std::endl;
				std::cout << "Number of players: " << nPlayers << std::endl;
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				nPlayers--;
				std::cout << "Client disconnected from the server" << std::endl;
				std::cout << "Number of players: " << nPlayers << std::endl;
				break;
			case ID_NEW_INCOMING_CONNECTION:
				nPlayers++;
				std::cout << "New client in the server" << std::endl;
				std::cout << "Number of players: " << nPlayers << std::endl;
				break;
			case ID_GAME_START:
				startGame();
				break;
            default:
                std::cout << "Receiving new packet" << std::endl;
                break;
		}
	}

}