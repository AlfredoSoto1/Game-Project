#pragma once

namespace Maths {

	template<unsigned int E_COUNT, typename E_TYPE>
	struct vec {
	protected:
		E_TYPE component[E_COUNT];

	public:

		vec() {
			for (E_TYPE& e : component)
				e = 0;
		}

		vec(const vec& vector) {
			for (int i = 0; i < E_COUNT; i++)
				component[i] = vector.component[i];
		}

		E_TYPE& operator [] (unsigned int index) {
			return component[index];
		}

		vec operator - () {
			vec<E_COUNT, E_TYPE> out;
			for (int i = 0; i < E_COUNT; i++)
				out[i] = -component[i];
			return out;
		}

		E_TYPE operator * (const vec& vector) const {
			E_TYPE result = 0;
			for (int i = 0; i < E_COUNT; i++)
				result += component[i] * vector.component[i];
			return result;
		}

		vec operator | (const vec& vector) const {
			return vector;
		}

		vec operator + (const vec& vector) const {
			vec<E_COUNT, E_TYPE> out;
			for (int i = 0; i < E_COUNT; i++)
				out[i] = component[i] + vector.component[i];
			return out;
		}

		vec operator - (const vec& vector) const {
			vec<E_COUNT, E_TYPE> out;
			for (int i = 0; i < E_COUNT; i++)
				out[i] = component[i] - vector.component[i];
			return out;
		}

		vec operator * (const float factor) const {
			vec<E_COUNT, E_TYPE> out;
			for (int i = 0; i < E_COUNT; i++)
				out[i] = component[i] * factor;
			return out;
		}

		vec operator / (const float factor) const {
			vec<E_COUNT, E_TYPE> out;
			for (int i = 0; i < E_COUNT; i++)
				out[i] = component[i] / factor;
			return out;
		}

		vec& operator += (const vec& vector) {
			for (int i = 0; i < E_COUNT; i++)
				component[i] += vector.component[i];
			return *this;
		}

		vec& operator -= (const vec& vector) {
			for (int i = 0; i < E_COUNT; i++)
				component[i] -= vector.component[i];
			return *this;
		}

		vec& operator *= (const float factor) {
			for (E_TYPE& e : component)
				e *= factor;
			return *this;
		}

		vec& operator /= (const float factor) {
			for (E_TYPE& e : component)
				e /= factor;
			return *this;
		}


		bool operator == (const float value) {
			int carry = 0;
			for (E_TYPE& e : component)
				carry += value == e;
			return carry == E_COUNT;
		}

		bool operator == (const vec& vector) {
			int carry = 0;
			for (int i = 0; i < E_COUNT; i++)
				carry += component[i] == vector.component[i];
			return carry == E_COUNT;
		}

		bool operator != (const vec& vector) {
			return !((*this) == vector);
		}
	};
}