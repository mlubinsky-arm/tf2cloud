## Using TFLite instead uTensor

```
git clone https://github.com/tensorflow/tensorflow.git
```
<https://developer.arm.com/solutions/machine-learning-on-arm/developer-material/how-to-guides/build-arm-cortex-m-voice-assistant-with-google-tensorflow-lite/single-page>

### TFlite uses  C++11 compiler, but Mbedos uses C++98

```
find . -name "*.json" | xargs grep "std=gnu++98"

./profiles/debug_size.json:        "cxx": ["-std=gnu++98", "-fno-rtti", "-Wvla"],
./profiles/debug_size.json:        "cxx": ["-fno-rtti", "-std=gnu++98"],
./profiles/size.json:        "cxx": ["-std=gnu++98", "-fno-rtti", "-Wvla"],
./profiles/size.json:        "cxx": ["-fno-rtti", "-std=gnu++98"],
```
Let update compiler version in Mbedos tooling to C++11:
```
python -c 'import fileinput, glob;
for filename in glob.glob("mbed-os/tools/profiles/*.json"):
  for line in fileinput.input(filename, inplace=True):
    print (line.replace("\"-std=gnu++98\"","\"-std=c++11\", \"-fpermissive\""))'

```
###  make version

TFLite Requires make version 3.82 or later.
On Mac you can use gmake:
```
brew install gmake
```

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

