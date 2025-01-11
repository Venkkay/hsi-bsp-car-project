use std::{env, fs};
use crate::models::DataLib;

pub fn read_json() -> DataLib {
    let json_file_path = env::var("JSON_FILE_PATH").expect("JSON_FILE_PATH not found");
    //let file = File::open(json_file_path).expect("file not found");
    println!("json_file_path: {}", json_file_path);

    let json_data: String = fs::read_to_string(json_file_path).expect("file not found");
    let data_lib: DataLib = serde_json::from_str(&json_data).expect("error while parsing json");
    data_lib
}