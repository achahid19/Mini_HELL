/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:22:00 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 22:03:51 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	free_global_tmp(t_env *tmp)
{
	t_env	*tmp2;

	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2->key);
		free(tmp2->value);
		free(tmp2);
	}
}

void	update_exported_variable(char *variable)
{
	t_env	*tmp;
	char	*key;

	key = ft_key(variable);
	tmp = g_global.e;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			update_value(tmp, variable);
			break ;
		}
		tmp = tmp->next;
	}
	free(key);
}

t_bool	ft_export_check(char **av, int i)
{
	int	d;

	while (av[i])
	{
		d = 0;
		while (av[i][d] == ' ' || av[i][d] == '\t')
			d++;
		if (!is_valid_identifier(av[i][d], 0))
		{
			printf("export: `%s': not a valid identifier\n", av[i]);
			return (false);
		}
		d++;
		while (av[i][d] && av[i][d] != '=' && !(av[i][d] == '+' && av[i][d
				+ 1] == '='))
		{
			if (!is_valid_identifier(av[i][d], d))
				return (printf("export: `%s': not a valid identifier\n", av[i]),
					false);
			d++;
		}
		i++;
	}
	return (true);
}

void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strlen(tmp->value) == 0)
			printf("declare -x %s\n", tmp->key);
		else
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

t_env	*ft_copy_env(t_env *env)
{
	t_env	*tmp;
	t_env	*new;
	t_env	*head;
	t_env	*prev;

	tmp = env;
	head = NULL;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "_") != 0)
		{
			new = (t_env *)malloc(sizeof(t_env));
			new->key = ft_strdup(tmp->key);
			new->value = ft_strdup(tmp->value);
			new->next = NULL;
			if (prev)
				prev->next = new;
			else
				head = new;
			prev = new;
		}
		tmp = tmp->next;
	}
	return (head);
}
