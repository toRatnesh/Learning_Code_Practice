/*********
  This example demonstrates about rapidjson library.
 ********/

#include <cstdio>

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filewritestream.h"

bool writeJsonToFile(const std::string filename, const rapidjson::Document & json_doc) {

    char writebuf[8192] = {0};
    FILE * fp = fopen(filename.c_str(), "w");
    if(NULL == fp) {
        std::clog << "Failed to open file " << filename << " for writing\n";
        return 1;
    }

    rapidjson::FileWriteStream l_fs(fp, writebuf, sizeof(writebuf));
    rapidjson::PrettyWriter<rapidjson::FileWriteStream> l_writer(l_fs);
    json_doc.Accept(l_writer);

    fclose(fp);


    return true;
}

int main(const int argc, const char * const argv[]) {

    if(2 != argc) {
        std::clog << "Usage: bin <filepath>\n";
        return 1;
    }

    rapidjson::Document json_doc;
    json_doc.SetObject();
    rapidjson::Document::AllocatorType & l_rj_alloc = json_doc.GetAllocator();

    rapidjson::Value l_str(rapidjson::Type::kStringType);
    l_str.SetString("rapidjson", strlen("rapidjson")) ;
    json_doc.AddMember("name", l_str, l_rj_alloc);

    rapidjson::Value l_num(rapidjson::Type::kNumberType);
    l_num.SetDouble(250.35);
    json_doc.AddMember("price", l_num, l_rj_alloc);

    l_num.SetUint(10);
    json_doc.AddMember("discount", l_num, l_rj_alloc);

    rapidjson::Value l_bool(rapidjson::Type::kTrueType);
    l_bool.SetBool(true);
    json_doc.AddMember("insale", l_bool, l_rj_alloc);

    rapidjson::Value l_arr(rapidjson::Type::kArrayType);
    l_arr.PushBack("read", l_rj_alloc).PushBack("write", l_rj_alloc);
    l_arr.PushBack(1, l_rj_alloc).PushBack(1.5, l_rj_alloc).PushBack(true, l_rj_alloc);
    rapidjson::Value l_obj(rapidjson::Type::kObjectType);
    l_obj.SetObject();
    l_str.SetString("json", strlen("json"));
    l_obj.AddMember("name", l_str, l_rj_alloc);
    l_num.SetUint(12);
    l_obj.AddMember("value", l_num, l_rj_alloc);
    l_arr.PushBack(l_obj, l_rj_alloc);
    json_doc.AddMember("operation", l_arr, l_rj_alloc);

    l_obj.SetObject();
    l_str.SetString("A street name", strlen("A street name"));
    l_obj.AddMember("address", l_str, l_rj_alloc);
    l_str.SetString("A city name", strlen("A city name"));
    l_obj.AddMember("city", l_str, l_rj_alloc);
    l_num.SetUint(274406);
    l_obj.AddMember("pin", l_num, l_rj_alloc);
    json_doc.AddMember("contact", l_obj, l_rj_alloc);

    /*   
    rapidjson::StringBuffer l_str_buf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> l_writer(l_str_buf);
    json_doc.Accept(l_writer);

    const std::string l_json_str = std::string(l_str_buf.GetString(), l_str_buf.GetSize());

    const std::filesystem::path filepath(argv[1]);
    writeJsonToFile(l_json_str, filepath);
    */

    /*
    char writebuf[8192] = {0};
    FILE * fp = fopen(argv[1], "w");
    if(NULL == fp) {
        std::clog << "Failed to open file " << argv[1] << " for writing\n";
        return 1;
    }

    rapidjson::FileWriteStream l_fs(fp, writebuf, sizeof(writebuf));
    rapidjson::PrettyWriter<rapidjson::FileWriteStream> l_writer(l_fs);
    json_doc.Accept(l_writer);

    fclose(fp);
    */

    writeJsonToFile(argv[1], json_doc);

    return 0;
}

/*****
  END OF FILE
 ******/


