/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:42:55 by akajjou           #+#    #+#             */
/*   Updated: 2024/08/29 01:38:24 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

t_bool	is_exported(char *variable)
{
	t_env	*tmp;
	char	*key;

	key = ft_key(variable);
	tmp = g_global.e;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			free(key);
			return (true);
		}
		tmp = tmp->next;
	}
	free(key);
	return (false);
}

void	update_value(t_env *tmp, char *variable)
{
	char	*new_value;

	if (ft_strchr(variable, '=') == NULL)
		return ;
	if (ft_strstr(variable, "+=") == NULL)
	{
		free(tmp->value);
		tmp->value = ft_strdup(ft_strchr(variable, '=') + 1);
	}
	else
	{
		new_value = malloc(ft_strlen(tmp->value) + ft_strlen(
					ft_strchr(variable, '=') + 1) + 1);
		if (!new_value)
			return ;
		ft_strcpy(new_value, tmp->value);
		ft_strcat(new_value, ft_strchr(variable, '=') + 1);
		free(tmp->value);
		tmp->value = new_value;
	}
}

t_env	*init_new_variable(char *variable, char *key)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (ft_strstr(variable, "+=") == NULL)
	{
		if (ft_strchr(variable, '=') == NULL)
			new->value = ft_strdup("");
		else
			new->value = ft_strdup(ft_strchr(variable, '=') + 1);
	}
	else
	{
		if (ft_strchr(variable, '=') == NULL)
			new->value = ft_strdup("");
		else
			new->value = ft_strdup(ft_strchr(variable, '=') + 1);
	}
	new->next = NULL;
	return (new);
}

void	add_exported_variable(char *variable)
{
	t_env	*tmp;
	t_env	*new;
	char	*key;

	key = ft_key(variable);
	tmp = g_global.e;
	new = init_new_variable(variable, key);
	if (!new)
		return ;
	if (!tmp)
		g_global.e = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	free(key);
}

t_bool	ft_export(char **av)
{
	int		i;
	t_env	*tmp;

	tmp = ft_copy_env(g_global.e);
	ft_sort_env(tmp);
	i = 1;
	if (!av[1])
		print_env(tmp);
	else
	{
		while (av[i])
		{
			if (ft_export_check(av, i) == false)
				;
			else if (is_exported(av[i]))
				update_exported_variable(av[i]);
			else
				add_exported_variable(av[i]);
			i++;
		}
	}
	return (free_global_tmp(tmp), true);
}
