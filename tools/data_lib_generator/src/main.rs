pub mod models;
mod generators;
mod file_managers;

use std::env;
use crate::file_managers::json_operations::read_json;
use crate::generators::main_generator::generate_data_lib;

// Parse command line arguments
fn parse_args() {
    let args: Vec<String> = env::args().collect();
    let mut parsed_args: Vec<Vec<String>> = Vec::new();
    for arg in args[1..].chunks(2) {
        parsed_args.push(arg.to_vec());
    }
    for pair in parsed_args {
        if pair[0] == "--json" {
            env::set_var("JSON_FILE_PATH", pair[1].clone());
        }
        if pair[0] == "--dest" {
            env::set_var("DEST_PATH", pair[1].clone());
        }
    }
    if env::var("JSON_FILE_PATH").is_err() {
        env::set_var("JSON_FILE_PATH", "applicative_data.json");
    }
    if env::var("DEST_PATH").is_err() {
        env::set_var("DEST_PATH", "libs/data_lib");
    }
}

fn main() {
    parse_args();
    let mut data_lib = read_json();
    generate_data_lib(&mut data_lib);
}
