use std::{env, fs};
use crate::generators::header_generator::generate_header;
use crate::generators::source_generator::generate_source;
use crate::models::DataLib;

// Main function to generate the data library
pub fn generate_data_lib(data_lib: &mut DataLib) {
    let file_name = "data_management";
    let mut dest_path = env::var("DEST_PATH").unwrap_or("../../libs/data_lib".to_string());
    if !dest_path.ends_with('/') {
        dest_path.push('/');
    }
    let header = fs::File::create(format!("{}{}.h", dest_path, file_name)).expect("Failed to create header file");
    let source = fs::File::create(format!("{}{}.c", dest_path, file_name)).expect("Failed to create source file");

    generate_header(header.try_clone().expect("Failed to clone header file"), data_lib, file_name);
    generate_source(source, header, data_lib, file_name);

}