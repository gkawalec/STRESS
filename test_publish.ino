double Get_Input(bool&); // will get the input based on an alternating value to select AR or HR
bool HR_AR = 1; //to get HR this will equal 1, to get AR, it will be 0
int testing = 0; //CAN BE REMOVED FOR REAL CODE


void setup() {
    bool HR_AR = 1; //to get HR this will equal 1, to get AR, it will be 0
    int testing = 0; //CAN BE REMOVED FOR REAL CODE

}

void loop() {
    char upload[255] = {0};
    int i = 0;
    int j = 120;
	while (j < 240){
		double input = Get_Input(HR_AR);
		bool error = 0;
		//This will write HR values (using i as an index keeper)
		//
		//
		if (!HR_AR){
			int count = 0;
			if (input >= 10000){ // values in excess of 10,000 will write an error message
				input = -10000;
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

			while (count < 8){ //this ensures there will be 8 digits in the string for every reading, and a blank space between values
				upload[i] = ' ';
				i++;
				count++;
			}
		}
		//This will write corresponding AR values (using j as an index keeper
		//
		//
		else{
			int count = 0;
			if (input >= 10000){ // values in excess of 10,000 will write an error message
				input = -10000;
			}
			if (input == 0 || (input < 0.01&& input >0)){
				upload[j] = '0';
				j++;
				count++;
			}
			if (input >= 1000){
				int temp = (int)input / 1000;
				upload[j] = 48 + temp;
				input -= temp * 1000;
				j++;
				count++;
				if (input < 100){
					upload[j] = '0';
					j++;
					count++;
					if (input < 10){
						upload[j] = '0';
						j++;
						count++;
						if (input < 1){
							upload[j] = '0';
							j++;
							count++;
						}
					}
				}
			}

			if (input >= 100){
				int temp = (int)input / 100;
				upload[j] = 48 + temp;
				input -= temp * 100;
				j++;
				count++;
				if (input < 10){
					upload[j] = '0';
					j++;
					count++;
					if (input < 1){
						upload[j] = '0';
						j++;
						count++;
					}
				}
			}
			if (input >= 10){
				int temp = (int)input / 10;
				upload[j] = 48 + temp;
				input -= temp * 10;
				j++;
				count++;
				if ((int)input == 0){
					upload[j] = (int)input + 48;
					j++;
					count++;
				}

			}
			if (input >= 1){
				int temp = (int)input;
				upload[j] = 48 + temp;
				input -= temp;
				j++;
				count++;
			}
			if (input > 0){
				int temp = (int)(input * 10);
				upload[j] = '.';
				upload[++j] = 48 + temp;
				input = input * 100 - temp * 10;
				count += 2;
				j++;
				if (input != 0){
					upload[j] = 48 + (int)input;
					count++;
					j++;
				}
			}
			if (input < 0){ //Negative values will give an error message
				upload[j] = 'E';
				upload[++j] = 'R';
				upload[++j] = 'R';
				upload[++j] = 'O';
				upload[++j] = 'R';
				count = 5;
				j++;
				input = 0;
			}

			while (count < 8){ //this ensures there will be 8 digits in the string for every reading, and a blank space between values
				upload[j] = ' ';
				j++;
				count++;
			}
		}



		testing++; //REMOVE FOR ACTUAL CODE
	}
	
	
	
	Particle.variable("Stress", upload);
	Particle.publish("Stress", upload);
	delay(10000);

}



double Get_Input(bool& HR_AR){
	if (HR_AR){
		double HR = 1000.23 + 100 * testing; //For test purposes only!!
		//Add function for interpreting HR here
		//
		//

		HR_AR = 0;
		return HR;
	}
	else{
		double AR = 8000 + testing * 100; //For test purposes only!!
		//Add function for interpreting AR here
		//
		//

		HR_AR = 1;
		return AR;
	}
}
