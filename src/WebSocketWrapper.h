typedef struct {
    PyObject_HEAD
        uWS::WebSocket<false, true>* ws;
} WebSocketObject;

static PyObject* WebSocket_end(WebSocketObject* self, PyObject* args) {

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* WebSocket_close(WebSocketObject* self, PyObject* Py_UNUSED(ignored)) {
    self->ws->close();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* WebSocket_send(WebSocketObject* self, PyObject** args, int nargs) {

    PyObject* pythonMessage = args[0];

    // string to utf8
    Py_ssize_t size;
    const char* str = PyUnicode_AsUTF8AndSize(pythonMessage, &size);
    std::string_view message(str, (size_t)size);

    // bara om redan utf8
    //auto *utf8 = PyUnicode_DATA(pythonMessage);
    //Py_ssize_t size = PyUnicode_GetLength(pythonMessage);

    //Py_buffer *buffer = PyMemoryView_GET_BUFFER(pythonMessage);
    //self->ws->send({(char *) buffer->buf, buffer->len}, uWS::OpCode::TEXT);

    self->ws->send({ str, (size_t)size }, uWS::OpCode::TEXT);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* WebSocket_getpeername(WebSocketObject* self, PyObject* Py_UNUSED(ignored)) {
    std::string_view remoteAddr = self->ws->getRemoteAddress();
    if (remoteAddr.length() == 0) {
        Py_INCREF(Py_None);
        return Py_None;
    }

    char addstr[128];
    memset(addstr, 0, sizeof(addstr));
    if (remoteAddr.length() == sizeof(in6_addr)) {
        inet_ntop(AF_INET6, remoteAddr.data(), addstr, sizeof(addstr));
        std::string_view cppstr_v(addstr);
        if (cppstr_v.find(".") != -1) {
            PyObject* pythonMessage = PyUnicode_FromString(cppstr_v.substr(cppstr_v.rfind("f") + 2).data());
            return pythonMessage;
        }
    }
    else if(remoteAddr.length() == sizeof(in_addr)) {
        inet_ntop(AF_INET, remoteAddr.data(), addstr, sizeof(addstr));
    }
    else {
        Py_INCREF(Py_None);
        return Py_None;
    }
    
    PyObject* pythonMessage = PyUnicode_FromString(addstr);
    return pythonMessage;
}

static PyMethodDef WebSocket_methods[] = {
    {"end", (PyCFunction)WebSocket_end, METH_VARARGS, "no doc"},
    {"send", (PyCFunction)WebSocket_send, METH_FASTCALL, "no doc"},
    {"close", (PyCFunction)WebSocket_close, METH_NOARGS, "no doc"},
    {"getpeername", (PyCFunction)WebSocket_getpeername, METH_NOARGS, "no doc"},
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
