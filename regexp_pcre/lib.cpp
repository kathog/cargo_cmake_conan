//
// Created by nerull on 23.03.2021.
//
#include <iostream>
#include "lib.h"
#include <pcre.h>
#include "json/json.h"
#include <glog/logging.h>

using namespace std;
auto stack0 = pcre_jit_stack_alloc(16384, 16384);
std::string pattern0 = "(Tom|Sawyer|Huckleberry|Finn)";
char const* error;
int offset;
auto regex = pcre_compile(pattern0.data(), 0,  &error, &offset, nullptr);
auto aid = pcre_study(regex, PCRE_STUDY_JIT_COMPILE, &error);

void example(const string& s) {
//    FLAGS_logtostderr = 1;
//    FLAGS_colorlogtostderr = 1;
//    google::InitGoogleLogging("cargo_cmake_conan");

    int pos = 0;
    for(int match[3]; pcre_jit_exec(regex, aid, s.data(), s.size(), pos, 0, match, 3, stack0) >= 0; pos = match[1]) {
        LOG(INFO) << "pcre found: " << pos;
    }

    Json::Value root;
    Json::Value data;
    constexpr bool shouldUseOldWay = false;
    root["action"] = "run";
    data["number"] = 1;
    root["data"] = data;

    if (shouldUseOldWay) {
        Json::FastWriter writer;
        const std::string json_file = writer.write(root);
        LOG(INFO) << "json_file" << json_file;
    } else {
        Json::StreamWriterBuilder builder;
        const std::string json_file = Json::writeString(builder, root);
        LOG(INFO) << json_file;
    }


}