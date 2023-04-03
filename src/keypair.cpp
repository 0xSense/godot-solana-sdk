#include "keypair.hpp"

#include <godot_cpp/core/class_db.hpp>

namespace godot{

void Keypair::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_public_value"), &Keypair::get_public_value);
    ClassDB::bind_method(D_METHOD("set_public_value", "p_value"), &Keypair::set_public_value);
    ClassDB::bind_method(D_METHOD("get_public_bytes"), &Keypair::get_public_bytes);
    ClassDB::bind_method(D_METHOD("set_public_bytes", "p_value"), &Keypair::set_public_bytes);
    ClassDB::bind_method(D_METHOD("get_private_value"), &Keypair::get_private_value);
    ClassDB::bind_method(D_METHOD("set_private_value", "p_value"), &Keypair::set_private_value);
    ClassDB::bind_method(D_METHOD("get_private_bytes"), &Keypair::get_private_bytes);
    ClassDB::bind_method(D_METHOD("set_private_bytes", "p_value"), &Keypair::set_private_bytes);
    ClassDB::bind_method(D_METHOD("get_unique"), &Keypair::get_unique);
    ClassDB::bind_method(D_METHOD("set_unique", "p_value"), &Keypair::set_unique);
}

void Keypair::_free_pointer(){
    free_keypair(data_pointer);
}
void Keypair::_update_pointer(){

}

void Keypair::_get_property_list(List<PropertyInfo> *p_list) const {
    PropertyUsageFlags visibility = PROPERTY_USAGE_DEFAULT;
    if(unique){
        visibility = PROPERTY_USAGE_NO_EDITOR;
    }
    p_list->push_back(PropertyInfo(Variant::BOOL, "unique"));
	p_list->push_back(PropertyInfo(Variant::STRING, "public_value", PROPERTY_HINT_NONE, "", visibility, ""));
    p_list->push_back(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "public_bytes", PROPERTY_HINT_NONE, "", visibility, ""));
    p_list->push_back(PropertyInfo(Variant::STRING, "private_value", PROPERTY_HINT_NONE, "", visibility, ""));
    p_list->push_back(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "private_bytes", PROPERTY_HINT_NONE, "", visibility, ""));
}

bool Keypair::_set(const StringName &p_name, const Variant &p_value) {
	String name = p_name;
	if (name == "public_value") {
		set_public_value(p_value);
		return true;
	}
    else if(name == "public_bytes"){
        set_public_bytes(p_value);
		return true;
    }
    else if (name == "private_value") {
		set_private_value(p_value);
		return true;
	}
    else if(name == "private_bytes"){
        set_private_bytes(p_value);
		return true;
    }
    else if(name == "unique"){
        set_unique(p_value);
        return true;
    }
	return false;
}

bool Keypair::_get(const StringName &p_name, Variant &r_ret) const {
	String name = p_name;
	if (name == "public_value") {
		r_ret = public_value;
		return true;
	}
    else if(name == "public_bytes"){
        r_ret = public_bytes;
		return true;
    }
    else if (name == "private_value") {
		r_ret = private_value;
		return true;
	}
    else if(name == "private_bytes"){
        r_ret = private_bytes;
		return true;
    }
    else if (name == "unique") {
		r_ret = unique;
		return true;
	}
	return false;
}

Keypair::Keypair() {
}

void Keypair::set_public_value(const String& p_value){
    public_value = p_value;
    PackedByteArray decoded_value = bs58_decode(public_value);
    public_bytes = decoded_value;
    if(decoded_value.is_empty() && public_value.length() != 0){
        internal::gde_interface->print_warning("Value contains non-base58 characters", "_set", "keypair.cpp", 97, false);
    }
    else if (decoded_value.size() != 32){
        internal::gde_interface->print_warning("Public key must be 32 bytes", "_set", "keypair.cpp", 100, false);
    }
}

String Keypair::get_public_value(){
    return public_value;
}

void Keypair::set_public_bytes(const PackedByteArray& p_value){
    public_bytes = p_value;
    if (public_bytes.size() == 0){
        public_value = "";
        return;
    }
    String encoded_value = bs58_encode(public_bytes);
    public_value = encoded_value;
    if (public_bytes.size() != 32){
        internal::gde_interface->print_warning("Public key must be 32 bytes", "_set", "pubkey.cpp", 117, false);
    }
}
PackedByteArray Keypair::get_public_bytes(){
    return public_bytes;
}

void Keypair::set_private_value(const String& p_value){
    private_value = p_value;
    PackedByteArray decoded_value = bs58_decode(private_value);
    private_bytes = decoded_value;
    if(decoded_value.is_empty() && private_value.length() != 0){
        internal::gde_interface->print_warning("Value contains non-base58 characters", "_set", "keypair.cpp", 129, false);
    }
    else if (decoded_value.size() != 32){
        internal::gde_interface->print_warning("Private key must be 32 bytes", "_set", "keypair.cpp", 132, false);
    }
}


String Keypair::get_private_value(){
    return private_value;
}

void Keypair::set_private_bytes(const PackedByteArray& p_value){
    private_bytes = p_value;
    if (private_bytes.size() == 0){
        private_value = "";
        return;
    }
    String encoded_value = bs58_encode(private_bytes);
    private_value = encoded_value;
    if (private_bytes.size() != 32){
        internal::gde_interface->print_warning("Private key must be 32 bytes", "_set", "keypair.cpp", 150, false);
    }
}
PackedByteArray Keypair::get_private_bytes(){
    return private_bytes;
}


void Keypair::set_unique(const bool p_value){
    unique = p_value;
    notify_property_list_changed();
}

bool Keypair::get_unique(){
    return unique;
}

Keypair::~Keypair() {
    _free_pointer_if_not_null();
}

}