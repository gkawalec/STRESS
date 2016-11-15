double Get_Input(bool&); // will get the input based on an alternating value to select AR or HR
bool HR_AR = 1; //to get HR this will equal 1, to get AR, it will be 0
double Max_HR = 0;
double Min_HR = 0;


void setup() {
}

void loop() {
    
    char upload[255] = {0};
    int i = 0;
	while (i < 240){
		double input = Get_Input(HR_AR);
		int count = 0;
		if (input >= 10000){ // values in excess of 10,000 will write an error message
			upload[i] = 'E';
			upload[++i] = 'R';
			upload[++i] = 'R';
			upload[++i] = 'O';
			upload[++i] = 'R';
			count = 5;
			i++;
			input = 0;
		}
		if (input == 0 || (input < 0.01&& input >0)){
			upload[i] = '0';
			i++;
			count++;
		}
		if (input >= 1000){
			int temp = (int)input / 1000;
			upload[i] = 48 + temp;
			input -= temp * 1000;
			i++;
			count++;
			if (input < 100){
				upload[i] = '0';
				i++;
				count++;
				if (input < 10){
					upload[i] = '0';
					i++;
					count++;
					if (input < 1){
						upload[i] = '0';
						i++;
						count++;
					}
				}
			}
		}

		if (input >= 100){
			int temp = (int)input / 100;
			upload[i] = 48 + temp;
			input -= temp * 100;
			i++;
			count++;
			if (input < 10){
				upload[i] = '0';
				i++;
				count++;
				if (input < 1){
					upload[i] = '0';
					i++;
					count++;
				}
			}
		}
		if (input >= 10){
			int temp = (int)input / 10;
			upload[i] = 48 + temp;
			input -= temp * 10;
			i++;
			count++;
			if ((int)input == 0){
				upload[i] = (int)input + 48;
				i++;
				count++;
			}

		}
		if (input >= 1){
			int temp = (int)input;
			upload[i] = 48 + temp;
			input -= temp;
			i++;
			count++;
		}
		if (input > 0){
			int temp = (int)(input * 10);
			upload[i] = '.';
			upload[++i] = 48 + temp;
			input = input * 100 - temp * 10;
			count += 2;
			i++;
			if (input != 0){
				upload[i] = 48 + (int)input;
				count++;
				i++;
			}
		}
		if (input < 0){ //Negative values will give an error message
			upload[i] = 'E';
			upload[++i] = 'R';
			upload[++i] = 'R';
			upload[++i] = 'O';
			upload[++i] = 'R';
			count = 5;
			i++;
			input = 0;
		}

		while (count < 7){ //this ensures there will be 8 digits in the string for every reading
			upload[i] = ' ';
			i++;
			count++;
		}
		if (!HR_AR){
			upload[i] = 9;
			i++;
		}
		else{
			upload[i] = '\n'; // newline
			i++;
		}
	}
	//Particle.publish("Stress", upload);

}



double Get_Input(bool& HR_AR){

	if (HR_AR == true){
		double HR = 1000.23;
		HR_AR = 0;
		if (HR > Max_HR){ //update maximum value
			Max_HR = HR;
		}
		if (HR < Min_HR){ //update minimum value
			Min_HR = HR;
		}
		return HR;
	}
	else{
		double AR = 17037.32;
		HR_AR = 1;
		return AR;
	}

}
