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
