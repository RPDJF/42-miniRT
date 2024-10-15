#include "exit_handler.h"

void	free_object(void *object)
{
	gfree(((t_object *)object)->data);
	gfree(object);
}

static void	clear_image(t_image *image)
{
	int	i;

	i = -1;
	if (image->data)
		while (++i < image->height)
			gfree(image->data[i]);
	if (image->data)
		gfree(image->data);
	gfree(image);
}

void	clear_memory(t_minirt *minirt)
{
	if (minirt && minirt->win.mlx && minirt->win.windo)
		mlx_destroy_window(minirt->win.mlx, minirt->win.windo);
	if (minirt && minirt->win.mlx)
		mlx_destroy_display(minirt->win.mlx);
	if (minirt && minirt->win.mlx)
		gfree(minirt->win.mlx);
	if (minirt && minirt->size)
		clear_image(minirt->size);
	if (minirt && minirt->amb)
		gfree(minirt->amb);
	if (minirt && minirt->cam)
		gfree(minirt->cam);
	if (minirt && minirt->scene)
		ft_lstclear(&minirt->scene, &free_object);
}

int	secure_exit(void *data)
{
	t_minirt	*minirt;

	minirt = data;
	clear_memory(minirt);
	cleargarbage();
	exit(0);
}

int	crash_exit(t_minirt *minirt, char **context, char *msg)
{
	while (context && *context)
	{
		ft_putstr_fd(*context, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		if (!context[1] && !ft_strcmp(*context, "warning"))
			ft_putstr_fd(C_YELLOW, STDERR_FILENO);
		else if (!context[1])
			ft_putstr_fd(C_RED, STDERR_FILENO);
		context++;
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	ft_putstr_fd(C_RESET, STDERR_FILENO);
	clear_memory(minirt);
	cleargarbage();
	exit(1);
}
