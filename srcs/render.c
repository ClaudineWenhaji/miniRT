#include "miniRT.h"

void    render(t_data *data)
{
    int     x;
    int     y;
    t_ray   ray;

    y = 0;
    while (y < WINDOWS_HEIGTH)
    {
        x = 0;
        while (x < WINDOWS_WIDTH)
        {
            ray = camera_ray(&data->camera, x, y);
            x++;
        }
        y++;
    }
}