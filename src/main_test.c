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


int    main(void)
{
	t_point3	ray_origin;
	float		wall_z;
	float		canvas_pixels;
	float		pixel_size;
	float		wall_size;
	float		half;
	t_image		*image;
	t_object	*shape;
	t_object	*light;
	t_amb		amb;

	shape = new_sphere(point3(0, 0, 0), 1, color(255, 51, 255));
	light = new_light(point3(-10, 10, -10), color(255, 255, 255), 1);
	amb = (t_amb){.light = 0.1, .rgb = color(255, 255, 255),
		.is_calc = false};
	ray_origin = point3(0, 0, -10);
	wall_z = 10;
	wall_size = 7;
	canvas_pixels = 500;
	pixel_size = wall_size / canvas_pixels;
	half = wall_size / 2;
	image = new_image(canvas_pixels, canvas_pixels);
	for (int y = 0; y < canvas_pixels; y++)
	{
		float world_y = half - pixel_size * y;
		for (int x = 0; x < canvas_pixels; x++)
		{
			float world_x = -half + pixel_size * x;
			t_point3 position = point3(world_x, world_y, wall_z);
			t_ray r = ray(ray_origin, vnormalized(vsub(position, ray_origin)));
			t_xs xs = shape->intersect(shape, r);
			if (hit(xs))
			{
				float t = xs.xs[0].t;
				t_point3 point = ray_at(r, t);
				t_vector3 normal = shape->normal_at(shape, point);
				t_vector3 eye = vneg(r.direction);
				t_lightning ln = new_lightning(*(t_light *)light->data, point, eye, normal);
				t_color c = lightning(shape, &amb, ln);
				image->data[y][x] = color_hex(c);
			}
		}
	}
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, canvas_pixels, canvas_pixels, "miniRT !");
	for (int i = 0; i < canvas_pixels; i++)
	{
		for (int j = 0; j < canvas_pixels; j++)
		{
			int color = image->data[j][i];
			mlx_pixel_put(mlx, win, i, j, color);
		}
	}
	mlx_loop(mlx);
	gfree(image->data);
	gfree(image);
	gfree(shape);
	return (0);
}


/*int    main(void)
{
	t_object	*obj;
	t_object	*light;
	t_vector3	eyev;
	t_vector3	normalv;
	t_color		color_;
	t_amb		amb;

	obj = new_sphere(point3(0, 0, 0), 1, color(255,255,255));
	light = new_light(point3(0, 0, -10), color(255,255,255), 1);
	eyev = vector3(0, sqrtf(2) / 2, -sqrtf(2) / 2);
	normalv = vector3(0, 0, -1);
	amb = (t_amb){.rgb = color(255,255,255), .light = 0.1, .is_calc = false};
	color_ = lightning(obj, &amb, new_lightning(*(t_light *)light->data, point3(0, 0, 0), eyev, normalv));
	printf("%f %f %f\n", color_.r / 256.0f, color_.g / 256.0f, color_.b / 256.0f);
}*/