#ifndef GL_MATH_H
#define GL_MATH_H

struct vector2d
{
	float vec[2];
};

struct matrix2d
{
	float m[2][2];
};


static inline struct matrix2d matrix_mult(float a[2][2], float b[2][2])
{
	struct matrix2d c;
	c.m[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0];
	c.m[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1];
	c.m[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0];
	c.m[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1];
	return c;
}

static inline struct vector2d matrix_vec_mult(float a[2][2], float b[2])
{
	struct vector2d c;
	c.vec[0] = a[0][0]*b[0] + a[0][1]*b[1];
	c.vec[1] = a[1][0]*b[0] + a[1][1]*b[1];
	return c;
}


static inline struct vector2d vec_add(struct vector2d a, struct vector2d b)
{
	struct vector2d ret = { {a.vec[0]+b.vec[0], a.vec[1]+b.vec[1]}};
	return ret;
}

static inline struct vector2d vec_sub(struct vector2d a, struct vector2d b)
{
	struct vector2d ret = { {a.vec[0]-b.vec[0], a.vec[1]-b.vec[1]}};
	return ret;
}

static inline struct vector2d scalar_mult(struct vector2d a, float scalar)
{
	struct vector2d ret = {{a.vec[0]*scalar, a.vec[1]*scalar}};
	return ret;
}

static inline struct vector2d scalar_div(struct vector2d a, float scalar)
{
	struct vector2d ret = {{a.vec[0]/scalar, a.vec[1]/scalar}};
	return ret;
}

static inline struct vector2d normalize(struct vector2d a)
{
	float length = sqrt(a.vec[0]*a.vec[0] + a.vec[1]*a.vec[1]);
	return scalar_div(a, length);
}

#ifndef PI
#define PI 3.14159265
#endif
static inline float torad(float angle)
{
	return angle*PI/180;
}

#endif
