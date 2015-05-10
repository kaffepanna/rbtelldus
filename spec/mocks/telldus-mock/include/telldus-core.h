#ifndef __TELLDUS_CORE_H__
#define __TELLDUS_CORE_H__

#define bool int
void tdInit(void);
void  tdClose(void);
void  tdReleaseString(char *thestring);

int  tdTurnOn(int intDeviceId);
int  tdTurnOff(int intDeviceId);
int  tdLearn(int intDeviceId);
int  tdDim(int intDeviceId, unsigned char level);
int  tdLastSentCommand( int intDeviceId, int methodsSupported );
int  tdMethods(int id, int methodsSupported);
int  tdGetNumberOfDevices();
int  tdGetDeviceId(int intDeviceIndex);

char * tdGetName(int intDeviceId);
bool  tdSetName(int intDeviceId, const char* chNewName);
char * tdLastSentValue( int intDeviceId );
char * tdGetProtocol(int intDeviceId);
bool  tdSetProtocol(int intDeviceId, const char* strProtocol);

/*
int  tdBell(int intDeviceId);
int  tdExecute(int intDeviceId);
int  tdUp(int intDeviceId);
int  tdDown(int intDeviceId);
int  tdStop(int intDeviceId);

int  tdGetDeviceType(int intDeviceId);

char * tdGetErrorString(int intErrorNo);

char *  tdGetModel(int intDeviceId);
bool  tdSetModel(int intDeviceId, const char *intModel);

char *  tdGetDeviceParameter(int intDeviceId, const char *strName, const char *defaultValue);
bool  tdSetDeviceParameter(int intDeviceId, const char *strName, const char* strValue);

int  tdAddDevice();
bool  tdRemoveDevice(int intDeviceId);

int  tdSendRawCommand(const char *command, int reserved);

void  tdConnectTellStickController(int vid, int pid, const char *serial);
void  tdDisconnectTellStickController(int vid, int pid, const char *serial);

int  tdSensor(char *protocol, int protocolLen, char *model, int modelLen, int *id, int *dataTypes);
int  tdSensorValue(const char *protocol, const char *model, int id, int dataType, char *value, int len, int *timestamp);

int  tdController(int *controllerId, int *controllerType, char *name, int nameLen, int *available);
int  tdControllerValue(int controllerId, const char *name, char *value, int valueLen);
int  tdSetControllerValue(int controllerId, const char *name, const char *value);
int  tdRemoveController(int controllerId);
*/
// Device methods
#define TELLSTICK_TURNON	1
#define TELLSTICK_TURNOFF	2
#define TELLSTICK_BELL		4
#define TELLSTICK_TOGGLE	8
#define TELLSTICK_DIM		16
#define TELLSTICK_LEARN		32
#define TELLSTICK_EXECUTE	64
#define TELLSTICK_UP		128
#define TELLSTICK_DOWN		256
#define TELLSTICK_STOP		512

// Sensor value types
#define TELLSTICK_TEMPERATURE	1
#define TELLSTICK_HUMIDITY		2
#define TELLSTICK_RAINRATE		4
#define TELLSTICK_RAINTOTAL		8
#define TELLSTICK_WINDDIRECTION	16
#define TELLSTICK_WINDAVERAGE	32
#define TELLSTICK_WINDGUST		64

// Error codes
#define TELLSTICK_SUCCESS 0
#define TELLSTICK_ERROR_NOT_FOUND -1
#define TELLSTICK_ERROR_PERMISSION_DENIED -2
#define TELLSTICK_ERROR_DEVICE_NOT_FOUND -3
#define TELLSTICK_ERROR_METHOD_NOT_SUPPORTED -4
#define TELLSTICK_ERROR_COMMUNICATION -5
#define TELLSTICK_ERROR_CONNECTING_SERVICE -6
#define TELLSTICK_ERROR_UNKNOWN_RESPONSE -7
#define TELLSTICK_ERROR_SYNTAX -8
#define TELLSTICK_ERROR_BROKEN_PIPE -9
#define TELLSTICK_ERROR_COMMUNICATING_SERVICE -10
#define TELLSTICK_ERROR_CONFIG_SYNTAX -11
#define TELLSTICK_ERROR_UNKNOWN -99

// Device typedef
#define TELLSTICK_TYPE_DEVICE	1
#define TELLSTICK_TYPE_GROUP	2
#define TELLSTICK_TYPE_SCENE	3

// Controller typedef
#define TELLSTICK_CONTROLLER_TELLSTICK      1
#define TELLSTICK_CONTROLLER_TELLSTICK_DUO  2
#define TELLSTICK_CONTROLLER_TELLSTICK_NET  3

// Device changes
#define TELLSTICK_DEVICE_ADDED			1
#define TELLSTICK_DEVICE_CHANGED		2
#define TELLSTICK_DEVICE_REMOVED		3
#define TELLSTICK_DEVICE_STATE_CHANGED	4

// Change types
#define TELLSTICK_CHANGE_NAME			1
#define TELLSTICK_CHANGE_PROTOCOL		2
#define TELLSTICK_CHANGE_MODEL			3
#define TELLSTICK_CHANGE_METHOD			4
#define TELLSTICK_CHANGE_AVAILABLE		5
#define TELLSTICK_CHANGE_FIRMWARE		6

#endif
