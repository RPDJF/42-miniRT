#ifndef PARSING_H
# define PARSING_H

# include "../miniRT.h"
# include "../objects/shape.h"
# include "../camera/image.h"
# include "../camera/camera.h"
# include "../objects/objects.h"
# include "../objects/plane.h"
# include "../objects/cylinder.h"
# include "../objects/sphere.h"
# include "../exit_handler/exit_handler.h"

//	return the len of a char **str
int			ft_strlen_tab(char **str);
//	ft_split but split auto sp and tab caractere.
char		**ft_split_sp_tab(char const *s);
//	Correct the '\n' for gnl function.
int			correct_dl(char *gnl);
//	get a new_image with default size.
void		get_size_default(t_minirt **minirt);
//	check basic error for parsing
void		check_error(int ac, char **av);
//	return a conver float of the string av
float		ft_atof(char *str);
//	do a ft_atof of x, y and z float. with a splited str gonna be free
int			ft_atof_xyz(float *x, float *y, float *z, char **str);
//	do a ft_atoi of x, y and z int. with a splited str gonna be free
int			ft_atoi_xyz(int *x, int *y, int *z, char **str);
//	check the format string of ambiance
void		check_amb_format(t_minirt **minirt, char **str);
//	get the amb struct for t_minirt->amb
void		get_amb(char **str, t_minirt **minirt);
//	check the format string of the camera
void		check_cam_format(char **str, t_minirt **minirt);
//	take the cam info
void		get_cam_info(t_point3 *origin, t_vector3 *target,
				t_minirt *minirt, char **str);
//	get the cam struct for t_minirt->cam
void		get_cam(char **str, t_minirt **minirt);
//	alloc a t_scene struct and return it
t_scene		*get_scene_struct(t_minirt **minirt);
//	get object struct, more obj can be added at the future.
void		get_obj(char **str, t_minirt **minirt);
//	check size format string for R(windo)
void		check_size_format(char **str, t_minirt **minirt);
//	get the size struct for t_minirt->size
void		get_size(char **str, t_minirt **minirt);
//	check the info for cylinder object
void		check_cy_info(char **str, t_minirt *minirt);
//	get the struct for t_obj->cy
void		get_cy(char **str, t_minirt **minirt);
//	check the format string for light
void		check_light_format(char **str, t_minirt **minirt, bool *bonus);
//	get the struct for t_obj->light
void		get_light(char **str, t_minirt **minirt);
//	check the format string for plane
void		check_pl_info(char **str, t_minirt *minirt);
//	get the struct for t_obj->plane
void		get_pl(char **str, t_minirt **minirt);
//	check the format string for sphere
void		check_sp_info(char **str, t_minirt *minirt);
//	get the struct for t_obj->sphere
void		get_sp(char **str, t_minirt **minirt);
//	return (1) if the string is a int else return (0)
int			only_digit(char *str);
//	return (1) if the string is a float else return (0)
int			only_float(char *str);
//	return (1) if the string "split" is a 0,0,0 format with only three int
int			only_digit_xyz(char *split, t_minirt *minirt);
//	return (1) if the string "split" is a 0.0,0.0,0.0 format
//	with only three float
int			only_float_xyz(char *split, t_minirt *minirt);
//	the second function for check et pars the object in the fd
void		pars_obj(char **str, t_minirt **minirt);
//	the principal function for the parsing
void		pars_map(char **av, t_minirt **minirt);
//	the fonction for print t_minirt token
void		print_token(t_minirt *rt, t_scene *tmp);
//	atoi for rgb t_color struc
int			ft_atoi_rgb(unsigned char *x, unsigned char *y,
				unsigned char *z, char **str);

#endif