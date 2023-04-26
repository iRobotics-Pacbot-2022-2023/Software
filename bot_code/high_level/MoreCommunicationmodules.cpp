//ignore the errors for now
#define PY_SSIZE_T_CLEAN
#include <Python.h>

int main()
{
    Py_Initialize();

    // Import necessary Python modules
    PyRun_SimpleString("import os\n");
    PyRun_SimpleString("import robomodules as rm\n");
    PyRun_SimpleString("from messages import *\n");

    // Load the Python program
    PyObject* module = PyImport_ImportModule("__main__");
    PyObject* dict = PyModule_GetDict(module);

    // Create Python objects for the necessary variables and classes
    PyObject* server_address = PyUnicode_FromString(os.environ.get("BIND_ADDRESS", "localhost"));
    PyObject* server_port = PyUnicode_FromString(os.environ.get("BIND_PORT", "11297"));
    PyObject* local_address = PyUnicode_FromString(os.environ.get("LOCAL_ADDRESS", "localhost"));
    PyObject* local_port = PyUnicode_FromString(os.environ.get("LOCAL_PORT", "11295"));
    PyObject* server_frequency = PyLong_FromLong(0);
    PyObject* local_frequency = PyLong_FromLong(30);

    PyObject* message_buffers = PyDict_GetItemString(dict, "message_buffers");
    PyObject* msg_type = PyDict_GetItemString(dict, "MsgType");

    PyObject* pacbot_server_client_class = PyDict_GetItemString(dict, "PacbotServerClient");
    PyObject* pacbot_comms_module_class = PyDict_GetItemString(dict, "PacbotCommsModule");

    // Create instances of the Python classes
    PyObject* pacbot_server_client_instance = PyObject_CallFunctionObjArgs(pacbot_server_client_class, server_address, server_port, local_frequency, NULL);
    PyObject* pacbot_comms_module_instance = PyObject_CallFunctionObjArgs(pacbot_comms_module_class, server_address, server_port, local_address, local_port, NULL);

    // Call the necessary functions in the Python program
    PyObject_CallMethod(pacbot_server_client_instance, "connect", NULL);
    PyObject_CallMethod(pacbot_comms_module_instance, "run", NULL);

    // Cleanup
    Py_DECREF(pacbot_server_client_instance);
    Py_DECREF(pacbot_comms_module_instance);
    Py_DECREF(server_address);
    Py_DECREF(server_port);
    Py_DECREF(local_address);
    Py_DECREF(local_port);
    Py_DECREF(server_frequency);
    Py_DECREF(local_frequency);

    Py_Finalize();
    return 0;
}


/**    Include the necessary C++ headers for embedding Python in your code, such as "Python.h".
    Initialize the Python interpreter by calling "Py_Initialize()".
    Import the necessary Python modules in your code, such as "robomodules" and "messages".
    Load the Python program using "PyImport_ImportModule()" or "PyRun_SimpleString()".
    Create Python objects for the necessary variables and classes used in the Python program.
    Call the necessary functions in the Python program using "PyObject_CallMethod()" or "PyObject_CallFunctionObjArgs()".
    Cleanup the Python interpreter by calling "Py_Finalize()".*/