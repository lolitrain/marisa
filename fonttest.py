import ctypes
import cairo


_initialized = False
def create_cairo_font_face_for_file (filename, faceindex=0, loadoptions=0):
    global _initialized
    global _freetype_so
    global _cairo_so
    global _ft_lib
    global _surface

    CAIRO_STATUS_SUCCESS = 0
    FT_Err_Ok = 0

    if not _initialized:

        # find shared objects
        _freetype_so = ctypes.CDLL ("libfreetype.so.6")
        _cairo_so = ctypes.CDLL ("libcairo.so.2")

        _cairo_so.cairo_ft_font_face_create_for_ft_face.restype = ctypes.c_void_p
        _cairo_so.cairo_ft_font_face_create_for_ft_face.argtypes = [ ctypes.c_void_p, ctypes.c_int ]
        _cairo_so.cairo_set_font_face.argtypes = [ ctypes.c_void_p, ctypes.c_void_p ]
        _cairo_so.cairo_font_face_status.argtypes = [ ctypes.c_void_p ]
        _cairo_so.cairo_status.argtypes = [ ctypes.c_void_p ]

        # initialize freetype
        _ft_lib = ctypes.c_void_p ()
        if FT_Err_Ok != _freetype_so.FT_Init_FreeType (ctypes.byref (_ft_lib)):
          raise "Error initialising FreeType library."

        class PycairoContext(ctypes.Structure):
            _fields_ = [("PyObject_HEAD", ctypes.c_byte * object.__basicsize__),
                ("ctx", ctypes.c_void_p),
                ("base", ctypes.c_void_p)]

        _surface = cairo.ImageSurface (cairo.FORMAT_A8, 0, 0)

        _initialized = True

    # create freetype face
    ft_face = ctypes.c_void_p()
    cairo_ctx = cairo.Context (_surface)
    cairo_t = PycairoContext.from_address(id(cairo_ctx)).ctx

    if FT_Err_Ok != _freetype_so.FT_New_Face (_ft_lib, filename, faceindex, ctypes.byref(ft_face)):
        raise Exception("Error creating FreeType font face for " + filename)

    # create cairo font face for freetype face
    cr_face = _cairo_so.cairo_ft_font_face_create_for_ft_face (ft_face, loadoptions)
    if CAIRO_STATUS_SUCCESS != _cairo_so.cairo_font_face_status (cr_face):
        raise Exception("Error creating cairo font face for " + filename)

    _cairo_so.cairo_set_font_face (cairo_t, cr_face)
    if CAIRO_STATUS_SUCCESS != _cairo_so.cairo_status (cairo_t):
        raise Exception("Error creating cairo font face for " + filename)

    face = cairo_ctx.get_font_face ()

    return face

if __name__ == '__main__':

    face = create_cairo_font_face_for_file ("/usr/share/fonts/dejavu/DejaVuSansMono-Bold.ttf", 0)
    surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, 512, 64)
    ctx = cairo.Context(surface)
    ctx.set_antialias(cairo.ANTIALIAS_NONE)


    ctx.set_font_face(face)
    ctx.set_font_size(12)

    height = 16
    width = 8
    for i in range(33,80):
        ctx.move_to(width * (i - 33), 13)
        ctx.show_text(chr(i))

    for i in range(80, 127):
        ctx.move_to(width * (i - 80), 29)
        ctx.show_text(chr(i))


    del ctx

    surface.write_to_png("testfont.png")
