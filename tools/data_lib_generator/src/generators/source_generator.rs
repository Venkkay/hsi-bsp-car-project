use std::fs::File;
use std::io::Write as IoWrite;
use std::fmt::Write as FmtWrite;
use regex::{Match, Regex};
use crate::models::data_init::InitialValueType;
use crate::models::data_type::{DeclarationType, DomainType};
use crate::models::{DataLib, Type};

// Generate the source file of the data management lib
pub fn generate_source(mut source: File, mut header: File, mut data_lib: &mut DataLib, file_name: &str) {
    write_source_include(&mut source, file_name);

    writeln!(header, "// Function signatures").unwrap();
    write_atomic_types_functions(&mut source, &mut header, &mut data_lib);

    write_flags_functions(&mut source, &mut header, &data_lib.types);
    write_enums_functions(&mut source, &mut header, &data_lib.types);
    write_structs_functions(&mut source, &mut header, &data_lib);

    write_init_functions(&mut source, &mut header, &data_lib);
    write_header_bottom_guard(&mut header, file_name);
}

// Write the include of the source file
fn write_source_include(source: &mut File, file_name: &str) {
    writeln!(source, "/**\n * \\file\t{}.c\n * \\brief\tSource file of the data management lib with the managements functions.\n * \\author\tdata_lib_generator tool\n */\n", file_name).unwrap();
    writeln!(source, "#include \"{}.h\"", file_name).unwrap();
    writeln!(source, "#include <stdint.h>\n#include <stdbool.h>\n").unwrap();
}

