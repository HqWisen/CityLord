#include <iostream>
#include <signal.h>
#include <cstdlib>

#include "CityLordClient.hpp"
#define PORT 27000

CityLordClient* client = nullptr;

void handler(int){
    if(client != nullptr){
        delete client;
    }
    std::cout<<"\n\n*** You left the game ***"<<std::endl;
    exit(0);
}

int main(int argc, char** argv){

  signal(SIGINT, &handler);
  char* hostname;
  if(argc != 2){
    printf("Hostname not given !\n");
    hostname = "localhost";
  }
  else{
      hostname = argv[1];
  }
  std::cout<<"*** To quit the game press CTRL+C ***"<<std::endl;
  client = new CityLordClient(hostname, PORT);
  client->runClient();
  delete client;
  return 0;
}
