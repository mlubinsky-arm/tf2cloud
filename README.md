## Using TFLite instead uTensor


## Configuring TD connection
Make sure you have TD account: https://console.treasuredata.com/

in main.cpp:
```
TreasureData_RESTAPI* td = new TreasureData_RESTAPI(net,"aiot_workshop_db",MBED_CONF_APP_TABLE_NAME, MBED_CONF_APP_API_KEY);

// Send data to Treasure Data
        int x = 0;
        x = sprintf(td_buff,"{\"temp\":%f,\"humidity\":%f,\"pressure\":%f}", temp_value[temp_index],humidity_value,pressure_value);
        td_buff[x]=0; //null terminate string
        td->sendData(td_buff,strlen(td_buff));
```
The MBED_CONF_APP_TABLE_NAME and MBED_CONF_APP_API_KEY shall be adjusted
in mbed_app.json
```
 "config": {
        ...
        "api-key":{
            "help":  "REST API Key for Treasure Data",
            "value": "\"CHANGE_ME\""
        },
        "table-name":{
            "help":  "name of table in Treasure Data to send data to",
            "value": "\"CHANGE_ME\""
        }
```

