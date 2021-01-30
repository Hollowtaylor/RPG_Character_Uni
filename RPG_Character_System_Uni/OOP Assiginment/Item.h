#pragma once
#include <string>
#include <vector>
#include <memory>


class Item
{
private:
	std::string itemName_;
	int itemValue_;
	float weight_;

public:
	virtual ~Item();

	Item(std::string itemName, int value, float weight);

	std::string GetItemName() const;
	void SetItemName(std::string itemName);

	int GetItemValue() const;
	void SetItemValue(int value);

	float GetWeight() const;
	void SetWeight(float weight);

};

