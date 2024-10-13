/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_generate.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:52:13 by ilyanar           #+#    #+#             */
/*   Updated: 2024/10/12 18:31:12 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GENERATE_H
# define RT_GENERATE_H

# include "betterft.h"
# include <time.h>
# include <sys/fcntl.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int	rt_generator(char *height, char *width, bool bonus);

int	gener_sp(int fd);
int	gener_cy(int fd);
int	gener_pl(int fd);
int	gener_obj(int fd);
int	gener_int(int min, int max);
int	gener_amb(int fd);
int	gener_lig(int fd, bool	bonus);
int	gener_win(char *height, char *width, int fd);
int	gener_cam(int fd);

int	ran_int(int min, int max, int fd);
int	ran_double(int min, int max, int fd);

int	put_xyz_int(int fd, int min, int max);
int	put_xyz_double(int fd, int min, int max);

int	exit_generator(int fd, const char *name);

#endif
