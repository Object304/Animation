#pragma once
#include "Operations.h"
#include "Trajectory.h"

ref class Knight1 {
public:
	Trajectory^ Tr;
	array<PointF>^ initial, ^ transformed;

	Knight1() {
		initial = gcnew array<PointF>(1);
		initial[0] = PointF(0, 0);
		Complex_Traj^ T = gcnew Complex_Traj(1);
		T->add(gcnew Traj_Move(initial[0], -0.8, 0));
		Tr = T;
	}

	void add(array<PointF>^ points) {
		initial = points;
		transformed = gcnew array<PointF>(initial->Length);
	}
};

ref class Castle {
public:
	Trajectory^ Tr;
	array<PointF>^ initial, ^ transformed;

	Castle() {
		initial = gcnew array<PointF>(1);
		initial[0] = PointF(0, 0);
		Complex_Traj^ T = gcnew Complex_Traj(1);
		T->add(gcnew Traj_Move(initial[0], -0.3, 0));
		Tr = T;
	}

	void add(array<PointF>^ points) {
		initial = points;
		transformed = gcnew array<PointF>(initial->Length);
	}
};

ref class Sphere1 {
public:
	Trajectory^ Tr;
	array<PointF>^ initial, ^ transformed;

	Sphere1() {
		initial = gcnew array<PointF>(1);
		initial[0] = PointF(0, 0);
		Complex_Traj^ T = gcnew Complex_Traj(1);
		T->add(gcnew Traj_Move(initial[0], -0.3, 0));
		Tr = T;
	}

	void add(array<PointF>^ points) {
		initial = points;
		transformed = gcnew array<PointF>(initial->Length);
	}
};