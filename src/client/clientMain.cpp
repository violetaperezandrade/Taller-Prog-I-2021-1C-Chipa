#include "Client.h"
#include "../common/Logger.h"
#include "../common/Config.h"

int main(int argc, char** argv){
    char host[10] = "localhost";
    Logger logger(argv[2]);
    Config config(argv[0], logger);
    logger.setLevel(config.getDebug());
    Client client(host, argv[0], logger, config);
    client.run();
    return 0;
}