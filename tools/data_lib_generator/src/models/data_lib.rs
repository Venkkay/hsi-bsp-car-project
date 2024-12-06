use crate::models::Type;
use serde::Deserialize;

#[derive(Deserialize)]
pub struct DataLib {
    pub(crate) types: Vec<Type>,
}
