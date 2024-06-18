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

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

typedef union u_vec2   t_vec2;
typedef union u_vec3   t_vec3;
typedef union u_color  t_color;
typedef union u_color2 t_color2;

union u_vec2
{
	float_t data[2];
	union
	{
		struct
		{
			float_t x;
			float_t u;
		};
		struct
		{
			float_t y;
			float_t v;
		};
	};
};

union u_vec3
{
	float_t data[3];
	union
	{
		struct
		{
			float_t x;
			float_t u;
		};
		struct
		{
			float_t y;
			float_t v;
		};
		struct
		{
			float_t z;
			float_t t;
		};
	};
};

union u_color
{
	int32_t argb;
	struct
	{
		uint8_t a;
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};
};

t_color color(const int32_t argb);

union u_color2
{
	int32_t argb[2];
	struct
	{
		t_color c[2];
	};
};

int32_t color2_lerp(t_vec2 at, t_vec2 start, t_vec2 end, const t_color2 start_end);
t_color2 color2(const int32_t argb1, const int32_t argb2);

// Vector operations
t_vec2  vec2(const float_t x, const float_t y);
t_vec2  vec2_add(const t_vec2 a, const t_vec2 b);
t_vec2  vec2_sub(const t_vec2 a, const t_vec2 b);
t_vec2  vec2_mul(const t_vec2 a, const t_vec2 b);
t_vec2  vec2_div(const t_vec2 a, const t_vec2 b);
float_t vec2_length(t_vec2 v);
float_t vec2_length_squared(t_vec2 v);
t_vec2  vec2_normalize(t_vec2 v);
void    vec2_normalized(t_vec2 *v);

t_vec3 vec3(const float_t x, const float_t y, const float_t z);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_mul(t_vec3 a, t_vec3 b);
t_vec3 vec3_div(t_vec3 a, t_vec3 b);
t_vec3 vec3_delta(const t_vec3 min, const t_vec3 max);

float_t vec3_length(t_vec3 v);
float_t vec3_length_squared(t_vec3 v);
float_t vec3_distance(t_vec3 a, t_vec3 b);
float_t vec3_distance_squared(t_vec3 a, t_vec3 b);
t_vec3  vec3_normalize(t_vec3 v);
void    vec3_normalized(t_vec3 *v);
t_vec3  vec3_rotate_x(t_vec3 v, float_t angle);
t_vec3  vec3_rotate_y(t_vec3 v, float_t angle);
t_vec3  vec3_rotate_z(t_vec3 v, float_t angle);

#endif
