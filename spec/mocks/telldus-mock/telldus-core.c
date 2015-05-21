#include <ruby.h>
#include "include/telldus-core.h"

#define STR2SYM(str) ID2SYM(rb_intern(str))
#define GET_SWITCH(id) rb_hash_aref(telldusState, INT2FIX(id));

#define GET_SWITCH_TEST(id, method) GET_SWITCH(id)\
	if(!RTEST(sw)) { \
		return TELLSTICK_ERROR_NOT_FOUND; \
	} \
	if(!supportMethod(sw, TELLSTICK_TURNON)) { \
		return TELLSTICK_ERROR_METHOD_NOT_SUPPORTED;\
	}\



VALUE rb_cTelldusSwitchState = Qnil;
static VALUE telldusState;

static int supportMethod(VALUE sw, int method)
{
	int supportedMethods;
	return FIX2INT(rb_funcall(sw, rb_intern("supported_methods"), 0)) & method;
}

void tdInit(void)
{
}

void  tdClose(void)
{
}

void  tdReleaseString(char *thestring)
{
}

int  tdTurnOn(int intDeviceId)
{
	VALUE sw;
	sw  = GET_SWITCH_TEST(intDeviceId, TELLSTICK_TURNON);
	rb_funcall(sw, rb_intern("on="), 1, Qtrue);
	rb_funcall(sw, rb_intern("last_command="), 1, INT2FIX(TELLSTICK_TURNON));
	return TELLSTICK_SUCCESS;
}


int  tdTurnOff(int intDeviceId)
{
	VALUE sw;
	sw  = GET_SWITCH_TEST(intDeviceId, TELLSTICK_TURNOFF);
	rb_funcall(sw, rb_intern("on="), 1, Qfalse);
	rb_funcall(sw, rb_intern("last_command="), 1, INT2FIX(TELLSTICK_TURNOFF));
	return TELLSTICK_SUCCESS;
}

int  tdLearn(int intDeviceId) {
	VALUE sw;
	sw  = GET_SWITCH_TEST(intDeviceId, TELLSTICK_LEARN);

	rb_funcall(sw, rb_intern("learning="), 1, Qtrue);
	rb_funcall(sw, rb_intern("last_command="), 1, INT2FIX(TELLSTICK_LEARN));
	return TELLSTICK_SUCCESS;
}


int  tdDim(int intDeviceId, unsigned char level) {
	VALUE sw;
	sw  = GET_SWITCH_TEST(intDeviceId, TELLSTICK_DIM);

	rb_funcall(sw, rb_intern("dim="), 1, INT2FIX(level));
	rb_funcall(sw, rb_intern("last_command="), 1, INT2FIX(TELLSTICK_DIM));

	return TELLSTICK_SUCCESS;
}

int  tdLastSentCommand( int intDeviceId, int methodsSupported ) {
	VALUE sw;
	VALUE lastcmd;

	sw = GET_SWITCH(intDeviceId);
	if(!RTEST(sw)) {
		return 0;
	}

	lastcmd = rb_funcall(sw, rb_intern("last_command"), 0);
	if(FIX2INT(lastcmd) & methodsSupported) {
		return FIX2INT(lastcmd);
	}
	return 0;

}
int  tdMethods(int id, int methodsSupported){
	VALUE sw; 
	VALUE methods;

	sw = GET_SWITCH(id);
	methods = rb_funcall(sw, rb_intern("supported_methods"), 0);
	return methods & FIX2INT(methods);
}

int  tdGetNumberOfDevices() {
	VALUE nitems;

	nitems = rb_funcall(telldusState, rb_intern("size"),0);
	return FIX2INT(nitems);
}


int  tdGetDeviceId(int intDeviceIndex) {
	VALUE arr;
	VALUE dev;
	VALUE id;

	arr = rb_funcall(telldusState, rb_intern("to_a"), 0);
	dev = rb_ary_entry(arr, intDeviceIndex); 
	if (!RTEST(dev)) {
		return TELLSTICK_ERROR_NOT_FOUND;
	}

	id = rb_funcall(dev, rb_intern("first"), 0);

	return FIX2INT(id);
}

