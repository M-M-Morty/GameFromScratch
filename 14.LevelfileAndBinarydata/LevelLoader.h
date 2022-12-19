#pragma once
#include <string>
#include <rapidjson/document.h>

#include "Math.h"

class LevelLoader
{
public:
	//加载关卡
	static bool LoadLevel(class Game* game, const std::string& fileName);
	//加载json文件，并生成RapidJSON文档对象
	static bool LoadJSON(const std::string fileName, rapidjson::Document& outDoc);
protected:
	//加载全局属性的辅助函数
	static void LoadGlobalProperties(class Game* game, const rapidjson::Value& inObject);
};


class JsonHelper
{
public:
	// Helpers - Return true if successful, and also sets out parameter to parsed value
	// For each function, the first parameter is the containing JSON object, the second is the
	// name of the property in the containing object, and the third is the value you acquire.
	// Furthermore, if the property is not found, each function is guaranteed not to modify the
	// return value.
	static bool GetInt(const rapidjson::Value& inObject, const char* inProperty, int& outInt);
	static bool GetFloat(const rapidjson::Value& inObject, const char* inProperty, float& outFloat);
	static bool GetString(const rapidjson::Value& inObject, const char* inProperty, std::string& outStr);
	static bool GetBool(const rapidjson::Value& inObject, const char* inProperty, bool& outBool);
	static bool GetVector3(const rapidjson::Value& inObject, const char* inProperty, Vector3& outVector);
	static bool GetQuaternion(const rapidjson::Value& inObject, const char* inProperty, Quaternion& outQuat);

	// Setter functions
	static void AddInt(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, int value);
	static void AddFloat(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, float value);
	static void AddString(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, const std::string& value);
	static void AddBool(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, bool value);
	static void AddVector3(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, const Vector3& value);
	static void AddQuaternion(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, const Quaternion& value);
};