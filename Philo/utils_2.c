int	check_arg(int ac, char **av)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	if (ac != 6 && ac != 5)
	{
		printf("check argument\n");
		return (1);
	}
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
			{
				printf("check argument\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
