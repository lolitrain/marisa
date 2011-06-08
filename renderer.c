#include <Python.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

#include "list.h"
#include "texture.h"
#include "gl_renderer.h"
#include "sprite.h"
#include "font.h"
#include "bullets.h"

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

long frame_time = 0;
static PyObject* renderer_set_frame_time(PyObject* self, PyObject* args)
{
	if(!PyArg_ParseTuple(args, "i", &frame_time))
	   return NULL;

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* renderer_bullets_draw(PyObject* self, PyObject* args)
{
	bullets_draw();

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* renderer_bullets_do_frame(PyObject* self, PyObject* args)
{
	bullets_do_frame();

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* renderer_bullets_count(PyObject* self, PyObject* args)
{
	return PyLong_FromLong(bullets_count());
}

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

struct py_font {
	PyObject_HEAD
	/* Type-specific fields go here. */
	struct font f;
};


static int py_font_init(struct py_font* self, PyObject* args, PyObject* kwargs)
{
	if(!PyArg_ParseTuple(args, "iiii", &self->f.texture, &self->f.cwidth, &self->f.cheight, &self->f.chars_per_line))
		return -1;

	return 0;
}

static PyObject* py_font_show_text(struct py_font* self, PyObject* args)
{
	const char* str;
	float bx, by;
	if(!PyArg_ParseTuple(args, "(ff)s", &bx, &by, &str))
		return NULL;

	font_show_text(&self->f, str, bx, by);
	
	Py_INCREF(Py_None);
	return Py_None;
}


static PyMethodDef py_font_methods[] = 
{
	{"show_text", (PyCFunction)py_font_show_text, METH_VARARGS, "Prints text on the screen"},

	{NULL, NULL, 0, NULL}
};

static PyTypeObject font_type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "renderer.Font",             /*tp_name*/
    sizeof(struct py_font), /*tp_basicsize*/
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
    "Font Object",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    py_font_methods,         /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)py_font_init,      /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};


static PyObject* renderer_bullet_create(PyObject* self, PyObject* args)
{
	struct py_sprite* sprite;
	struct vector2d start, headto;
	float speed;
	if(!PyArg_ParseTuple(args, "O!(ff)(ff)f", &sprite_type, &sprite, &start.vec[0], &start.vec[1], &headto.vec[0], &headto.vec[1], &speed))
	   return NULL;

	if(bullet_create(&sprite->s, start, headto, speed) < 0)
		return NULL;
	
	get_sprite(&sprite->s);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* renderer_bullets_shutdown(PyObject* self, PyObject* args)
{
	bullets_shutdown();
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
	{"set_frame_time", renderer_set_frame_time, METH_VARARGS, "Sets the current frame time for C code"},
	{"bullets_draw", renderer_bullets_draw, METH_VARARGS, "Draws all current bullets on the screen"},
	{"bullets_do_frame", renderer_bullets_do_frame, METH_VARARGS, "Calculates one frame of bullet motion"},
	{"bullets_count", renderer_bullets_count, METH_VARARGS, "Returns the number of active bullets"},
	{"bullets_shutdown", renderer_bullets_shutdown, METH_VARARGS, "Clears all the bullets"},
	{"bullet_create", renderer_bullet_create, METH_VARARGS, "Adds a new bullet"},
	
	{NULL, NULL, 0, NULL}
};


void initrenderer()
{
	PyObject* m;
	sprite_type.tp_new = PyType_GenericNew;
	font_type.tp_new = PyType_GenericNew;
	if(PyType_Ready(&sprite_type) < 0)
	{
		printf("Sprite Type was not ready\n");
		return;
	}

	if(PyType_Ready(&font_type) < 0)
	{
		printf("Font type was not ready\n");
		return;
	}
	m = Py_InitModule("renderer", renderer_methods);
	Py_INCREF(&sprite_type);
	PyModule_AddObject(m, "Sprite", (PyObject*)&sprite_type);
	Py_INCREF(&font_type);
	PyModule_AddObject(m, "Font", (PyObject*)&font_type);
}
