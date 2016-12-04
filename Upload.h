
#ifndef UPLOAD_H
#define UPLOAD_H

class Upload{
public:
	Upload();
	char upload[255];
	void write(double input, bool HR_AR); //will write input to correct place in char upload[], based on a value of 0 for HR and 1 for AR
	void reset(); //resets all the values of the class
	int HR_int;
	int AR_int;
	int HR_col;
	int AR_col;
	unsigned long HR_writetime;
	unsigned long AR_writetime;
	unsigned long AR_write_next;
	unsigned long prev_uploadtime;
	unsigned long upload_interval;
private:
	bool publish(); //publishes char upload[] to cloud
};

Upload::Upload() // default constructor
{
    char upload[255] = {0};
	HR_int = 0;
	AR_int = 120;
	HR_col = 0;
	AR_col = 0;
	HR_writetime =0;
	AR_writetime =0;
    AR_write_next =0;
	prev_uploadtime =0;
    upload_interval = 59500;
}

void Upload::reset(){
	Upload temp;
	
	temp.HR_writetime = HR_writetime;
	temp.AR_writetime = AR_writetime;
	temp.AR_write_next = AR_write_next;
	temp.prev_uploadtime = prev_uploadtime;
	
	*this = temp;
	
}

bool Upload::publish(){
	// publish data here
    if (millis() > prev_uploadtime + upload_interval){
	    Particle.variable("Stress", upload);
	    Particle.publish("Stress", upload);
	    prev_uploadtime = millis();
	    return true;
    }
    else{
        return false;
    }

	//delay(10000);

}

void Upload::write(double input, bool HR_AR)
{

	//This will write HR values (using HR_int as an index keeper)
	//
	//
	if (HR_AR==false){
		int count = 0;
		if (input >= 10000){ // values in excess of 10,000 will write an error message
			input = -10000;
		}
		if (input == 0 || (input < 0.01&& input >0)){
			upload[HR_int] = '0';
			HR_int++;
			count++;
		}
		if (input >= 1000){
			int temp = (int)input / 1000;
			upload[HR_int] = 48 + temp;
			input -= temp * 1000;
			HR_int++;
			count++;
			if (input < 100){
				upload[HR_int] = '0';
				HR_int++;
				count++;
				if (input < 10){
					upload[HR_int] = '0';
					HR_int++;
					count++;
					if (input < 1){
						upload[HR_int] = '0';
						HR_int++;
						count++;
					}
				}
			}
		}

		if (input >= 100){
			int temp = (int)input / 100;
			upload[HR_int] = 48 + temp;
			input -= temp * 100;
			HR_int++;
			count++;
			if (input < 10){
				upload[HR_int] = '0';
				HR_int++;
				count++;
				if (input < 1){
					upload[HR_int] = '0';
					HR_int++;
					count++;
				}
			}
		}
		if (input >= 10){
			int temp = (int)input / 10;
			upload[HR_int] = 48 + temp;
			input -= temp * 10;
			HR_int++;
			count++;
			if ((int)input == 0){
				upload[HR_int] = (int)input + 48;
				HR_int++;
				count++;
			}

		}
		if (input >= 1){
			int temp = (int)input;
			upload[HR_int] = 48 + temp;
			input -= temp;
			HR_int++;
			count++;
		}
		if (input > 0){
			int temp = (int)(input * 10);
			upload[HR_int] = '.';
			upload[++HR_int] = 48 + temp;
			input = input * 100 - temp * 10;
			count += 2;
			HR_int++;
			if (input != 0){
				upload[HR_int] = 48 + (int)input;
				count++;
				HR_int++;
			}
		}
		if (input < 0){ //Negative values will give an error message
			upload[HR_int] = 'E';
			upload[++HR_int] = 'R';
			upload[++HR_int] = 'R';
			upload[++HR_int] = 'O';
			upload[++HR_int] = 'R';
			count = 5;
			HR_int++;
			input = 0;
		}

		while (count < 8){ //this ensures there will be 8 digits in the string for every reading, and a blank space between values
			upload[HR_int] = ' ';
			HR_int++;
			count++;
		}
		HR_col++;
		HR_writetime = millis();
	}
	//This will write corresponding AR values (using AR_int as an index keeper
	//
	//
	else{
		int count = 0;
		if (input >= 100){ // values in excess of 10,000 will write an error message
			input = -10000;
		}
		if (input == 0 || (input < 0.0001&& input >0)){
			upload[AR_int] = '0';
			AR_int++;
			count++;
		}
		if (input >= 1000){
			int temp = (int)input / 1000;
			upload[AR_int] = 48 + temp;
			input -= temp * 1000;
			AR_int++;
			count++;
			if (input < 100){
				upload[AR_int] = '0';
				AR_int++;
				count++;
				if (input < 10){
					upload[AR_int] = '0';
					AR_int++;
					count++;
					if (input < 1){
						upload[AR_int] = '0';
						AR_int++;
						count++;
					}
				}
			}
		}

		if (input >= 100){
			int temp = (int)input / 100;
			upload[AR_int] = 48 + temp;
			input -= temp * 100;
			AR_int++;
			count++;
			if (input < 10){
				upload[AR_int] = '0';
				AR_int++;
				count++;
				if (input < 1){
					upload[AR_int] = '0';
					AR_int++;
					count++;
				}
			}
		}
		if (input >= 10){
			int temp = (int)input / 10;
			upload[AR_int] = 48 + temp;
			input -= temp * 10;
			AR_int++;
			count++;
			if ((int)input == 0){
				upload[AR_int] = (int)input + 48;
				AR_int++;
				count++;
			}

		}
		if (input >= 1){
			int temp = (int)input;
			upload[AR_int] = 48 + temp;
			input -= temp;
			AR_int++;
			count++;
		}
		if (input > 0){
			int temp = (int)(input * 10);
			upload[AR_int] = '.';
			upload[++AR_int] = 48 + temp;
			input = input * 10 - temp;
			count += 2;
			AR_int++;
			if (input != 0){
				int temp1 = (int)(input * 10);
				upload[AR_int] = 48 + temp1;
				input = input * 10 - temp1;
				count++;
				AR_int++;
			}
			if (input != 0){
				int temp1 = (int)(input * 10);
				upload[AR_int] = 48 + temp1;
				input = input * 10 - temp1;
				count++;
				AR_int++;
			}
			if (input != 0){
				int temp1 = (int)(input * 10);
				upload[AR_int] = 48 + temp1;
				input = input * 10 - temp1;
				count++;
				AR_int++;
			}

		}
		if (input < 0){ //Negative values will give an error message
			upload[AR_int] = 'E';
			upload[++AR_int] = 'R';
			upload[++AR_int] = 'R';
			upload[++AR_int] = 'O';
			upload[++AR_int] = 'R';
			count = 5;
			AR_int++;
			input = 0;
		}

		while (count < 8){ //this ensures there will be 8 digits in the string for every reading, and a blank space between values
			upload[AR_int] = ' ';
			AR_int++;
			count++;
		}
		AR_col++;
		AR_writetime = millis();
		AR_write_next = AR_writetime;

	

	    if (AR_col ==15 && HR_col == 15){
		       //upload data to cloud and reset
		    while (AR_int < 255){
			    upload[AR_int] = '\0';
			    AR_int++;
		    }
		    	
		for(int i =0;i<5;i++){
		    if(publish()){
		        break;
		    }
		}
		publish();
		reset();
	    
		    
	    }
	    
	}
		
		//publish(); // these need to move back up for final version
		//reset();   //
	


}





#endif
