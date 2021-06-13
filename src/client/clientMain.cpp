#include "Client.h"
#include "../common/Logger.h"
#include "Config.h"

int main(int argc, char** argv){
    char host[10] = "localhost";
    Logger logger(argv[2]);
    Config config(argv[0], logger);
    Client client(host, argv[0], config, logger);
    client.run();
    return 0;
}