#include "camera/image.h"
#include "miniRT.h"

int	main(void)
{
	t_image		*image;
	t_camera	*camera;
	t_scene		*scene;

	image = new_image(WIDTH, HEIGHT);
	if (!image)
		return (1);
	camera = new_camera(point3(5, 1, 0), vector3(0, 1, 0), 90, WIDTH / HEIGHT);
	if (!camera)
	{
		gfree(image->data);
		gfree(image);
		return (1);
	}
	scene = ft_lstadd(0, new_plane(point3(0, 0, 0), vector3(0, 1, 0)));
	ft_lstpush(scene, new_sphere(point3(0, 2.5, 0), 2.1));
	ft_lstpush(scene, new_sphere(point3(0, 0, -2.8), 1.5));
	ray_trace(image, camera, scene);
	t_minirt	minirt;
	init_minirt_mlx(&minirt);
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			int color = image->data[(int)(j * WIDTH + i)];
			if (color == 1)
				color = 0xFFFFFFFF;
			else
				color = 0x00000000;
			mlx_pixel_put(minirt.win.mlx, minirt.win.windo, i, j, color);
		}
	}
	mlx_loop(minirt.win.mlx);
	gfree(image->data);
	gfree(image);
	gfree(camera);
	ft_lstclear(&scene, gfree);
	return (0);
}