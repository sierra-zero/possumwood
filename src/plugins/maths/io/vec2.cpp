#include "vec2.h"

namespace possumwood {

namespace {

template<typename T>
void toJson(::possumwood::io::json& json, const Imath::Vec2<T>& value) {
	json["x"] = value.x;
	json["y"] = value.y;
}

template<typename T>
void fromJson(const ::possumwood::io::json& json, Imath::Vec2<T>& value) {
	value.x = json["x"].get<T>();
	value.y = json["y"].get<T>();
}

}

IO<Imath::Vec2<float>> Traits<Imath::Vec2<float>>::io(&toJson<float>, &fromJson<float>);
IO<Imath::Vec2<unsigned>> Traits<Imath::Vec2<unsigned>>::io(&toJson<unsigned>, &fromJson<unsigned>);
IO<Imath::Vec2<int>> Traits<Imath::Vec2<int>>::io(&toJson<int>, &fromJson<int>);

}
