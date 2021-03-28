#include <iostream>
#include <json/json.h>
#include "lib.h"
#include <pcre.h>

using namespace std;
auto stack0 = pcre_jit_stack_alloc(16384, 16384);

int main() {

    Json::Value root;
    Json::Value data;
    constexpr bool shouldUseOldWay = true;
    root["action"] = "run";
    data["number"] = 1;
    root["data"] = data;

    if (shouldUseOldWay) {
        Json::FastWriter writer;
        const std::string json_file = writer.write(root);
        std::cout << "json_file" << json_file << std::endl;
    } else {
//        Json::StreamWriterBuilder builder;
//        const std::string json_file = Json::writeString(builder, root);
//        std::cout << json_file << std::endl;
    }

    std::string pattern0 = "/post/\\w+";

    std::string uri = "/post/dfsdfds";
    char const* error;
    int offset;
    auto regex = pcre_compile(pattern0.data(), 0,  &error, &offset, nullptr);
    auto aid = pcre_study(regex, PCRE_STUDY_JIT_COMPILE, &error);

    int pos = 0;
    for(int match[3]; pcre_jit_exec(regex, aid, uri.data(), uri.size(), pos, 0, match, 3, stack0) >= 0; pos = match[1]) {
        std::cout << "pcre found: " << pos << std::endl;
    }

    return 0;
}
