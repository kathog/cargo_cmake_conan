use cmake::Config;
extern crate conan;
use conan::*;
use std::path::Path;

fn main() {

    let conan_profile = "default";
    let command = InstallCommandBuilder::new()
        .with_profile(&conan_profile)
        .build_policy(BuildPolicy::Missing)
        .recipe_path(Path::new("regexp_pcre/conanfile.txt"))
        .build();

    let build_info = command.generate().unwrap();
    let json_include = build_info.get_dependency("jsoncpp").unwrap().get_include_dir().unwrap();
    let glog_include = build_info.get_dependency("glog").unwrap().get_include_dir().unwrap();
    let gflag_include = build_info.get_dependency("gflags").unwrap().get_include_dir().unwrap();

    let dst = Config::new("regexp_pcre")
        .build();

    cxx_build::bridge("src/main.rs")
        .file("src/blodstone.cpp")
        .include("include")
        .include("target/cxxbridge/rust")
        .include("target/cxxbridge/cargo_cmake_conan/src")
        .include(json_include)
        .include(glog_include)
        .include(gflag_include)
        .opt_level_str("fast")
        .flag("-std=c++20")
        .compiler("clang++")
        .compile("cxx-test");

    println!("cargo:rustc-link-search=native={}", dst.display());
    println!("cargo:rustc-link-lib=regexp_pcre_lib");
    build_info.cargo_emit();

}