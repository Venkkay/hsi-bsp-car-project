use crate::models::Type;
use serde::Deserialize;
use crate::models::DataInit;

#[derive(Deserialize)]
pub struct DataLib {
    pub(crate) types: Vec<Type>,
    pub(crate) data: Vec<DataInit>,
}
