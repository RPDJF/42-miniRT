#include "camera.h"
#include "../miniRT.h"

static void	camera_pos_move(int key, t_camera *cam)
{
	t_vector3	side;
	t_vector3	move;

	side = vnormalized(vcross(vector3(0, 1, 0), cam->target));
	move = cam->target;
	move.y = 0;
	if (key == KEY_D)
		cam->origin = vadd(cam->origin, side);
	else if (key == KEY_A)
		cam->origin = vsub(cam->origin, side);
	else if (key == KEY_W)
		cam->origin = vadd(cam->origin, move);
	else if (key == KEY_S)
		cam->origin = vsub(cam->origin, move);
	else if (key == KEY_SPACE)
		cam->origin.y += 1;
	else if (key == KEY_SHIFT)
		cam->origin.y -= 1;
}

static t_matrix4	m4rodrigues_rotation(t_vector3 a, double angle)
{
	double		cost;
	double		sint;
	double		xt;
	double		yt;
	double		zt;

	cost = cos(angle);
	sint = sin(angle);
	a = vnormalized(a);

	xt = a.x * (1 - cost);
	yt = a.y * (1 - cost);
	zt = a.z * (1 - cost);
	return ((t_matrix4){.data = {
			{cost + a.x * xt, a.x * yt - a.z * sint, a.x * zt + a.y * sint, 0},
			{a.y * xt + a.z * sint, cost + a.y * yt, a.y * zt - a.x * sint, 0},
			{a.z * xt - a.y * sint, a.z * yt + a.x * sint, cost + a.z * zt, 0},
			{0, 0, 0, 1}
		}
	});
}

static void	camera_dir_move(int key, t_camera *cam)
{
	t_vector3	right;
	t_matrix4	rot;

	right = vcross(cam->up, cam->target);
	right = vnormalized(right);
	if (key == KEY_LEFT)
		rot = m4rotating(-0.2, Y_AXIS);
	else if (key == KEY_RIGHT)
		rot = m4rotating(0.2, Y_AXIS);
	if (key == KEY_UP)
		rot = m4rodrigues_rotation(right, -0.2);
	else if (key == KEY_DOWN)
		rot = m4rodrigues_rotation(right, 0.2);
	cam->target = tm4mul(rot, cam->target);
}

void	camera_move(int key)
{
	t_camera	*cam;

	cam = get_minirt()->cam;
	if (key == 114)
	{
		cam->origin = point3(0, 0, 0);
		cam->target = vector3(0, 0, 1);
	}
	else if (key == KEY_D || key == KEY_A || key == KEY_W || key == KEY_S
		|| key == KEY_SPACE || key == KEY_SHIFT)
		camera_pos_move(key, cam);
	else if (key == KEY_LEFT || key == KEY_UP
		|| key == KEY_RIGHT || key == KEY_DOWN)
		camera_dir_move(key, cam);
	get_minirt()->cam = new_camera(cam->origin, cam->target, cam->fov);
	gfree(cam);
	fast_render();
}