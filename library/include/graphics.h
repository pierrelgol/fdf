/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 07:54:24 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/15 07:54:24 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "essentials.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef union u_vec2 t_vec2;
typedef union u_vec3 t_vec3;
typedef union u_vec4 t_vec4;
typedef union u_col4 t_color;
typedef union u_mat4 t_mat4;

union u_vec2
{
	int32_t data[2];
	struct
	{
		union
		{
			int32_t x;
			int32_t u;
		};

		union
		{
			int32_t y;
			int32_t v;
		};
	};
};

t_vec2  vec2(const int32_t x, const int32_t y);
t_vec2  vec2_add(const t_vec2 v0, const t_vec2 v1);
t_vec2  vec2_sub(const t_vec2 v0, const t_vec2 v1);
t_vec2  vec2_mul(const t_vec2 v0, const t_vec2 v1);
t_vec2  vec2_div(const t_vec2 v0, const t_vec2 v1);
t_vec2  vec2_scale(const t_vec2 v, const int32_t scale);
float_t vec2_distance(const t_vec2 v1, const t_vec2 v2);

union u_vec3
{
	int32_t data[3];

	struct
	{
		union
		{
			int32_t x;
			int32_t u;
		};

		union
		{
			int32_t y;
			int32_t v;
		};

		union
		{
			int32_t z;
			int32_t s;
		};
	};
};

t_vec3  vec3(const int32_t x, const int32_t y, const int32_t z);
t_vec3  vec3_add(const t_vec3 v0, const t_vec3 v1);
t_vec3  vec3_sub(const t_vec3 v0, const t_vec3 v1);
t_vec3  vec3_mul(const t_vec3 v0, const t_vec3 v1);
t_vec3  vec3_div(const t_vec3 v0, const t_vec3 v1);
t_vec3  vec3_scale(const t_vec3 v, const int32_t scale);
float_t vec3_distance(const t_vec3 v1, const t_vec3 v2);

union u_vec4
{
	int32_t data[4];

	struct
	{
		union
		{
			int32_t x;
			int32_t u;
		};

		union
		{
			int32_t y;
			int32_t v;
		};

		union
		{
			int32_t z;
			int32_t s;
		};

		union
		{
			int32_t w;
			int32_t t;
		};
	};
};

t_vec4 vec4(const int32_t x, const int32_t y, const int32_t z, const int32_t w);
t_vec4 vec4_add(const t_vec4 v0, const t_vec4 v1);
t_vec4 vec4_sub(const t_vec4 v0, const t_vec4 v1);
t_vec4 vec4_mul(const t_vec4 v0, const t_vec4 v1);
t_vec4 vec4_div(const t_vec4 v0, const t_vec4 v1);
t_vec4 vec4_scale(const t_vec4 v, const int32_t scale);

union u_mat4
{
	int32_t data[16];
	struct
	{
		t_vec4 rows[4];
	};
};

t_mat4 mat4(const t_vec4 r0, const t_vec4 r1, const t_vec4 r2, const t_vec4 r3);
t_mat4 mat4_identity(void);

union u_col4
{
	int32_t color;
	struct
	{
		uint8_t a;
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};
};

t_color color(const int32_t value);
int32_t clamp(const int32_t min, const int32_t value, const int32_t max);
float fclamp(float min, float value, float max) ;
int32_t	color_value(const t_color col);
float_t	vec2per(const t_vec2 start, const t_vec2 end, const t_vec2 at);
float_t	vec3_percentage(const t_vec3 start, const t_vec3 end, const t_vec3 at);
t_color lerp(const t_color start, const t_color end, const float_t scalar);

#endif
