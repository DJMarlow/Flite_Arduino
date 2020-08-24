**Get Controller Info**
----
  Returns json data about the Flite controller.

* **URL**

  /getControllerInfo

* **Method:**

  `GET`

* **Success Response:**

  * **Code:** 200 <br />
    **Content:** `{ "id" : "controller id", "version" : "controller firmware version" }`
 
* **Error Response:**

  * **Code:** 404 NOT FOUND <br />

* **Sample Call:**

  ```java
GET curl http://192.168.1.123/getControllerInfo
  ```
