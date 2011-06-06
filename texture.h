#ifndef TEXTURES_H
#define TEXTURES_H

// Maximum number of textures that can be allocated
#define MAX_TEXTURES 10

// initializes the texture module
void init_textures();

// loads a texture from file
// returns texture id, negative if allocation failed
int alloc_texture(const char* filename);

// Check if the texture with this id have been allocated
int is_texture_allocated(int id);

// Frees an allocated texture
void free_texture(int id);

int get_texture_width(int id);
int get_texture_height(int id);

// Makes the id active texture
void bind_texture(int id);
#endif
