#pragma once
#include <string>
#include <unordered_map>
using namespace std;
template <typename T>
class AssetDictionary {
private:
	unordered_map<string, T> data;
public:
	AssetDictionary();
	~AssetDictionary();
	T GetItem(string itemName);
	void AddItem(string itemName, T item);
	int GetCount();
};

template<typename T>
inline AssetDictionary<T>::AssetDictionary()
{
}

template<typename T>
AssetDictionary<T>::~AssetDictionary()
{
	data.clear();
}

template<typename T>
T AssetDictionary<T>::GetItem(string itemName)
{
	if (data.find(itemName) == data.end()) {
		return nullptr;
	}
	return data[itemName];
}

template<typename T>
inline void AssetDictionary<T>::AddItem(string itemName, T item)
{
	data[itemName] = item;
}

template<typename T>
inline int AssetDictionary<T>::GetCount()
{
	return data.size();
}
