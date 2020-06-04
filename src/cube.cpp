/**
 * @file cube.cpp
 * @brief Visual 3D cube model
 *
 * Generates a 3D cube model. Manipulate the cube dimension, location,
 * rotation and scale.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


namespace rmg {

using Sample = shared_ptr<internal::VBO>;
std::vector<std::pair<uint32_t, Sample>> Cube3D::samples;

/**
 * @brief Constructs a 3D cube model from specific dimensions
 * 
 * @param ctx Container context
 * @param l Length
 * @param b Breadth
 * @param h Height
 */
Cube3D::Cube3D(Context* ctx, float l, float b, float h): Object3D(ctx)
{
    setDimension(l, b, h);
    
    uint32_t ctxID = getContext()->getID();
    for(auto it=samples.begin(); it!=samples.end(); it++) {
        if(it->first == ctxID) {
            setSharedVBO(it->second);
            return;
        }
    }
    
    Sample sample = std::make_shared(internal::VBO());
    setSharedVBO(sample);
    Vec3 verticies[24];
    Vec3 normals[24];
    Vec2 textures[24];
    uint32_t* indecies[36];
    setMesh(Mesh(verticies, normals, textures, 24, indecies, 36));
    auto elem = std::pair<uint32_t,Sample>(ctxID,sample);
    samples.insert(elem);
}

/**
 * @brief Destructor
 */
Cube3D::~Cube3D() {
    uint32_t ctxID = getContext()->getID();
    for(auto it=samples.begin(); it!=samples.end(); it++) {
        if(it->first == ctxID) {
            if(it->second.use_count() == 2)
                samples.erase(it);
            return;
        }
    }
}

/**
 * @brief Modify the dimension of the cube
 * 
 * @param l Length
 * @param b Breadth
 * @param h Height
 */
void Cube3D::setDimension(float l, float b, float h) {
    length = l;
    breadth = b;
    height = h;
    modelMatrix[0][0] = rotationMatrix[0][0] * scale.x * l;
    modelMatrix[1][1] = rotationMatrix[1][1] * scale.y * b;
    modelMatrix[2][2] = rotationMatrix[2][2] * scale.z * h;
}

/**
 * Gets the dimension of the cube
 * 
 * @return Cubic dimension
 */
Vec3 Cube3D::getDimension() {
    return Vec3(lenght, breadth, height);
}

/**
 * @brief Sets the orientaion of the cube
 * 
 * Sets the rotation matrix and the model matrix. Rotation of the cube
 * is in Euler angles. Rotation order is ZYX (Yaw-Pitch-Roll).
 * Model matrix calculation includes additional factors length, width and
 * height.
 * 
 * @param rot Euler angles
 */
void Cube3D::setRotation(const Euler& rot) {
    rotationMatrix = rot.toRotationMatrix();
    modelMatrix[0][0] = rotationMatrix[0][0] * scale.x * length;
    modelMatrix[0][1] = rotationMatrix[0][1];
    modelMatrix[0][2] = rotationMatrix[0][2];
    modelMatrix[1][0] = rotationMatrix[1][0];
    modelMatrix[1][1] = rotationMatrix[1][1] * scale.y * breadth;
    modelMatrix[1][2] = rotationMatrix[1][2];
    modelMatrix[2][0] = rotationMatrix[2][0];
    modelMatrix[2][1] = rotationMatrix[2][1];
    modelMatrix[2][2] = rotationMatrix[2][2] * scale.z * height;
}

/**
 * @brief Sets the scale of the cube
 * 
 * Sets the scale and the model matrix.
 * The function is virtual as the derived classes' handling of model
 * matrix involves additional scaling components.
 * Model matrix calculation includes additional factors length, width and
 * height.
 * 
 * @param x Scaling factor in x-component
 * @param y Scaling factor in y-component
 * @param z Scaling factor in z-component
 */
void Cube3D::setScale(float x, float y, float z) {
    scale.x = x;
    scale.y = y;
    scale.z = z;
    modelMatrix[0][0] = rotationMatrix[0][0] * x * length;
    modelMatrix[1][1] = rotationMatrix[1][1] * y * breadth;
    modelMatrix[2][2] = rotationMatrix[2][2] * z * height;
}

/**
 * @brief Sets the scale of the cube
 * 
 * Sets the scale and the model matrix.
 * The function is virtual as the derived classes' handling of model
 * matrix involves additional scaling components.
 * Model matrix calculation includes additional factors length, width and
 * height.
 * 
 * @param f Scaling factor
 */
void Cube3D::setScale(float f) {
    scale.x = f;
    scale.y = f;
    scale.z = f;
    modelMatrix[0][0] = rotationMatrix[0][0] * f * length;
    modelMatrix[1][1] = rotationMatrix[1][1] * f * breadth;
    modelMatrix[2][2] = rotationMatrix[2][2] * f * height;
}

}
