#include "base/ccConfig.h"
#ifndef __cocos2dx_custom_h__
#define __cocos2dx_custom_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_cocos2d_UtilsEx_class;
extern JSObject *jsb_cocos2d_UtilsEx_prototype;

bool js_cocos2dx_custom_UtilsEx_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_UtilsEx_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_UtilsEx(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_UtilsEx_decrypt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_UtilsEx_saveServerConfig(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_custom_h__
