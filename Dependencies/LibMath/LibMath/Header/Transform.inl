#ifndef __LIBMATH__TRANSFORM_INL__
#define __LIBMATH__TRANSFORM_INL__

#include "Transform.h"

#include "Matrix/Matrix3.h"

namespace LibMath
{
    inline Transform::Transform()
        : Transform(Vector3::zero(), Quaternion::identity(), Vector3::one())
    {
    }

    inline Transform::Transform(const Vector3& position, const TVector3<Radian>& angles, const Vector3& scale)
        : Transform(position, Quaternion(angles), scale)
    {
    }

    inline Transform::Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
        : m_position(position), m_rotation(rotation), m_scale(scale), m_parent(nullptr)
    {
        m_matrix = generateMatrix(m_position, m_rotation, m_scale);
        updateWorldMatrix();
    }

    inline Transform::Transform(Matrix4x4 matrix)
        : m_matrix(std::move(matrix)), m_parent(nullptr)
    {
        decomposeMatrix(m_matrix, m_position, m_rotation, m_scale);
        updateWorldMatrix();
    }

    inline Transform::Transform(const Transform& other)
        : m_position(other.m_position), m_rotation(other.m_rotation), m_scale(other.m_scale), m_matrix(other.m_matrix),
        m_parent(nullptr)
    {
        if (other.m_parent)
            setParent(other.m_parent, false);
        else
            updateWorldMatrix();
    }

    inline Transform::Transform(Transform&& other) noexcept
        : m_position(other.m_position), m_rotation(other.m_rotation), m_scale(other.m_scale), m_matrix(std::move(other.m_matrix)),
        m_parent(nullptr), m_notifier(std::move(other.m_notifier))
    {
        if (other.m_parent)
            setParent(other.m_parent, false);
        else
            updateWorldMatrix();
    }

    inline Transform::~Transform()
    {
        if (m_parent && m_notificationHandlerId)
            m_parent->m_notifier.unsubscribe(m_notificationHandlerId);

        m_notifier.broadcast(TransformNotifier::ENotificationType::TRANSFORM_DESTROYED, nullptr);
    }

    inline Transform& Transform::operator=(const Transform& other)
    {
        if (&other == this)
            return *this;

        m_position = other.m_position;
        m_rotation = other.m_rotation;
        m_scale = other.m_scale;
        m_matrix = other.m_matrix;

        if (other.m_parent != m_parent)
            setParent(other.m_parent, false);
        else
            updateWorldMatrix();

        return *this;
    }

    inline Transform& Transform::operator=(Transform&& other) noexcept
    {
        if (&other == this)
            return *this;

        m_notifier.broadcast(TransformNotifier::ENotificationType::TRANSFORM_DESTROYED, nullptr);

        m_position = other.m_position;
        m_rotation = other.m_rotation;
        m_scale = other.m_scale;
        m_matrix = std::move(other.m_matrix);
        m_notifier = std::move(other.m_notifier);

        if (other.m_parent != m_parent)
            setParent(other.m_parent, false);
        else
            updateWorldMatrix();

        return *this;
    }

    inline Transform& Transform::operator*=(const Transform& other)
    {
        m_matrix *= other.getWorldMatrix();
        decomposeMatrix(m_matrix, m_position, m_rotation, m_scale);
        updateWorldMatrix();

        return *this;
    }

    inline Transform Transform::operator*(const Transform& other) const
    {
        Transform result = *this;
        return result *= other;
    }

    inline Vector3 Transform::forward() const
    {
        return right().cross(up());
    }

    inline Vector3 Transform::right() const
    {
        Vector3 right = Vector3::right();
        right.rotate(m_rotation);
        return right;
    }

    inline Vector3 Transform::up() const
    {
        Vector3 up = Vector3::up();
        up.rotate(m_rotation);
        return up;
    }

    inline Vector3 Transform::back() const
    {
        return -forward();
    }

    inline Vector3 Transform::left() const
    {
        return -right();
    }

    inline Vector3 Transform::down() const
    {
        return -up();
    }

