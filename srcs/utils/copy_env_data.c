#include "parse.h"

char	**copy_env(char **env)
{
	char		**ret;
	int			i;
	const int	len = ft_strslen(env);

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
