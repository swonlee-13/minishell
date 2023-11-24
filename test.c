#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*find_env(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp(str, env[i], strlen(str)) == 0)
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
	str = find_env(env, "PWD=");
	printf("%s\n", str);
	str = find_env(env, "OLDPWD=");
	printf("%s\n", str);
	printf("\n\n-----------------------------\n\n\n");
	chdir("..");
	getcwd(tmp, 1024);
	printf("after chdir : %s\n", tmp);
	str = find_env(env, "PWD=");
	printf("%s\n", str);
	str = find_env(env, "OLDPWD=");
	printf("%s\n", str);
	free(tmp);
}
