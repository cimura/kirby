#include <mlx.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800

typedef struct s_point
{
	double x;
	double y;
}			t_point;


void draw_bezier_curve(void *mlx, void *win, t_point p0, t_point p1, t_point p2, int color)
{
    double t;
    for (t = 0.0; t <= 1.0; t += 0.001)
    {
        double x = (1 - t) * (1 - t) * p0.x + 2 * (1 - t) * t * p1.x + t * t * p2.x;
        double y = (1 - t) * (1 - t) * p0.y + 2 * (1 - t) * t * p1.y + t * t * p2.y;
        mlx_pixel_put(mlx, win, x, y, color);
    }
}

void draw_filled_circle(void *mlx, void *win, int xc, int yc, int r, int color)
{
    for (int y = -r; y <= r; y++)
    {
        for (int x = -r; x <= r; x++)
        {
            if (x * x + y * y <= r * r)
                mlx_pixel_put(mlx, win, xc + x, yc + y, color);
        }
    }
}

void draw_filled_ellipse(void *mlx, void *win, int xc, int yc, int rx, int ry, int color)
{
    for (int y = -ry; y <= ry; y++)
    {
        for (int x = -rx; x <= rx; x++)
        {
            if ((x * x) * (ry * ry) + (y * y) * (rx * rx) <= (rx * rx) * (ry * ry))
                mlx_pixel_put(mlx, win, xc + x, yc + y, color);
        }
    }
}

void draw_kirby(void *mlx, void *win)
{
    // Body (Pink)
    draw_filled_circle(mlx, win, 400, 400, 200, 0xFFB6C1);

    // Hands (Pink)
    draw_filled_circle(mlx, win, 200, 450, 50, 0xFFB6C1);
    draw_filled_circle(mlx, win, 600, 450, 50, 0xFFB6C1);

    // Feet (Red)
    draw_filled_ellipse(mlx, win, 300, 580, 80, 50, 0xFF5192);
    draw_filled_ellipse(mlx, win, 500, 580, 80, 50, 0xFF5192);

    // Eyes (Dark Blue)
    draw_filled_ellipse(mlx, win, 350, 320, 22, 44, 0x000022);
    draw_filled_ellipse(mlx, win, 450, 320, 22, 44, 0x000022);

    // Eye highlights (White)
    draw_filled_ellipse(mlx, win, 350, 300, 12, 15, 0xFFFFFF);
    draw_filled_ellipse(mlx, win, 450, 300, 12, 15, 0xFFFFFF);

    // Eye highlights (Light blue)
    draw_filled_ellipse(mlx, win, 350, 350, 10, 12, 0x0000BB);
    draw_filled_ellipse(mlx, win, 450, 350, 10, 12, 0x0000BB);

    // Cheeks (Light Pink)
    draw_filled_ellipse(mlx, win, 300, 380, 30, 10, 0xFF99CC);
    draw_filled_ellipse(mlx, win, 500, 380, 30, 10, 0xFF99CC);

    // Mouth (Black)
    // draw_filled_circle(mlx, win, 400, 450, 10, 0x000000);
	// mlx_put_image_to_window(mlx, win, img, 100, 100);

    t_point mouth_left = {375, 400};
    t_point mouth_mid = {400, 420};
    t_point mouth_rigth = {425, 400};

    // draw_bezier_curve(mlx, win, foot_left_p0, foot_left_p1, foot_left_p2, 0xFF0066);
    draw_bezier_curve(mlx, win, mouth_left, mouth_mid, mouth_rigth, 0);

}

int main()
{
    void *mlx;
    void *win;
	// void *img;

    mlx = mlx_init();
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "Kirby");
	// img = mlx_new_image(mlx, WIDTH, HEIGHT);

    draw_kirby(mlx, win);

    mlx_loop(mlx);

    return 0;
}
