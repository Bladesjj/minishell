#include "../includes/minishell.h"

int	change_dir(char **args, t_env_list *env)
{
	int			val;
	char		*old;
	t_env_list	*home;
	t_env_list	*pwd;
	t_env_list	*old_pwd;

	home = get_env_value(env, "HOME");
	pwd = get_env_value(env, "PWD");
	old_pwd = get_env_value(env, "OLDPWD");
	old = getcwd(NULL, 0);
	if (!args ||  !args[0] || ft_strcmp(args[0], "cd") != 0)
		return 1;
	val = chdir(args[1]);
	if (!args[1] && home == NULL) // for if we unset HOME
		return (ft_putstr_fd(2, "minishell: cd: HOME not set\n"), 1);
	else if (!args[1]) // redirecting to home
		chdir(home->value);
	if (val == -1 && args[1]) // if invalid direction
		return (perror(args[1]), 1);
	free(old_pwd->value);
	old_pwd->value = old;
	insert_node_last(&env, pwd->key, getcwd(NULL, 0), 0);
	return 0;
}
