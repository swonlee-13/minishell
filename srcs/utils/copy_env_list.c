#include "parse.h"

char	**copy_env_list(char **env)
{
	char		**ret;
	int			idx;
	const int	len = ft_strslen(env);

	idx = 0;
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	while (idx < len)
	{
		ret[idx] = ft_strdup(env[idx]);
		idx++;
	}
	ret[idx] = NULL;
	return (ret);
}
