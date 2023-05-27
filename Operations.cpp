#pragma once
#include <cassert>
#include <math.h>
#include "Operations.h"

void multiply(array<float, 2>^ A, array<float, 2>^ B, array<float, 2>^ C) {
	int n = A->GetLength(0), m = B->GetLength(1), k = A->GetLength(1);
	assert(k == B->GetLength(0) && n == C->GetLength(0) && m == C->GetLength(1));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			C[i, j] = 0;
			for (int p = 0; p < k; p++)
				C[i, j] += A[i, p] * B[p, j];
		}
}
//единичная матрица
void identity_mat(array<float, 2>^ M) {
	int n = M->GetLength(0), m = M->GetLength(1);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			M[i, j] = float(i == j);
}
//функция сдвига
void move_mat(float dx, float dy, array<float, 2>^ T) {
	identity_mat(T);
	T[0, T->GetLength(1) - 1] = dx;
	T[1, T->GetLength(1) - 1] = dy;
}
//функция масштабирования
void scale_mat(float kx, float ky, array<float, 2>^ S) {
	identity_mat(S);
	S[0, 0] = kx;
	S[1, 1] = ky;
}
//функция поворота
void rotate_mat(float phi, array<float, 2>^ R) {
	identity_mat(R);
	R[0, 0] = cos(phi);
	R[1, 1] = R[0, 0];
	R[0, 1] = sin(phi);
	R[1, 0] = -R[0, 1];
}

PointF apply(PointF p, array<float, 2>^ M) {//что она делает, зачем нужна?
	return PointF(p.X * M[0, 0] + p.Y * M[0, 1] + M[0, 2], p.X * M[1, 0] + p.Y * M[1, 1] + M[1, 2]);
}

void scale_mat(PointF c, float kx, float ky, array<float, 2>^ S) {
	scale_mat(kx, ky, S);
	PointF scaled_c = apply(c, S);
	S[0, S->GetLength(1) - 1] = c.X - scaled_c.X;
	S[1, S->GetLength(1) - 1] = c.Y - scaled_c.Y;
}

void rotate_mat(PointF c, float phi, array<float, 2>^ R) {
	rotate_mat(phi, R);
	PointF rot_c = apply(c, R);
	R[0, R->GetLength(1) - 1] = c.X - rot_c.X;
	R[1, R->GetLength(1) - 1] = c.Y - rot_c.Y;
}

PointF rotate(PointF p, PointF c, float phi) {
	return PointF(c.X + (p.X - c.X) * cos(phi) - (p.Y - c.Y) * sin(phi),
		c.Y + (p.X - c.X) * sin(phi) + (p.Y - c.Y) * cos(phi));
}

