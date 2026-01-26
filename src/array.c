mod errors;
use errors::ArrayError;
use std::ops::Add;
use std::ops::Index;

#[macro_export]
macro_rules! box_array {

    ($value:expr; $len:expr) => {{
        vec![$value; $len].into_boxed_slice()
    }};

    ($($value:expr),* $(,)?) => {{
        vec![$($value),*].into_boxed_slice()
    }};
}

pub struct Array {
    array: Box<[f64]>,
    shape: Box<[usize]>,
}

impl Array {
    fn new(array: &[f64], shape: &[usize]) -> Array {
        Self {
            array: array.into(),
            shape: shape.into(),
        }
    }

    fn zeros(shape: &[usize]) -> Array {
        Self {
            array: box_array![0.0; shape.iter().product()],
            shape: shape.into(),
        }
    }

    fn ones(shape: &[usize]) -> Array {
        Self {
            array: box_array![1.0; shape.iter().product()],
            shape: shape.into(),
        }
    }

    fn len(&self) -> usize {
        self.shape.iter().product()
    }

    fn reshape(&mut self, new_shape: &[usize]) -> Result<(), ArrayError> {
        if self.len() == new_shape.iter().product() {
            self.shape = new_shape.into()
        }
        Err(ArrayError::ReshapeError)
    }
}

pub struct ArrayView<'a> {
    array: &'a [f64],
    shape: Box<[usize]>,
}

impl<'a> Index<usize> for Array {
    type Output = Box<ArrayView<'a>>;

    fn index(&'a self, index: usize) -> &ArrayView<'a> {
        &self.array
    }
}

impl Add for Array {
    type Output = Array;

    fn add(&self, other: &self) -> Result<Array, ArrayError> {
        if self.shape != other.shape {
            Err(ArrayError::ShapeError)
        }
        let i = 0;
        let new_array: Box<[f64]> = Into::into(vec![0.0; self.array.len()]);

        while i < self.array.len() {
            new_array[i] = self.array[i] + other.array[i];
        }
        todo!()
    }
}
