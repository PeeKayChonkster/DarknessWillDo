#pragma once
#include "SFML/Graphics.hpp"
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"

namespace chonky {
	template<typename T>
	inline sf::Vector2<T> glm_to_sf_vec(const glm::vec<2, T>& vec)
	{
		return sf::Vector2<T>(vec.x, vec.y);
	}

	template<typename T>
	inline glm::vec<2, T> sf_to_glm_vec(const sf::Vector2<T>& vec)
	{
		return glm::vec<2, T>(vec.x, vec.y);
	}

	template<typename T>
	inline glm::vec<2, T> clampVec(const glm::vec<2, T>& vec, const float minVal, const float maxVal)
	{
		float newLength = glm::clamp(glm::length(vec), minVal, maxVal);
		return glm::normalize(vec) * newLength;
	}

	inline float lerp(float a, float b, float ratio)
	{
		return (b - a) * ratio + a;
	}

	inline float lerpAngle(float a, float b, float ratio)
	{
		float result;
		float diff = b - a;
		if (diff < -180.f)
		{
			// lerp upwards past 360
			b += 360.f;
			result = lerp(a, b, ratio);
			if (result >= 360.f)
			{
				result -= 360.f;
			}
		}
		else if (diff > 180.f)
		{
			// lerp downwards past 0
			b -= 360.f;
			result = lerp(a, b, ratio);
			if (result < 0.f)
			{
				result += 360.f;
			}
		}
		else
		{
			// straight lerp
			result = lerp(a, b, ratio);
		}

		return result;
	}
}