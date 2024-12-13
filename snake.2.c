void two_player_key_control(unsigned char key)
{
	if (status_time < 8)
		return;
	if (iAnimPause[5] == 1)
		iResumeTimer(5);


	
	if (key == 'w')
	{
		if (direction_x2 != 0)
		{
			printf("snake2 goes up\n");
			direction_y2 = 1;
			direction_x2 = 0;
		}
	}
	if (key == 's')
	{
		if (direction_x2 != 0)
		{
			printf("snake2 goes down\n");
			direction_y2 = -1;
			direction_x2 = 0;
		}
	}
	if (key == 'd')
	{
		if (direction_y2 != 0)
		{
			printf("snake2 turns right\n");
			direction_y2 = 0;
			direction_x2 = 1;
		}
	}
	if (key == 'a')
	{
		if (direction_y2 != 0)
		{
			printf("snake2 turns left\n");
			direction_y2 = 0;
			direction_x2 = -1;
		}
	}
}
