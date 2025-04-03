#include <pybind11/pybind11.h>
#include <pybind11/stl.h> 
#include "ArraySequence.h"
#include "ListSequence.h"

namespace py = pybind11;
PYBIND11_MODULE(sequences, m) {
    m.doc() = "pybind11 bindings for sequecnces Sequence<int>";
    py::class_<Sequence<int>>(m, "SequenceInt");
    py::class_<MutableArraySequence<int>, Sequence<int>>(m, "MutableArraySequence")
        .def(py::init<>()) 
        .def(py::init([](std::vector<int> init) {
            if (init.empty())
                return new MutableArraySequence<int>();
            else
                return new MutableArraySequence<int>(init.data(), static_cast<int>(init.size()));
        }), py::arg("init_list"))
        .def("get", &MutableArraySequence<int>::Get)
        .def("getFirst", &MutableArraySequence<int>::GetFirst)
        .def("getLast", &MutableArraySequence<int>::GetLast)
        .def("getLength", &MutableArraySequence<int>::GetLength)
        .def("getSubsequence", &MutableArraySequence<int>::GetSubsequence, py::return_value_policy::take_ownership)
        .def("append", &MutableArraySequence<int>::Append, py::return_value_policy::reference_internal)
        .def("prepend", &MutableArraySequence<int>::Prepend, py::return_value_policy::reference_internal)
        .def("insertAt", &MutableArraySequence<int>::InsertAt, py::return_value_policy::reference_internal)
        .def("concat", &MutableArraySequence<int>::Concat, py::return_value_policy::take_ownership);

    py::class_<ImmutableArraySequence<int>, Sequence<int>>(m, "ImmutableArraySequence")
        .def(py::init<>())
        .def(py::init([](std::vector<int> init) {
            if (init.empty())
                return new ImmutableArraySequence<int>();
            else
                return new ImmutableArraySequence<int>(init.data(), static_cast<int>(init.size()));
        }), py::arg("init_list"))
        .def("get", &ImmutableArraySequence<int>::Get)
        .def("getFirst", &ImmutableArraySequence<int>::GetFirst)
        .def("getLast", &ImmutableArraySequence<int>::GetLast)
        .def("getLength", &ImmutableArraySequence<int>::GetLength)
        .def("getSubsequence", &ImmutableArraySequence<int>::GetSubsequence, py::return_value_policy::take_ownership)
        .def("append", &ImmutableArraySequence<int>::Append, py::return_value_policy::take_ownership)
        .def("prepend", &ImmutableArraySequence<int>::Prepend, py::return_value_policy::take_ownership)
        .def("insertAt", &ImmutableArraySequence<int>::InsertAt, py::return_value_policy::take_ownership)
        .def("concat", &ImmutableArraySequence<int>::Concat, py::return_value_policy::take_ownership);

    py::class_<MutableListSequence<int>, Sequence<int>>(m, "MutableListSequence")
        .def(py::init<>())
        .def(py::init([](std::vector<int> init) {
            if (init.empty())
                return new MutableListSequence<int>();
            else
                return new MutableListSequence<int>(init.data(), static_cast<int>(init.size()));
        }), py::arg("init_list"))
        
        .def("get", &MutableListSequence<int>::Get)
        .def("getFirst", &MutableListSequence<int>::GetFirst)
        .def("getLast", &MutableListSequence<int>::GetLast)
        .def("getLength", &MutableListSequence<int>::GetLength)
        .def("getSubsequence", &MutableListSequence<int>::GetSubsequence, py::return_value_policy::take_ownership)
        .def("append", &MutableListSequence<int>::Append, py::return_value_policy::reference_internal)
        .def("prepend", &MutableListSequence<int>::Prepend, py::return_value_policy::reference_internal)
        .def("insertAt", &MutableListSequence<int>::InsertAt, py::return_value_policy::reference_internal)
        .def("concat", &MutableListSequence<int>::Concat, py::return_value_policy::take_ownership);

    py::class_<ImmutableListSequence<int>, Sequence<int>>(m, "ImmutableListSequence")
        .def(py::init<>())
        .def(py::init([](std::vector<int> init) {
            if (init.empty())
                return new ImmutableListSequence<int>();
            else
                return new ImmutableListSequence<int>(init.data(), static_cast<int>(init.size()));
        }), py::arg("init_list"))
        
        .def("get", &ImmutableListSequence<int>::Get)
        .def("getFirst", &ImmutableListSequence<int>::GetFirst)
        .def("getLast", &ImmutableListSequence<int>::GetLast)
        .def("getLength", &ImmutableListSequence<int>::GetLength)
        .def("getSubsequence", &ImmutableListSequence<int>::GetSubsequence, py::return_value_policy::take_ownership)
        .def("append", &ImmutableListSequence<int>::Append, py::return_value_policy::take_ownership)
        .def("prepend", &ImmutableListSequence<int>::Prepend, py::return_value_policy::take_ownership)
        .def("insertAt", &ImmutableListSequence<int>::InsertAt, py::return_value_policy::take_ownership)
        .def("concat", &ImmutableListSequence<int>::Concat, py::return_value_policy::take_ownership);
}
