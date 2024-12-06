use serde::Deserialize;

#[derive(Deserialize, Debug)]
pub struct Type {
    pub(crate) name: String,
    pub(crate) kind: String,
    pub(crate) declaration: Option<DeclarationType>,
    pub(crate) domain: Option<DomainType>,
    pub(crate) comment: String,
}

#[derive(Deserialize, Debug)]
#[serde(untagged)]
pub enum DeclarationType {
    String(String),
    FieldStructDeclarations(Vec<FieldStructDeclaration>),
    FieldEnumDeclarations(Vec<FieldEnumDeclaration>),
}

#[derive(Deserialize, Debug)]
pub struct FieldStructDeclaration {
    pub(crate) name: String,
    #[serde(rename = "type")]
    pub(crate) field_type: String,
}

#[derive(Deserialize, Debug)]
pub struct FieldEnumDeclaration {
    pub(crate) name: String,
    pub(crate) value: i8,
}

#[derive(Deserialize, Debug)]
#[serde(untagged)]
pub enum DomainType {
    String(String),
    DomainMinMax(DomainMinMax),
}

#[derive(Deserialize, Debug)]
pub struct DomainMinMax {
    pub(crate) min: i32,
    pub(crate) max: i32,
}
