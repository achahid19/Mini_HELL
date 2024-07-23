/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:00:17 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 01:42:16 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

// Function to set an environment variable's value
void	set_env(t_env *env, const char *key, const char *value)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = strdup(value);
			return ;
		}
		env = env->next;
	}
	// If key not found, add a new environment variable
	t_env	*new_env = (t_env *)malloc(sizeof(t_env));
	new_env->key = strdup(key);
	new_env->value = strdup(value);
	new_env->next = g_global.e;
	g_global.e = new_env;
}

// Function to print an error message
void	error(const char *cmd, const char *msg)
{
	if (msg)
		printf("%s: %s\n", cmd, msg);
	else
		perror(cmd);
}

static void	change_pwd(t_env *envs, const char *old_pwd, const char *pwd)
{
	set_env(envs, "OLDPWD", old_pwd);
	set_env(envs, "PWD", pwd);
}

t_bool	ft_cd(char **av)
{
	char		old_pwd[PATH_MAX];
	char		new_pwd[PATH_MAX];
	struct stat	info;

	if (!getcwd(old_pwd, PATH_MAX))
		return (error("cd", "getcwd failed"), false);
	if (!av[1])
	{
		char *home = get_env_value(g_global.e, "HOME");
		if (!home)
			return (error("cd", "HOME not set"), false);
		strcpy(new_pwd, home);
	}
	else
	{
		strcpy(new_pwd, av[1]);
		if (access(new_pwd, F_OK) == -1)
			return (error("cd", "No such file or directory"), false);
		if (stat(new_pwd, &info) == -1)
			return (error("cd", NULL), false);
		if (!S_ISDIR(info.st_mode))
			return (error("cd", "Not a directory"), false);
		if (access(new_pwd, R_OK | X_OK) == -1)
			return (error("cd", "Permission denied"), false);
	}
	if (chdir(new_pwd) == -1)
		return (error("cd", new_pwd), false);
	if (!getcwd(new_pwd, PATH_MAX))
		return (error("cd", "getcwd failed"), false);
	change_pwd(g_global.e, old_pwd, new_pwd);
	return (true);
}
