use std::fs::File;
use std::io::Write as IoWrite;
use crate::models::data_init::InitialValueType;
use crate::models::data_type::DeclarationType;
use crate::models::{DataInit, DataLib, Type};

// Generate the header file
pub fn generate_header(mut header: File, data_lib: &DataLib, file_name: &str) {
    write_header_top_guard(&mut header, file_name);
    write_include(&mut header);
    write_define(&mut header, &data_lib.data);
    write_atomic_type(&mut header, &data_lib.types);
    write_flags(&mut header, &data_lib.types);
    write_enums(&mut header, &data_lib.types);
    write_structs(&mut header, &data_lib.types);
}

// Write the top guard of the header file
fn write_header_top_guard(header: &mut File, file_name: &str) {
    writeln!(header, "/**\n * \\file\t{}.h\n * \\brief\tHeader file of the data management lib with the types, enums, structs and functions declarations.\n * \\author\tdata_lib_generator tool\n */\n", file_name).unwrap();
    writeln!(header, "#ifndef {}_H", file_name.to_uppercase()).unwrap();
    writeln!(header, "#define {}_H\n", file_name.to_uppercase()).unwrap();
}

// Write the include statements
fn write_include(header: &mut File) {
    writeln!(header, "#include <stdint.h>\n#include <stdbool.h>\n").unwrap();
}

// Write the define statements
fn write_define(header: &mut File, data_constant: &Vec<DataInit>) {
    for data_constant in data_constant {
        if data_constant.kind == "define" {
            if let Some(InitialValueType::Integer(initialization_value)) = &data_constant.initialization_value {
                writeln!(header, "#define {} {}", data_constant.name, initialization_value).unwrap();
            }else {
                eprintln!("Error: initial_value is None for data_constant");
            }
        }
    }
    writeln!(header, "\n").unwrap();
}

// Write the atomic types definitions
fn write_atomic_type(header: &mut File, data_types: &Vec<Type>) {
    for data_type in data_types {
        if data_type.kind == "atomic" {
            if let Some(DeclarationType::String(declaration)) = &data_type.declaration {
                writeln!(header, "/**\n * Atomic type {}.\n *\n * \\details {} \n*/", data_type.name, data_type.comment).unwrap();
                writeln!(header, "typedef {} {};", declaration, data_type.name).unwrap();
            }else {
                eprintln!("Error: declaration is None for atomic type");
            }
        }
    }
    writeln!(header, "\n").unwrap();
}

// Write the flags definitions
fn write_flags(header: &mut File, data_types: &Vec<Type>) {
    for data_type in data_types {
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
}

// Write the enums definitions
fn write_enums(header: &mut File, data_types: &Vec<Type>) {
    for data_type in data_types {
        if data_type.kind == "enum" {
            if let Some(DeclarationType::FieldEnumDeclarations(declaration)) = &data_type.declaration {
                writeln!(header, "/**\n * Enum {}.\n *\n * \\details {} \n*/", data_type.name, data_type.comment).unwrap();
                writeln!(header, "typedef enum {}_struct {{", data_type.name).unwrap();
                for field_enum_declaration in &declaration.values {
                    writeln!(header, "    {} = {},", field_enum_declaration.name, field_enum_declaration.value).unwrap();
                }
                writeln!(header, "}} {};\n", data_type.name).unwrap();

            }else {
                eprintln!("Error: declaration is None for enum type");
            }
        }
    }
    writeln!(header, "\n").unwrap();
}

// Write the structs definitions
fn write_structs(header: &mut File, data_types: &Vec<Type>) {
    for data_type in data_types {
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



