void Matrix_IdentityFunction(float* matrix);
void Matrix_Multiply(float* destination, float* operand1, float* operand2);
void Matrix_Translate(float* matrix, float x, float y, float z);
void Matrix_Scale(float* matrix, float x, float y, float z);
void Matrix_Frustum(float* matrix, float left, float right, float bottom, float top, float zNear, float zFar);
void Matrix_RotateX(float* matrix, float angle);
void Matrix_RotateY(float* matrix, float angle);
void Matrix_RotateZ(float* matrix, float angle);
void Matrix_Perspective(float* matrix, float fieldOfView, float aspectRatio, float zNear, float zFar);