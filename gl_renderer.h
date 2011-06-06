#ifndef GL_RENDERER_H
#define GL_RENDERER_H

void gl_init();
void gl_do_frame();
void gl_vertex(float v1, float v2, float v3, float u, float v);
void gl_bind_texture(int id); 
void gl_shutdown();

#endif
