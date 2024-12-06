use std::io::Write;
pub mod models;

use crate::models::{DataLib, Type};
use std::{env, fs};
use crate::models::data_type::DeclarationType;

fn read_json() -> DataLib {
    let json_file_path = "../../applicative_data.json";
    //let file = File::open(json_file_path).expect("file not found");

    let json_data: String = fs::read_to_string(json_file_path).expect("file not found");
    let data_lib: DataLib = serde_json::from_str(&json_data).expect("error while parsing json");
    data_lib
}

fn generate_header(mut header: fs::File, data_lib: &DataLib, file_name: &str) {
    writeln!(header, "#ifndef {}_H", file_name.to_uppercase()).unwrap();
    writeln!(header, "#define {}_H\n", file_name.to_uppercase()).unwrap();
    writeln!(header, "#include <stddef.h>\n").unwrap();
    for data_type in &data_lib.types {
        if(data_type.kind == "atomic") {
            if let Some(DeclarationType::String(declaration)) = &data_type.declaration {
                writeln!(header, "typedef {} {};", declaration, data_type.name).unwrap();
            }else {
                eprintln!("Error: declaration is None for atomic type");
            }
        }
    }
    writeln!(header, "\n").unwrap();
    for data_type in &data_lib.types {
        if(data_type.kind == "enum") {
            if let Some(DeclarationType::FieldEnumDeclarations(declaration)) = &data_type.declaration {
                writeln!(header, "enum {} {{", data_type.name).unwrap();
                for field_enum_declaration in declaration {
                    writeln!(header, "    {} = {},", field_enum_declaration.name, field_enum_declaration.value).unwrap();
                }
                writeln!(header, "}};\n").unwrap();

            }else {
                eprintln!("Error: declaration is None for enum type");
            }
        }
    }
    for data_type in &data_lib.types {
        if(data_type.kind == "struct") {
            if let Some(DeclarationType::FieldStructDeclarations(declaration)) = &data_type.declaration {
                writeln!(header, "typedef struct {{").unwrap();
                for field_struct_declaration in declaration {
                    writeln!(header, "    {} {};", field_struct_declaration.field_type, field_struct_declaration.name).unwrap();
                }
                writeln!(header, "}} {};\n", data_type.name).unwrap();

            }else {
                eprintln!("Error: declaration is None for enum type");
            }
        }
    }
    writeln!(header, "#endif").unwrap();
}

fn generate_data_lib(data_lib: &DataLib) {
    let file_name = "data_management";
    let mut dest_path = env::var("DEST_PATH").unwrap_or("../../libs/data_lib".to_string());
    if !dest_path.ends_with('/') {
        dest_path.push('/');
    }
    let header = fs::File::create(format!("{}{}.h", dest_path, file_name)).expect("Failed to create header file");
    let mut source = fs::File::create(format!("{}{}.c", dest_path, file_name)).expect("Failed to create source file");

    generate_header(header, data_lib, file_name);
    

    /*
        println!("name: {}", data_type.name);
        println!("kind: {}", data_type.kind);
        println!("declaration: {:?}", data_type.declaration);
        println!("domain: {:?}", data_type.domain);
        println!("comments: {}", data_type.comment);

     */

}

fn parse_args() {
    let args: Vec<String> = env::args().collect();
    let j = 0;
    let mut parsed_args: Vec<Vec<String>> = Vec::new();
    for arg in args[1..].chunks(2) {
        parsed_args.push(arg.to_vec());
    }
    for pair in parsed_args {
        if(pair[0] == "--json") {
            env::set_var("JSON_FILE_PATH", pair[1].clone());
        }
        if(pair[0] == "--dest") {
            env::set_var("DEST_PATH", pair[1].clone());
        }
    }
    if env::var("JSON_FILE_PATH").is_err() {
        env::set_var("JSON_FILE_PATH", "../../libs/data_lib");
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    println!("Hello, world!");
    let data_lib = read_json();
    generate_data_lib(&data_lib);
}

/*
use std::fs::File;
use std::io::{self, Write};

fn generate_c_code(spec: &TypeSpec) {
    for t in &spec.types {
        let mut header = File::create(format!("{}.h", t.name)).expect("Failed to create header file");
        let mut source = File::create(format!("{}.c", t.name)).expect("Failed to create source file");

        // Générer le fichier d'en-tête
        writeln!(header, "#ifndef {}_H", t.name.to_uppercase()).unwrap();
        writeln!(header, "#define {}_H\n", t.name.to_uppercase()).unwrap();

        writeln!(header, "typedef struct {{").unwrap();
        for field in &t.fields {
            writeln!(header, "    {} {};", field.field_type, field.name).unwrap();
        }
        writeln!(header, "}} {};\n", t.name).unwrap();

        for field in &t.fields {
            if field.getter {
                writeln!(
                    header,
                    "{} get_{}_{}({}* instance);",
                    field.field_type, t.name, field.name, t.name
                )
                .unwrap();
            }
            if field.setter {
                writeln!(
                    header,
                    "void set_{}_{}({}* instance, {} value);",
                    t.name, field.name, t.name, field.field_type
                )
                .unwrap();
            }
        }

        writeln!(header, "\n#endif").unwrap();

        // Générer le fichier source
        writeln!(source, "#include \"{}.h\"\n", t.name).unwrap();

        for field in &t.fields {
            if field.getter {
                writeln!(
                    source,
                    "{} get_{}_{}({}* instance) {{ return instance->{}; }}",
                    field.field_type, t.name, field.name, t.name, field.name
                )
                .unwrap();
            }
            if field.setter {
                writeln!(
                    source,
                    "void set_{}_{}({}* instance, {} value) {{ instance->{} = value; }}",
                    t.name, field.name, t.name, field.field_type, field.name
                )
                .unwrap();
            }
        }
    }
}

 */
