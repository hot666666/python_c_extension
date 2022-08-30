#include <Python.h>
#include <stdio.h>

static PyObject *
spam_print(PyObject *self, PyObject *args)
{
    PyObject *pObj = NULL;

    pObj = PyBytes_FromString("Hello Spam World\n"); /* Object creation, ref count = 1. */
    PyObject_Print(pObj, stdout, 0);
    Py_DECREF(pObj); /* ref count becomes 0, object deallocated.
                      * Miss this step and you have a memory leak. */
    Py_RETURN_NONE;
}

static void
PyPrint(char *temp)
{
    PyObject *pObj = NULL;
    pObj = PyBytes_FromString(temp); /* Object creation, ref count = 1. */
    PyObject_Print(pObj, stdout, 0);
    Py_DECREF(pObj);
}

static PyObject *
spam_list_add(PyObject *self, PyObject *args)
{
    PyPrint((char *)"inialize_spamadd\n");

    PyObject *a = NULL;
    PyObject *b = NULL;
    PyObject *ret;
    Py_ssize_t tot_len;
    PyObject *temp_item1 = NULL;
    PyObject *temp_item2 = NULL;

    // OO : PythonObject(PyList), PythonObject(PyList) : args -> &a, &b
    if (!PyArg_ParseTuple(args, "OO", &a, &b))
    {
        PyErr_SetString(PyExc_RuntimeError, "arguments is not a python list");
    };
    if (!PyList_Check(a) || !PyList_Check(b))
    {
        PyErr_SetString(PyExc_RuntimeError, "arguments is not a python list");
    };

    tot_len = PyList_Size(a);
    ret = PyList_New(tot_len);
    if (tot_len < 0)
    {
        PyErr_SetString(PyExc_RuntimeError, "array have any value");
    };

    long val1, val2, ret_val;

    for (int i = 0; i < tot_len; i++)
    {
        temp_item1 = PyList_GetItem(a, i);
        val1 = PyLong_AsLong(temp_item1);
        temp_item2 = PyList_GetItem(b, i);
        val2 = PyLong_AsLong(temp_item2);
        ret_val = val1 + val2;
        PyList_SetItem(ret, i, PyLong_FromLong(ret_val));
    };

    Py_DECREF(a);
    Py_DECREF(b);
    Py_DECREF(temp_item1);
    Py_DECREF(temp_item2);

    Py_INCREF(ret);
    return ret;
};

static PyMethodDef SpamMethods[] = {
    //{"Python에서 호출될 함수명", C에서 정의한 함수, 매개변수를 받을 방법, 함수의 Docs}
    {"sprint", spam_print, METH_VARARGS, "print sample string in python"},
    {"spadd", spam_list_add, METH_VARARGS, "add list object with numerical add"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef spammodule = {
    //필수 포함
    PyModuleDef_HEAD_INIT,
    // python에서 import할 때 모듈의 이름
    "spam",
    //모듈의 docs
    "it is test module",
    // GIL 관련 Parameter, 일반적으로 -1로 지정
    -1,
    //모듈에 포함될 Method Array
    SpamMethods};

PyMODINIT_FUNC
PyInit_spam(void)
{
    return PyModule_Create(&spammodule);
}