char *tdGetName(int intDeviceId) {
	VALUE sw;
	VALUE name;

	sw = GET_SWITCH(intDeviceId);
	if(!RTEST(sw)) {
		return 0;
	}

	name = rb_funcall(sw, rb_intern("name"), 0);
	return StringValueCStr(name);
}

bool  tdSetName(int intDeviceId, const char* chNewName) {
	VALUE sw;
	VALUE name;

	sw = GET_SWITCH(intDeviceId);
	if(!RTEST(sw))
		return 0;

	name = rb_str_new_cstr(chNewName);
	rb_funcall(sw, rb_intern("name="), 1, name);
	return 1;
}

char * tdLastSentValue( int intDeviceId )
{
	VALUE sw;
	VALUE dim;
	VALUE str;

	sw = GET_SWITCH(intDeviceId);
	dim = rb_funcall(sw, rb_intern("dim"), 0);
	str = rb_funcall(dim, rb_intern("to_s"),0);

	return StringValueCStr(str);
}

char * tdGetProtocol(int intDeviceId) {
	VALUE sw;
	VALUE protocol;

	sw = GET_SWITCH(intDeviceId);
	protocol = rb_funcall(sw, rb_intern("protocol"), 0);
	return StringValueCStr(protocol);
}
bool  tdSetProtocol(int intDeviceId, const char* strProtocol) {
	VALUE sw;
	VALUE protocol;

	sw = GET_SWITCH(intDeviceId);
	protocol = rb_str_new_cstr(strProtocol);
	rb_funcall(sw, rb_intern("protocol="), 1, protocol);
	return 1;
}

int tdGetDeviceType(int intDeviceId) {
	VALUE sw;
	VALUE type;

	sw = GET_SWITCH(intDeviceId);

	if (!RTEST(sw)) {
		return TELLSTICK_ERROR_NOT_FOUND;
	}

	type = rb_funcall(sw, rb_intern("device_type"), 0);
	return FIX2INT(type);
}

int  tdAddDevice()
{
	VALUE sw;
	VALUE id;

	sw = rb_class_new_instance(0, 0, rb_cTelldusSwitchState);
	id = rb_funcall(sw, rb_intern("id"), 0); 
	return FIX2INT(id);
}

bool  tdRemoveDevice(int intDeviceId)
{
	VALUE sw;

	sw = GET_SWITCH(intDeviceId);


	if (!RTEST(sw))
		return 0;

	rb_funcall(telldusState, rb_intern("delete"), 1, INT2FIX(intDeviceId));
	return 1;
}

char *  tdGetModel(int intDeviceId) {
	VALUE sw;
	VALUE model;

	sw = GET_SWITCH(intDeviceId);
	if (!RTEST(sw))
		return 0;
	model = rb_funcall(sw, rb_intern("model"),0);
	return StringValueCStr(model);
}

bool  tdSetModel(int intDeviceId, const char *intModel) {
	VALUE sw;
	sw = GET_SWITCH(intDeviceId);
	if (!RTEST(sw))
		return 0;
	rb_funcall(sw, rb_intern("model="), 1, rb_str_new_cstr(intModel));
	return 1;
}
char *  tdGetDeviceParameter(int intDeviceId, const char *strName, const char *defaultValue) {
	VALUE sw;
	VALUE params;
	VALUE param;

	sw = GET_SWITCH(intDeviceId);
	if (!RTEST(sw))
		return 0;

	params = rb_funcall(sw, rb_intern("params"),0);
	param = rb_hash_aref(params, rb_str_new_cstr(strName));

	if (!RTEST(param))
		return (char*)defaultValue;
	return StringValueCStr(param);
}
bool  tdSetDeviceParameter(int intDeviceId, const char *strName, const char* strValue)
{
	VALUE sw;
	VALUE params;

	sw = GET_SWITCH(intDeviceId);

	if (!RTEST(sw))
		return 0;

	params = rb_funcall(sw, rb_intern("params"),0);
	rb_hash_aset(params, rb_str_new_cstr(strName), rb_str_new_cstr(strValue));
	return 1;
}

