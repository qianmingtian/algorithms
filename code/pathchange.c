//2.20 s

static void voice_path_change_to_valid(void)
{
	int m;
	int n;
	int node_index;
	int path_num;
	FIN(voice_path_change_to_valid());
	m = ((int)(op_sim_time() - local_variable.nmop_start_time + 0.5) % 400) / 100;
	n = ((int)(op_sim_time() - local_variable.nmop_start_time + 0.5) % 400) % 100;

	node_index = 4 * m + n + 1;

	for (int i = 1; i <= 6; i++)
	{
		if (local_variable.Voice_start_node_path[i - 1] == node_index && local_variable.Voice_state_path[i - 1] == 1)
		{
			local_variable.Voice_state_path[i - 1] = 2;
			path_num = i - 1;
		}
	}

	if (op_prg_odb_ltrace_active("voice_path_state_change_to_valid_time") == OPC_TRUE)
	{
		printf("\nvoice_path:%d--->%d--->%d----path_state_change_to_valid_time----%f of node %d\n", local_variable.Voice_start_node_path[path_num], local_variable.Voice_mid_node_path[path_num], local_variable.Voice_end_node_path[path_num], op_sim_time(), user_id);
	}

	FOUT;
}

//4.10 s

static void voice_path_change_to_invalid(void)
{
	int m;
	int n;
	int node_index;
	int path_num;
	FIN(voice_path_change_to_invalid());
	m = ((int)(op_sim_time() - local_variable.nmop_start_time + 0.5) % 400) / 100;
	n = ((int)(op_sim_time() - local_variable.nmop_start_time + 0.5) % 400) % 100;
	node_index = 4 * m + n + 1;

	for (int i = 1; i <= 6; i++)
	{
		if (local_variable.Voice_start_node_path[i - 1] == node_index && local_variable.Voice_state_path[i - 1] == 3)
		{
			if (op_prg_odb_ltrace_active("voice_path_state_change_to_invalid_time") == OPC_TRUE)
			{
				printf("\nvoice_path:%d--->%d--->%d----path_state_change_to_invalid_time----%f of node %d\n", local_variable.Voice_start_node_path[i - 1], local_variable.Voice_mid_node_path[i - 1], local_variable.Voice_end_node_path[i - 1], op_sim_time(), user_id);
			}
			local_variable.Voice_state_path[i - 1] = 0;
			local_variable.Voice_start_node_path[i - 1] = 0;
			local_variable.Voice_mid_node_path[i - 1] = 0;
			local_variable.Voice_end_node_path[i - 1] = 0;
			path_num = i - 1;
		}
	}

	FOUT;
}

//4.10 s

//lack of dealing with Video_path

static void video_path_change_to_valid(void)
{
	int m;
	int n;
	int node_index;
	int path_num;
	FIN(video_path_change_to_valid());
	m = ((int)(op_sim_time() - local_variable.nmop_start_time + 0.5) % 400) / 100;
	n = ((int)(op_sim_time() - local_variable.nmop_start_time + 0.5) % 400) % 100;

	node_index = 4 * m + n + 1;

	for (int i = 1; i <= 2; i++)
	{
		if (local_variable.Video_start_node_path[i - 1] == node_index && local_variable.Video_state_path[i - 1] == 1)
		{
			local_variable.Video_state_path[i - 1] = 2;
			path_num = i - 1;
		}
	}

	if (op_prg_odb_ltrace_active("video_path_state_change_to_valid_time") == OPC_TRUE)
	{
		printf("\nvideo path:%d--->%d--->%d----path_state_change_to_valid_time----%f of node %d\n", local_variable.Video_start_node_path[path_num], local_variable.Video_mid_node_path[path_num], local_variable.Video_end_node_path[path_num], op_sim_time(), user_id);
	}

	FOUT;
}

static void video_path_change_to_invalid(void)
{
	int m;
	int n;
	int node_index;
	int path_num;
	FIN(video_path_change_to_invalid());
	m = ((int)(op_sim_time() - local_variable.nmop_start_time + 0.5) % 400) / 100;
	n = ((int)(op_sim_time() - local_variable.nmop_start_time + 0.5) % 400) % 100;

	node_index = 4 * m + n + 1;

	for (int i = 1; i <= 2; i++)
	{
		if (local_variable.Video_start_node_path[i - 1] == node_index && local_variable.Video_state_path[i - 1] == 3)
		{
			if (op_prg_odb_ltrace_active("video_path_state_change_to_invalid_time") == OPC_TRUE)
			{
				printf("\nvideo path:%d--->%d--->%d----path_state_change_to_invalid_time----%f of node %d\n", local_variable.Video_start_node_path[i - 1], local_variable.Video_mid_node_path[i - 1], local_variable.Video_end_node_path[i - 1], op_sim_time(), user_id);
			}

			local_variable.Video_state_path[i - 1] = 0;
			local_variable.Video_start_node_path[i - 1] = 0;
			local_variable.Video_mid_node_path[i - 1] = 0;
			local_variable.Video_end_node_path[i - 1] = 0;
			path_num = i - 1;
		}
	}

	FOUT;
}

