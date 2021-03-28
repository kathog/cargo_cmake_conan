use crate::bridge::{format_stream, example};
use cxx::{let_cxx_string};

#[cxx::bridge]
mod bridge {

unsafe extern "C++" {
    include!("cargo_cmake_conan/include/blodstone.h");
    include!("cargo_cmake_conan/target/include/lib.h");

    pub(crate) fn format_stream();
    pub(crate) fn example(s: &CxxString);
}
}

fn main() {

    unsafe {
        // funckaj z projektu wewnętrznego
        format_stream();
        // funkcja z projektu CMake
        let_cxx_string!(s = "Huckleberry");
        example(&s);
    }

}