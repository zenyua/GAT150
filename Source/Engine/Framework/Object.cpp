#include "Object.h"
#include "rapidjson-master/include/rapidjson/writer.h"
#include "rapidjson-master/include/rapidjson/stringbuffer.h"

namespace ringo {
	void Object::Read(const rapidjson::Value& value) {
		READ_DATA(value, name);
	}
}