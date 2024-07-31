#include "color.h"

t_color	color(t_byte r, t_byte g, t_byte b)
{
	t_color	new_color;

	new_color.r = r;
	new_color.g = g;
	new_color.b = b;
	return (new_color);
}

t_byte	byte_clamp(float value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return ((t_byte)value);
}

int	color_hex(t_color c)
{
	int	hex;

	hex = 0;
	hex |= c.r << 16;
	hex |= c.g << 8;
	hex |= c.b;
	return (hex);
}