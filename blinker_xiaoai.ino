#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT
#include <Blinker.h>

char auth[] = "745f664e6d40";
char ssid[] = "1024";
char pswd[] = "12345678";

// 新建组件对象
BlinkerButton Button1("btn-abc");
BlinkerNumber Number1("num-abc");

int counter = 0;

//小爱同学控制电源开关的函数
void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(0, LOW);

        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    }
    else if (state == BLINKER_CMD_OFF) {
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(0, HIGH);

        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
}
void miotQuery(int32_t queryCode)
{
    BLINKER_LOG("MIOT Query codes: ", queryCode);

    switch (queryCode)
    {
        case BLINKER_CMD_QUERY_PM25_NUMBER :
            BLINKER_LOG("MIOT Query PM25");
            BlinkerMIOT.pm25(20);
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_HUMI_NUMBER :
            BLINKER_LOG("MIOT Query HUMI");
            BlinkerMIOT.humi(20);
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_TEMP_NUMBER :
            BLINKER_LOG("MIOT Query TEMP");
            BlinkerMIOT.temp(20);
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_TIME_NUMBER :
            BLINKER_LOG("MIOT Query Time");
//            BlinkerMIOT.time(millis());
            BlinkerMIOT.print();
            break;
        default :
            BlinkerMIOT.temp(20);
            BlinkerMIOT.humi(20);
            BlinkerMIOT.pm25(20);
            BlinkerMIOT.co2(20);
            BlinkerMIOT.print();
            break;
    }
}

// 按下按键即会执行该函数
void button1_callback(const String & state)
{
    BLINKER_LOG("get button state: ", state);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    //控制继电器
    digitalWrite(0, !digitalRead(0));
}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}

void setup()
{
    // 初始化串口
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    
    // 初始化有LED的IO
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    //控制继电器
    pinMode(0, OUTPUT);
    digitalWrite(0, HIGH);    
    
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);

    Button1.attach(button1_callback);
    //小爱同学电源回调函数
    BlinkerMIOT.attachPowerState(miotPowerState);
    BlinkerMIOT.attachQuery(miotQuery);
}

void loop() {
    Blinker.run();
}