// Write the functions to manage the atomic types
fn write_atomic_types_functions(source: &mut File, header: &mut File, data_lib: &mut DataLib) {
    writeln!(header, "// Atomic types setter").unwrap();
    for data_type in &mut data_lib.types {
        if data_type.kind == "atomic" {
            if let Some(DeclarationType::String(declaration)) = &data_type.declaration {
                //writeln!(source, "/**\n * Get the value of {}.\n *\n * @param[in] instance An instance of {}.\n * @return Return the value of the instance.\n */", data_type.name, data_type.name).unwrap();
                //writeln!(source, "{} get_{}({} instance) {{\n    return instance;\n}}", declaration, data_type.name, data_type.name).unwrap();
                let mut check_number = 0;
                let mut tmp_atomic_check = String::new();

                if let Some(DomainType::DomainMinMax(domain)) = &data_type.domain {
                    if let Some(min) = domain.min {
                        if !(declaration.starts_with('u') && min <= 0) {
                            write!(tmp_atomic_check, "    if (value < {}) {{ return false; }}\n", min).unwrap();
                            check_number += 1;
                        }
                    }
                    if let Some(max) = domain.max {
                        let regex_int_size = Regex::new(r"u?(\d+)").unwrap();
                        let int_size_result: Option<Match> = regex_int_size.find(declaration);
                        let int_size = int_size_result.unwrap().as_str().parse::<i32>().unwrap_or(0);
                        if int_size == 32 || (int_size < 32 && max < (2_i32.pow(int_size as u32) - 1)) {
                            write!(tmp_atomic_check, "    if (value > {}) {{ return false; }}", max).unwrap();
                            check_number += 1;
                        }
                    }
                }

                if check_number > 0 {
                    writeln!(header, "/**\n * Check the value of {}.\n *\n * \\param[in] value : The value to check.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name).unwrap();
                    writeln!(header, "bool check_{}(const {} value);", data_type.name, declaration).unwrap();
                    writeln!(source, "bool check_{}(const {} value){{", data_type.name, declaration).unwrap();
                    writeln!(source, "{}", tmp_atomic_check).unwrap();
                    writeln!(source, "    return true;\n}}\n").unwrap();
                    data_type.is_checked = true;
                }

                writeln!(header, "/**\n * Set the value of {}.\n *\n * \\param[out] instance : An instance of {}.\n * \\param[in] value : The value to set.\n * \\return bool : Return True if the value is set, False otherwise.\n */", data_type.name, data_type.name).unwrap();
                writeln!(header, "bool set_{}({}* instance, const {} value);", data_type.name, data_type.name, declaration).unwrap();
                if data_type.is_checked {
                    writeln!(source, "bool set_{}({}* instance, const {} value) {{\n    if (check_{}(value)) {{\n        *instance = value;\n        return true;\n    }}\n    return false;\n}}\n", data_type.name, data_type.name, declaration, data_type.name).unwrap();
                } else {
                    writeln!(source, "bool set_{}({}* instance, const {} value) {{\n    *instance = value;\n    return true;\n}}\n", data_type.name, data_type.name, declaration).unwrap();
                }
            }else {
                eprintln!("Error: declaration is None for atomic type");
            }
        }
    }
}

// Write the functions to manage the flags
fn write_flags_functions(source: &mut File, header: &mut File, data_types: &Vec<Type>) {
    writeln!(header, "\n// Flags getter and setter").unwrap();
    for data_type in data_types {
        if data_type.kind == "flags" {
            if let Some(DeclarationType::FlagsStruct(declaration)) = &data_type.declaration {
                let total_size = declaration.flags.iter().fold(0, |acc, flag| acc + flag.bit_size);
                let mut shift = total_size;
                writeln!(source, "// Flags for {}.\n", data_type.name).unwrap();
                for flag in &declaration.flags {
                    shift -= flag.bit_size;
                    writeln!(header, "/**\n * Get {} flag from {}.\n *\n * @param[in] instance An instance of {}.\n * @return {} : Return the value of the got flag.\n */", flag.name, data_type.name, data_type.name, declaration.field_type).unwrap();
                    writeln!(header, "{} get_{}_from_{}(const {} instance);", declaration.field_type, flag.name, data_type.name, data_type.name).unwrap();
                    writeln!(source, "{} get_{}_from_{}(const {} instance) {{\n    return (instance & 0x{:0fill$x}) >> {};\n}}", declaration.field_type, flag.name, data_type.name, data_type.name, flag.bit_size << shift, shift, fill=(total_size/4 )as usize).unwrap();

                    writeln!(header, "/**\n * Check the value of {}.\n *\n * \\param[in] value : The value to check.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", flag.name).unwrap();
                    writeln!(header, "bool check_{}_in_{}(const {} value);", flag.name, data_type.name, declaration.field_type).unwrap();
                    writeln!(source, "bool check_{}_in_{}(const {} value){{\n    if(value >> {} != 0) {{\n        return false;\n    }}\n    return true;\n}}", flag.name, data_type.name, declaration.field_type, flag.bit_size).unwrap();

                    writeln!(header, "/**\n * Set {} flag in {}.\n *\n * @param[out] instance An instance of {}.\n * \\param[in] value : The value to set.\n * @return Return True if the value is valid, False otherwise.\n */", flag.name, data_type.name, data_type.name).unwrap();
                    writeln!(header, "bool set_{}_in_{}({}* instance, const {} value);", flag.name, data_type.name, data_type.name, declaration.field_type).unwrap();
                    writeln!(source, "bool set_{}_in_{}({}* instance, const {} value) {{\n    if(check_{}_in_{}(value)) {{\n        *instance &= ~0x{:0fill$x};\n        *instance |= value << {};\n        return true;\n    }}\n    return false;\n}}\n", flag.name, data_type.name, data_type.name, declaration.field_type, flag.name, data_type.name, flag.bit_size << shift, shift,  fill=(total_size/4 )as usize).unwrap();
                }
                writeln!(header, "/**\n * Set all flag in {}.\n *\n * @param[out] instance An instance of {}.\n * @return Return True if the value is valid, False otherwise.\n */", data_type.name, data_type.name).unwrap();
                write!(header, "bool set_all_flag_{}({}* instance", data_type.name, data_type.name).unwrap();
                write!(source, "bool set_all_flag_{}({}* instance", data_type.name, data_type.name).unwrap();
                for flag in &declaration.flags {
                    write!(header, ", const {} {}", declaration.field_type, flag.name).unwrap();
                    write!(source, ", const {} {}", declaration.field_type, flag.name).unwrap();
                }
                writeln!(header, ");").unwrap();
                writeln!(source, ") {{").unwrap();
                for flag in &declaration.flags {
                    writeln!(source, "    set_{}_in_{}(instance, {});", flag.name, data_type.name, flag.name).unwrap();
                }
                writeln!(source, "    return true;\n}}\n").unwrap();

                writeln!(header, "/**\n * Set {}.\n *\n * \\param[out] instance An instance of {}.\n * \\param[in] value : The value to set.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name, data_type.name).unwrap();
                writeln!(header, "bool set_{}({}* instance, const {} value);", data_type.name, data_type.name, declaration.field_type).unwrap();
                writeln!(source, "bool set_{}({}* instance, const {} value) {{\n    *instance = value;\n    return true;\n}}\n", data_type.name, data_type.name, data_type.name).unwrap();

                writeln!(source, "\n").unwrap();
            }else {
                eprintln!("Error: declaration is None for atomic type");
            }
        }
    }
}

// write the functions to manage the enums
fn write_enums_functions(source: &mut File, header: &mut File, data_types: &Vec<Type>) {
    writeln!(source, "// Enums Setter\n").unwrap();
    writeln!(header, "\n// Enums getter and setter").unwrap();
    for data_type in data_types {
        if data_type.kind == "enum" {
            if let Some(DeclarationType::FieldEnumDeclarations(declaration)) = &data_type.declaration {
                writeln!(header, "/**\n * Check the value of {}.\n *\n * \\param[in] value The value to check.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name).unwrap();
                writeln!(header, "bool check_{}({} value);", data_type.name, declaration.value_type).unwrap();

                write!(source, "bool check_{}(const {} value){{\n    if(!(", data_type.name, declaration.value_type).unwrap();
                for (i, field_enum_declaration) in declaration.values.iter().enumerate() {
                    if i < declaration.values.len() - 1 {
                        write!(source, "value == {} || ", field_enum_declaration.name).unwrap();
                    }
                    else {
                        write!(source, "value == {}", field_enum_declaration.name).unwrap();
                    }
                }
                writeln!(source, ")) {{\n        return false;\n    }}\n    return true;\n}}\n").unwrap();


                writeln!(header, "/**\n * Set the value of {}.\n *\n * \\param[out] instance An instance of {}.\n * \\param[in] value : The value to set.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name, data_type.name).unwrap();
                writeln!(header, "bool set_{}({}* instance, {} value);", data_type.name, data_type.name, declaration.value_type).unwrap();
                writeln!(source, "bool set_{}({}* instance, const {} value) {{\n    if (check_{}(value)) {{\n        *instance = value;\n        return true;\n    }}\n    return false;\n}}\n", data_type.name, data_type.name, declaration.value_type, data_type.name).unwrap();

            }else {
                eprintln!("Error: declaration is None for atomic type");
            }
        }
    }
}

// Write the functions to manage the structs
fn write_structs_functions(source: &mut File, header: &mut File, data_lib: &DataLib) {
    writeln!(source, "// Struct getter and setter\n").unwrap();
    writeln!(header, "\n// Struct getter and setter").unwrap();
    for data_type in &data_lib.types {
        if data_type.kind == "struct" {
            if let Some(DeclarationType::FieldStructDeclarations(declaration)) = &data_type.declaration {
                for field_struct_declaration in declaration {
                    let current_type = data_lib.types.iter().find(|&x| x.name == field_struct_declaration.field_type).unwrap();
                    let mut current_type_declaration = String::new();
                    if let Some(DeclarationType::String(declaration)) = &current_type.declaration {
                        current_type_declaration = declaration.clone();
                    }
                    else if let Some(DeclarationType::FlagsStruct(declaration)) = &current_type.declaration {
                        current_type_declaration = declaration.field_type.clone();
                    }
                    else if let Some(DeclarationType::FieldEnumDeclarations(declaration)) = &current_type.declaration {
                        current_type_declaration = declaration.value_type.clone();
                    }

                    writeln!(header, "/**\n * Get {} field from {}.\n *\n * \\param[in] instance An instance of {}.\n * \\return {} : Return the value of the got field.\n */", field_struct_declaration.name, data_type.name, data_type.name, field_struct_declaration.field_type).unwrap();
                    writeln!(header, "{} get_{}_from_{}(const {} instance);", field_struct_declaration.field_type, field_struct_declaration.name, data_type.name, data_type.name).unwrap();
                    writeln!(source, "{} get_{}_from_{}(const {} instance) {{\n    return instance.{};\n}}", field_struct_declaration.field_type, field_struct_declaration.name, data_type.name, data_type.name, field_struct_declaration.name).unwrap();

                    writeln!(header, "/**\n * Set {} field in {}.\n *\n * \\param[out] instance : An instance of {}.\n * \\param[in] value : The value to set.\n * \\return bool :  Return True if the value is valid, False otherwise.\n */", field_struct_declaration.name, data_type.name, data_type.name).unwrap();
                    writeln!(header, "bool set_{}_in_{}({}* instance, const {} value);", field_struct_declaration.name, data_type.name, data_type.name, current_type_declaration).unwrap();
                    writeln!(source, "bool set_{}_in_{}({}* instance, const {} value) {{\n    return set_{}(&instance->{}, value);\n}}\n", field_struct_declaration.name, data_type.name, data_type.name, current_type_declaration, field_struct_declaration.field_type, field_struct_declaration.name).unwrap();
                }


                let mut tmp_signature_body = String::new();
                let mut tmp_check_body = String::new();
                let mut is_checked = false;
                for (i, field) in declaration.iter().enumerate() {
                    let current_type = data_lib.types.iter().find(|&x| x.name == field.field_type).unwrap();
                    if current_type.is_checked {
                        if i < declaration.len() - 1  {
                            write!(tmp_signature_body, "const {} {}, ", field.field_type, field.name).unwrap();
                        }
                        else{
                            write!(tmp_signature_body, "const {} {}", field.field_type, field.name).unwrap();
                        }
                        writeln!(tmp_check_body, "    if (!check_{}({})) {{ return false;}}", field.field_type, field.name).unwrap();
                    }
                }
                if tmp_signature_body.len() > 0 {
                    writeln!(header, "/**\n * Check all values to set in {}.\n *\n * \\param[out] instance : An instance of {}.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name, data_type.name).unwrap();
                    if tmp_signature_body.ends_with(", "){
                        tmp_signature_body.pop();
                        tmp_signature_body.pop();
                    }
                    write!(header, "bool check_{}(", data_type.name).unwrap();
                    write!(source, "bool check_{}(", data_type.name).unwrap();
                    write!(header, "{}", tmp_signature_body).unwrap();
                    write!(source, "{}", tmp_signature_body).unwrap();
                    writeln!(header, ");").unwrap();
                    writeln!(source, ") {{").unwrap();
                    write!(source, "{}", tmp_check_body).unwrap();
                    writeln!(source, "    return true;\n}}\n\n").unwrap();
                    is_checked = true;
                }

                writeln!(header, "/**\n * Set all field in {}.\n *\n * \\param[out] instance : An instance of {}.\n * \\return bool : Return True if the value is valid, False otherwise.\n */", data_type.name, data_type.name).unwrap();
                write!(header, "bool set_{}({}* instance", data_type.name, data_type.name).unwrap();
                write!(source, "bool set_{}({}* instance", data_type.name, data_type.name).unwrap();
                for field in declaration {
                    write!(header, ", {} {}", field.field_type, field.name).unwrap();
                    write!(source, ", {} {}", field.field_type, field.name).unwrap();
                }
                writeln!(header, ");").unwrap();
                writeln!(source, ") {{").unwrap();
                let mut tmp_set_body = String::new();
                if is_checked {
                    write!(source, "    if (!check_{}(", data_type.name).unwrap();
                    for (i, field) in declaration.iter().enumerate() {
                        let current_type = data_lib.types.iter().find(|&x| x.name == field.field_type).unwrap();
                        if current_type.is_checked {
                            if i < declaration.len() - 1 {
                                write!(tmp_set_body, "{}, ", field.name).unwrap();
                            }
                            else {
                                write!(tmp_set_body, "{}", field.name).unwrap();
                            }
                        }
                    }
                    if tmp_set_body.ends_with(", "){
                        tmp_set_body.pop();
                        tmp_set_body.pop();
                    }
                    write!(source, "{}", tmp_set_body).unwrap();
                    writeln!(source, ")) {{\n        return false;\n    }}").unwrap();
                }

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
}

// Write the functions to init the data
fn write_init_functions(source: &mut File, header: &mut File, data_lib: &DataLib) {
    for data_init in &data_lib.data {
        if data_init.field_type == "init" {
            writeln!(header, "/**\n * \\brief\tInit {}\n * \\return\t{} : the initialized struct.\n */", data_init.name, data_init.field_type).unwrap();
            writeln!(source, "{} init_{}(){{\n", data_init.field_type, data_init.name).unwrap();
            if let Some(InitialValueType::FieldStructInitDeclarations(declaration)) = &data_init.initialization_value {
                writeln!(source, "    {} {} = {{", data_init.field_type, data_init.name).unwrap();
                for (i, field_struct_init_declaration) in declaration.iter().enumerate() {
                    if i < declaration.len() - 1 {
                        writeln!(source, "        .{} = {},", field_struct_init_declaration.name, field_struct_init_declaration.value).unwrap();
                    } else {
                        writeln!(source, "        .{} = {}", field_struct_init_declaration.name, field_struct_init_declaration.value).unwrap();
                    }
                }
                writeln!(source, "    }};\n    return {};\n}}\n", data_init.name).unwrap();
            }
        }
    }
}

// Write the bottom guard of the header file
fn write_header_bottom_guard(header: &mut File, file_name: &str) {
    writeln!(header, "#endif // {}_H", file_name.to_uppercase()).unwrap();
}