#include "Shape.h"
#include "Object.h"

void Shape::ApplyTorque(double torque) {
	object->ApplyTorque(torque);
}
void Shape::ApplyImpulse(Vector2D r, Vector2D p) {
	object->ApplyImpulse(r, p);
}
void Shape::ApplyCorrectiveImpulse(Vector2D r, Vector2D p) {
	object->ApplyCorrectiveImpulse(r, p);
}
const Matrix3x3 &Shape::GetTransformToWorld() const {
	return object->transformToWorld;
}
const Matrix3x3 &Shape::GetTransformToWorldInverse() const {
	return object->transformToWorldInverse;
}

Vector2D Shape::GetCentroidPosition() {
	return object->transformToWorld(centroidPosition);
}

void Shape::SetBoundaryWidth(double width) {
	boundaryWidth = width;
}