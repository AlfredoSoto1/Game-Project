#pragma once

#define ADD  0 // add
#define SUB  1 // substract
#define MUL  2 // multiply with factor
#define DIV  3 // divide with factor
#define mMUL 4 // multiply with another matrix

namespace Maths {

	template<unsigned int ROW, unsigned int COL, typename E_TYPE>
	struct mat {
	private:
		E_TYPE matrix[ROW * COL];

		//operation constructor
		mat(const mat& _mat1, const mat& _mat2, unsigned int _operation, E_TYPE _value) {
			switch (_operation) {
			case ADD:
				for (int i = 0; i < ROW * COL; i++)
					matrix[i] = _mat1.matrix[i] + _mat2.matrix[i];
				break;
			case SUB:
				for (int i = 0; i < ROW * COL; i++)
					matrix[i] = _mat1.matrix[i] - _mat2.matrix[i];
				break;
			case MUL:
				for (int i = 0; i < ROW * COL; i++)
					matrix[i] = _mat1.matrix[i] * _value;
				break;
			case DIV:
				for (int i = 0; i < ROW * COL; i++)
					matrix[i] = _mat1.matrix[i] / _value;
				break;
			case mMUL:
				for (int i = 0; i < ROW; i++)
					for (int j = 0; j < COL; j++) {
						E_TYPE element = 0;
						for (int k = 0; k < ROW; k++)
							element += _mat1.matrix[k + j * ROW] * _mat2.matrix[i + k * COL];
						matrix[i + j * COL] = element;
					}
				break;
			}
		}

	public:
		mat(E_TYPE _value) {
			for (E_TYPE& e : matrix)
				e = _value;
		}

		mat(unsigned int _count, E_TYPE* _value) {
			if (_count / sizeof(*_value) >= ROW * COL)
				return;
			for (int i = 0; i < ROW * COL; i++)
				matrix[i] = _value[i];
		}

		E_TYPE& operator [] (unsigned int _index) {
			return matrix[_index];
		}

		E_TYPE& operator () (unsigned int row, unsigned int col) {
			return matrix[row + col * COL];
		}

		mat operator + (const mat& _other) {
			return mat(*this, _other, ADD, 0);
		}

		mat operator - (const mat& _other) {
			return mat(*this, _other, SUB, 0);
		}

		mat operator * (const mat& _other) {
			return mat(*this, _other, mMUL, 0);
		}

		mat operator * (float _factor) {
			return mat(*this, *this, MUL, _factor);
		}

		mat operator / (float _factor) {
			return mat(*this, *this, DIV, _factor);
		}


		mat& operator += (const mat& _other) {
			for (int i = 0; i < ROW * COL; i++)
				matrix[i] += _other.matrix[i];
			return *this;
		}

		mat& operator -= (const mat& _other) {
			for (int i = 0; i < ROW * COL; i++)
				matrix[i] -= _other.matrix[i];
			return *this;
		}

		mat& operator *= (float _factor) {
			for (E_TYPE& e : matrix) e *= _factor;
			return *this;
		}

		mat& operator /= (float _factor) {
			for (E_TYPE& e : matrix) e /= _factor;
			return *this;
		}

		bool operator == (const mat& _other) {
			for (int i = 0; i < ROW * COL; i++)
				if (matrix[i] != _other.matrix[i])
					return false;
			return true;
		}
	};

	template<unsigned int ROW, unsigned int COL, typename E_TYPE>
	void toIdentity(mat<ROW, COL, E_TYPE>* _matrix) {
		if (ROW != COL)
			return;
		for (int i = 0; i < ROW; i++)
			for (int j = 0; j < COL; j++)
				if (i == j)
					(*_matrix)[j + i * COL] = 1;
				else
					(*_matrix)[j + i * COL] = 0;
	}

	template<unsigned int ROW, unsigned int COL, typename E_TYPE>
	mat<ROW, COL, E_TYPE> toIdentity(const mat<ROW, COL, E_TYPE>& _matrix) {
		mat<ROW, COL, E_TYPE> result = _matrix;
		toIdentity(&result);
		return result;
	}

	template<unsigned int ROW, unsigned int COL, typename E_TYPE>
	void subMatOf(mat<ROW, COL, E_TYPE>& _matrix, unsigned int _row, unsigned int _col, mat<ROW == 2 ? 2 : ROW - 1, COL == 2 ? 2 : COL - 1, E_TYPE>* _dest) {
		int subRow = 0, subCol = 0;
		for (unsigned int row = 0; row < COL; row++)
			for (unsigned int col = 0; col < COL; col++)
				if (row != _row && col != _col) {
					(*_dest)[subCol++ + subRow * (COL - 1)] = _matrix[col + row * COL];
					if (subCol == COL - 1) {
						subCol = 0;
						subRow++;
					}
				}
	}

	template<typename E_TYPE>
	E_TYPE determinantOf(const mat<2U, 2U, E_TYPE>& _matrix) {
		return _matrix[0] * _matrix[3] - _matrix[1] * _matrix[2];
	}

	template<unsigned int ROW, unsigned int COL, typename E_TYPE>
	E_TYPE determinantOf(mat<ROW, COL, E_TYPE>& _matrix) {
		if (ROW == 2)
			return _matrix[0] * _matrix[3] - _matrix[1] * _matrix[2];

		mat<ROW == 2 ? 2 : ROW - 1, COL == 2 ? 2 : COL - 1, E_TYPE> temp(0);

		E_TYPE determinant = 0;
		for (int sign = 1, i = 0; i < COL; i++) {
			subMatOf(_matrix, 0, i, &temp);
			determinant += sign * _matrix[i] * determinantOf(temp);
			sign = -sign;
		}
		return determinant;
	}

	template<unsigned int ROW, unsigned int COL, typename E_TYPE>
	mat<ROW, COL, E_TYPE> transpose(mat<ROW, COL, E_TYPE>& _matrix) {
		mat<ROW, COL, E_TYPE> temp(0);
		for (int i = 0; i < ROW; i++)
			for (int j = 0; j < COL; j++)
				temp[i + j * ROW] = _matrix[j + i * COL];
		return temp;
	}

	template<unsigned int ROW, unsigned int COL, typename E_TYPE>
	mat<ROW, COL, E_TYPE> inverse(mat<ROW, COL, E_TYPE>& _matrix) {
		if (ROW != COL)
			return _matrix;

		if (ROW == 2) {
			mat<ROW, COL, E_TYPE> outMatrix(0);
			outMatrix[0] =  _matrix[3];
			outMatrix[1] = -_matrix[1];
			outMatrix[2] = -_matrix[2];
			outMatrix[3] =  _matrix[0];
			outMatrix /= determinantOf(_matrix);
			return outMatrix;
		}
		mat<ROW, COL, E_TYPE> adjointMatrix(0);
		mat<ROW == 2 ? 2 : ROW - 1, COL == 2 ? 2 : COL - 1, E_TYPE> temp(0);
		for (int i = 0, sign = 1; i < ROW; i++)
			for (int j = 0; j < COL; j++) {
				subMatOf(_matrix, i, j, &temp);
				adjointMatrix[j + i * COL] = determinantOf(temp) * sign;
				sign = -sign;
			}
		mat<ROW, COL, E_TYPE> outMatrix = transpose(adjointMatrix);
		outMatrix /= determinantOf(_matrix);
		return outMatrix;
	}
}