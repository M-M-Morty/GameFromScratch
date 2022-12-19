#include <fstream>
#include <SDL/SDL.h>
#include <vector>

#include "LevelLoader.h"
#include "Game.h"
#include "Renderer.h"

const int LevelVersion = 1;


bool LevelLoader::LoadLevel(Game* game, const std::string& fileName)
{
    rapidjson::Document doc;
    if (!LoadJSON(fileName, doc))
    {
        SDL_Log("Failed to load level %s", fileName.c_str());
        return false;
    }

	int version = 0;
	if (!JsonHelper::GetInt(doc, "version", version) ||
		version != LevelVersion)
	{
		SDL_Log("Incorrect level file version for %s", fileName.c_str());
		return false;
	}
	//处理全局属性
	const rapidjson::Value& globals = doc["globalProperties"];
	if (globals.IsObject())
	{
		LoadGlobalProperties(game, globals);
	}

    return false;
}

bool LevelLoader::LoadJSON(const std::string fileName, rapidjson::Document& outDoc)
{
    //以二进制模式从文件末尾开始加载文件
    std::ifstream file(fileName, std::ios::in | std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        SDL_Log("File %s not found", fileName.c_str());
        return false;
    }

    //获取文件流的当前位置（即文件大小）
    std::ifstream::pos_type fileSize = file.tellg();
    //将文件流的当前位置设置到开头
    file.seekg(0, std::ios::beg);

    //创建大小为size+1的字符数组（末尾为null）
    std::vector<char> bytes(static_cast<size_t>(fileSize) + 1);
    //开始读取（复制）数据
    file.read(bytes.data(), static_cast<size_t>(fileSize));

    outDoc.Parse(bytes.data());
    if (!outDoc.IsObject())
    {
        SDL_Log("File %s is not valid JSON", fileName.c_str());
        return false;
    }

    return false;
}

void LevelLoader::LoadGlobalProperties(Game* game, const rapidjson::Value& inObject)
{
	//获取环境光照属性
	Vector3 ambient;
	if (JsonHelper::GetVector3(inObject, "ambientlight", ambient))
	{
		game->GetRenderer()->SetAmbientLight(ambient);
	}

	//获取平行光的属性
	const rapidjson::Value& dirObj = inObject["directionalLight"];
	if (dirObj.IsObject())
	{
		DirectionalLight& light = game->GetRenderer()->GetDirectionalLight();

		// Set direction/color, if they exist
		JsonHelper::GetVector3(dirObj, "direction", light.mDirection);
		JsonHelper::GetVector3(dirObj, "color", light.mDiffuseColor);
	}

}














bool JsonHelper::GetInt(const rapidjson::Value& inObject, const char* inProperty, int& outInt)
{
	// Check if this property exists
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	// Get the value type, and check it's an integer
	auto& property = itr->value;
	if (!property.IsInt())
	{
		return false;
	}

	// We have the property
	outInt = property.GetInt();
	return true;
}

bool JsonHelper::GetFloat(const rapidjson::Value& inObject, const char* inProperty, float& outFloat)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;
	if (!property.IsDouble())
	{
		return false;
	}

	outFloat = property.GetDouble();
	return true;
}

bool JsonHelper::GetString(const rapidjson::Value& inObject, const char* inProperty, std::string& outStr)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;
	if (!property.IsString())
	{
		return false;
	}

	outStr = property.GetString();
	return true;
}

bool JsonHelper::GetBool(const rapidjson::Value& inObject, const char* inProperty, bool& outBool)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;
	if (!property.IsBool())
	{
		return false;
	}

	outBool = property.GetBool();
	return true;
}

bool JsonHelper::GetVector3(const rapidjson::Value& inObject, const char* inProperty, Vector3& outVector)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;
	if (!property.IsArray() || property.Size() != 3)
	{
		return false;
	}

	for (rapidjson::SizeType i = 0; i < 3; i++)
	{
		if (!property[i].IsDouble())
		{
			return false;
		}
	}

	outVector.x = property[0].GetDouble();
	outVector.y = property[1].GetDouble();
	outVector.z = property[2].GetDouble();

	return true;
}

bool JsonHelper::GetQuaternion(const rapidjson::Value& inObject, const char* inProperty, Quaternion& outQuat)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;

	for (rapidjson::SizeType i = 0; i < 4; i++)
	{
		if (!property[i].IsDouble())
		{
			return false;
		}
	}

	outQuat.x = property[0].GetDouble();
	outQuat.y = property[1].GetDouble();
	outQuat.z = property[2].GetDouble();
	outQuat.w = property[3].GetDouble();

	return true;
}

void JsonHelper::AddInt(rapidjson::Document::AllocatorType& alloc,
	rapidjson::Value& inObject, const char* name, int value)
{
	rapidjson::Value v(value);
	inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::AddFloat(rapidjson::Document::AllocatorType& alloc,
	rapidjson::Value& inObject, const char* name, float value)
{
	rapidjson::Value v(value);
	inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::AddString(rapidjson::Document::AllocatorType& alloc,
	rapidjson::Value& inObject, const char* name, const std::string& value)
{
	rapidjson::Value v;
	v.SetString(value.c_str(), static_cast<rapidjson::SizeType>(value.length()),
		alloc);
	inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::AddBool(rapidjson::Document::AllocatorType& alloc,
	rapidjson::Value& inObject, const char* name, bool value)
{
	rapidjson::Value v(value);
	inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::AddVector3(rapidjson::Document::AllocatorType& alloc,
	rapidjson::Value& inObject, const char* name, const Vector3& value)
{
	// Create an array
	rapidjson::Value v(rapidjson::kArrayType);
	// Push back elements
	v.PushBack(rapidjson::Value(value.x).Move(), alloc);
	v.PushBack(rapidjson::Value(value.y).Move(), alloc);
	v.PushBack(rapidjson::Value(value.z).Move(), alloc);

	// Add array to inObject
	inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::AddQuaternion(rapidjson::Document::AllocatorType& alloc,
	rapidjson::Value& inObject, const char* name, const Quaternion& value)
{
	// Create an array
	rapidjson::Value v(rapidjson::kArrayType);
	// Push back elements
	v.PushBack(rapidjson::Value(value.x).Move(), alloc);
	v.PushBack(rapidjson::Value(value.y).Move(), alloc);
	v.PushBack(rapidjson::Value(value.z).Move(), alloc);
	v.PushBack(rapidjson::Value(value.w).Move(), alloc);

	// Add array to inObject
	inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}
