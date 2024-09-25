/*
 * Basic example code shows how to read orientation data from the MPU9250 EIMU Module
 * which have been succesfully calibrated with filter and covariances setup
 *
 * The code basically reads roll, pitch, and yaw values from the MPU9250 EIMU Module connected to it.
 * read printed values from serial monitor or serial plotter.
 *
 * you can copy the code and use it in your project as you will.
 */

// Easy IMU i2c communication library
#include <eimu.h>

// please update with the address with that which you set when doing
// calibration and filter setup with the eimu_setup_application
uint8_t imuAddress = 104; // i.e 0x68 in HEX
EIMU imu(imuAddress);

float toRad = 2 * PI / 360;
float toDeg = 1 / toRad;

float roll, pitch, yaw; // create variables to store orientations
String ref_frame;

long prevSampleTime;
long sampleTime = 100; // millisec

void setup()
{
  // start i2c communication
  Wire.begin();

  // setup serial communication to print result on serial minitor
  Serial.begin(115200);

  // wait for the imu module to fully setup
  for (int i = 1; i <= 6; i += 1)
  {
    delay(1000);
    Serial.println(i);
  }

  // change the reference frame to ENU frame (0 - NWU,  1 - ENU,  2 - NED)
  imu.setRefFrame(1);

  // check the refence frame the IMU is working in (0 - NWU,  1 - ENU,  2 - NED)
  int ref_frame_id;
  imu.getRefFrame(ref_frame_id);
  if (ref_frame_id == 0)
    Serial.println("Reference Frame is North-West-Up (NWU)");
  else if (ref_frame_id == 1)
    Serial.println("Reference Frame is East-North-Up (ENU)");
  else if (ref_frame_id == 2)
    Serial.println("Reference Frame is North-East-Down (NED)");

  // wait for the imu module to fully setup
  for (int i = 1; i <= 4; i += 1)
  {
    delay(1000);
    Serial.println(i);
  }

  prevSampleTime = millis();
}

void loop()
{

  if ((millis() - prevSampleTime) >= sampleTime)
  {
    /* CODE SHOULD GO IN HERE*/

    imu.getRPY(roll, pitch, yaw); // read roll, pitch, yaw in radians

    Serial.print(roll, 4);
    Serial.print(", ");
    Serial.print(pitch, 4);
    Serial.print(", ");
    Serial.println(yaw, 4);

    // Serial.print(roll * toDeg, 1);
    // Serial.print(", ");
    // Serial.print(pitch * toDeg, 1);
    // Serial.print(", ");
    // Serial.println(yaw * toDeg, 1);

    prevSampleTime = millis();
  }
}