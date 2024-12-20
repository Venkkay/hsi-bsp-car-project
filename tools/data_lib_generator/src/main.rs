pub mod models;

use crate::models::{DataLib, Type};
use std::fs;

use std::{error::Error, fs::File, process};
use std::str::FromStr;
use std::string::ParseError;
use csv::{StringRecordsIter};
use crate::models::data_type::{DeclarationType, DomainType, FieldEnumDeclaration, FieldStructDeclaration};
use crate::models::data_type::DeclarationType::{FieldEnumDeclarations, FieldStructDeclarations, String};
use std::string::String as OtherString;

use regex::{Regex, RegexSet};

impl FromStr for DeclarationType {
    type Err = ParseError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s {
            "struct" => Ok(FieldStructDeclarations(Vec::new())),
            "enum" => Ok(FieldEnumDeclarations(Vec::new())),
                _ => Ok(String(s.parse().unwrap()))
        }
    }
}

impl FromStr for DomainType{
    type Err = ParseError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s {
            _ => Ok(DomainType::String(s.to_string()))
        }
    }
}

fn read_json() -> DataLib {
    let json_file_path = "../../applicative_data.json";
    //let file = File::open(json_file_path).expect("file not found");

    let json_data: OtherString = fs::read_to_string(json_file_path).expect("file not found");
    let data_lib: DataLib = serde_json::from_str(&json_data).expect("error while parsing json");
    data_lib
}

fn read_csv() -> Result<(), Box<dyn Error>> {
    let csv_file_path = "../../applicative_data.csv";
    //let file = File::open(json_file_path).expect("file not found");

    let file = File::open(csv_file_path)?;
    let mut rdr = csv::Reader::from_reader(file);
    generate_json_from_csv(rdr.records()).expect("Can't generate JSON");
    Ok(())
}

fn generate_json_from_csv(csv_input: StringRecordsIter<File>) -> Result<(), Box<dyn Error>> {
    for result in csv_input {

        let record = result?;
        let name = &record[0];
        let kind = &record[1];
        let declaration = &record[2];
        let domain = &record[3];
        let comments = &record[4];

        if kind == "enum" {
            println!("ENUM");
            let vec_enum = parse_enum(declaration);
            let data : Type = Type
            {
                name: name.to_string(),
                kind: kind.to_string(),
                declaration: vec_enum,
                domain: domain.parse().unwrap(),
                comment: comments.to_string()
            };
        }else if kind == "struct" {
            println!("STRUCT");
            let vec_struct = parse_struct(declaration);
        }else{
            println!("ATOMIC");
            if(domain != "" && domain != "boolean" && domain != "unsigned int"){
                println!("PARSE DOMAIN");
                //parse_domain(domain);
            }
        }
        //parse_domain(domain);
        //println!("{:?}", data);
    }
    Ok(())
}

fn parse_domain(domain : &str)
{
    let reg = Regex::new(r"\d+").unwrap();
    let Some(found) = reg.captures(&domain) else { return };

    println!("{:?}", found);
    
    let data = r#"
        {
            "min": {found},
            "max": 255
        }"#;
    
    //"T".to_string()
}

fn parse_enum(enum_input : &str) -> DeclarationType {
    let enums_declaration : Vec<FieldEnumDeclaration> = vec![];

    println!("{:?}", enum_input);



    DeclarationType::FieldEnumDeclarations(enums_declaration)
}

fn parse_struct(struct_input : &str) -> DeclarationType {
    let mut structs_declaration : Vec<FieldStructDeclaration> = vec![];

    println!("{:?}", struct_input);

    let mut iter = struct_input.split_whitespace();

    for i in iter {
        if(i != "{" && i != "}") {
            let re = Regex::new(r"[a-zA-Z_]*[^;]");
            let Some(caps) = re.unwrap().captures(i) else {
                println!("ERROR");
                return DeclarationType::FieldStructDeclarations(Vec::new());
            };
            println!("{:?}", &caps[0]);
            let data_parsed: FieldStructDeclaration = FieldStructDeclaration {
                name: "test".to_string(),
                field_type: "test".to_string(),
            };
        }
    }


    //structs_declaration.push(data_parsed);

    DeclarationType::FieldStructDeclarations(structs_declaration)
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
    //let data_lib = read_json();
    //generate_data_lib(data_lib);
    if let Err(err) = read_csv() {
        println!("{}", err);
        process::exit(1);
    }
}
