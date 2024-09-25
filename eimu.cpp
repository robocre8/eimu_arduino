#include "eimu.h"

EIMU::EIMU(int slave_addr)
{
  slaveAddr = slave_addr;
}

// bool EIMU::setFilterGain(float filterGain = 0.1)
// {
//   return send("/gain", filterGain);
// }

void EIMU::getFilterGain(float &filterGain)
{
  get("/gain");

  filterGain = valA;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

void EIMU::getRefFrame(int &ref_frame_id) //(0 - NWU, 1 - ENU, 2 - NED)
{
  get("/frame-id");

  ref_frame_id = (int)valA;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

bool EIMU::setRefFrame(int ref_frame_id) //(0 - NWU, 1 - ENU, 2 - NED)
{
  send("/frame-id", (float)ref_frame_id);
}

void EIMU::getRPY(float &roll, float &pitch, float &yaw)
{
  get("/rpy");

  roll = valA;
  pitch = valB;
  yaw = valC;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

void EIMU::getQuat(float &qw, float &qx, float &qy, float &qz)
{
  float r, p, y;
  getRPY(r, p, y);

  qw = cos(r / 2) * cos(p / 2) * cos(y / 2) + sin(r / 2) * sin(p / 2) * sin(y / 2);
  qx = sin(r / 2) * cos(p / 2) * cos(y / 2) - cos(r / 2) * sin(p / 2) * sin(y / 2);
  qy = cos(r / 2) * sin(p / 2) * cos(y / 2) + sin(r / 2) * cos(p / 2) * sin(y / 2);
  qz = cos(r / 2) * cos(p / 2) * sin(y / 2) - sin(r / 2) * sin(p / 2) * cos(y / 2);
}

void EIMU::getGyro(float &roll_rate, float &pitch_rate, float &yaw_rate)
{
  get("/gyro-cal");

  roll_rate = valA;
  pitch_rate = valB;
  yaw_rate = valC;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

void EIMU::getAcc(float &ax, float &ay, float &az)
{
  get("/acc-cal");

  ax = valA;
  ay = valB;
  az = valC;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

void EIMU::getRollVariance(float &r)
{
  get("/r-var");

  r = valA;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

void EIMU::getPitchVariance(float &p)
{
  get("/p-var");

  p = valA;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

void EIMU::getYawVariance(float &y)
{
  get("/y-var");

  y = valA;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

void EIMU::getAxVariance(float &ax)
{
  get("/ax-var");

  ax = valA;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

void EIMU::getAyVariance(float &ay)
{
  get("/ay-var");

  ay = valA;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

void EIMU::getAzVariance(float &az)
{
  get("/az-var");

  az = valA;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

void EIMU::getGxVariance(float &gx)
{
  get("/gx-var");

  gx = valA;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

void EIMU::getGyVariance(float &gy)
{
  get("/gy-var");

  gy = valA;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

void EIMU::getGzVariance(float &gz)
{
  get("/gz-var");

  gz = valA;

  valA = 0.0;
  valB = 0.0;
  valC = 0.0;
}

void EIMU::get(String cmd_route)
{
  masterSendData(cmd_route);
  dataMsg = masterReceiveData();

  int indexPos = 0, i = 0;
  do
  {
    indexPos = dataMsg.indexOf(',');
    if (indexPos != -1)
    {
      dataMsgBuffer = dataMsg.substring(0, indexPos);
      dataMsg = dataMsg.substring(indexPos + 1, dataMsg.length());
      dataBuffer[i] = dataMsgBuffer;
      dataMsgBuffer = "";
    }
    else
    {
      if (dataMsg.length() > 0)
        dataBuffer[i] = dataMsg;
    }
    i += 1;
  } while (indexPos >= 0);

  valA = dataBuffer[0].toFloat();
  valB = dataBuffer[1].toFloat();
  valC = dataBuffer[2].toFloat();

  dataMsg = "";
  dataMsgBuffer = "";
  dataBuffer[0] = "";
  dataBuffer[1] = "";
  dataBuffer[2] = "";
}

bool EIMU::send(String cmd_route, float valA)
{
  String msg_buffer = cmd_route;
  msg_buffer += ",";
  msg_buffer += String(valA, 3);

  masterSendData(msg_buffer);
  String data = masterReceiveCharData();
  if (data == "1")
    return true;
  else
    return false;
}

void EIMU::masterSendData(String i2c_msg)
{
  char charArray[i2c_msg.length() + 1];
  i2c_msg.toCharArray(charArray, i2c_msg.length() + 1);

  Wire.beginTransmission(slaveAddr);
  Wire.write(charArray);
  Wire.endTransmission();
}

String EIMU::masterReceiveData()
{
  String i2c_msg = "";
  Wire.requestFrom(slaveAddr, 32);
  while (Wire.available())
  {
    char c = Wire.read();
    i2c_msg += c;
  }
  int indexPos = i2c_msg.indexOf((char)255);
  if (indexPos != -1)
  {
    return i2c_msg.substring(0, indexPos);
  }
  return i2c_msg;
}

String EIMU::masterReceiveCharData()
{
  String i2c_msg = "";
  Wire.requestFrom(slaveAddr, 1);
  while (Wire.available())
  {
    char c = Wire.read();
    i2c_msg += c;
  }
  int indexPos = i2c_msg.indexOf((char)255);
  if (indexPos != -1)
  {
    return i2c_msg.substring(0, indexPos);
  }
  return i2c_msg;
}