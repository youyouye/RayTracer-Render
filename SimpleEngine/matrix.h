#ifndef MATRIX_H_
#define MATRIX_H_
#include "mymath.h"
#include "vector.h"
class Matrix{
public:
	float p[16];
	Matrix(){
		for (int i = 0; i < 16; i++){
			p[i] = 0;
		}
	}
	Matrix(float values[]){
		for (int i = 0; i < 16; i++)
		{
			p[i] = values[i];
		}
	}
	bool operator==(const Matrix &m) const{
		bool equal = true;
		for (int i = 0; i < 16; i++){
			//还有这样的比较方法.
			equal = equal && floatEqual(p[i],m.p[i]);
		}
		return equal;
	}
	static Matrix identify(){
		float values[] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1,
		};
		return Matrix(values);
	}

	static Matrix rotationX(float angle){
		float s = sinf(angle*PI / 180);
		float c = cosf(angle*PI / 180);
		float values[16] = {
			1, 0,  0,  0,
			0, c,  -s,  0,
			0, s, c,  0,
			0, 0,  0,  1,
		};
		return Matrix(values);
	}
	static Matrix rotationY(float angle) {
		float s = sinf(angle*PI / 180);
		float c = cosf(angle*PI / 180);
		float values[16] = {
			c, 0, s, 0,
			0, 1, 0, 0,
			-s, 0, c, 0,
			0, 0, 0, 1,
		};
		return Matrix(values);
	}
	static Matrix rotationZ(float angle) {
		float s = sinf(angle*PI/180);
		float c = cosf(angle*PI / 180);
		float values[16] = {
			c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};
		return Matrix(values);
	}
	static Matrix rotation(const Vector3 &r) {
		Matrix x = Matrix::rotationX(r.x);
		Matrix y = Matrix::rotationY(r.y);
		Matrix z = Matrix::rotationZ(r.z);
		return z * x * y;
	}
	static Matrix rotate(const float degree,const Vector3 &axis){
		Vector3 w = axis.normalize();
		Vector3 t(w.x,w.y,1);
		Vector3 u = t.cross(w).normalize();
		Vector3 v = w.cross(u);
		float p1[16] = {
			u.x, v.x, w.x, 0,
			u.y, v.y, w.y, 0,
			u.z, v.z, w.z, 0,
			0,   0,   0,   1
		};
		float p2[16] = {
			cosf(degree*PI / 180), -sinf(degree*PI / 180),0,0,
			sinf(degree*PI / 180), cosf(degree*PI / 180),0,0,
			0, 0 ,1,0,
			0, 0 ,0,1
		};
		float p3[16] = {
			u.x, u.y,u.z,0,
			v.x, v.y,v.z,0,
			w.x, w.y,w.z,0,
			0, 0,0,1
		};
		Matrix t1(p1); Matrix t2(p2); Matrix t3(p3);
		return t1*t2*t3;
	}
	Matrix inverse(){
		double inv[16];

		inv[0] = p[5] * p[10] * p[15] -
			p[5] * p[11] * p[14] -
			p[9] * p[6] * p[15] +
			p[9] * p[7] * p[14] +
			p[13] * p[6] * p[11] -
			p[13] * p[7] * p[10];

		inv[4] = -p[4] * p[10] * p[15] +
			p[4] * p[11] * p[14] +
			p[8] * p[6] * p[15] -
			p[8] * p[7] * p[14] -
			p[12] * p[6] * p[11] +
			p[12] * p[7] * p[10];

		inv[8] = p[4] * p[9] * p[15] -
			p[4] * p[11] * p[13] -
			p[8] * p[5] * p[15] +
			p[8] * p[7] * p[13] +
			p[12] * p[5] * p[11] -
			p[12] * p[7] * p[9];

		inv[12] = -p[4] * p[9] * p[14] +
			p[4] * p[10] * p[13] +
			p[8] * p[5] * p[14] -
			p[8] * p[6] * p[13] -
			p[12] * p[5] * p[10] +
			p[12] * p[6] * p[9];

		inv[1] = -p[1] * p[10] * p[15] +
			p[1] * p[11] * p[14] +
			p[9] * p[2] * p[15] -
			p[9] * p[3] * p[14] -
			p[13] * p[2] * p[11] +
			p[13] * p[3] * p[10];

		inv[5] = p[0] * p[10] * p[15] -
			p[0] * p[11] * p[14] -
			p[8] * p[2] * p[15] +
			p[8] * p[3] * p[14] +
			p[12] * p[2] * p[11] -
			p[12] * p[3] * p[10];

		inv[9] = -p[0] * p[9] * p[15] +
			p[0] * p[11] * p[13] +
			p[8] * p[1] * p[15] -
			p[8] * p[3] * p[13] -
			p[12] * p[1] * p[11] +
			p[12] * p[3] * p[9];

		inv[13] = p[0] * p[9] * p[14] -
			p[0] * p[10] * p[13] -
			p[8] * p[1] * p[14] +
			p[8] * p[2] * p[13] +
			p[12] * p[1] * p[10] -
			p[12] * p[2] * p[9];

		inv[2] = p[1] * p[6] * p[15] -
			p[1] * p[7] * p[14] -
			p[5] * p[2] * p[15] +
			p[5] * p[3] * p[14] +
			p[13] * p[2] * p[7] -
			p[13] * p[3] * p[6];

		inv[6] = -p[0] * p[6] * p[15] +
			p[0] * p[7] * p[14] +
			p[4] * p[2] * p[15] -
			p[4] * p[3] * p[14] -
			p[12] * p[2] * p[7] +
			p[12] * p[3] * p[6];

		inv[10] = p[0] * p[5] * p[15] -
			p[0] * p[7] * p[13] -
			p[4] * p[1] * p[15] +
			p[4] * p[3] * p[13] +
			p[12] * p[1] * p[7] -
			p[12] * p[3] * p[5];

		inv[14] = -p[0] * p[5] * p[14] +
			p[0] * p[6] * p[13] +
			p[4] * p[1] * p[14] -
			p[4] * p[2] * p[13] -
			p[12] * p[1] * p[6] +
			p[12] * p[2] * p[5];

		inv[3] = -p[1] * p[6] * p[11] +
			p[1] * p[7] * p[10] +
			p[5] * p[2] * p[11] -
			p[5] * p[3] * p[10] -
			p[9] * p[2] * p[7] +
			p[9] * p[3] * p[6];

		inv[7] = p[0] * p[6] * p[11] -
			p[0] * p[7] * p[10] -
			p[4] * p[2] * p[11] +
			p[4] * p[3] * p[10] +
			p[8] * p[2] * p[7] -
			p[8] * p[3] * p[6];

		inv[11] = -p[0] * p[5] * p[11] +
			p[0] * p[7] * p[9] +
			p[4] * p[1] * p[11] -
			p[4] * p[3] * p[9] -
			p[8] * p[1] * p[7] +
			p[8] * p[3] * p[5];

		inv[15] = p[0] * p[5] * p[10] -
			p[0] * p[6] * p[9] -
			p[4] * p[1] * p[10] +
			p[4] * p[2] * p[9] +
			p[8] * p[1] * p[6] -
			p[8] * p[2] * p[5];

		double det = p[0] * inv[0] + p[1] * inv[4] + p[2] * inv[8] + p[3] * inv[12];

		if (det == 0) { return Matrix::identify(); }

		Matrix ret;
		det = 1.0 / det;
		for (int i = 0; i < 16; ++i)
			ret.p[i] = inv[i] * det;
		return ret;
	}
	Matrix transposition(){
		float values[16] = {
			p[0], p[4], p[8], p[12],
			p[1], p[5], p[9], p[13],
			p[2], p[6], p[10], p[14],
			p[3], p[7], p[11], p[15]
		};
		return Matrix(values);
	}
	static Matrix scale(const Vector3 &s) {
		float values[16] = {
			s.x, 0, 0, 0,
			0, s.y, 0, 0,
			0, 0, s.z, 0,
			0, 0, 0, 1,
		};
		return Matrix(values);
	}
	static Matrix translation(const Vector3 &t) {
		float values[16] = {
			1, 0, 0, t.x,
			0, 1, 0, t.y,
			0, 0, 1, t.z,
			0, 0, 0, 1,
		};
		return Matrix(values);
	}

	static Matrix standardsView(int w,int h){
		float values[16] = {
			w / 2, 0, (w - 1) / 2, 0,
			0, -h / 2, (h - 1) / 2, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		return Matrix(values);
	}

	static Matrix lookAtLH(const Vector3 &eye, const Vector3 &target, const Vector3 &up){
		Vector3 axisZ = (target - eye).normalize();
		Vector3 axisX = up.cross(axisZ).normalize();
		Vector3 axisY = axisZ.cross(axisX).normalize();

		float values[16] = {
			axisX.x, axisY.x, axisZ.x, 0,
			axisX.y, axisY.y, axisZ.y, 0,
			axisX.z, axisY.z, axisZ.z, 0,
			0, 0, 0, 1,
		};
		float values2[16] = {
			1, 0, 0, -eye.x,
			0, 1, 0, -eye.y,
			0, 0, 1, -eye.z,
			0, 0, 0, 1
		};
		return Matrix(values)*Matrix(values2);
	}
	static Matrix perspectiveFovLH(float fieldOfView, float aspect, float znear, float zfar){
		float height = 1 / tan(fieldOfView / 2);
		float width = height / aspect;
		float values[16] = {
			width, 0, 0, 0,
			0, height, 0, 0,
			0, 0, -(zfar + znear) / (zfar - znear), (2*znear * zfar) / (znear - zfar),
			0, 0, -1, 0,
		};
		return Matrix(values);
	}

	Vector3 transform(const Vector3 &v) const {
		float x = v.x * p[0 * 4 + 0] + v.y * p[0 * 4 + 1] + v.z * p[0 * 4 + 2] + p[0 * 4 + 3];
		float y = v.x * p[1 * 4 + 0] + v.y * p[1 * 4 + 1] + v.z * p[1 * 4 + 2] + p[1 * 4 + 3];
		float z = v.x * p[2 * 4 + 0] + v.y * p[2 * 4 + 1] + v.z * p[2 * 4 + 2] + p[2 * 4 + 3];
		float w = v.x * p[3 * 4 + 0] + v.y * p[3 * 4 + 1] + v.z * p[3 * 4 + 2] + p[3 * 4 + 3];
		return Vector3(x / w, y / w, z / w);
	}
	Vector3 transformD(const Vector3 &v) const {
		float x = v.x * p[0 * 4 + 0] + v.y * p[0 * 4 + 1] + v.z * p[0 * 4 + 2]  ;
		float y = v.x * p[1 * 4 + 0] + v.y * p[1 * 4 + 1] + v.z * p[1 * 4 + 2]  ;
		float z = v.x * p[2 * 4 + 0] + v.y * p[2 * 4 + 1] + v.z * p[2 * 4 + 2]  ;
		float w = v.x * p[3 * 4 + 0] + v.y * p[3 * 4 + 1] + v.z * p[3 * 4 + 2]  ;
		return Vector3(x , y , z);
	}
	Matrix operator*(const Matrix &matrix) const{
		const Matrix &m = matrix;
		float values[16];
		for (int index = 0; index < 16; index++){
			int i = index / 4;
			int j = index % 4;
			values[index] = p[i * 4] * m.p[j] + p[i * 4 + 1] * m.p[1 * 4 + j] + p[i * 4 + 2] * m.p[2 * 4 + j] + p[i * 4 + 3] * m.p[3 * 4 + j];
		}
		return Matrix(values);
	}
};


#endif