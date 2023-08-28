#include "Json.h"
#include "rapidjson-master/include/rapidjson/istreamwrapper.h"
#include "Core/FileIO.h"
#include "Logger.h"
#include <sstream>

namespace ringo {
	bool Json::Load(const std::string& filename, rapidjson::Document& document)
	{
		std::string buffer;
		if (!readFile(filename, buffer)) {
			WARNING_LOG("Cannot open file: " << filename);
			return false;
		}

		std::stringstream stream(buffer);
		rapidjson::IStreamWrapper istream(stream);

		//parse stream to json
		document.ParseStream(istream);
		if (document.HasParseError()) {
			WARNING_LOG("Json file cannot be parsed: " << filename);
			return false;
		}

		INFO_LOG("Successfully read json: " << filename);

		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string& name, int& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt()) {
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}

		data = value[name.c_str()].GetInt();

		INFO_LOG("Json read: " << "int");

		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, float& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsFloat()) {
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}

		data = value[name.c_str()].GetFloat();

		INFO_LOG("Json read: " << "float");

		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool()) {
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}

		data = value[name.c_str()].GetBool();

		INFO_LOG("Json read: " << "bool");

		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString()) {
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}

		data = value[name.c_str()].GetString();

		INFO_LOG("Json read: " << "string");

		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, vec2& data, bool required)
	{
		if (!value.HasMember(name.c_str())) {
			ERROR_LOG("Missing member in json: " << name.c_str());
			return false;
		}

		// check if 'name' member exists and is an array with 2 elements
		if (!value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data[i] = array[i].GetFloat();
		}
		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, Color& data, bool required)
	{
		if (!value.HasMember(name.c_str())) {
			ERROR_LOG("Missing member in json: " << name.c_str());
			return false;
		}

		// check if 'name' member exists and is an array with 2 elements
		if (!value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data[i] = array[i].GetFloat();
		}
		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, Rect& data, bool required)
	{
		if (!value.HasMember(name.c_str())) {
			ERROR_LOG("Missing member in json: " << name.c_str());
			return false;
		}

		// check if 'name' member exists and is an array with 2 elements
		if (!value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data[i] = array[i].GetInt();
		}
		return true;
	}

}