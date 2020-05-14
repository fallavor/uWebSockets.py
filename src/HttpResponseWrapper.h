typedef struct {
    PyObject_HEAD
	uWS::HttpResponse<false> *res;
} HttpResponseObject;

static PyObject *HttpResponse_end(HttpResponseObject *self, PyObject **args, int nargs) {

	PyObject *one = args[0];

	// string to utf8
	Py_ssize_t size;
	const char *str = PyUnicode_AsUTF8AndSize(one, &size);
	std::string_view message(str, size);

	self->res->end(message);

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *HttpResponse_writeHeader(HttpResponseObject *self, PyObject *args) {

	PyObject *key, *value;
	PyArg_ParseTuple(args, "OO", &key, &value);

	// string to utf8
	Py_ssize_t size;
	const char *str = PyUnicode_AsUTF8AndSize(key, &size);
	std::string_view keyString(str, size);

	str = PyUnicode_AsUTF8AndSize(value, &size);
	std::string_view valueString(str, size);

	self->res->writeHeader(keyString, valueString);

	Py_INCREF(Py_None);
	return Py_None;
}

// HttpResponse method list
static PyMethodDef HttpResponse_methods[] = {
	{"end", (PyCFunction) HttpResponse_end, METH_FASTCALL, "no doc"},
	{"writeHeader", (PyCFunction) HttpResponse_writeHeader, METH_VARARGS, "no doc"},
    {NULL}
};

static PyTypeObject HttpResponseType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "HttpResponse",  // tp_name
    sizeof(HttpResponseObject), // tp_basicsize
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

    HttpResponse_methods, // tp_methods
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