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


bool jioSendAppNetworkReady(const std::filesystem::path filepath) {

	rapidjson::Document l_appNetworkReadyAckDoc;
	l_appNetworkReadyAckDoc.SetObject();
	rapidjson::Document::AllocatorType & l_rj_allocator = l_appNetworkReadyAckDoc.GetAllocator();

	rapidjson::Value l_rjv_str(rapidjson::kStringType);
	constexpr char l_msgType[] = "APP_NETWORK_READY";
	l_rjv_str.SetString(l_msgType, static_cast<rapidjson::SizeType>(strlen(l_msgType)));
	l_appNetworkReadyAckDoc.AddMember("msgType", l_rjv_str, l_rj_allocator);

	rapidjson::Value l_app_config(rapidjson::Type::kObjectType);
	{
		// parse config file and get json object
		std::ifstream l_ifs(filepath);
		if(!(l_ifs.is_open())) {
			std::clog << "Failed to open file " << filepath << '\n';
			return false;
		}

		rapidjson::IStreamWrapper l_isw(l_ifs);
		rapidjson::Document l_conf_doc;
		l_conf_doc.ParseStream(l_isw);
		// close opened file after parsing
		l_ifs.close();

		if(l_conf_doc.HasParseError()) {
			std::clog << "Error in parsing Json, file: " << filepath <<  " error number: " << l_conf_doc.GetParseError() << " offset: " << l_conf_doc.GetErrorOffset();
			rapidjson::Value l_err(rapidjson::Type::kStringType);
			constexpr char l_errstr[] = "Invalid config json";
			l_err.SetString(l_errstr, static_cast<rapidjson::SizeType>(strlen(l_errstr)));
			l_app_config.AddMember("error", l_err, l_rj_allocator);
		}
		else {
			if(l_conf_doc.HasMember("sftpPwd")) {
				l_conf_doc["sftpPwd"].SetString("", strlen(""));    // DONOT SHARE PASSWORD
			}
			//l_app_config = (l_conf_doc.GetObject());
            l_app_config.CopyFrom(l_conf_doc, l_rj_allocator);  // deep copy no address sanitizer error
		}
	}
	l_appNetworkReadyAckDoc.AddMember("configData", l_app_config, l_rj_allocator);

	rapidjson::StringBuffer l_str_buf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> l_writer(l_str_buf);
	l_appNetworkReadyAckDoc.Accept(l_writer);

	const char * l_req_msg = l_str_buf.GetString();
	std::clog << "Message for APP_NETWORK_READY: " << '\n' << l_req_msg << '\n';

	return true;

} // jioSendAppNetworkReady

int main(const int argc, const char  * const argv[]) {

    if(argc != 2) {
        std::clog << "Usage: bin <filepath>\n";
        return 1;
    }


    const std::filesystem::path filepath(argv[1]);
    jioSendAppNetworkReady(filepath);

    return 0;
}

/********
  END OF FILE
 *******/
