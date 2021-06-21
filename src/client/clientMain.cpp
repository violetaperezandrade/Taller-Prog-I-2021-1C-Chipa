#include "Client.h"
#include "../common/Logger.h"
#include "../common/Config.h"

int main(int argc, char** argv){
   if (argc != 5){
        std::cerr << "Invalid number of parameters" << std::endl;
        return -1;
    }
    char* host = argv[1];
    char* port = argv[2];
    char* loggerPath = argv[3];
    char* configPath = argv[4];
    Logger logger(loggerPath);
    Config config(configPath, logger);
    logger.setLevel(config.getDebug());
    Client client(host, port, logger, config);
    client.run();
    return 0;
}