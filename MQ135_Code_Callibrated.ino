#include <MQUnifiedsensor.h>

// Definitions
#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A1 // Analog input 0 of your Arduino
#define type "MQ-135" // MQ135
#define ADC_Bit_Resolution 10 // For Arduino UNO/MEGA/NANO

// Define your custom Ro value
const float customRo = 59.0; // Replace with your desired Ro value in Ohms

// Declare Sensor
MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void setup() {
  // Init the serial port communication - for debugging the library
  Serial.begin(9600);

  // Set math model to calculate the PPM concentration and the value of constants
  MQ135.setRegressionMethod(1); // _PPM = a * ratio^b

  /*****************************  MQ Init ********************************************/
  // Remarks: Configure the pin of the Arduino as an input.
  /************************************************************************************/
  MQ135.init();
  
  // Set the custom Ro value
  MQ135.setR0(customRo);

  Serial.println("Using custom Ro value for calibration.");
  Serial.print("Ro = ");
  Serial.print(MQ135.getR0());
  Serial.println(" Ohms");

  Serial.println("** Values from MQ-135 **");
  Serial.println("|    CO    |  Alcohol |   CO2      |  Toluen  |  NH4     |  Aceton  |");
}

void loop() {
  MQ135.update(); // Update data, the Arduino will read the voltage from the analog pin

  MQ135.setA(605.18); MQ135.setB(-3.937); // Configure the equation to calculate CO concentration value
  float CO = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(77.255); MQ135.setB(-3.18); // Configure the equation to calculate Alcohol concentration value
  float Alcohol = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(110.47); MQ135.setB(-2.862); // Configure the equation to calculate CO2 concentration value
  float CO2 = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(44.947); MQ135.setB(-3.445); // Configure the equation to calculate Toluen concentration value
  float Toluen = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(102.2); MQ135.setB(-2.473); // Configure the equation to calculate NH4 concentration value
  float NH4 = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(34.668); MQ135.setB(-3.369); // Configure the equation to calculate Aceton concentration value
  float Aceton = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  Serial.print("|   "); Serial.print(CO);
  Serial.print("   |   "); Serial.print(Alcohol);
  Serial.print("   |   "); Serial.print(CO2 + 400); // Offset for CO2
  Serial.print("   |   "); Serial.print(Toluen);
  Serial.print("   |   "); Serial.print(NH4);
  Serial.print("   |   "); Serial.print(Aceton);
  Serial.println("   |");

  delay(500); // Sampling frequency
}
