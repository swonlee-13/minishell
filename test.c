#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

# define PATH_MAX	1024

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

// int main(int ac, char **av, char **env)
// {
// 	(void)ac; (void)av;
// 	char	*tmp = malloc(sizeof(char) * PATH_MAX);
// 	char	*str;

// 	getcwd(tmp, PATH_MAX);
// 	printf("current directory : %s\n", tmp);
// 	str = find_env(env, "PWD=");
// 	printf("%s\n", str);
// 	str = find_env(env, "OLDPWD=");
// 	printf("%s\n", str);
// 	printf("\n\n-----------------------------\n\n\n");
// 	chdir("..");
// 	getcwd(tmp, PATH_MAX);
// 	printf("after chdir : %s\n", tmp);
// 	str = find_env(env, "PWD=");
// 	printf("%s\n", str);
// 	str = find_env(env, "OLDPWD=");
// 	printf("%s\n", str);
// 	free(tmp);
// }

int main(void)
{
    int ret;
    char	*tmp = malloc(sizeof(char) * PATH_MAX);

    tmp = getcwd(tmp, PATH_MAX);
    printf("current PATH: %s\n", tmp);
	printf("------------------------------------\n");
    tmp = getenv("HOME");
	printf("getenv(\"HOME\") = %s\n", tmp);
	ret = chdir(tmp);
	printf("%s\n", tmp);
    printf("ret: %d\n", ret);
	printf("------------------------------------\n");
    tmp = "Desktop";
	ret = chdir(tmp);
	printf("%s\n", tmp);
    printf("ret: %d\n", ret);
	printf("------------------------------------\n");
    tmp = "/42Seoul";
	ret = chdir(tmp);
	printf("%s\n", tmp);
    printf("ret: %d\n", ret);
	printf("------------------------------------\n");
    tmp = "42Seoul";
	ret = chdir(tmp);
	printf("%s\n", tmp);
    printf("ret: %d\n", ret);
	printf("------------------------------------\n");
	tmp = "-";
	ret = chdir(tmp);
	printf("%s\n", tmp);
    printf("ret: %d\n", ret);
	printf("------------------------------------\n");
	tmp = ".";
	ret = chdir(tmp);
	printf("%s\n", tmp);
    printf("ret: %d\n", ret);
	printf("------------------------------------\n");
	tmp = "..";
	ret = chdir(tmp);
	printf("%s\n", tmp);
    printf("ret: %d\n", ret);
}