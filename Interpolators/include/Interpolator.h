#pragma once

#include <vector>
#include <algorithm>
#include <Defines.h>

namespace aux
{

	template <typename KeyType, typename ValueType>
	struct InterpolatorPair
	{
		KeyType key;
		ValueType value;
	};

	template <typename KeyType, typename ValueType>
	int find_corresponding_interval_index(KeyType key, std::vector<InterpolatorPair<KeyType, ValueType>> const & _valueList)
	{
		InterpolatorPair<KeyType, ValueType> pair = { key,{} };

		auto comparator = [](InterpolatorPair<KeyType, ValueType> const & left, InterpolatorPair<KeyType, ValueType> const & right)
		{
			return left.key < right.key;
		};

		auto it = std::lower_bound(_valueList.begin(), _valueList.end(), pair, comparator);

		int index = std::max((int)(it - _valueList.begin()) - 1, 0);
		return index;
	}

	template<typename KeyType, typename ValueType>
	class Interpolator
	{
#pragma region api

	public:

		virtual ~Interpolator() = default;

		virtual void add(KeyType &&key, ValueType &&type)
		{
			_valueList.push_back({ key,type });
		}

		virtual void clear()
		{
			_valueList.clear();
		}

		virtual ValueType get(KeyType key) const
		{
			ValueType result{};

			if (key < _valueList[0].key)
			{
				result = _valueList[0].value;
			}
			else if (key > _valueList[_valueList.size() - 1].key)
			{
				result = _valueList[_valueList.size() - 1].value;
			}
			else
			{
				int idx = find_corresponding_interval_index(key, _valueList);
				result = interpolate(_valueList[idx], _valueList[idx + 1], key);
			}

			return result;
		}

		void validate()
		{
			size_t size = _valueList.size();

			assert(size > 1, "no enough interpolation data");

			for (int i = 0; i < size - 1; i++)
			{
				assert(_valueList[i].key < _valueList[i + 1].key, "Collection must be sorted")
			}
		}

#pragma endregion

#pragma region private methods

	private:

		pure_virtual ValueType interpolate(InterpolatorPair<KeyType, ValueType>const & left, InterpolatorPair<KeyType, ValueType> const & right, KeyType const & key) const = 0;

#pragma endregion

#pragma region members

	private:

		std::vector<InterpolatorPair<KeyType, ValueType>> _valueList;

#pragma endregion

	};


	template<typename KeyType, typename ValueType>
	class LinearInterpolator : public Interpolator<KeyType, ValueType>
	{

	private:

		ValueType interpolate(InterpolatorPair<KeyType, ValueType>const & left, InterpolatorPair<KeyType, ValueType> const & right, KeyType const & key) const override
		{
			auto divider = (right.key - left.key);
			auto dx = (key - left.key);

			ValueType dy = (right.value - left.value) / divider;

			return  left.value + (dy * dx);
		}
	};


	template<typename KeyType, typename ValueType>
	class CosineInterpolator : public Interpolator<KeyType, ValueType>
	{

	private:

		ValueType interpolate(InterpolatorPair<KeyType, ValueType>const & left, InterpolatorPair<KeyType, ValueType> const & right, KeyType const & key) const override
		{
			auto divider = (right.key - left.key);
			auto dx = (key - left.key);

			double x_r = dx / (double)divider;

			auto  mu2 = (1 - cos(x_r*3.14159)) / 2;
			return (left.value*(1 - mu2) + right.value * mu2);
		}
	};


}