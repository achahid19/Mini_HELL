/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:42:55 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/21 03:48:23 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	print_env(t_env *env)
{
	t_env *tmp;

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
	new = NULL;
	head = NULL;
	prev = NULL;
	while (tmp)
	{
		if (strcmp(tmp->key, "_") != 0)
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

void	ft_sort_env(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*key;
	char	*value;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (strcmp(tmp->key, tmp2->key) > 0)
			{
				key = tmp->key;
				value = tmp->value;
				tmp->key = tmp2->key;
				tmp->value = tmp2->value;
				tmp2->key = key;
				tmp2->value = value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

t_bool	is_valid_identifier(char c, int i)
{
	if (i == 0)
	{
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
			return (true);
	}
	else
	{
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
			(c >= '0' && c <= '9') || c == '_')
			return (true);
	}
	return (false);
}

t_bool	ft_export_check(char **av)
{
	int	d;
	int	i;

	i = 1;
	while (av[i])
	{
		d = 0;
		while (av[i][d] == ' ' || av[i][d] == '\t')
			d++;
		if (!is_valid_identifier(av[i][d], 0))
		{
			printf("minishell: export: `%s': not a valid identifier\n", av[i]);
			return (false);
		}
		d++;
		while (av[i][d] && av[i][d] != '=' && !(av[i][d] == '+' && av[i][d + 1] == '='))
		{
			if (!is_valid_identifier(av[i][d], d))
			{
				printf("minishell: export: `%s': not a valid identifier\n", av[i]);
				return (false);
			}
			d++;
		}
		i++;
	}
	return (true);
}

char	*ft_key(char *variable)
{
	char	*key;
	int		i;

	i = 0;
	while (variable[i] && variable[i] != '=' && !(variable[i] == '+' && variable[i + 1] == '='))
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (variable[i] && variable[i] != '=' && !(variable[i] == '+' && variable[i + 1] == '='))
	{
		key[i] = variable[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

t_bool	is_exported(char *variable)
{
	t_env	*tmp;
	char	*key;

	key = ft_key(variable);
	tmp = g_global.e;
	while (tmp)
	{
		if (strcmp(key, tmp->key) == 0)
		{
			free(key);
			return (true);
		}
		tmp = tmp->next;
	}
	free(key);
	return (false);
}

void	update_exported_variable(char *variable)
{
	t_env	*tmp;
	char	*key;
	char	*new_value;

	key = ft_key(variable);
	tmp = g_global.e;
	if (strstr(variable, "+=") == NULL)
	{
		while (tmp)
		{
			if (strcmp(key, tmp->key) == 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup(strchr(variable, '=') + 1);
				break ;
			}
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			if (strcmp(key, tmp->key) == 0)
			{
				new_value = malloc(strlen(tmp->value) +
					strlen(strchr(variable, '=') + 1) + 1);
				strcpy(new_value, tmp->value);
				strcat(new_value, strchr(variable, '=') + 1);
				free(tmp->value);
				tmp->value = new_value;
				break ;
			}
			tmp = tmp->next;
		}
	}
	free(key);
}

void	add_exported_variable(char *variable)
{
	t_env	*tmp;
	t_env	*new;
	char	*key;

	key = ft_key(variable);
	tmp = g_global.e;
	new = (t_env *)malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	if (strstr(variable, "+=") == NULL)
	{
		if (strchr(variable, '=') == NULL)
			new->value = ft_strdup("");
		else
			new->value = ft_strdup(strchr(variable, '=') + 1);
	}
	else
	{
		if (strchr(variable, '=') == NULL)
			new->value = ft_strdup("");
		else
			new->value = ft_strdup(strchr(variable, '=') + 1);
	}
	new->next = NULL;
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
		if (ft_export_check(av) == false)
			return (false);
		while (av[i])
		{
			if (is_exported(av[i]))
				update_exported_variable(av[i]);
			else
				add_exported_variable(av[i]);
			i++;
		}
	}
	return (true);
}