//Gyro scope 
#include "Wire.h"

const int MPU_ADDR = 0x68;

int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;
int16_t temperature;

char tmp_str[7];
char* convert_int16_to_str(int16_t i) {
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

// distance scope 
const int trigPin = 9; 
const int echoPin = 10; 

long duration;
int distance;

// Controller scope 
#include <IRremote.h>

const int RECV_PIN = 7; 
IRrecv irrecv(RECV_PIN);
decode_results results; 

bool label = true; //for printing csv headers


void setup() {
  // Gyro code 
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  // Distance measurement
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  Serial.begin(9600);
  // Controller settup 
  // Serial.begin(9600); 
  // irrecv.enableIRIn();
  // irrecv.blinnk13(true);
}

void loop() {

  // if (irrecv.decode(&results.value)){
  //   switch(results.value){
  //         case 0xFF38C7: //Keypad button "5"
  //         digitalWrite(redPin, HIGH);
  //         delay(2000);
  //         digitalWrite(redPin, LOW);
  //         }
  // }
  // GYRO SETTUP 
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 7 * 2, true);
  // "wire.read ()<<8| Wire.read;" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read() << 8 | Wire.read();
  accelerometer_y = Wire.read() << 8 | Wire.read();
  accelerometer_z = Wire.read() << 8 | Wire.read();
  temperature = Wire.read() << 8 | Wire.read();
  gyro_x = Wire.read() << 8 | Wire.read();
  gyro_y = Wire.read() << 8 | Wire.read();
  gyro_z = Wire.read() << 8 | Wire.read();

  //ditance code 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;

  // CONTROLLER SETTUP 

  //Printing CSV Headers
     //print out column headers
    while(label){ //runs once
        Serial.print("accelerometer_x");
        Serial.print(",");
        Serial.println("accelerometer_y");
        Serial.print(",");
        Serial.println("accelerometer_z");
        Serial.print(",");
        Serial.println("temp");
        Serial.print(",");
        Serial.println("gyro_x");
        Serial.print(",");
        Serial.println("gyro_y");
        Serial.print(",");
        Serial.println("gyro_z");
        Serial.print(",");
        Serial.println("distance");
        label=false;
    }

    // Print data to CSV
    Serial.print(convert_int16_to_str(accelerometer_x));
    Serial.print(",");
    Serial.print(convert_int16_to_str(accelerometer_y));
    Serial.print(",");
    Serial.print(convert_int16_to_str(accelerometer_z));
    Serial.print(",");
    Serial.print(temperature / 340.00 + 36.53);
    Serial.print(",");
    Serial.print(convert_int16_to_str(gyro_x));
    Serial.print(",");
    Serial.print(convert_int16_to_str(gyro_y));
    Serial.print(",");
    Serial.print(convert_int16_to_str(gyro_z));
    Serial.print(",");
    Serial.println(distance);

    // Delay
    delay(1000);


//   // print out data
//   Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
//   Serial.print(" | aY = ");
//   Serial.print(convert_int16_to_str(accelerometer_y));
//   Serial.print(" | aZ = ");
//   Serial.print(convert_int16_to_str(accelerometer_z));
//   // the following equation was taken from the documentation
//   Serial.print(" | tmp = ");
//   Serial.print(temperature / 340.00 + 36.53);
//   Serial.print(" | gX = ");
//   Serial.print(convert_int16_to_str(gyro_x));
//   Serial.print(" | gY = ");
//   Serial.print(convert_int16_to_str(gyro_y));
//   Serial.print(" | gZ = ");
//   Serial.print(convert_int16_to_str(gyro_z));

//   // implementation of distance
//   Serial.print(" | Dist = ");
//   Serial.println(distance);

//   //delay
//   delay(1000);
// }
