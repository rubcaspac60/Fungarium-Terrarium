
void setup(){
  // put your setup code here, to run once:
 Serial.begin(9600);  //com enable
 int Soil_sensor1 = analogRead(A1);
  int Soil_sensor2 = analogRead(A2);
   int Soil_sensor3 = analogRead(A4); //assigning analog pins
 int moist1;
 int moist2;
 int moist3;
 int average;
 int moisture;
 int dryness;
 int Soil_data_0;
 int Soil_data_15;
 int Soil_data_30;
 int Soil_data_45;
 int Soil_data_60;
 int Soil_data_75;
 int Soil_data_90;
 int Soil_data_100; //variables for calculations
 }

int main(void){
Serial.println("Soil Moisture Sensor Calibration");
Serial.println("Please enter the soil moisture value for the following soil moisture values (start from 0%):");
Serial.println("0%, 15%, 30%, 45%, 60%, 75%, 90%, 100%");

Serial.println("Please enter the soil moisture value for 0%:");
int moist1 = analogRead(A1);
int moist2 = analogRead(A2);
int moist3 = analogRead(A4); //assigning analog pins
   delay(10);  
   moist1 = analogRead(A1); //take reading 1
   moist2 = analogRead(A2);  //take reading 2
   moist3 = analogRead(A4);  //take reading 3
   delay(500); //delay to allow ADC

// calculate the average of all the readings
   int average = (moist1 + moist2 + moist3) / 3;
   // calculate the percentage of moisture
   int moisture = (average - 1023) * -1;
   // calculate the percentage of dryness
   int dryness = moisture - 100;
   delay(500);

// create an array with all the values of moist1,2,3, average, moisture percentage and dryness percentage
int Soil_data_0[6] = {moist1, moist2, moist3, average, moisture, dryness};
// save the array to a file
save_to_file(Soil_data_0);
delay(500);
/----------------------------------------------------------------------------------------------------------------------------/
// prompt a message to the user to enter the soil moisture value for 15%

Serial.println("Please enter the soil moisture value for 15%:");
// wait to the user to press enter
while (Serial.available() == 0) {
  delay(100);
  // print a dot to show that the program is waiting for the user to press enter
    Serial.print("Press enter to continue...");
    Serial.println(".");
}
// read the soil moisture value for 15%
int moist1 = analogRead(A1);
int moist2 = analogRead(A2);
int moist3 = analogRead(A4); //assigning analog pins
   delay(10);  
   moist1 = analogRead(A1); //take reading 1
   moist2 = analogRead(A2);  //take reading 2
   moist3 = analogRead(A4);  //take reading 3
   delay(500); //delay to allow ADC

// calculate the average of all the readings
   int average = (moist1 + moist2 + moist3) / 3;
   // calculate the percentage of moisture
   int moisture = (average - 1023) * -1;
   // calculate the percentage of dryness
   int dryness = moisture - 100;
   delay(500);

// create an array with all the values of moist1,2,3, average, moisture percentage and dryness percentage
int Soil_data_15[6] = {moist1, moist2, moist3, average, moisture, dryness};
// save the array to a file
save_to_file(Soil_data_15);

/----------------------------------------------------------------------------------------------------------------------------/


// prompt a message to the user to enter the soil moisture value for 30%

Serial.println("Please enter the soil moisture value for 30%:");
// wait to the user to press enter
while (Serial.available() == 0) {
  delay(100);
  // print a dot to show that the program is waiting for the user to press enter
    Serial.print("Press enter to continue...");
    Serial.println(".");
}
// read the soil moisture value for 15%
int moist1 = analogRead(A1);
int moist2 = analogRead(A2);
int moist3 = analogRead(A4); //assigning analog pins
   delay(10);  
   moist1 = analogRead(A1); //take reading 1
   moist2 = analogRead(A2);  //take reading 2
   moist3 = analogRead(A4);  //take reading 3
   delay(500); //delay to allow ADC

// calculate the average of all the readings
   int average = (moist1 + moist2 + moist3) / 3;
   // calculate the percentage of moisture
   int moisture = (average - 1023) * -1;
   // calculate the percentage of dryness
   int dryness = moisture - 100;
   delay(500);

// create an array with all the values of moist1,2,3, average, moisture percentage and dryness percentage
int Soil_data_30[6] = {moist1, moist2, moist3, average, moisture, dryness};
// save the array to a file
save_to_file(Soil_data_30);

/----------------------------------------------------------------------------------------------------------------------------/


// prompt a message to the user to enter the soil moisture value for 45%

Serial.println("Please enter the soil moisture value for 45%:");
// wait to the user to press enter
while (Serial.available() == 0) {
  delay(100);
  // print a dot to show that the program is waiting for the user to press enter
    Serial.print("Press enter to continue...");
    Serial.println(".");
}
// read the soil moisture value for 45%
int moist1 = analogRead(A1);
int moist2 = analogRead(A2);
int moist3 = analogRead(A4); //assigning analog pins
   delay(10);  
   moist1 = analogRead(A1); //take reading 1
   moist2 = analogRead(A2);  //take reading 2
   moist3 = analogRead(A4);  //take reading 3
   delay(500); //delay to allow ADC

// calculate the average of all the readings
   int average = (moist1 + moist2 + moist3) / 3;
   // calculate the percentage of moisture
   int moisture = (average - 1023) * -1;
   // calculate the percentage of dryness
   int dryness = moisture - 100;
   delay(500);

// create an array with all the values of moist1,2,3, average, moisture percentage and dryness percentage
int Soil_data_45[6] = {moist1, moist2, moist3, average, moisture, dryness};
// save the array to a file
save_to_file(Soil_data_45);

/----------------------------------------------------------------------------------------------------------------------------/


// prompt a message to the user to enter the soil moisture value for 60%

Serial.println("Please enter the soil moisture value for 60%:");
// wait to the user to press enter
while (Serial.available() == 0) {
  delay(100);
  // print a dot to show that the program is waiting for the user to press enter
    Serial.print("Press enter to continue...");
    Serial.println(".");
}
// read the soil moisture value for 60%
int moist1 = analogRead(A1);
int moist2 = analogRead(A2);
int moist3 = analogRead(A4); //assigning analog pins
   delay(10);  
   moist1 = analogRead(A1); //take reading 1
   moist2 = analogRead(A2);  //take reading 2
   moist3 = analogRead(A4);  //take reading 3
   delay(500); //delay to allow ADC

// calculate the average of all the readings
   int average = (moist1 + moist2 + moist3) / 3;
   // calculate the percentage of moisture
   int moisture = (average - 1023) * -1;
   // calculate the percentage of dryness
   int dryness = moisture - 100;
   delay(500);

// create an array with all the values of moist1,2,3, average, moisture percentage and dryness percentage
int Soil_data_60[6] = {moist1, moist2, moist3, average, moisture, dryness};
// save the array to a file
save_to_file(Soil_data_60);

/----------------------------------------------------------------------------------------------------------------------------/


// prompt a message to the user to enter the soil moisture value for 75%

Serial.println("Please enter the soil moisture value for 75%:");
// wait to the user to press enter
while (Serial.available() == 0) {
  delay(100);
  // print a dot to show that the program is waiting for the user to press enter
    Serial.print("Press enter to continue...");
    Serial.println(".");
}
// read the soil moisture value for 75%
int moist1 = analogRead(A1);
int moist2 = analogRead(A2);
int moist3 = analogRead(A4); //assigning analog pins
   delay(10);  
   moist1 = analogRead(A1); //take reading 1
   moist2 = analogRead(A2);  //take reading 2
   moist3 = analogRead(A4);  //take reading 3
   delay(500); //delay to allow ADC

// calculate the average of all the readings
   int average = (moist1 + moist2 + moist3) / 3;
   // calculate the percentage of moisture
   int moisture = (average - 1023) * -1;
   // calculate the percentage of dryness
   int dryness = moisture - 100;
   delay(500);

// create an array with all the values of moist1,2,3, average, moisture percentage and dryness percentage
int Soil_data_75[6] = {moist1, moist2, moist3, average, moisture, dryness};
// save the array to a file
save_to_file(Soil_data_75);
/----------------------------------------------------------------------------------------------------------------------------/


// prompt a message to the user to enter the soil moisture value for 90%

Serial.println("Please enter the soil moisture value for 90%:");
// wait to the user to press enter
while (Serial.available() == 0) {
  delay(100);
  // print a dot to show that the program is waiting for the user to press enter
    Serial.print("Press enter to continue...");
    Serial.println(".");
}
// read the soil moisture value for 90%
int moist1 = analogRead(A1);
int moist2 = analogRead(A2);
int moist3 = analogRead(A4); //assigning analog pins
   delay(10);  
   moist1 = analogRead(A1); //take reading 1
   moist2 = analogRead(A2);  //take reading 2
   moist3 = analogRead(A4);  //take reading 3
   delay(500); //delay to allow ADC

// calculate the average of all the readings
   int average = (moist1 + moist2 + moist3) / 3;
   // calculate the percentage of moisture
   int moisture = (average - 1023) * -1;
   // calculate the percentage of dryness
   int dryness = moisture - 100;
   delay(500);

// create an array with all the values of moist1,2,3, average, moisture percentage and dryness percentage
int Soil_data_90[6] = {moist1, moist2, moist3, average, moisture, dryness};
// save the array to a file
save_to_file(Soil_data_90);

/----------------------------------------------------------------------------------------------------------------------------/


// prompt a message to the user to enter the soil moisture value for 100%

Serial.println("Please enter the soil moisture value for 100%:");
// wait to the user to press enter
while (Serial.available() == 0) {
  delay(100);
  // print a dot to show that the program is waiting for the user to press enter
    Serial.print("Press enter to continue...");
    Serial.println(".");
}
// read the soil moisture value for 100%
int moist1 = analogRead(A1);
int moist2 = analogRead(A2);
int moist3 = analogRead(A4); //assigning analog pins
   delay(10);  
   moist1 = analogRead(A1); //take reading 1
   moist2 = analogRead(A2);  //take reading 2
   moist3 = analogRead(A4);  //take reading 3
   delay(500); //delay to allow ADC

// calculate the average of all the readings
   int average = (moist1 + moist2 + moist3) / 3;
   // calculate the percentage of moisture
   int moisture = (average - 1023) * -1;
   // calculate the percentage of dryness
   int dryness = moisture - 100;
   delay(500);

// create an array with all the values of moist1,2,3, average, moisture percentage and dryness percentage
int Soil_data_100[6] = {moist1, moist2, moist3, average, moisture, dryness};
// save the array to a file
save_to_file(Soil_data_100);
// print a message to the user to show that the program has finished
Serial.println("The program has finished. Please check the file to see the results.");
}

