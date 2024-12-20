use std::io::Write;
pub mod models;

use crate::models::{DataLib};
use std::{env, fs};
use std::fs::File;
use crate::models::data_init::InitialValueType;
use crate::models::data_type::{DeclarationType, DomainType};

fn read_json() -> DataLib {
    let json_file_path = "../../applicative_data.json";
    //let file = File::open(json_file_path).expect("file not found");

    let json_data: String = fs::read_to_string(json_file_path).expect("file not found");
    let data_lib: DataLib = serde_json::from_str(&json_data).expect("error while parsing json");
    data_lib
}
fn generate_header(mut header: File, data_lib: &DataLib, file_name: &str) {
    writeln!(header, "#ifndef {}_H", file_name.to_uppercase()).unwrap();
    writeln!(header, "#define {}_H\n", file_name.to_uppercase()).unwrap();
    writeln!(header, "#include <stdint.h>\n#include <stdbool.h>\n").unwrap();
    for data_constant in &data_lib.data {
        if data_constant.field_type == "define" {
            if let Some(InitialValueType::Integer(initialization_value)) = &data_constant.initialization_value {
                writeln!(header, "#define {} {}", data_constant.name, initialization_value).unwrap();
            }else {
                eprintln!("Error: initial_value is None for data_constant");
            }
        }
    }
    writeln!(header, "\n").unwrap();
    for data_type in &data_lib.types {
        if data_type.kind == "atomic" {
            if let Some(DeclarationType::String(declaration)) = &data_type.declaration {
                writeln!(header, "/**\n * Atomic type {}.\n *\n * \\details {} \n*/", data_type.name, data_type.comment).unwrap();
                writeln!(header, "typedef {} {};", declaration, data_type.name).unwrap();
            }else {
                eprintln!("Error: declaration is None for atomic type");
            }
        }
    }
    for data_type in &data_lib.types {
        if data_type.kind == "flags" {
            if let Some(DeclarationType::FlagsStruct(declaration)) = &data_type.declaration {
                writeln!(header, "/**\n * Flag {}.\n *\n * \\details {} \n*/", data_type.name, data_type.comment).unwrap();
                writeln!(header, "typedef {} {};", declaration.field_type, data_type.name).unwrap();
            }else {
                eprintln!("Error: declaration is None for atomic type");
            }
        }
    }
    writeln!(header, "\n").unwrap();
    for data_type in &data_lib.types {
        if data_type.kind == "enum" {
            if let Some(DeclarationType::FieldEnumDeclarations(declaration)) = &data_type.declaration {
                writeln!(header, "/**\n * Enum {}.\n *\n * \\details {} \n*/", data_type.name, data_type.comment).unwrap();
                writeln!(header, "typedef enum {}_struct {{", data_type.name).unwrap();
                for field_enum_declaration in declaration {
                    writeln!(header, "    {} = {},", field_enum_declaration.name, field_enum_declaration.value).unwrap();
                }
                writeln!(header, "}} {};\n", data_type.name).unwrap();

            }else {
                eprintln!("Error: declaration is None for enum type");
            }
        }
    }
    for data_type in &data_lib.types {
        if data_type.kind == "struct" {
            if let Some(DeclarationType::FieldStructDeclarations(declaration)) = &data_type.declaration {
                writeln!(header, "/**\n * Struct type {}.\n *\n * \\details {} \n*/", data_type.name, data_type.comment).unwrap();
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
}

fn generate_source(mut source: File, mut header: File, data_lib: &DataLib, file_name: &str) {
    writeln!(source, "#include \"{}.h\"", file_name).unwrap();
    writeln!(source, "#include <stdint.h>\n#include <stdbool.h>\n").unwrap();

    writeln!(header, "// Function signatures").unwrap();
    writeln!(header, "// Atomic types setter").unwrap();
    for data_type in &data_lib.types {
        if data_type.kind == "atomic" {
            if let Some(DeclarationType::String(declaration)) = &data_type.declaration {
                //writeln!(source, "/**\n * Get the value of {}.\n *\n * @param[in] instance An instance of {}.\n * @return Return the value of the instance.\n */", data_type.name, data_type.name).unwrap();
                //writeln!(source, "{} get_{}({} instance) {{\n    return instance;\n}}", declaration, data_type.name, data_type.name).unwrap();
                if let Some(DomainType::DomainMinMax(domain)) = &data_type.domain {
                    //TODo check system for flags ?
                    writeln!(source, "/**\n * Check the value of {}.\n *\n * \\param[in] value : The value to check.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name).unwrap();
                    writeln!(source, "bool check_{}({} value){{\n    if (value >= {} && value <= {}) {{\n        return true;\n    }}\n    return false;\n}}\n  ", data_type.name, declaration, domain.min, domain.max).unwrap();
                    writeln!(header, "bool check_{}({} value);", data_type.name, declaration).unwrap();

                }else {
                    writeln!(source, "/**\n * Check the value of {}.\n *\n * \\param[in] value : The value to check.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name).unwrap();
                    writeln!(source, "bool check_{}({} value){{\n    return true;\n}}\n  ", data_type.name, declaration).unwrap();
                    writeln!(header, "bool check_{}({} value);", data_type.name, declaration).unwrap();
                }
                writeln!(source, "/**\n * Set the value of {}.\n *\n * \\param[out] instance : An instance of {}.\n * \\param[in] value : The value to set.\n * \\return bool : Return True if the value is set, False otherwise.\n */", data_type.name, data_type.name).unwrap();
                writeln!(source, "bool set_{}({}* instance, {} value) {{\n    if (check_{}(value)) {{\n        *instance = value;\n        return true;\n    }}\n    return false;\n}}\n", data_type.name, data_type.name, declaration, data_type.name).unwrap();
                writeln!(header, "bool set_{}({}* instance, {} value);", data_type.name, data_type.name, declaration).unwrap();
            }else {
                eprintln!("Error: declaration is None for atomic type");
            }
        }
    }

    writeln!(header, "\n// Flags getter and setter").unwrap();
    for data_type in &data_lib.types {
        if data_type.kind == "flags" {
            if let Some(DeclarationType::FlagsStruct(declaration)) = &data_type.declaration {
                let total_size = declaration.flags.iter().fold(0, |acc, flag| acc + flag.bit_size);
                // println!("total_size: {}", total_size);
                let mut shift = total_size;
                writeln!(source, "// Flags for {}.\n", data_type.name).unwrap();
                for flag in &declaration.flags {
                    shift -= flag.bit_size;
                    // println!("flag bit size: {}", shift);
                    writeln!(source, "/**\n * Get {} flag from {}.\n *\n * @param[in] instance An instance of {}.\n * @return {} : Return the value of the got flag.\n */", flag.name, data_type.name, data_type.name, declaration.field_type).unwrap();
                    writeln!(source, "{} get_{}_from_{}({} instance) {{\n    return (instance & 0x{:0fill$x}) >> {};\n}}", declaration.field_type, flag.name, data_type.name, data_type.name, flag.bit_size << shift, shift, fill=((total_size/4 )as usize)).unwrap();
                    writeln!(header, "{} get_{}_from_{}({} instance);", declaration.field_type, flag.name, data_type.name, data_type.name).unwrap();

                    writeln!(source, "/**\n * Set {} flag in {}.\n *\n * @param[out] instance An instance of {}.\n * \\param[in] value : The value to set.\n * @return Return True if the value is valid, False otherwise.\n */", flag.name, data_type.name, data_type.name).unwrap();
                    writeln!(source, "bool set_{}_in_{}({}* instance, {} value) {{\n    *instance &= ~0x{:0fill$x};\n    *instance |= value << {};\n    return true;\n}}\n", flag.name, data_type.name, data_type.name, declaration.field_type,flag.bit_size << shift, shift,  fill=((total_size/4 )as usize)).unwrap();
                    writeln!(header, "bool set_{}_in_{}({}* instance, {} value);", flag.name, data_type.name, data_type.name, declaration.field_type).unwrap();
                }
                writeln!(source, "/**\n * Set all flag in {}.\n *\n * @param[out] instance An instance of {}.\n * @return Return True if the value is valid, False otherwise.\n */", data_type.name, data_type.name).unwrap();
                write!(source, "bool set_all_flag_{}({}* instance", data_type.name, data_type.name).unwrap();
                write!(header, "bool set_all_flag_{}({}* instance", data_type.name, data_type.name).unwrap();
                for flag in &declaration.flags {
                    write!(source, ", {} {}", declaration.field_type, flag.name).unwrap();
                    write!(header, ", {} {}", declaration.field_type, flag.name).unwrap();
                }
                writeln!(source, ") {{").unwrap();
                writeln!(header, ");").unwrap();
                for flag in &declaration.flags {
                    writeln!(source, "    set_{}_in_{}(instance, {});", flag.name, data_type.name, flag.name).unwrap();
                }
                writeln!(source, "    return true;\n}}\n").unwrap();

                writeln!(source, "/**\n * Check the value of {}.\n *\n * \\param[in] value : The value to check.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name).unwrap();
                writeln!(source, "bool check_{}({} value){{\n    return true;\n}}\n  ", data_type.name, declaration.field_type).unwrap();
                writeln!(header, "bool check_{}({} value);", data_type.name, declaration.field_type).unwrap();
                writeln!(source, "/**\n * Set {}.\n *\n * \\param[out] instance An instance of {}.\n * \\param[in] value : The value to set.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name, data_type.name).unwrap();
                writeln!(source, "bool set_{}({}* instance, {} value) {{\n    *instance = value;\n    return true;\n}}\n", data_type.name, data_type.name, data_type.name).unwrap();
                writeln!(header, "bool set_{}({}* instance, {} value);", data_type.name, data_type.name, declaration.field_type).unwrap();
                writeln!(source, "\n").unwrap();
            }else {
                eprintln!("Error: declaration is None for atomic type");
            }
        }
    }

    writeln!(source, "// Enums Setter\n").unwrap();
    writeln!(header, "\n// Enums getter and setter").unwrap();
    for data_type in &data_lib.types {
        if data_type.kind == "enum" {
            if let Some(DeclarationType::FieldEnumDeclarations(declaration)) = &data_type.declaration {
                //writeln!(source, "/**\n * Get the value of {}.\n *\n * @param[in] instance An instance of {}.\n * @return Return the value of the instance.\n */", data_type.name, data_type.name).unwrap();
                //writeln!(source, "{} get_{}({} instance) {{\n    return instance;\n}}", data_type.name, data_type.name, data_type.name).unwrap();
                writeln!(source, "/**\n * Check the value of {}.\n *\n * \\param[in] value The value to check.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name).unwrap();
                writeln!(source, "bool check_{}({} value){{\n    return true;\n}}\n  ", data_type.name, data_type.name).unwrap();
                writeln!(header, "bool check_{}({} value);", data_type.name, data_type.name).unwrap();

                writeln!(source, "/**\n * Set the value of {}.\n *\n * \\param[out] instance An instance of {}.\n * \\param[in] value : The value to set.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name, data_type.name).unwrap();
                writeln!(source, "bool set_{}({}* instance, {} value) {{\n    *instance = value;\n    return true;\n}}\n\n", data_type.name, data_type.name, data_type.name).unwrap();
                writeln!(header, "bool set_{}({}* instance, {} value);", data_type.name, data_type.name, data_type.name).unwrap();
            }else {
                eprintln!("Error: declaration is None for atomic type");
            }
        }
    }

    writeln!(source, "// Struct getter and setter\n").unwrap();
    writeln!(header, "\n// Struct getter and setter").unwrap();
    for data_type in &data_lib.types {
        if data_type.kind == "struct" {
            if let Some(DeclarationType::FieldStructDeclarations(declaration)) = &data_type.declaration {
                //writeln!(source, "fn get{}\n", declaration.field_type).unwrap();
                // let total_size = declaration.flags.iter().fold(0, |acc, flag| acc + flag.bit_size);
                // println!("total_size: {}", total_size);
                // let mut shift = total_size;
                for field_struct_declaration in declaration {
                    //shift -= flag.bit_size;
                    // println!("flag bit size: {}", shift);
                    writeln!(source, "/**\n * Get {} field from {}.\n *\n * \\param[in] instance An instance of {}.\n * \\return {} : Return the value of the got field.\n */", field_struct_declaration.name, data_type.name, data_type.name, field_struct_declaration.field_type).unwrap();
                    writeln!(source, "{} get_{}_from_{}({} instance) {{\n    return instance.{};\n}}", field_struct_declaration.field_type, field_struct_declaration.name, data_type.name, data_type.name, field_struct_declaration.name).unwrap();
                    writeln!(header, "{} get_{}_from_{}({} instance);", field_struct_declaration.field_type, field_struct_declaration.name, data_type.name, data_type.name).unwrap();

                    writeln!(source, "/**\n * Set {} field in {}.\n *\n * \\param[out] instance : An instance of {}.\n * \\param[in] value : The value to set.\n * \\return bool :  Return True if the value is valid, False otherwise.\n */", field_struct_declaration.name, data_type.name, data_type.name).unwrap();
                    writeln!(source, "bool set_{}_in_{}({}* instance, {} value) {{\n    return set_{}(&instance->{}, value);\n}}\n", field_struct_declaration.name, data_type.name, data_type.name, field_struct_declaration.field_type, field_struct_declaration.field_type, field_struct_declaration.name).unwrap();
                    writeln!(header, "bool set_{}_in_{}({}* instance, {} value);", field_struct_declaration.name, data_type.name, data_type.name, field_struct_declaration.field_type).unwrap();
                }

                writeln!(source, "/**\n * Check all values to set in {}.\n *\n * \\param[out] instance : An instance of {}.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name, data_type.name).unwrap();
                write!(source, "bool check_{}(", data_type.name).unwrap();
                write!(header, "bool check_{}(", data_type.name).unwrap();
                for (i, field) in declaration.iter().enumerate() {
                    if i < declaration.len() - 1  {
                        write!(source, "{} {}, ", field.field_type, field.name).unwrap();
                        write!(header, "{} {}, ", field.field_type, field.name).unwrap();
                    }
                    else{
                        write!(source, "{} {}", field.field_type, field.name).unwrap();
                        write!(header, "{} {}", field.field_type, field.name).unwrap();
                    }
                }
                writeln!(source, ") {{").unwrap();
                writeln!(header, ");").unwrap();
                //writeln!(source, "    if ").unwrap();
                for field in declaration {
                    writeln!(source, "    if (!check_{}({})) {{ return false;}}", field.field_type, field.name).unwrap();
                }
                writeln!(source, "    return true;\n}}\n\n").unwrap();

                writeln!(source, "/**\n * Set all field in {}.\n *\n * \\param[out] instance : An instance of {}.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name, data_type.name).unwrap();
                write!(source, "bool set_{}({}* instance", data_type.name, data_type.name).unwrap();
                write!(header, "bool set_{}({}* instance", data_type.name, data_type.name).unwrap();
                for field in declaration {
                    write!(source, ", {} {}", field.field_type, field.name).unwrap();
                    write!(header, ", {} {}", field.field_type, field.name).unwrap();
                }
                writeln!(source, ") {{").unwrap();
                writeln!(header, ");").unwrap();
                write!(source, "    if (!check_{}(", data_type.name).unwrap();
                for (i, field) in declaration.iter().enumerate() {
                    if i < declaration.len() - 1 {
                        write!(source, "{}, ", field.name).unwrap();
                    }
                    else {
                        write!(source, "{}", field.name).unwrap();
                    }
                }
                writeln!(source, ")) {{\n        return false;\n    }}").unwrap();
                for field in declaration {
                    writeln!(source, "    set_{}_in_{}(instance, {});", field.name, data_type.name, field.name).unwrap();
                }
                writeln!(source, "    return true;\n}}\n\n").unwrap();
                writeln!(source, "\n").unwrap();
            }else {
                eprintln!("Error: declaration is None for atomic type");
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
    let source = fs::File::create(format!("{}{}.c", dest_path, file_name)).expect("Failed to create source file");

    generate_header(header.try_clone().expect("Failed to clone header file"), data_lib, file_name);
    generate_source(source, header, data_lib, file_name);


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
        if pair[0] == "--json" {
            env::set_var("JSON_FILE_PATH", pair[1].clone());
        }
        if pair[0] == "--dest" {
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
