/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 06:55:10 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 00:22:51 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int	ft_env_search(char *tmp, t_env *envp)
{
	int	i;
	int	len;

	i = 1;
	if (tmp[i] == '\0')
		return (1);
	while (envp)
	{
		if (ft_strlen(tmp) - 1 > ft_strlen(envp->key))
			len = ft_strlen(tmp) - 1;
		else
			len = ft_strlen(envp->key);
		if (ft_strncmp(tmp + i, envp->key, len) == 0)
			return (0);
		envp = envp->next;
	}
	return (1);
}

void	ft_expand_know(char **line, t_env *envp)
{
	int	flag;

	flag = 0;
	while (envp)
	{
		if (ft_strncmp(*(line) + 1, envp->key, ft_strlen(envp->key)) == 0)
		{
			flag = 1;
			break ;
		}
		envp = envp->next;
	}
	free(*line);
	if (flag == 1)
		*line = ft_strdup(envp->value);
	else
		*line = ft_strdup("");
}

char	*ft_last_line(char **line_split)
{
	int		i;
	char	*new_line;

	i = 0;
	new_line = NULL;
	while (line_split[i])
	{
		new_line = ft_strjoin(new_line, line_split[i]);
		i++;
	}
	return (new_line);
}

void	process_line_split(char **line_split, t_env *envp, int i)
{
	int	d;

	while (line_split[i])
	{
		d = 0;
		while (line_split[i][d])
		{
			if (line_split[i][d] == '$' && line_split[i][d + 1] != '\0')
			{
				if (line_split[i][d + 1] == '?')
				{
					free(line_split[i]);
					//get_status();
					line_split[i] = ft_itoa(g_global.status);
				}
				else if (ft_env_search(line_split[i], envp) == 0)
					ft_expand_know(&line_split[i], envp);
				else
					line_split[i] = ft_strdup("");
			}
			d++;
		}
		i++;
	}
}

char	*ft_expand_heredoc(char *line, t_env *envp)
{
	char	**line_split;
	char	*new_line;
	int		i;

	i = 0;
	line_split = ft_advanced_split(line);
	free(line);
	process_line_split(line_split, envp, i);
	new_line = ft_last_line(line_split);
	ft_free_array(line_split);
	return (new_line);
}
