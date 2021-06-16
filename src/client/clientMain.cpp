#include "Client.h"
#include "../common/Logger.h"
#include "../common/Config.h"

int main(int argc, char** argv){
    char host[10] = "localhost";
    char port[5] = "8080";
    char loggerPath[17] = "../logClient.txt";
    char configPath[13] = "../data.json";
    Logger logger(loggerPath);
    Config config(configPath, logger);
    logger.setLevel(config.getDebug());
    Client client(host, port, logger, config);
    client.run();
    return 0;
}