    inline Vector3 Transform::getPosition() const
    {
        return m_position;
    }

    inline Quaternion Transform::getRotation() const
    {
        return m_rotation;
    }

    inline TVector3<Radian> Transform::getEuler(const ERotationOrder rotationOrder) const
    {
        return m_rotation.toEuler(rotationOrder);
    }

    inline Vector3 Transform::getScale() const
    {
        return m_scale;
    }

    inline Matrix4x4 Transform::getMatrix() const
    {
        return m_matrix;
    }

    inline Transform& Transform::setPosition(const Vector3& position)
    {
        m_position = position;
        m_matrix = generateMatrix(m_position, m_rotation, m_scale);

        updateWorldMatrix();

        return *this;
    }

    inline Transform& Transform::setEuler(const TVector3<Radian>& euler, const ERotationOrder rotationOrder)
    {
        return setRotation(Quaternion::fromEuler(euler, rotationOrder));
    }

    inline Transform& Transform::setRotation(const Quaternion& rotation)
    {
        m_rotation = rotation;
        m_matrix = generateMatrix(m_position, m_rotation, m_scale);

        updateWorldMatrix();

        return *this;
    }

    inline Transform& Transform::setScale(const Vector3& scale)
    {
        m_scale = scale;
        m_matrix = generateMatrix(m_position, m_rotation, m_scale);

        updateWorldMatrix();

        return *this;
    }

