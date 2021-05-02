#include <iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <string>

int main(){

    //saving the file pointer in "file" using fstream
    std::ifstream file("/home/mauricio/Documents/Taller Azcurra/Taller-Prog-I-2021-1C-Chipa/config.json");
    Json::Value actualJson;
    Json::Reader reader;

    //using reader to parse the json
    reader.parse(file, actualJson);

    //actualJson has all the json data
    std::cout << "Total jsondata: \n" << actualJson << std::endl;

    return 0;
}
