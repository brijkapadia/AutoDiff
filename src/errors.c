use std::fmt;
#[derive(Debug, PartialEq, Eq, Clone, Copy)]
pub enum ArrayError {
    ShapeError,
    ReshapeError,
}

impl fmt::Display for ArrayError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{:?}", self)
    }
}

impl std::error::Error for ArrayError {}