    inline Transform& Transform::setAll(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
    {
        m_position = position;
        m_rotation = rotation;
        m_scale = scale;
        m_matrix = generateMatrix(m_position, m_rotation, m_scale);

        updateWorldMatrix();

        return *this;
    }

    inline Transform& Transform::setMatrix(const Matrix4x4& matrix)
    {
        m_matrix = matrix;
        decomposeMatrix(m_matrix, m_position, m_rotation, m_scale);

        updateWorldMatrix();

        return *this;
    }

    inline Transform& Transform::translate(const Vector3& translation)
    {
        setPosition(m_position + translation);

        return *this;
    }

    inline Transform& Transform::rotate(const TVector3<Radian>& euler, const ERotationOrder rotationOrder)
    {
        setRotation(m_rotation * Quaternion::fromEuler(euler, rotationOrder));

        return *this;
    }

    inline Transform& Transform::rotate(const Quaternion& rotation)
    {
        setRotation(m_rotation * rotation);

        return *this;
    }

    inline Transform& Transform::scale(const Vector3& scale)
    {
        setScale(m_scale * scale);

        return *this;
    }

    inline bool Transform::hasParent() const
    {
        return m_parent != nullptr;
    }

    inline const Transform* Transform::getParent() const
    {
        return m_parent;
    }

    inline Transform* Transform::getParent()
    {
        return m_parent;
    }

    inline bool Transform::setParent(Transform* parent, const bool keepWorld)
    {
        if (m_parent == parent)
            return false;

        if (m_parent && m_notificationHandlerId != 0)
            m_parent->m_notifier.unsubscribe(m_notificationHandlerId);

        m_parent = parent;

        if (m_parent)
        {
            auto handlerLambda = [this](const TransformNotifier::ENotificationType notificationType, Transform* newParent)
            {
                notificationHandler(notificationType, newParent);
            };

            m_notificationHandlerId = m_parent->m_notifier.subscribe(handlerLambda);
        }
        else
        {
            m_notificationHandlerId = 0;
        }

        if (keepWorld)
            updateLocalMatrix();
        else
            updateWorldMatrix();

        return true;
    }

    inline Vector3 Transform::worldForward() const
    {
        return worldRight().cross(worldUp());
    }

    inline Vector3 Transform::worldRight() const
    {
        Vector3 right = Vector3::right();
        right.rotate(m_worldRotation);
        return right;
    }

    inline Vector3 Transform::worldUp() const
    {
        Vector3 up = Vector3::up();
        up.rotate(m_worldRotation);
        return up;
    }

    inline Vector3 Transform::worldBack() const
    {
        return -worldForward();
    }

    inline Vector3 Transform::worldLeft() const
    {
        return -worldRight();
    }

    inline Vector3 Transform::worldDown() const
    {
        return -worldUp();
    }

    inline Vector3 Transform::getWorldPosition() const
    {
        return m_worldPosition;
    }

    inline Quaternion Transform::getWorldRotation() const
    {
        return m_worldRotation;
    }

    inline TVector3<Radian> Transform::getWorldEuler(const ERotationOrder rotationOrder) const
    {
        return m_worldRotation.toEuler(rotationOrder);
    }

    inline Vector3 Transform::getWorldScale() const
    {
        return m_worldScale;
    }

    inline Matrix4x4 Transform::getWorldMatrix() const
    {
        return m_worldMatrix;
    }

    inline Transform& Transform::setWorldPosition(const Vector3& position)
    {
        m_worldPosition = position;
        m_worldMatrix = generateMatrix(m_worldPosition, m_worldRotation, m_worldScale);

        updateLocalMatrix();

        return *this;
    }

    inline Transform& Transform::setWorldEuler(const TVector3<Radian>& euler, const ERotationOrder rotationOrder)
    {
        return setWorldRotation(Quaternion::fromEuler(euler, rotationOrder));
    }

    inline Transform& Transform::setWorldRotation(const Quaternion& rotation)
    {
        m_worldRotation = rotation;
        m_worldMatrix = generateMatrix(m_worldPosition, m_worldRotation, m_worldScale);

        updateLocalMatrix();

        return *this;
    }

    inline Transform& Transform::setWorldScale(const Vector3& scale)
    {
        m_worldScale = scale;
        m_worldMatrix = generateMatrix(m_worldPosition, m_worldRotation, m_worldScale);

        updateLocalMatrix();

        return *this;
    }

    inline Transform& Transform::setAllWorld(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
    {
        m_worldPosition = position;
        m_worldRotation = rotation;
        m_worldScale = scale;
        m_worldMatrix = generateMatrix(m_worldPosition, m_worldRotation, m_worldScale);

        updateLocalMatrix();

        return *this;
    }

    inline Transform& Transform::setWorldMatrix(const Matrix4x4& matrix)
    {
        m_worldMatrix = matrix;
        decomposeMatrix(m_worldMatrix, m_worldPosition, m_worldRotation, m_worldScale);

        updateLocalMatrix();

        return *this;
    }

    inline Transform& Transform::worldTranslate(const Vector3& translation)
    {
        setWorldPosition(m_worldPosition + translation);

        return *this;
    }

    inline Transform& Transform::worldRotate(const TVector3<Radian>& euler, const ERotationOrder rotationOrder)
    {
        setWorldRotation(m_worldRotation * Quaternion::fromEuler(euler, rotationOrder));

        return *this;
    }

    inline Transform& Transform::worldRotate(const Quaternion& rotation)
    {
        setWorldRotation(m_worldRotation * rotation);

        return *this;
    }

    inline Transform& Transform::worldScale(const Vector3& scale)
    {
        setWorldScale(m_worldScale * scale);

        return *this;
    }

    inline void Transform::invert()
    {
        m_position *= -1.f;
        m_rotation = m_worldRotation.inverse();
        m_scale = { 1.f / m_scale.m_x, 1.f / m_scale.m_y, 1.f / m_scale.m_z };
        m_matrix = generateMatrix(m_position, m_rotation, m_scale);

        updateWorldMatrix();
    }

    inline Transform Transform::inverse() const
    {
        Transform tmp = *this;
        tmp.invert();
        return tmp;
    }

    inline void Transform::invertWorld()
    {
        m_worldPosition *= -1.f;
        m_worldRotation = m_worldRotation.inverse();
        m_worldScale = { 1.f / m_worldScale.m_x, 1.f / m_worldScale.m_y, 1.f / m_worldScale.m_z };
        m_worldMatrix = generateMatrix(m_worldPosition, m_worldRotation, m_worldScale);

        updateLocalMatrix();
    }

    inline Transform Transform::inverseWorld() const
    {
        Transform tmp = *this;
        tmp.invertWorld();
        return tmp;
    }

    inline Transform Transform::interpolate(Transform from, const Transform& to, const float t)
    {
        from.m_position = lerp(from.m_position, to.m_position, t);
        from.m_rotation = slerp(from.m_rotation, to.m_rotation, t);
        from.m_scale = lerp(from.m_scale, to.m_scale, t);
        from.m_matrix = generateMatrix(from.m_position, from.m_rotation, from.m_scale);

        from.updateWorldMatrix();

        return from;
    }

    inline Transform Transform::interpolateWorld(Transform from, const Transform& to, const float t)
    {
        from.m_worldPosition = lerp(from.m_worldPosition, to.m_worldPosition, t);
        from.m_worldRotation = slerp(from.m_worldRotation, to.m_worldRotation, t);
        from.m_worldScale = lerp(from.m_worldScale, to.m_worldScale, t);
        from.m_worldMatrix = generateMatrix(from.m_worldPosition, from.m_worldRotation, from.m_worldScale);

        from.updateLocalMatrix();

        return from;
    }

    inline Matrix4x4 Transform::generateMatrix(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
    {
        return translation(position)
            * LibMath::rotation(rotation)
            * scaling(scale);
    }

    inline void Transform::decomposeMatrix(const Matrix4x4& matrix, Vector3& position, Quaternion& rotation, Vector3& scale)
    {
        position.m_x = matrix(0, 3);
        position.m_y = matrix(1, 3);
        position.m_z = matrix(2, 3);

        Vector3 columns[3] =
        {
            { matrix(0, 0), matrix(1, 0), matrix(2, 0) },
            { matrix(0, 1), matrix(1, 1), matrix(2, 1) },
            { matrix(0, 2), matrix(1, 2), matrix(2, 2) },
        };

        scale.m_x = columns[0].magnitude();
        scale.m_y = columns[1].magnitude();
        scale.m_z = columns[2].magnitude();

        if (scale.m_x > 0)
            columns[0] /= scale.m_x;

        if (scale.m_y > 0)
            columns[1] /= scale.m_y;

        if (scale.m_z > 0)
            columns[2] /= scale.m_z;

        Matrix3 rotationMatrix;

        rotationMatrix(0, 0) = columns[0].m_x;
        rotationMatrix(1, 0) = columns[0].m_y;
        rotationMatrix(2, 0) = columns[0].m_z;
        rotationMatrix(0, 1) = columns[1].m_x;
        rotationMatrix(1, 1) = columns[1].m_y;
        rotationMatrix(2, 1) = columns[1].m_z;
        rotationMatrix(0, 2) = columns[2].m_x;
        rotationMatrix(1, 2) = columns[2].m_y;
        rotationMatrix(2, 2) = columns[2].m_z;

        rotation = Quaternion(rotationMatrix);
    }

    inline void Transform::onChange()
    {
        m_notifier.broadcast(TransformNotifier::ENotificationType::TRANSFORM_CHANGED, this);
    }

    inline void Transform::notificationHandler(const TransformNotifier::ENotificationType notificationType, Transform* newParent)
    {
        m_parent = newParent;

        switch (notificationType)
        {
        case TransformNotifier::ENotificationType::TRANSFORM_CHANGED:
            updateWorldMatrix();
            break;
        case TransformNotifier::ENotificationType::TRANSFORM_DESTROYED:
            updateLocalMatrix();
            m_notificationHandlerId = 0;
            break;
        default: ;
        }
    }

    inline void Transform::updateLocalMatrix()
    {
        m_matrix = m_parent ? m_parent->m_worldMatrix.inverse() * m_worldMatrix : m_worldMatrix;
        decomposeMatrix(m_matrix, m_position, m_rotation, m_scale);

        onChange();
    }

    inline void Transform::updateWorldMatrix()
    {
        m_worldMatrix = m_parent ? m_parent->m_worldMatrix * m_matrix : m_matrix;
        decomposeMatrix(m_worldMatrix, m_worldPosition, m_worldRotation, m_worldScale);

        onChange();
    }
}

#endif // !__LIBMATH__TRANSFORM_INL__
