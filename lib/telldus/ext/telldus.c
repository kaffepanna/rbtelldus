#include <ruby.h>
#include <telldus-core.h>
static VALUE rb_mTelldus;
static VALUE rb_cDevice;


static VALUE telldus_on(VALUE self, VALUE id)
{
	int ret;
	ret = tdTurnOn(FIX2INT(id));
	return INT2FIX(ret);
}

static VALUE telldus_off(VALUE self, VALUE id)
{
	int ret;
	ret = tdTurnOff(FIX2INT(id));
	return INT2FIX(ret);
}

static VALUE telldus_dim(VALUE self, VALUE id, VALUE level)
{
	int ret;
	ret = tdDim(FIX2INT(id), FIX2INT(level));
	return INT2FIX(ret);
}

static VALUE telldus_learn(VALUE self, VALUE id)
{
	int ret;
	ret = tdLearn(FIX2INT(id));
	return INT2FIX(ret);
}

static VALUE telldus_get_name(VALUE self, VALUE id)
{
	VALUE rname;
	char *name;
	name = tdGetName(FIX2INT(id));
	rname = rb_str_new_cstr(name);
	tdReleaseString(name);
	return rname;
}

static VALUE telldus_set_name(VALUE self, VALUE id, VALUE name)
{
	int ret;
	char *cname = StringValueCStr(name);
	ret = tdSetName(FIX2INT(id), cname);
	if(!ret)
		return Qfalse;
	return Qtrue;
}

static VALUE telldus_last_command(VALUE self, VALUE id, VALUE mask)
{
	int ret;
	ret = tdLastSentCommand(FIX2INT(id), FIX2INT(mask));
	return INT2FIX(ret);
}

static VALUE telldus_last_value(VALUE self, VALUE id)
{
	char *ret;
	unsigned char value;
	ret = tdLastSentValue(FIX2INT(id));
	value = atoi(ret);
	return INT2FIX(value);
}

static VALUE telldus_create(VALUE self)
{
	int ret = tdAddDevice();
	return INT2FIX(ret);
}

static VALUE telldus_remove(VALUE self, VALUE id)
{
	int ret = tdRemoveDevice(FIX2INT(id));
	if(ret)
		return Qtrue;
	return Qfalse;
}

static VALUE telldus_get_param(VALUE self, VALUE id, VALUE name, VALUE defaultValue)
{
	char *value = tdGetDeviceParameter(FIX2INT(id), StringValueCStr(name), StringValueCStr(defaultValue));
	VALUE val = rb_str_new_cstr(value);
	tdReleaseString(value);
	return val;
}

static VALUE telldus_set_param(VALUE self, VALUE id, VALUE name, VALUE value)
{
	int ret = tdSetDeviceParameter(FIX2INT(id),
			StringValueCStr(name),
			StringValueCStr(value));
	if (ret)
		return Qtrue;
	return Qfalse;
}

static VALUE telldus_get_model(VALUE self, VALUE id)
{
	char *value = tdGetModel(FIX2INT(id));
	VALUE val = rb_str_new_cstr(value);
	tdReleaseString(value);
	return val;
}

static VALUE telldus_set_model(VALUE self, VALUE id, VALUE name)
{
	int ret = tdSetModel(FIX2INT(id),
			StringValueCStr(name));
	if (ret)
		return Qtrue;
	return Qfalse;
}

Init_telldus(void)
{
	rb_mTelldus = rb_define_module("Telldus");
	rb_define_singleton_method(rb_mTelldus, "on", telldus_on, 1);
	rb_define_singleton_method(rb_mTelldus, "off", telldus_off, 1);
	rb_define_singleton_method(rb_mTelldus, "dim", telldus_dim, 2);
	rb_define_singleton_method(rb_mTelldus, "learn", telldus_learn, 1);
	rb_define_singleton_method(rb_mTelldus, "getName", telldus_get_name, 1);
	rb_define_singleton_method(rb_mTelldus, "setName", telldus_set_name, 2);
	rb_define_singleton_method(rb_mTelldus, "lastCommand", telldus_last_command, 2);
	rb_define_singleton_method(rb_mTelldus, "lastValue", telldus_last_value, 1);

	rb_define_singleton_method(rb_mTelldus, "getParam", telldus_get_param, 3);
	rb_define_singleton_method(rb_mTelldus, "setParam", telldus_set_param, 3);

	rb_define_singleton_method(rb_mTelldus, "create", telldus_create, 0);
	rb_define_singleton_method(rb_mTelldus, "remove", telldus_remove, 1);

	rb_define_singleton_method(rb_mTelldus, "getModel", telldus_get_model, 1);
	rb_define_singleton_method(rb_mTelldus, "setModel", telldus_set_model, 2);

	rb_define_const(rb_mTelldus, "SUCCESS", INT2FIX(TELLSTICK_SUCCESS));
	rb_define_const(rb_mTelldus, "NOT_FOUND", INT2FIX(TELLSTICK_ERROR_NOT_FOUND));
	rb_define_const(rb_mTelldus, "PERMISSION_DENIED", INT2FIX(TELLSTICK_ERROR_PERMISSION_DENIED));
	rb_define_const(rb_mTelldus, "METHOD_NOT_SUPPORTED", INT2FIX(TELLSTICK_ERROR_METHOD_NOT_SUPPORTED));

	rb_define_const(rb_mTelldus, "TURNON", INT2FIX(TELLSTICK_TURNON));
	rb_define_const(rb_mTelldus, "TURNOFF", INT2FIX(TELLSTICK_TURNOFF));
	rb_define_const(rb_mTelldus, "DIM", INT2FIX(TELLSTICK_DIM));
}
