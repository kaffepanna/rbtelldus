#include <ruby.h>
#include <telldus-core.h>
static VALUE rb_mTelldus;
static VALUE rb_cDevice;

Init_telldus(void)
{
	rb_mTelldus = rb_define_module("Telldus");
}
