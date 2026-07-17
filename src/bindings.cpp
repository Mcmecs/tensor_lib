#include <pybind11/pybind11.h>
#include <pybind11/operators.h> // for the math operators (+, -, and *)
#include "matrix.h"

namespace py = pybind11;

// This macro creates the Python module.
// "tensor_ext"
PYBIND11_MODULE(tensor_ext, m) {
    m.doc() = "A high-performance C++ tensor library exported to Python";

    // Expose the Matrix<float> class to Python
    py::class_<Matrix<float>>(m, "Matrix")
        .def(py::init<size_t, size_t>()) // Expose the constructor
        .def("get_rows", &Matrix<float>::getRows)
        .def("get_cols", &Matrix<float>::getCols)
        .def("print", &Matrix<float>::print)
        
        // This allows Python: mat.set(0, 0, 5.5)
        .def("set", [](Matrix<float>& m, size_t r, size_t c, float v) { m(r, c) = v; })
        .def("get", [](const Matrix<float>& m, size_t r, size_t c) { return m(r, c); })

        // Pybind11 automatically maps these to Python's +, -, and * symbols
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * py::self)
        .def(py::self * float()) // scalar multiplication
        .def(py::self + float()); // scalar addition
}