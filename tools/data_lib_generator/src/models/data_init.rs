use serde::Deserialize;
use crate::models::data_type::{FieldEnumDeclaration, FieldStructDeclaration};

#[derive(Deserialize, Debug)]
pub struct DataInit {
    pub(crate) id: i32,
    pub(crate) name: String,
    #[serde(rename = "type")]
    pub(crate) field_type: String,
    pub(crate) dimension: i32,
    pub(crate) initialization_value: Option<InitialValueType>,
    pub(crate) comment: String,
}

#[derive(Deserialize, Debug)]
#[serde(untagged)]
pub enum InitialValueType {
    Integer(i32),
    FieldStructInitDeclarations(Vec<FieldStructInitDeclaration>),
}

#[derive(Deserialize, Debug)]
pub struct FieldStructInitDeclaration {
    pub(crate) name: String,
    pub(crate) value: i32,
}