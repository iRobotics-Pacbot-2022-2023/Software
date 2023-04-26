//ignore the errors for now
#define PY_SSIZE_T_CLEAN
#include <Python.h>

int main()
{
    Py_Initialize();

    // Import necessary Python modules
    PyRun_SimpleString("import robomodules\n");
    PyRun_SimpleString("from messages import MsgType\n");

    // Load the Python program
    PyObject* module = PyImport_ImportModule("__main__");
    PyObject* dict = PyModule_GetDict(module);
    PyObject* main_func = PyDict_GetItemString(dict, "main");

    // Call the main function in the Python program
    PyObject* result = PyObject_CallObject(main_func, NULL);

    Py_Finalize();
    return 0;
}

