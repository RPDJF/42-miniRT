/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:44:57 by ilyanar           #+#    #+#             */
/*   Updated: 2024/10/28 23:44:58 by ilyanar          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_HANDLER_H
# define EXIT_HANDLER_H

# include "../miniRT.h"
# include "betterft.h"

//	secure_exit: Securely exit the program
int		secure_exit(void *data);
//	crash_exit: Exit the program with an error message
int		crash_exit(t_minirt *minirt, char **context, char *msg);
void	clear_memory(t_minirt *minirt);
void	free_mat(void *content);

#endif
