typedef struct {
    PyObject_HEAD
	uWS::HttpRequest *req;
} HttpRequestObject;

static PyObject *HttpRequest_getHeader(HttpRequestObject *self, PyObject *args) {

	PyObject *one;
	PyArg_ParseTuple(args, "O", &one);

	// string to utf8
	Py_ssize_t size;
	const char *str = PyUnicode_AsUTF8AndSize(one, &size);
	std::string_view header(str, size);

	std::cout << header << " is: " << self->req->getHeader(header) << std::endl;
	
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef HttpRequest_methods[] = {
    {"getHeader", (PyCFunction) HttpRequest_getHeader, METH_VARARGS, "no doc"},
    {NULL}
};

static PyTypeObject HttpRequestType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "HttpRequest",  // tp_name
    sizeof(HttpRequestObject), // tp_basicsize
    0, // tp_itemsize
    nullptr,  // tp_dealloc
    0,  // tp_print
    nullptr, // tp_getattr
    nullptr, // tp_setattr
    nullptr, // tp_as_async

    nullptr, // tp_repr

    nullptr, // tp_as_number;
    nullptr, // tp_as_sequence;
    nullptr, // tp_as_mapping;

    nullptr, // tp_hash;
    nullptr, // tp_call;
    nullptr, // tp_str;
    nullptr, // tp_getattro;
    nullptr, // tp_setattro;

    nullptr, // tp_as_buffer

    Py_TPFLAGS_DEFAULT,  // tp_flags
    "no doc",  // tp_doc

    nullptr, // tp_traverse

    nullptr, // tp_clear
    nullptr, // tp_richcompare

    0, //tp_weaklistoffset

    nullptr, // tp_iter;
    nullptr, // tp_iternext;

    HttpRequest_methods, // tp_methods
    nullptr, // tp_members;
    nullptr, // tp_getset;
    nullptr, // tp_base;

    nullptr, // tp_dict;
    nullptr, // tp_descr_get;
    nullptr, // tp_descr_set;
    0, // tp_dictoffset;
    nullptr, // tp_init;
    nullptr, // tp_alloc;    
    PyType_GenericNew, //tp_new
};