//
// Created by nerull on 28.03.2021.
//
#include <iostream>
#include <json/json.h>
#include <glog/logging.h>

void format_stream() {
    FLAGS_logtostderr = 1;
    FLAGS_colorlogtostderr = 1;
    google::InitGoogleLogging("cargo_cmake_conan");
    std::string s;
    Json::Value root;
    Json::Value data;
    constexpr bool shouldUseOldWay = true;
    root["action"] = "run";
    data["number"] = 1;
    root["data"] = data;

    if (shouldUseOldWay) {
        Json::FastWriter writer;
        const std::string json_file = writer.write(root);
        LOG(INFO) << "json_file " << json_file;
    } else {
        Json::StreamWriterBuilder builder;
        const std::string json_file = Json::writeString(builder, root);
        std::cout << json_file << std::endl;
    }

    s.append(std::to_string(54765.03));
}