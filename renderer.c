#include <Python.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

#include "texture.h"
#include "gl_renderer.h"
#include "sprite.h"

static PyObject* renderer_init(PyObject* self, PyObject* args)
{
	gl_init();
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* renderer_do_frame(PyObject* self, PyObject* args)
{
	gl_do_frame();
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* renderer_load_texture(PyObject* self, PyObject* args)
{
	const char* filename;
	int id;
	if(!PyArg_ParseTuple(args, "s", &filename))
		return NULL;

	id = alloc_texture(filename);
	if(id < 0)
	{
		printf("Error loading texture %s\n", filename);
		return NULL;
	}

	return Py_BuildValue("i", id);
}

static PyObject* renderer_free_texture(PyObject* self, PyObject* args)
{
	int id;
	if(!PyArg_ParseTuple(args, "i", &id))
		return NULL;

	free_texture(id);

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* renderer_bind(PyObject* self, PyObject* args)
{
	int id;
	if(!PyArg_ParseTuple(args, "i", &id))
		return NULL;

	gl_bind_texture(id);

	Py_INCREF(Py_None);
	return Py_None;

}

static PyObject* renderer_texture_width(PyObject* self, PyObject* args)
{
	int id;
	if(!PyArg_ParseTuple(args, "i", &id))
		return NULL;

	return PyLong_FromLong(get_texture_width(id));	
}

static PyObject* renderer_texture_height(PyObject* self, PyObject* args)
{
	int id;
	if(!PyArg_ParseTuple(args, "i", &id))
		return NULL;

	return PyLong_FromLong(get_texture_height(id));	
}

static PyObject* renderer_shutdown(PyObject* self, PyObject* args)
{
	gl_shutdown();
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* renderer_vertex(PyObject* self, PyObject* args)
{
	float v1,v2,v3, u,v;
	if(!PyArg_ParseTuple(args, "(fff)(ff)", &v1, &v2, &v3, &u, &v))
		return NULL;

	gl_vertex(v1,v2,v3,u,v);

	Py_INCREF(Py_None);
	return Py_None;
}

static PyMethodDef renderer_methods[] = 
{
	{"init", renderer_init, METH_VARARGS, "Starts the rendering subsystem"},
	{"do_frame", renderer_do_frame, METH_VARARGS, "Draws one frame"},
	{"load_texture", renderer_load_texture, METH_VARARGS, "Loads a texture from a png file"},
	{"free_texture", renderer_free_texture, METH_VARARGS, "Releases resources used by the texture"},
	{"bind", renderer_bind, METH_VARARGS, "Bind a texture"},
	{"texture_width", renderer_texture_width, METH_VARARGS, "Get texture width"},
	{"texture_height", renderer_texture_height, METH_VARARGS, "Get texture height"},
	{"vertex", renderer_vertex, METH_VARARGS, "Loads a vertex into the renderer"},
	{"shutdown", renderer_shutdown, METH_VARARGS, "shuts down the renderer subsystem"},

	{NULL, NULL, 0, NULL}
};

struct py_sprite {
	PyObject_HEAD
	/* Type-specific fields go here. */
	struct sprite s;
};


static int py_sprite_init(struct py_sprite* self, PyObject* args, PyObject* kwargs)
{
	if(!PyArg_ParseTuple(args, "ffi", &self->s.width, &self->s.height, &self->s.texture))
		return -1;

	return 0;
}

static PyObject* py_sprite_draw(struct py_sprite* self, PyObject* args)
{
	float cx, cy;
	if(!PyArg_ParseTuple(args, "(ff)", &cx, &cy))
		return NULL;

	sprite_draw(&self->s, cx, cy);
	
	Py_INCREF(Py_None);
	return Py_None;
}


static PyMethodDef py_sprite_methods[] = 
{
	{"draw", (PyCFunction)py_sprite_draw, METH_VARARGS, "Draws a sprite on the screen"},

	{NULL, NULL, 0, NULL}
};

static PyTypeObject sprite_type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "renderer.Sprite",             /*tp_name*/
    sizeof(struct py_sprite), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,                         /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    "Sprite Object",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    py_sprite_methods,         /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)py_sprite_init,      /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};

void initrenderer()
{
	PyObject* m;
	sprite_type.tp_new = PyType_GenericNew;
	if(PyType_Ready(&sprite_type) < 0)
	{
		printf("Sprite Type was not ready\n");
		return;
	}
	m = Py_InitModule("renderer", renderer_methods);
	Py_INCREF(&sprite_type);
	PyModule_AddObject(m, "Sprite", (PyObject*)&sprite_type);
}
