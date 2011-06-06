#include <Python.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

#include "texture.h"
#include "gl_renderer.h"

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

PyMethodDef renderer_methods[] = 
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

void initrenderer()
{
	Py_InitModule("renderer", renderer_methods);
}
