#include "scripting/js-bindings/auto/jsb_cocos2dx_custom_auto.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "CustomDef.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}
JSClass  *jsb_cocos2d_UtilsEx_class;
JSObject *jsb_cocos2d_UtilsEx_prototype;

bool js_cocos2dx_custom_UtilsEx_decrypt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_UtilsEx_decrypt : Error processing arguments");

        char* ret = cocos2d::UtilsEx::decrypt(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_UtilsEx_decrypt : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_UtilsEx_saveServerConfig(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        const char* arg0 = nullptr;
        const char* arg1 = nullptr;
        int arg2 = 0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_UtilsEx_saveServerConfig : Error processing arguments");

        bool ret = cocos2d::UtilsEx::saveServerConfig(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_UtilsEx_saveServerConfig : wrong number of arguments");
    return false;
}


void js_register_cocos2dx_custom_UtilsEx(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_UtilsEx_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_UtilsEx_class->name = "UtilsEx";
    jsb_cocos2d_UtilsEx_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_UtilsEx_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_UtilsEx_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_UtilsEx_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_UtilsEx_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_UtilsEx_class->resolve = JS_ResolveStub;
    jsb_cocos2d_UtilsEx_class->convert = JS_ConvertStub;
    jsb_cocos2d_UtilsEx_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("decrypt", js_cocos2dx_custom_UtilsEx_decrypt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("saveServerConfig", js_cocos2dx_custom_UtilsEx_saveServerConfig, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_UtilsEx_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocos2d_UtilsEx_class,
        dummy_constructor<cocos2d::UtilsEx>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_UtilsEx_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "UtilsEx"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::UtilsEx>(cx, jsb_cocos2d_UtilsEx_class, proto, JS::NullPtr());
}

void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "jsb", &ns);

    js_register_cocos2dx_custom_UtilsEx(cx, ns);
}