//4.17 s

static void time_slot_allocation(void)
{

	FIN(time_slot_allocation());
	if (op_prg_odb_ltrace_active("time_slot_allocate_intrpt") == OPC_TRUE)
	{
		printf("\nlocal_variable.nmop_start_time: %f-----execute time: %f---of user %d\n", local_variable.nmop_start_time, op_sim_time(), user_id);
		printf("\n##############################################################\n");
	}

	int pos = 0;

	//reset the voice_time_slot_info matrix;
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 4; j++)
			voice_time_slot_info[i][j] = 0;

	for (int i = 0; i < 6; i++)
	{
		if (local_variable.Voice_state_path[i] == 2 || local_variable.Voice_state_path[i] == 3)
		{
			voice_time_slot_info[pos][0] = 1;
			voice_time_slot_info[pos][1] = local_variable.Voice_start_node_path[i];
			voice_time_slot_info[pos][2] = local_variable.Voice_mid_node_path[i];
			voice_time_slot_info[pos][3] = local_variable.Voice_end_node_path[i];
			if (pos == 0 || pos == 1 || pos == 2 || pos == 3 || pos == 4 || pos == 5)
			{
				if (user_id == local_variable.Voice_start_node_path[i])
				{
					op_intrpt_schedule_self(op_sim_time() + 16 + pos, VOICE_PACKET_TRANSMIT_INTRPT_CODE);		//set the first intrpt  in one NMOP time cycle;
					op_intrpt_schedule_self(op_sim_time() + 16 + pos + 200, VOICE_PACKET_TRANSMIT_INTRPT_CODE); //set the second intrpt in one NMOP time cycle;
				}

				pos += 6;
			}
			else
			{
				if (user_id == local_variable.Voice_start_node_path[i])
				{
					op_intrpt_schedule_self(op_sim_time() + 100 + 16 + pos - 6, VOICE_PACKET_TRANSMIT_INTRPT_CODE);		  //set the first intrpt  in one NMOP time cycle;
					op_intrpt_schedule_self(op_sim_time() + 100 + 16 + pos - 6 + 200, VOICE_PACKET_TRANSMIT_INTRPT_CODE); //set the second intrpt in one NMOP time cycle;
				}
				pos -= 5;
			}

			if (local_variable.Voice_mid_node_path[i] != local_variable.Voice_end_node_path[i])
			{
				voice_time_slot_info[pos][0] = 2;
				voice_time_slot_info[pos][1] = local_variable.Voice_start_node_path[i];
				voice_time_slot_info[pos][2] = local_variable.Voice_mid_node_path[i];
				voice_time_slot_info[pos][3] = local_variable.Voice_end_node_path[i];

				if (pos == 0 || pos == 1 || pos == 2 || pos == 3 || pos == 4 || pos == 5)
				{
					if (user_id == local_variable.Voice_mid_node_path[i])
					{
						op_intrpt_schedule_self(op_sim_time() + 16 + pos, VOICE_PACKET_TRANSMIT_INTRPT_CODE);
						op_intrpt_schedule_self(op_sim_time() + 16 + pos + 200, VOICE_PACKET_TRANSMIT_INTRPT_CODE);
					}
					pos += 6;
				}
				else
				{
					if (user_id == local_variable.Voice_mid_node_path[i])
					{
						op_intrpt_schedule_self(op_sim_time() + 100 + 16 + pos - 6, VOICE_PACKET_TRANSMIT_INTRPT_CODE);
						op_intrpt_schedule_self(op_sim_time() + 100 + 16 + pos - 6 + 200, VOICE_PACKET_TRANSMIT_INTRPT_CODE);
					}
					pos -= 5;
				}
			}
		}
		else
			continue;
	}

	//4.18 sxq
	//set the initial voice transmit intrpt for each node

	//4.23 sxq
	if (op_prg_odb_ltrace_active("voice_time_slot_info") == OPC_TRUE)
	{

		if (user_id == 12)
		{
			printf("\n +_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+_+_+_+_+- \n");
			printf("voice_time_slot_info------current time %f", op_sim_time());
			for (int i = 0; i < 12; i++)
			{
				printf("\n  %d-------%d--------%d---------%d-----------%d-----\n", i, voice_time_slot_info[i][0], voice_time_slot_info[i][1], voice_time_slot_info[i][2], voice_time_slot_info[i][3]);
				printf("===========================================================");
			}
		}
	}

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 4; j++)
			video_time_slot_info[i][j] = 0;

	int pos1 = 0;

	if (voice_time_slot_info[5][0] != 0) //it indicates that only 14 large time slots can be scheduled for video, if voice_time_slot_info[5][0] ==0 , 15 large time slots can be used.
	{
		pos1 += 1;
	}

	// fill the video_time_slot_info matrix;

	for (int i = 0; i < 2; i++)
	{
		if (local_variable.Video_state_path[i] == 2 || local_variable.Video_state_path[i] == 3)
		{
			video_time_slot_info[pos1][0] = 1;
			video_time_slot_info[pos1][1] = local_variable.Video_start_node_path[i];
			video_time_slot_info[pos1][2] = local_variable.Video_mid_node_path[i];
			video_time_slot_info[pos1][3] = local_variable.Video_end_node_path[i];

			if (user_id == local_variable.Video_start_node_path[i])
			{
				op_intrpt_schedule_self(op_sim_time() + 16 + 5 + 5 * pos1, VIDEO_PACKET_TRANSMIT_INTRPT_CODE);		 //set the first intrpt  in one NMOP time cycle;
				op_intrpt_schedule_self(op_sim_time() + 16 + 5 + 5 * pos1 + 100, VIDEO_PACKET_TRANSMIT_INTRPT_CODE); //set the second intrpt in one NMOP time cycle;
				op_intrpt_schedule_self(op_sim_time() + 16 + 5 + 5 * pos1 + 200, VIDEO_PACKET_TRANSMIT_INTRPT_CODE);
				op_intrpt_schedule_self(op_sim_time() + 16 + 5 + 5 * pos1 + 300, VIDEO_PACKET_TRANSMIT_INTRPT_CODE);
			}

			pos1 += 1;

			if (local_variable.Video_mid_node_path[i] != local_variable.Video_end_node_path[i])
			{
				video_time_slot_info[pos1][0] = 2;
				video_time_slot_info[pos1][1] = local_variable.Video_start_node_path[i];
				video_time_slot_info[pos1][2] = local_variable.Video_mid_node_path[i];
				video_time_slot_info[pos1][3] = local_variable.Video_end_node_path[i];
				if (user_id == local_variable.Video_mid_node_path[i])
				{
					op_intrpt_schedule_self(op_sim_time() + 16 + 5 + 5 * pos1, VIDEO_PACKET_TRANSMIT_INTRPT_CODE);		 //set the first intrpt  in one NMOP time cycle;
					op_intrpt_schedule_self(op_sim_time() + 16 + 5 + 5 * pos1 + 100, VIDEO_PACKET_TRANSMIT_INTRPT_CODE); //set the second intrpt in one NMOP time cycle;
					op_intrpt_schedule_self(op_sim_time() + 16 + 5 + 5 * pos1 + 200, VIDEO_PACKET_TRANSMIT_INTRPT_CODE);
					op_intrpt_schedule_self(op_sim_time() + 16 + 5 + 5 * pos1 + 300, VIDEO_PACKET_TRANSMIT_INTRPT_CODE);
				}

				pos1 += 1;
			}
		}
		else
			continue;
	}

	if (op_prg_odb_ltrace_active("video_time_slot_info") == OPC_TRUE)
	{

		if (user_id == 5)
		{
			printf("\n +_+_+_+_+_+_+_+_+_+_++_+_+_+_+_+_+_+_+_+_+_+_+_+_+- \n");
			printf("video_time_slot_info-----current time %f", op_sim_time());
			for (int i = 0; i < 15; i++)
			{
				printf("\n  %d-------%d--------%d---------%d-----------%d-----\n", i, video_time_slot_info[i][0], video_time_slot_info[i][1], video_time_slot_info[i][2], video_time_slot_info[i][3]);
				printf("===========================================================");
			}
		}
	}

	if (user_id == 5)
	{
		printf("###################################################\n");
		printf("----op_sim_time() : %f---\n", op_sim_time());
		for (int i = 0; i < 12; i++)
			printf("%d----%d-----%d-----%d\n", voice_time_slot_info[i][0], voice_time_slot_info[i][1], voice_time_slot_info[i][2], voice_time_slot_info[i][3]);
		printf("###################################################\n");
	}
	
		
	FOUT;
}

//4.26 s
