//f:t->M
//Trajectory.h
#pragma once
#include <cmath>
#include "Operations.h"
using namespace System::Drawing;
ref class Trajectory {
public:
	Trajectory() {
		to = 0;
		M = gcnew array<float, 2>(3, 3);
		reset();
	}
	void reset() {
		t = to;
	}
	array<float, 2>^ next() {
		position(t, M);
		t++;
		return M;
	}
protected:
	int t, to;
	array<float, 2>^ M;
	virtual void position(float t, array<float, 2>^ M) = 0;
};

ref class Complex_Traj : public Trajectory {
public:
	Complex_Traj(int max) {
		trajectories = gcnew array<Trajectory^>(max);
		M1 = gcnew array<float, 2>(3, 3);
		clear();
	}
	bool isfull() {
		return n >= trajectories->Length;
	}
	bool isempty() {
		return n <= 0;
	}
	void clear() {
		n = 0;
	}
	void add(Trajectory^ Tr) {
		if (isfull())
			throw "Невозможно добавить траекторию";
		trajectories[n++] = Tr;
	}
	void remove_last() {
		if (isempty())
			throw "Невозможно удалить траекторию";
		n--;
	}
protected:
	void position(float t, array<float, 2>^ M)override {
		identity_mat(M1);
		for (int i = 0; i < n; i++) {
			multiply(trajectories[i]->next(), M1, M);
			array<float, 2>::Copy(M, M1, M->Length);
		}
	}
private:
	int n;
	array<Trajectory^>^ trajectories;
	array<float, 2>^ M1;
};

//f(t) = fo + Asin(omega * t + phi)
ref class Traj_Harmonic :public Trajectory {
public:
	Traj_Harmonic(float fo, float A, float omega, float phi) {
		this->fo = fo;
		this->A = A;
		this->omega = omega;
		this->phi = phi;
	}
protected:
	void position(float t, array<float, 2>^ M)override {
		float f = fo + A * sin(omega * t + phi);
		move_mat(t, f, M);
	}
private:
	float fo, A, omega, phi;
};

ref class Traj_Rotate :public Trajectory {
public:
	Traj_Rotate(PointF c, float omega, float init_angle) {
		this->c = c;
		this->omega = omega;
		this->init_angle = init_angle;
	}
protected:
	void position(float t, array<float, 2>^ M)override {
		rotate_mat(c, omega * t + init_angle, M);
	}
private:
	PointF c;
	float omega, init_angle;
};

ref class Traj_Move :public Trajectory {
public:
	Traj_Move(PointF c, float dx, float dy) {
		this->c = c;
		this->dx = dx;
		this->dy = dy;
	}
protected:
	void position(float t, array<float, 2>^ M)override {
		move_mat(dx * t, dy * t, M);
	}
private:
	PointF c;
	float dx, dy;
};

ref class Traj_Scale :public Trajectory {
public:
	Traj_Scale(PointF c, float kx, float ky) {
		this->c = c;
		this->kx = kx;
		this->ky = ky;
	}
protected:
	void position(float t, array<float, 2>^ M)override {
		scale_mat(c, kx * t, ky * t, M);
	}
private:
	PointF c;
	float kx, ky;
};