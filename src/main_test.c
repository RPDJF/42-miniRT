#include "camera/image.h"
#include "miniRT.h"
/*
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
	scene = ft_lstnew_back(0, new_plane(point3(0, 0, 0), vector3(0, 1, 0), color(255, 255, 255)));
	ft_lstnew_back(scene, new_sphere(point3(0, 2.5, 0), 2.1, color(255, 0, 0)));
	ft_lstnew_back(scene, new_sphere(point3(0, 0, -2.8), 1.5, color(0, 255, 0)));
	ray_trace(image, camera, scene);
	t_minirt	minirt;
	minirt.size = galloc(sizeof(t_image));
	minirt.size->height = HEIGHT;
	minirt.size->width = WIDTH;
	init_minirt_mlx(&minirt);
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			int color = image->data[j][i];
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
*/

int	main(void)
{
	t_sphere	*sphere;
	t_ray		r;
	int 		xs;
	t_point3 	p;

	sphere = new_raw_sphere(point3(0, 0, 0), 1, color(255, 255, 255));
	r = ray(point3(0, 0, -5), vector3(0, 0, 1));
	xs = 0;
	for (float i = RAY_T_MIN; i < 10 && xs < 2; i += EPSILONF)
	{
		p = ray_at(r, i);
		printf("Point: %f %f %f\n", p.x, p.y, p.z);
		if (ft_equalsf(p.z, sphere->origin.z - sphere->radius) || ft_equalsf(p.z, sphere->origin.z + sphere->radius))
		{
			xs++;
			printf("Intersection %d: %f\n", xs, i);
		}
	}
	return (0);
}
