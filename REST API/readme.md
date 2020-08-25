**Get Controller Info**
----
  Returns a json object containing data about the Flite controller.

* **URL**

  /getControllerInfo

* **Method:**

  `GET`

* **Success Response:**

  * **Code:** 200 <br />
    **Content:** `{"id" : "5WfDzd0feF", "version" : "1.0"}`
 
* **Error Response:**

  * **Code:** 404 NOT FOUND <br />

* **Sample Call:**

  `curl http://192.168.1.123/getControllerInfo`


**Get Sensor Values (BLACK Flite Sensor)**
----
  Returns a json object representing the current values for a connected Black Flite Sensor.

* **URL**

  /getValuesBlack

* **Method:**

  `GET`

* **Success Response:**

  * **Code:** 200 <br />
    **Content:** `{"level" : "3.2", "temperature" : "48.5", "pressure" : "8.7"}`
 
* **Error Response:**

  * **Code:** 404 NOT FOUND <br />

* **Sample Call:**

  `curl http://192.168.1.123/getValuesBlack`


**Get Zero Calibration Offset (BLACK Flite Sensor)**
----
  Returns a json object representing the stored zero pressure offset for a connected Black Flite Sensor.

* **URL**

  /getZeroPressureBlack

* **Method:**

  `GET`

* **Success Response:**

  * **Code:** 200 <br />
    **Content:** `{"pressure" : "14.6"}`
 
* **Error Response:**

  * **Code:** 404 NOT FOUND <br />

* **Sample Call:**

  `curl http://192.168.1.123/getZeroPressureBlack`
  
  
  **Get Level Calibration Coefficients (BLACK Flite Sensor)**
----
  Returns a json object representing the stored high and low calibration coefficients for a connected Black Flite Sensor.
  Level high and level low represent the gallons when the corrseponding calibration was performed.
  Distance high and distance low represent the distance away from the sensor when the corrseponding calibration was performed.

* **URL**

  /getLevelCalBlack

* **Method:**

  `GET`

* **Success Response:**

  * **Code:** 200 <br />
    **Content:** `{"levelLow": "0.0", "levelHigh": "4.6", "distanceLow": "630.0", "distanceHigh": "87.0"}`
 
* **Error Response:**

  * **Code:** 404 NOT FOUND <br />

* **Sample Call:**

  `curl http://192.168.1.123/getLevelCalBlack`
