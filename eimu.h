#ifndef EIMU_H
#define EIMU_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Wire.h>
#include <math.h>

class EIMU
{
public:
  EIMU(int);

  // bool setFilterGain(float);
  void getFilterGain(float &);
  void getRefFrame(int &);
  bool setRefFrame(int);

  void getRPY(float &, float &, float &);
  void getGyro(float &, float &, float &);
  void getAcc(float &, float &, float &);
  void getQuat(float &, float &, float &, float &);

  void getRollVariance(float &);
  void getPitchVariance(float &);
  void getYawVariance(float &);

  void getAxVariance(float &);
  void getAyVariance(float &);
  void getAzVariance(float &);

  void getGxVariance(float &);
  void getGyVariance(float &);
  void getGzVariance(float &);

private:
  int slaveAddr;
  String dataMsg = "", dataMsgBuffer = "", dataBuffer[3];
  float valA, valB, valC;

  void get(String);

  bool send(String, float);

  void masterSendData(String);

  String masterReceiveData();

  String masterReceiveCharData();
};

#endif
