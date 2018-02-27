#include "jsb_cocos2dx_custom_manual.h"
#include "js_manual_conversions.h"
#include "js_bindings_config.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"
#include "js_bindings_opengl.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "editor-support/cocostudio/ActionTimeline/CCActionTimeline.h"

bool jsb_cocos2dx_custom_loadCsb(JSContext * cx, uint32_t argc, jsval * vp) {
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	bool ok = true;
	std::string arg0;

	ok &= jsval_to_std_string(cx, args.get(0), &arg0);
	JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
	cocos2d::CSLoader* loader = cocos2d::CSLoader::getInstance();

	cocos2d::Node* ret;
	ret = loader->createNode(arg0);
	js_type_class_t * typeClass = js_get_type_from_native<cocos2d::Node>(ret);
	JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::Node"));
	
	args.rval().set(OBJECT_TO_JSVAL(jsret));
	return true;
}


bool jsb_cocos2dx_custom_createTimeline(JSContext * cx, uint32_t argc, jsval * vp) {
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	bool ok = true;
	std::string arg0;

	ok &= jsval_to_std_string(cx, args.get(0), &arg0);
	JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
	cocos2d::CSLoader* loader = cocos2d::CSLoader::getInstance();

	cocostudio::timeline::ActionTimeline* ret;
	ret = loader->createTimeline(arg0);
	js_type_class_t * typeClass = js_get_type_from_native<cocostudio::timeline::ActionTimeline>(ret);
	JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::ActionTimeline"));

	args.rval().set(OBJECT_TO_JSVAL(jsret));
	return true;
}

extern JSObject *jsb_cocos2d_UtilsEx_prototype;

void register_all_cocos2dx_custom_manual(JSContext * cx, JS::HandleObject global)
{
	JS::RootedObject UtilsEx(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));

	JS::RootedValue exVal(cx);
	exVal = OBJECT_TO_JSVAL(UtilsEx);
	JS_SetProperty(cx, global, "UtilsEx", exVal);

	JS::RootedObject ccns(cx);
	get_or_create_js_obj(cx, global, "cc", &ccns);

	js_register_cocos2dx_GLNode(cx, ccns);
	JS_DefineFunction(cx, UtilsEx, "loadCsb", jsb_cocos2dx_custom_loadCsb, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE);
	JS_DefineFunction(cx, UtilsEx, "createTimeline", jsb_cocos2dx_custom_createTimeline, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE);
}
