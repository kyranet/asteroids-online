#include <thread>

#include "AsteroidsGame.h"
#include "ClientInfo.h"
#include "Server.h"

using namespace std;

void clientMode(char* host, const int port) {
  ClientInfo::initInstance(host, port);
  AsteroidsGame g;
  g.start();
}
void serverMode(const int port) {
  Server s;
  thread serverThread([port, &s]() { s.start(port); });
  const char* host = "localhost";
  clientMode((char*)host, port);
  s.stop();
  serverThread.join();
}

int main(const int argc, char** argv) {
  if (SDLNet_Init() < 0) {
    cout << "Error: " << SDLNet_GetError() << endl;
    cout << "Connected: " << ClientInfo::instance()->getClientId() << endl;
    exit(1);
  }
  if (argc == 3 && strcmp(argv[1], "server") == 0) {
    serverMode(atoi(argv[2]));
  } else if (argc == 4 && strcmp(argv[1], "client") == 0) {
    clientMode(argv[2], atoi(argv[3]));
  } else {
    cout << "Usage: " << endl;
    cout << " " << argv[0] << " client host port " << endl;
    cout << " " << argv[0] << " server port " << endl;
  }

  return 0;
}
