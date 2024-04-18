temp_lst = (sh.env_lst);
	while (temp_lst->next)
	{
		printf("%s %s %d\n", ((t_env *)(temp_lst->content))->key, \
			((t_env *)(temp_lst->content))->value, \
				((t_env *)(temp_lst->content))->visible);
		temp_lst = temp_lst->next;
	}
	printf("%s %s %d\n", ((t_env *)(temp_lst->content))->key, \
		((t_env *)(temp_lst->content))->value, \
			((t_env *)(temp_lst->content))->visible);
