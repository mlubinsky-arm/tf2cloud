## Using TFLite instead uTensor

<https://gitter.im/tensorflow/sig-micro>


<https://developer.arm.com/solutions/machine-learning-on-arm/developer-material/how-to-guides/build-arm-cortex-m-voice-assistant-with-google-tensorflow-lite/single-page>
```
git clone https://github.com/tensorflow/tensorflow.git
cd tensorflow
```

###  make version

TFLite requires the make version 3.82 or later.
On Mac you can use gmake:
```
brew install gmake
```

### Install curl and unzip in Docker
```
apt-get update
apt-get -y install curl
apt-get install unzip
```
### Compile "hello world" example
 Documentation (master):
<https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/hello_world/#deploy-to-stm32f746>

 Documentation (experimental)
<https://github.com/tensorflow/tensorflow/tree/v2.1.0/tensorflow/lite/experimental/micro/examples/hello_world#deploy-to-stm32f746>

```
(g)make -f tensorflow/lite/micro/tools/make/Makefile  TARGET=mbed TAGS="CMSIS disco_f746ng" generate_hello_world_mbed_project
```
Outcome:
```
tensorflow/lite/micro/tools/make/download_and_extract.sh "https://github.com/google/gemmlowp/archive/719139ce755a0f31cbf1c37f7f98adcc7fc9f425.zip" "7e8191b24853d75de2af87622ad293ba" tensorflow/lite/micro/tools/make/downloads/gemmlowp

downloading https://github.com/google/gemmlowp/archive/719139ce755a0f31cbf1c37f7f98adcc7fc9f425.zip
tensorflow/lite/micro/tools/make/download_and_extract.sh "https://github.com/google/flatbuffers/archive/v1.12.0.tar.gz" "c62ffefb3d4548b127cca14ce047f16c" tensorflow/lite/micro/tools/make/downloads/flatbuffers

downloading https://github.com/google/flatbuffers/archive/v1.12.0.tar.gz
tensorflow/lite/micro/tools/make/download_and_extract.sh "https://github.com/ARM-software/CMSIS_5/archive/b2937134bd2047bd569c4408391ae20d7677d35c.zip" "04cb3a2cb4834284767a01e8f1c6f834" tensorflow/lite/micro/tools/make/downloads/cmsis

downloading https://github.com/ARM-software/CMSIS_5/archive/b2937134bd2047bd569c4408391ae20d7677d35c.zip
tensorflow/lite/micro/tools/make/download_and_extract.sh "https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2018q2/gcc-arm-none-eabi-7-2018-q2-update-mac.tar.bz2" "a66be9828cf3c57d7d21178e07cd8904" tensorflow/lite/micro/tools/make/downloads/gcc_embedded

downloading https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2018q2/gcc-arm-none-eabi-7-2018-q2-update-mac.tar.bz2
tensorflow/lite/micro/tools/make/download_and_extract.sh "https://github.com/mborgerding/kissfft/archive/v130.zip" "438ba1fef5783cc5f5f201395cc477ca" tensorflow/lite/micro/tools/make/downloads/kissfft patch_kissfft

downloading https://github.com/mborgerding/kissfft/archive/v130.zip
Finished patching kissfft
tensorflow/lite/micro/tools/make/download_and_extract.sh "https://storage.googleapis.com/download.tensorflow.org/data/tf_lite_micro_person_data_grayscale_2019_11_21.zip" "fe2934bd0788f1dcc7af3f0a954542ab" tensorflow/lite/micro/tools/make/downloads/person_model_grayscale

downloading https://storage.googleapis.com/download.tensorflow.org/data/tf_lite_micro_person_data_grayscale_2019_11_21.zip
tensorflow/lite/micro/tools/make/download_and_extract.sh "https://github.com/google/ruy/archive/91d62808498cea7ccb48aa59181e218b4ad05701.zip" "5e653ae8863408ede2a0ca104fea5b1e" tensorflow/lite/micro/tools/make/downloads/ruy

downloading https://github.com/google/ruy/archive/91d62808498cea7ccb48aa59181e218b4ad05701.zip
tensorflow/lite/micro/tools/make/download_and_extract.sh "https://storage.googleapis.com/download.tensorflow.org/data/tf_lite_micro_person_data_int8_grayscale_2020_01_13.zip" "8a7d2c70325f53136faea6dde517b8cc" tensorflow/lite/micro/tools/make/downloads/person_model_int8

downloading https://storage.googleapis.com/download.tensorflow.org/data/tf_lite_micro_person_data_int8_grayscale_2020_01_13.zip
```
Now let build the Mbedos project:

```
cd tensorflow/lite/micro/tools/make/gen/mbed_cortex-m4/prj/hello_world/mbed
```
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
### Compile mbed hello_word project
```
mbed compile -m DISCO_F746NG -t GCC_ARM 

ls ./BUILD/DISCO_F746NG/GCC_ARM/mbed.bin 
```
### Modify source code 

./lite/micro/examples/hello_world/disco_f746ng/

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

