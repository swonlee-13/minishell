#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*find_pwd_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp("PWD=", env[i], 4) == 0)
			break;
		i++;
	}
	return (env[i]);
}

int main(int ac, char **av, char **env)
{
	(void)ac; (void)av;
	char	*tmp = malloc(sizeof(char) * 1024);
	char	*str;

	getcwd(tmp, 1024);
	printf("current directory : %s\n", tmp);
	str = find_pwd_env(env);
	printf("current PWD : %s\n", str);
	chdir("..");
	getcwd(tmp, 1024);
	str = find_pwd_env(env);
	printf("after chdir : %s\n", tmp);
	printf("current PWD : %s\n", str);
	free(tmp);
}
