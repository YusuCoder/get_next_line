/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:14:13 by ryusupov          #+#    #+#             */
/*   Updated: 2024/05/01 11:02:54 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The function "*g_new_line" greturns the part of "buffer" until '\n' or '\0'
// The function "*remaining" returns part after '\n' if it exists
// The function "get_next_line" gets part of vars until \n or \0
// under the vars descriptor fd
//in the main functtion after opening the fie fd = 3, because
//0, 1, 2 is already in use.
#include "get_next_line.h"

char	*read_data(t_struct *vars, char *buffer)
{
	char	temp[BUFFER_SIZE + 1];
	int		i;

	i = 1;
	while (new_line(buffer) == -1 && i > 0)
	{
		i = read(vars->fd, temp, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			return (NULL);
		}
		temp[i] = '\0';
		buffer = ft_strjoin_new(buffer, temp);
		if (buffer == NULL || ft_strlen(buffer) == 0)
		{
			free(buffer);
			return (NULL);
		}
		if (new_line(buffer) != -1 || i == 0)
			break ;
	}
	return (buffer);
}

char	*g_new_line(t_struct *vars, char *buffer)
{
	char	*temp;
	char	*result;

	if (buffer == NULL || ft_strlen(buffer) == '\0')
	{
		return (NULL);
	}
	vars->new_l_buffer = new_line(buffer);
	if (vars->new_l_buffer >= 0)
	{
		result = ft_strndup(buffer, 0, vars->new_l_buffer + 1);
		return (result);
	}
	temp = ft_strndup(buffer, 0, ft_strlen(buffer));
	return (temp);
}

char	*remaining(t_struct *vars, char *buffer)
{
	char	*temp;

	temp = NULL;
	if (buffer == NULL || ft_strlen(buffer) == '\0')
	{
		free(buffer);
		return (NULL);
	}
	if (vars->new_l_buffer != -1)
		temp = ft_strndup(buffer, vars->new_l_buffer + 1, ft_strlen(buffer));
	free(buffer);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	t_struct	*vars;
	char		*result;

	if (read(fd, NULL, 0) == -1)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	vars = get_t_struct(fd);
	buffer = read_data(vars, buffer);
	result = g_new_line(vars, buffer);
	buffer = remaining(vars, buffer);
	free(vars);
	return (result);
}

// int	main(void)
// {


// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening vars");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
