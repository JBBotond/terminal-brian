#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string.h>
#include <cstdio>

std::ofstream dout("debug");
//dout.flush();

void debug_out(int frame[10][10]) {

	for(int i = 0; i < 10 ; i ++) {
		for(int j = 0; j < 10; j ++)
			dout<<frame[i][j]<<' ';
		dout<<std::endl;
	}
}

void matrix_out(int matrix[10][10]) {
	for(int i=0;i<10;i++) {
		for(int j=0;j<10;j++) {
			if(matrix[i][j] == 0)
				std::cout<<' ';
			else std::cout<<'#';
		}
		std::cout<<std::endl;
		}
}

bool valid_input(char input) {
	if(strchr("01",input)!=0)
		return 1;
	else return 0;

}

void frame_read(int frame_1[10][10], int frame_2[10][10]) {
	char input_raw;
	int i=0, j=0;
	std::ifstream in("frames.in");

	while(in >> input_raw ) {
		if(valid_input(input_raw)) {
			if(j==10) {
				j=0;
				i++;
			}

			if(input_raw == '1')
				frame_1[i][j]++;
			j++;
		}
	}
	
	in.close();
	
	i=0; j=0;
	std::ifstream in1("frames1.in");
	while(in1 >> input_raw ) {
		if(valid_input(input_raw)) {
			if(j==10) {
				j=0;
				i++;
			}

			if(input_raw == '1') {
				
				frame_2[i][j]++;
			}
			j++;
		}
	}


}
/* int frame_2[10][10] = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,0,0,1,0},
	{0,0,0,0,1,1,0,1,0,0},
	{0,0,0,1,1,1,1,0,0,0},
	{0,0,1,0,1,1,0,0,0,0},
	{0,1,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,1,0,0,1,0,0,0},
	{0,0,0,1,0,0,1,0,0,0},
	{0,0,0,1,0,0,1,0,0,0}
	}; */

void frame_animate(int frame_1[10][10], int frame_2[10][10]) {
	std::system("clear");
	matrix_out(frame_2);
	sleep(1);	
	std::system("clear");
	matrix_out(frame_1);
	sleep(1);

}

void build_frame_jump(int frame_jump[10][10], int frame_1[10][10]) {
	for(int j=0;j<10;j++)
		frame_jump[9][j] = 0;
	for(int i=0; i<9;i++)
		for(int j=0;j<10;j++)
			frame_jump[i-1][j] = frame_1[i][j];

}

int char_to_num(char a) {
	return a - '0';
}

int main() {

	dout<<123<<std::endl;

	int frame_1[10][10] = {0}, frame_2[10][10] = {0},
	frame_jump[10][10] = {0};
	
	frame_read(frame_1,frame_2);
	build_frame_jump(frame_jump, frame_1);
	char command[30];

	char closing_tag[2];
	
	std::system("clear");

	frame_2[9][3]++;
	frame_2[9][6]++;

	frame_jump[8][3]++;
	frame_jump[8][6]++;

	matrix_out(frame_1);

	std::cin.getline(command, 29);
	while(true) {
		if( strstr(command,"wave") != 0) {
			if( strchr(command,'-')!=0) {
				char raw_number[3];
				strcpy(raw_number, (strchr(command, '-')+1));
				int times = char_to_num(raw_number[0]);	
				for(int i=1; i<= times; i++)
					frame_animate(frame_1,frame_2);

			}
			else frame_animate(frame_1,frame_2);
			strcpy(command," ");
			std::cin.getline(command, 29);

		}
		else if( strstr(command, "jump") != 0) {
			if( strchr(command,'-')!=0) {
				char raw_number[3];
				strcpy(raw_number, (strchr(command, '-')+1));
				int times = char_to_num(raw_number[0]);	
				for(int i=1; i<= times; i++)
					frame_animate(frame_1,frame_jump);

			}
			else frame_animate(frame_1,frame_jump);
			strcpy(command," ");
			std::cin.getline(command, 29);
		}
		else if( strstr(command, "exit") != 0) {
			return 0;
			dout.close();
		}
		else {
			std::cout<<"invalid command!"<<std::endl;
			std::cin.getline(command,29);
		}

	}
}
