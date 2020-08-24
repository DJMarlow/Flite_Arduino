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

  ```
GET curl http://<ControllerIP>/getControllerInfo
  ```
