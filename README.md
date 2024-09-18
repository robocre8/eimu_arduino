## Easy IMU Arduino I2C Lib
This library helps communicate with the already setup **`Easy IMU Module`** (i.e **`MPU9250 EIMU Module`**) with  arduino microcontroller projects via I2C, after successful setup with the [eimu_setup_application](https://github.com/samuko-things-company/eimu_setup_application).

> you can use it in your Arduino-based robotics project (e.g Arduino UNO, Arduino NANO, Arduino MEGA, Esp32, etc.)

A simple way to get started is simply to try out and follow the example code


## How to Use the Library
- Ensure you have the **`Easy IMU Module`** (i.e **`MPU9250 EIMU Module`**). Calibrate it and set it up using the **`eimu_setup_application`**.

- Download download the library by clicking on the green Code button above (or clone it)
  > if you download it, extract it and change the folder name to `eimu_arduino`

- Move the downloaded library file - **`eimu_arduino`** - to your Arduino library folder
  > e.g on linux: ... home/Arduino/libraries/
  >
  > e.g on windows: ... Documents/Arduino/libraries/
  >
  > (or any where your arduino libraries are stored)

- restart your ArduinoIDE and navigate to examples and run the example **`read_rpy.ino`** code and see the IMU readings.

- you can copy this example code into your project and modify it to your taste.


## Basic Library functions and usage

- connect to Easy IMU module via i2c by creating an object
  > `EIMU` imu(i2cAddress)

- get filtered Roll, Pitch and Yaw values in 6dp
  > imu.`getRPY`(&roll, &pitch, &yaw)

- get filtered quaternion [qw, qx, qy, qz] values in 6dp
  > imu.`getQuat`(&qw, &qx, &qy, &qz)

- get Roll, Pitch and Yaw rates value in 6dp
  > imu.`getGyro`(&gx, &gy, &gz)

- get linear acceleration values ax, ay, az in 6dp
  > imu.`getAcc`(&ax, &ay, &az)

- get roll variance in 10dp
  > imu.`getRollVariance`(&r_var)

- get pitch variance in 10dp
  > imu.`getPitchVariance`(&p_var)

- get yaw variance in 10dp
  > imu.`getYawVariance`(&y_var)

- get roll rate variances in 10dp
  > imu.`getGxVariance`(&gx_var)

- get pitch rate variances in 10dp
  > imu.`getGyVariance`(&gy_var)

- get yaw rate variances in 10dp
  > imu.`getGzVariance`(&gz_var)

- get accX variances in 10dp
  > imu.`getAxVariance`(&ax_var)

- get accY variances in 10dp
  > imu.`getAyVariance`(&ay_var)

- get accZ variances in 10dp
  > imu.`getAzVariance`(&az_var)

- get get filter gain in float
  > imu.`getFilterGain`(&gain)

- get get reference frame in string
  > imu.`getRefFrame`(&ref_frame)