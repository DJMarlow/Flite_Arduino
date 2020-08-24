![Flite](https://github.com/DJMarlow/Flite/blob/master/logo_raw.png)

#Header

**Get Controller Info**
----
  Returns a json object containing data about the Flite controller.

* **URL**

  /getControllerInfo

* **Method:**

  `GET`

* **Success Response:**

  * **Code:** 200 <br />
    **Content:** `{"id" : "controller id", "version" : "controller firmware version"}`
 
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
    **Content:** `{"level" : "current black sensor level", "temperature" : "current black sensor temperature", "pressure" : "current black sensor pressure"}`
 
* **Error Response:**

  * **Code:** 404 NOT FOUND <br />

* **Sample Call:**

`curl http://192.168.1.123/getValuesBlack`
