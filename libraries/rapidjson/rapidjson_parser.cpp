/********
  This example demonstrates about rapidjson library.
 *******/


#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

bool printJsonObject(const rapidjson::Value & obj);

bool printJsonArray(const rapidjson::Value & arr) {
    if(!arr.IsArray()) {
        return false;
    }

    for(auto it = arr.Begin(); it != arr.End(); ++it) {
        const rapidjson::Value & value = *it;
        switch(value.GetType()) {
            case rapidjson::Type::kNullType:
            case rapidjson::Type::kFalseType:
                std::clog << value.GetBool() << '\n';
                break;
            case rapidjson::Type::kTrueType:
                std::clog << value.GetBool() << '\n';
                break;
            case rapidjson::Type::kObjectType: 
                printJsonObject(value);    
                break;
            case rapidjson::Type::kArrayType:
                printJsonArray(value);    
                break;
            case rapidjson::Type::kStringType: 	
                std::clog << value.GetString() << '\n';
                break;
            case rapidjson::Type::kNumberType:
                if(value.IsDouble()) {
                    std::clog << value.GetDouble() << '\n';
                }
                else {
                    std::clog << value.GetInt() << '\n';
                }
                break;
            default:
                break;

        }
    }

    return true;
}

bool printJsonObject(const rapidjson::Value & obj) {

    if(!obj.IsObject()) {
        return false;
    }

    for(auto it = obj.MemberBegin(); it != obj.MemberEnd(); ++it) {

        switch(it->value.GetType()) {
            case rapidjson::Type::kNullType:
            case rapidjson::Type::kFalseType:
                std::clog << it->name.GetString() << " : " << it->value.GetBool() << '\n';
                break;
            case rapidjson::Type::kTrueType:
                std::clog << it->name.GetString() << " : " << it->value.GetBool() << '\n';
                break;
            case rapidjson::Type::kObjectType: 
                std::clog << it->name.GetString() << " : ";
                printJsonObject(it->value);    
                std::clog << '\n';
                break;
            case rapidjson::Type::kArrayType:
                std::clog << it->name.GetString() << " : ";
                printJsonArray(it->value);    
                std::clog << '\n';
                break;
            case rapidjson::Type::kStringType: 	
                std::clog << it->name.GetString() << " : " << it->value.GetString() << '\n';
                break;
            case rapidjson::Type::kNumberType:
                if(it->value.IsDouble()) {
                    std::clog << it->name.GetString() << " : " << it->value.GetDouble() << '\n';
                }
                else {
                    std::clog << it->name.GetString() << " : " << it->value.GetInt() << '\n';
                }
                break;
            default:
                break;

        }
    }

    return true;
}

bool parseJsonString(const std::string & str_data) {
    rapidjson::Document json_doc;

    if(json_doc.Parse(str_data.c_str()).HasParseError()) {
        std::clog << "Json parsing error\n";
        return false;
    } 

    if(!printJsonObject(json_doc.GetObject())) {
        return false;
    }

    return true;
}

bool parseJsonFile(const std::filesystem::path filepath) {

    std::ifstream ifs(filepath);
    std::istreambuf_iterator<char> begin(ifs), end;

    const std::string json_str(begin, end);
    if(!parseJsonString(json_str)) {
        return false;
    }

    return true;
}

int main(const int argc, const char * const argv []) {

    if(2 != argc) {
        std::clog << "Usage: bin <inputJsonFile> ";
        return 1;
    }

    std::filesystem::path filepath(argv[1]);
    if(!parseJsonFile(filepath)) {
        return 1;
    }

    return 0;
}

/******
  END OF FILE
 *****/
