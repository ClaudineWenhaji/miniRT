#include "miniRT.h"

void    render(t_data *data)
{
    int     pixel_x;
    int     pixel_y;
    t_ray   ray;

    pixel_y = 0;
    while (pixel_y < WINDOWS_HEIGHT)
    {
        pixel_x = 0;
        while (pixel_x < WINDOWS_WIDTH)
        {
            ray = camera_ray(&data->camera, pixel_x, pixel_y);
            pixel_x++;
        }
        pixel_y++;
    }
}