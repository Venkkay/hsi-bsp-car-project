pub mod models;

use crate::models::DataLib;
use std::fs;

fn read_json() -> DataLib {
    let json_file_path = "../../applicative_data.json";
    //let file = File::open(json_file_path).expect("file not found");

    let json_data: String = fs::read_to_string(json_file_path).expect("file not found");
    let data_lib: DataLib = serde_json::from_str(&json_data).expect("error while parsing json");
    data_lib
}

fn generate_data_lib(data_lib: DataLib) {
    for data_type in data_lib.types {
        println!("name: {}", data_type.name);
        println!("kind: {}", data_type.kind);
        println!("declaration: {:?}", data_type.declaration);
        println!("domain: {:?}", data_type.domain);
        println!("comments: {}", data_type.comment);
    }
}

fn main() {
    println!("Hello, world!");
    let data_lib = read_json();
    generate_data_lib(data_lib);
}
