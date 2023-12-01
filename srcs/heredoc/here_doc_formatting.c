#include "parse.h"

char	*here_doc_formatting(char *str, char **env_copy)
{
	char	**tmp;
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	tmp = shell_split_here_doc(str);
	while (tmp[i])
	{
		tmp[i] = env_var_replace(tmp[i], env_copy);
		i++;
	}
	ret = merge_splitted_cmd(tmp);
	ft_free(tmp);
	free(str);
	return (ret);
}
