typedef struct {
    PyObject_HEAD
	uWS::WebSocket<false, true> *ws;
} WebSocketObject;

static PyObject *WebSocket_end(WebSocketObject *self, PyObject *args) {

    Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *WebSocket_send(WebSocketObject *self, PyObject **args, int nargs) {

	PyObject *pythonMessage = args[0];

	// string to utf8
	Py_ssize_t size;
	const char *str = PyUnicode_AsUTF8AndSize(pythonMessage, &size);
	std::string_view message(str, (size_t) size);

    // bara om redan utf8
    //auto *utf8 = PyUnicode_DATA(pythonMessage);
    //Py_ssize_t size = PyUnicode_GetLength(pythonMessage);

    //Py_buffer *buffer = PyMemoryView_GET_BUFFER(pythonMessage);
	//self->ws->send({(char *) buffer->buf, buffer->len}, uWS::OpCode::TEXT);

    self->ws->send({str, (size_t) size}, uWS::OpCode::TEXT);

    Py_INCREF(Py_None);
	return Py_None;
}

static PyMethodDef WebSocket_methods[] = {
    {"end", (PyCFunction) WebSocket_end, METH_VARARGS, "no doc"},
    {"send", (PyCFunction) WebSocket_send, METH_FASTCALL, "no doc"},
    {NULL}
};

static PyTypeObject WebSocketType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "WebSocket",  // tp_name
    sizeof(WebSocketObject), // tp_basicsize
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

    WebSocket_methods, // tp_methods
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