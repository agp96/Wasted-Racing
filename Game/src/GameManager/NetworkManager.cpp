#include "NetworkManager.h"

NetworkManager& NetworkManager::getInstance() {
    static NetworkManager instance;
    return instance;
}

void NetworkManager::init() {
    //Get instance of the peer
    peer = RakNet::RakPeerInterface::GetInstance();

    //Match not started
    started = false;
}

void NetworkManager::update() {
    RakNet::Packet* packet;
    packet = peer->Receive();
    if(packet)
    {
        switch(packet->data[0])
        {
            case ID_CREATE_PLAYER:
                std::cout << "Creando player en su posicion" << std::endl;
                break;
            default:
                std::cout << "ALGO PASO" << std::endl;
                break;
        }
    }
}

void NetworkManager::close() {

}

void NetworkManager::initLobby(){
    std::cout << "Attempting to connect to server" << std::endl;
    RakNet::SocketDescriptor socket(0, 	0);
	socket.socketFamily = AF_INET;
    peer->Startup(1, &socket, 1);
    RakNet::ConnectionAttemptResult result;
    result = peer->Connect("192.168.1.32", 39017, 0, 0);

    if(result == RakNet::CONNECTION_ATTEMPT_STARTED)
    {
        std::cout << "Connection Attempt Started Correctly" << std::endl;
    }
}

void NetworkManager::updateLobby(){
    RakNet::Packet* result;
    RakNet::BitStream stream;
    result = peer->Receive();
    if(result)
    {
        switch(result->data[0])
        {
            case ID_CONNECTION_REQUEST_ACCEPTED:
                std::cout << "Connection Accepted" << std::endl;
                stream.Write((unsigned char)ID_GAME_START);
                peer->Send(&stream, HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
                break;
            case ID_CONNECTION_ATTEMPT_FAILED:
                std::cout << "Connection Failed" << std::endl;
                break;
            case ID_GAME_START:
                std::cout << "Game started " << std::endl;
                started = true;
                break;
            default:
                break;
        }
        peer->DeallocatePacket(result);
    }
}

IComponent::Pointer NetworkManager::createRemotePlayerComponent(GameObject& newGameObject) {

        IComponent::Pointer component = std::make_shared<RemotePlayerComponent>(newGameObject);

        newGameObject.addComponent(component);

        EventData data;
        data.Component = component;

        EventManager::getInstance().addEvent(Event {EventType::RemotePlayerComponent_Create, data});

        return component;
    }
