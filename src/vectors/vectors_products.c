/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_products.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:54:00 by rude-jes          #+#    #+#             */
/*   Updated: 2024/10/28 22:54:01 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

double	vdot(t_vector3 v, t_vector3 u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z + v.w * u.w);
}

t_vector3	vcross(t_vector3 v, t_vector3 u)
{
	return (vector3(
			v.y * u.z - v.z * u.y,
			v.z * u.x - v.x * u.z,
			v.x * u.y - v.y * u.x
		)
	);
}
