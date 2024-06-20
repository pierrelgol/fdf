/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:44:47 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 13:44:47 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void renderer_init_frame_data(t_renderer *const self, const int32_t width, const int32_t height)
{
    memory_copy(self->world_coords_buffer, self->map_data->world_coords_buffer, width * height * sizeof(t_vec3));
    memory_copy(self->world_colors_buffer, self->map_data->world_colors_buffer, width * height * sizeof(int32_t));
    self->map_center_x = width / 2.0;
    self->map_center_y = height / 2.0;

    self->camera_position = camera_get_position(self->camera);
    self->camera_rotation = camera_get_rotation(self->camera);
    self->camera_amplitude = camera_get_amplitude(self->camera);
    self->camera_zoom = camera_get_zoom(self->camera);

    self->cos_pitch = cos(self->camera_rotation.x);
    self->sin_pitch = sin(self->camera_rotation.x);
    self->cos_yaw = cos(self->camera_rotation.y);
    self->sin_yaw = sin(self->camera_rotation.y);
    self->cos_roll = cos(self->camera_rotation.z);
    self->sin_roll = sin(self->camera_rotation.z);
    self->zoom = self->camera_zoom.z;
    self->screen_center = vec3(WIDTH / 2.0f, HEIGHT / 2.0f, 0.0f);
}

void renderer_init_world_data(t_renderer *const self, const int32_t width, const int32_t height)
{
    int32_t x, y;


    double screen_center_x = WIDTH / 2.0;
    double screen_center_y = HEIGHT / 2.0;

    double camera_x = self->camera_position.x;
    double camera_y = self->camera_position.y;
    double camera_z = self->camera_position.z;

    double camera_pitch = self->camera_rotation.x * M_PI / 180.0; // convert to radians
    double camera_yaw = self->camera_rotation.y * M_PI / 180.0;   // convert to radians
    double camera_roll = self->camera_rotation.z * M_PI / 180.0;  // convert to radians

    double cos_pitch = cos(camera_pitch);
    double sin_pitch = sin(camera_pitch);
    double cos_yaw = cos(camera_yaw);
    double sin_yaw = sin(camera_yaw);
    double cos_roll = cos(camera_roll);
    double sin_roll = sin(camera_roll);

    double cos30 = cos(30.0 * M_PI / 180.0);
    double sin30 = sin(30.0 * M_PI / 180.0);

    double scaling_factor = self->zoom; // Assume this is defined in t_renderer and set elsewhere

    for (y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
        {
            // Source: world coordinates
            t_vec3 p = vec3_mul(self->world_coords[y][x], vec3(WIDTH, HEIGHT, self->camera_amplitude.z));

            p = vec3_add(self->world_coords[y][x], self->screen_center);


            p.x -= camera_x;
            p.y -= camera_y;
            p.z -= camera_z;

            // Apply rotations
            double temp_x = p.x;
            double temp_y = p.y;
            double temp_z = p.z;

            // Rotate around X (Pitch)
            p.y = cos_pitch * temp_y - sin_pitch * temp_z;
            p.z = sin_pitch * temp_y + cos_pitch * temp_z;

            // Update temp variables
            temp_y = p.y;
            temp_z = p.z;

            // Rotate around Y (Yaw)
            p.x = cos_yaw * temp_x + sin_yaw * temp_z;
            p.z = -sin_yaw * temp_x + cos_yaw * temp_z;

            // Update temp variables
            temp_x = p.x;
            temp_z = p.z;

            // Rotate around Z (Roll)
            p.x = cos_roll * temp_x - sin_roll * temp_y;
            p.y = sin_roll * temp_x + cos_roll * temp_y;

            // Apply scaling
            p.x += (p.x * scaling_factor);
            p.y += (p.y * scaling_factor);
            p.z += (p.z * scaling_factor);

            // Project to 2D screen coordinates (orthographic projection)
            double screen_x = (p.x - p.y) * cos30;
            double screen_y = (p.x + p.y) * sin30 - p.z;

            // Center on screen
            screen_x += screen_center_x;
            screen_y += screen_center_y;

            // Store in screen coordinates
            self->screen_coords[y][x] = (t_vec2){{screen_x, screen_y}};
        }
    }

    // printf("\nAFTER\n");
    // print_vec_buffer2(self->screen_coords, width, height);
    // printf("\n");
}




void renderer_render(t_renderer *const self, const int32_t width, const int32_t height)
{
    draw_clear(self);
    draw(self, width, height);
}
