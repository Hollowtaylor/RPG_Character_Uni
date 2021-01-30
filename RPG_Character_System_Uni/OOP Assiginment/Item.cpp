#include "Item.h"



Item::~Item()  {
}

Item::Item(std::string itemName, int value, float weight) : itemName_(itemName), itemValue_(value), weight_(weight)  {
}

std::string Item::GetItemName() const  {
	return itemName_;
}

void Item::SetItemName(std::string itemName)  {
	itemName_ = itemName;
}

int Item::GetItemValue() const  {
	return itemValue_;
}

void Item::SetItemValue(int value)  {
	itemValue_ = value;
}

float Item::GetWeight() const  {
	return weight_;
}

void Item::SetWeight(float weight)  {
	weight_ = weight;
}

