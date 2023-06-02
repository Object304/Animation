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
		T->add(gcnew Traj_Move(initial[0], -1.8, 0));
		Tr = T;
	}

	void add(array<PointF>^ points) {
		initial = points;
		transformed = gcnew array<PointF>(initial->Length);
	}

	void Update() {
		Tr->reset();
		Complex_Traj^ T = gcnew Complex_Traj(1);
		T->add(gcnew Traj_Move(initial[0], 0, 2.3));
		Tr = T;
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
		T->add(gcnew Traj_Move(initial[0], -1, 0));
		Tr = T;
	}

	void add(array<PointF>^ points) {
		initial = points;
		transformed = gcnew array<PointF>(initial->Length);
	}

	void Update() {
		Tr->reset();
		Complex_Traj^ T = gcnew Complex_Traj(1);
		T->add(gcnew Traj_Move(initial[0], 0, 0.25));
		Tr = T;
	}

	void Update1() {
		Tr->reset();
		Complex_Traj^ T = gcnew Complex_Traj(1);
		T->add(gcnew Traj_Move(initial[0], 0, 0));
		Tr = T;
	}
};

ref class Sphere1 {
public:
	Trajectory^ Tr;
	array<PointF>^ initial, ^ transformed;

	Sphere1() {
		initial = gcnew array<PointF>(1);
		initial[0] = PointF(339, 209);
		Complex_Traj^ T = gcnew Complex_Traj(2);
		T->add(gcnew Traj_Scale(PointF(339, 209), 0.01, 0.01));
		T->add(gcnew Traj_Rotate(PointF(339, 209), 0.1, atan(209 / 339)));
		Tr = T;
	}

	void add(array<PointF>^ points) {
		initial = points;
		transformed = gcnew array<PointF>(initial->Length);
	}

	void Update() {
		Tr->reset();
		Complex_Traj^ T = gcnew Complex_Traj(3);
		T->add(gcnew Traj_Scale(PointF(339, 209), 0.005, 0.005));
		T->add(gcnew Traj_Rotate(PointF(339, 209), 0.1, atan(209 / 339)));
		T->add(gcnew Traj_Move(PointF(0, 0), 0, -0.6));
		Tr = T;
	}
	void Update1() {
		Tr->reset();
		Complex_Traj^ T = gcnew Complex_Traj(1);
		T->add(gcnew Traj_Rotate(PointF(339, 209), 0.1, atan(209 / 339)));
		Tr = T;
	}
};