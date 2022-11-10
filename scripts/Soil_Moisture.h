
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
 int Soil_data_array; //variables for calculations
 }

void loop(){
int moist1 = analogRead(A1);
   delay(10);  
   moist1 = analogRead(A1); //take reading 1
   Serial.print("sensor 1's reading: ");
   Serial.println(moist1);
   delay(500); //delay to allow ADC
   
   int moist2 = analogRead(A2);
   delay(10);
   moist2 = analogRead(A2);  //take reading 2
   Serial.print("sensor 2's reading: ");
   Serial.println(moist2);
   delay(500);
   
   int moist3 = analogRead(A4);
   delay(10);
   moist3 = analogRead(A4);  //take reading 3
   Serial.print("sensor 3's reading: ");
   Serial.println(moist3);
   delay(500);

// calculate the average of all the readings
   int average = (moist1 + moist2 + moist3) / 3;
   Serial.print("average reading: ");
   Serial.println(average);
   delay(500);
   
   // calculate the percentage of moisture
   int moisture = (average - 1023) * -1;
   Serial.print("moisture percentage: ");
   Serial.println(moisture);
   delay(500);
   
   // calculate the percentage of dryness
   int dryness = moisture - 100;
   Serial.print("dryness percentage: ");
   Serial.println(dryness);
   delay(500);

// create an array with all the values of moist1,2,3, average, moisture percentage and dryness percentage
int Soil_data_array[6] = {moist1, moist2, moist3, average, moisture, dryness};
// save the array to a file
save_to_file(Soil_data_array);
delay(500);
}
