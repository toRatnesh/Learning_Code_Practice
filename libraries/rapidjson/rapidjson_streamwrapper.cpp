/*************
  This example demonstrates about parsing a Json file and updating it.
 **************/


#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h" 
#include "rapidjson/filewritestream.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"

#include <filesystem>
#include <iostream>
#include <fstream>


bool updateJsonFile(const rapidjson::Document & json_doc, std::ostream & ofs) {

    rapidjson::OStreamWrapper rj_osw2(ofs);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer2(rj_osw2);
    json_doc.Accept(writer2);

    return true;
}

bool parseJsonFile(const std::filesystem::path filepath) {

    std::ifstream ifs(filepath);
    rapidjson::IStreamWrapper rj_isw(ifs);
    rapidjson::Document l_json_doc;
    if(l_json_doc.ParseStream(rj_isw).HasParseError()) {
        ifs.close();
        std::clog << "Error in parsing Json,  file: " << filepath << ", error number: " << l_json_doc.GetParseError() << ", offset: " << l_json_doc.GetErrorOffset() << '\n';
        return false;
    }
    ifs.close();

    rapidjson::OStreamWrapper rj_osw(std::cout);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(rj_osw);
    l_json_doc.Accept(writer);
    std::clog << '\n';

    std::clog << "\n=== Updating name element of Json ===\n";
    if(l_json_doc.HasMember("name") && l_json_doc["name"].IsString()) {
        l_json_doc["name"].SetString("rapidjson-parse-and-modify", strlen("rapidjson-parse-and-modify"));
    }

    /*
    rapidjson::OStreamWrapper rj_osw2(std::cout);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer2(rj_osw2);
    l_json_doc.Accept(writer2);
    std::clog << '\n';
    */

    updateJsonFile(l_json_doc, std::cout);

    std::filesystem::path outfilpath("out.json");
    std::ofstream ofs(outfilpath);
    updateJsonFile(l_json_doc, ofs);

    return true;
}


int main(const int argc, const char  * const argv[]) {

    if(argc != 2) {
        std::clog << "Usage: bin <filepath>\n";
        return 1;
    }


    const std::filesystem::path filepath(argv[1]);
    parseJsonFile(filepath);

    return 0;
}

/********
  END OF FILE
 *******/