static VALUE telldus_switch_state_initialize(int argc, VALUE* argv, VALUE self)
{
	VALUE args;
	VALUE next_id;
	VALUE default_args;

	int supported_methods = (TELLSTICK_TURNON
					| TELLSTICK_TURNOFF
					| TELLSTICK_DIM
					| TELLSTICK_LEARN) ;
	default_args = rb_hash_new();
	next_id = rb_eval_string("(TelldusState.keys.sort.last || 0) + 1");

	rb_hash_aset(default_args, STR2SYM("id"), next_id);
	rb_hash_aset(default_args, STR2SYM("on"), Qfalse);
	rb_hash_aset(default_args, STR2SYM("dim"), INT2FIX(0));
	rb_hash_aset(default_args, STR2SYM("last_command"), INT2FIX(0));
	rb_hash_aset(default_args, STR2SYM("learning"), Qfalse);
	rb_hash_aset(default_args, STR2SYM("name"), rb_str_new_cstr(""));
	rb_hash_aset(default_args, STR2SYM("model"), rb_str_new_cstr("model name"));
	rb_hash_aset(default_args, STR2SYM("protocol"), rb_str_new_cstr("ikea"));
	rb_hash_aset(default_args, STR2SYM("device_type"), INT2FIX(TELLSTICK_TYPE_DEVICE));
	rb_hash_aset(default_args, STR2SYM("supported_methods"), INT2FIX(supported_methods));
	rb_hash_aset(default_args, STR2SYM("params"), rb_hash_new());

	rb_scan_args(argc, argv, ":", &args);
	if (!RTEST(args)) {
		args = rb_hash_new();
	}
	args = rb_funcall(default_args, rb_intern("merge"), 1, args);

	rb_iv_set(self, "@id", rb_hash_aref(args, STR2SYM("id")));
	rb_iv_set(self, "@on", rb_hash_aref(args, STR2SYM("on")));
	rb_iv_set(self, "@dim", rb_hash_aref(args, STR2SYM("dim")));
	rb_iv_set(self, "@last_command", rb_hash_aref(args, STR2SYM("last_command")));
	rb_iv_set(self, "@learning", rb_hash_aref(args, STR2SYM("learning")));
	rb_iv_set(self, "@name", rb_hash_aref(args, STR2SYM("name")));
	rb_iv_set(self, "@model", rb_hash_aref(args, STR2SYM("model")));
	rb_iv_set(self, "@supported_methods", rb_hash_aref(args, STR2SYM("supported_methods")));
	rb_iv_set(self, "@protocol", rb_hash_aref(args, STR2SYM("protocol")));
	rb_iv_set(self, "@device_type", rb_hash_aref(args, STR2SYM("device_type")));
	rb_iv_set(self, "@params", rb_hash_aref(args, STR2SYM("params")));
	rb_hash_aset(telldusState, rb_iv_get(self, "@id"), self);
	return self;
}

void Init_telldus_state(void)
{
	rb_cTelldusSwitchState = rb_define_class("TelldusSwitchState", rb_cObject);
	rb_define_method(rb_cTelldusSwitchState, "initialize", telldus_switch_state_initialize, -1);
	rb_define_attr(rb_cTelldusSwitchState, "id", 1,0);
	rb_define_attr(rb_cTelldusSwitchState, "on", 1,1);
	rb_define_attr(rb_cTelldusSwitchState, "dim", 1,1);
	rb_define_attr(rb_cTelldusSwitchState, "last_command", 1,1);
	rb_define_attr(rb_cTelldusSwitchState, "learning", 1,1);
	rb_define_attr(rb_cTelldusSwitchState, "name", 1,1);
	rb_define_attr(rb_cTelldusSwitchState, "model", 1,1);
	rb_define_attr(rb_cTelldusSwitchState, "supported_methods", 1,1);
	rb_define_attr(rb_cTelldusSwitchState, "protocol", 1,1);
	rb_define_attr(rb_cTelldusSwitchState, "device_type", 1,1);
	rb_define_attr(rb_cTelldusSwitchState, "params", 1,1);

	telldusState = rb_hash_new();
	rb_define_global_const("TelldusState", telldusState);
}
