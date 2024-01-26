#ifndef __LIBMATH__TRANSFORM_H__
#define __LIBMATH__TRANSFORM_H__

#include "Interpolation.h"
#include "Quaternion.h"
#include "TransformNotifier.h"

#include "Matrix/Matrix4.h"

#include "Vector/Vector3.h"

namespace LibMath
{
    class Transform
    {
    public:
        /**
         * \brief Creates a transform with no translation, no rotation and a scale of 1
         */
        inline Transform();

        /**
         * \brief Creates a transform with the given position, rotation and scale
         * \param position The transform's initial position
         * \param angles The transform's initial angles (x = yaw, y = pitch, z = roll)
         * \param scale The transform's initial scale
         */
        inline Transform(const Vector3& position, const TVector3<Radian>& angles, const Vector3& scale);

        /**
         * \brief Creates a transform with the given position, rotation and scale
         * \param position The transform's initial position
         * \param rotation The transform's initial rotation
         * \param scale The transform's initial scale
         */
        inline Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

        /**
         * \brief Creates a transform from the given transformation matrix
         * \param matrix The transform's initial transformation matrix
         */
        explicit inline Transform(Matrix4x4 matrix);

        /**
         * \brief Creates a copy of the given transform
         * \param other The transform to copy
         */
        inline Transform(const Transform& other);

        /**
         * \brief Creates a move copy of the given transform
         * \param other The transform to move
         */
        inline Transform(Transform&& other) noexcept;

        /**
         * \brief Destroys the transform
         */
        inline virtual ~Transform();

        /**
         * \brief Copies the given transform's data into the current one
         * \param other The transform to copy
         * \return A reference to the current transform
         */
        inline Transform& operator=(const Transform& other);

        /**
         * \brief Moves the given transform's data into the current one
         * \param other The transform to move
         * \return A reference to the current transform
         */
        inline Transform& operator=(Transform&& other) noexcept;

        /**
         * \brief Applies the given transformations to the current transform
         * \param other The transform to apply to the current transform
         * \return A reference to the current transform
         */
        inline Transform& operator*=(const Transform& other);

        /**
         * \brief Applies the given transformations to the current transform
         * \param other The transform to apply to the current transform
         * \return The transformed transform
         */
        inline Transform operator*(const Transform& other) const;

        /**
         * \brief Checks whether the transform has a parent or not
         * \return True if the transform has a parent, false otherwise
         */
        inline bool hasParent() const;

        /**
         * \brief Gets the transform's parent
         * \return A pointer to the parent if it exists, nullptr otherwise
         */
        inline const Transform* getParent() const;

        /**
         * \brief Gets the transform's parent
         * \return A pointer to the parent if it exists, nullptr otherwise
         */
        inline Transform* getParent();

        /**
         * \brief Sets the transform's parent
         * \param parent The transform's new parent
         * \param keepWorld Whether the transform's world coordinates should be conserved
         * \return True if the parent changed, false otherwise
         */
        inline bool setParent(Transform* parent, bool keepWorld = true);

        /**
         * \brief Computes the transform's forward vector
         * \return The transform's forward vector
         */
        inline Vector3 forward() const;

        /**
         * \brief Computes the transform's right vector
         * \return The transform's right vector
         */
        inline Vector3 right() const;

        /**
         * \brief Computes the transform's up vector
         * \return The transform's up vector
         */
        inline Vector3 up() const;

        /**
         * \brief Computes the transform's back vector
         * \return The transform's back vector
         */
        inline Vector3 back() const;

        /**
         * \brief Computes the transform's left vector
         * \return The transform's left vector
         */
        inline Vector3 left() const;

        /**
         * \brief Computes the transform's down vector
         * \return The transform's down vector
         */
        inline Vector3 down() const;

        /**
         * \brief Gets the transform's current position
         * \return The transform's position
         */
        inline Vector3 getPosition() const;

        /**
         * \brief Gets the transform's current rotation
         * \return The transform's rotation
         */
        inline Quaternion getRotation() const;

        /**
         * \brief Gets a euler angles representation of the transform's current local rotation
         * \param rotationOrder The rotation application order
         * \return A euler angles representation of the transform's current local rotation
         */
        inline TVector3<Radian> getEuler(ERotationOrder rotationOrder) const;

        /**
         * \brief Gets the transform's current scale
         * \return The transform's scale
         */
        inline Vector3 getScale() const;

        /**
         * \brief Gets the transform's current local transformation matrix
         * \return The transform's local transformation matrix
         */
        inline Matrix4x4 getMatrix() const;

        /**
         * \brief Sets the transform's current local position
         * \param position The transform's new local position
         * \return A reference to the current transform
         */
        inline Transform& setPosition(const Vector3& position);

        /**
         * \brief Sets the transform's current local rotation
         * \param euler The transform's new local euler angles in degrees
         * \param rotationOrder The rotation application order
         * \return A reference to the current transform
         */
        inline Transform& setEuler(const TVector3<Radian>& euler, ERotationOrder rotationOrder);

        /**
         * \brief Sets the transform's current local rotation
         * \param rotation The transform's new local rotation
         * \return A reference to the current transform
         */
        inline Transform& setRotation(const Quaternion& rotation);

        /**
         * \brief Sets the transform's current local rotation
         * \param scale The transform's new local scale
         * \return A reference to the current transform
         */
        inline Transform& setScale(const Vector3& scale);

        /**
         * \brief Sets the transform's current local position, rotation and scale
         * \param position The transform's new local position
         * \param rotation The transform's new local rotation
         * \param scale The transform's new local scale
         * \return A reference to the current transform
         */
        inline Transform& setAll(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

        /**
         * \brief Sets the transform's current local matrix
         * \param matrix The transform's new local matrix
         * \return A reference to the current transform
         */
        inline Transform& setMatrix(const Matrix4x4& matrix);

        /**
         * \brief Adds the given vector to the transform's current local position
         * \param translation The translation vector to apply
         * \return A reference to the current transform
         */
        inline Transform& translate(const Vector3& translation);

        /**
         * \brief Adds the given vector to the transform's current local rotation
         * \param euler The rotation euler angles to apply
         * \param rotationOrder The rotation application order
         * \return A reference to the current transform
         */
        inline Transform& rotate(const TVector3<Radian>& euler, ERotationOrder rotationOrder);

        /**
         * \brief Applies the given rotation to the transform's current local rotation
         * \param rotation The rotation quaternion to apply
         * \return A reference to the current transform
         */
        inline Transform& rotate(const Quaternion& rotation);

        /**
         * \brief Multiplies the transform's current local scale by the given vector
         * \param scale The scaling vector to apply
         * \return A reference to the current transform
         */
        inline Transform& scale(const Vector3& scale);

        /**
         * \brief Computes the transform's forward vector
         * \return The transform's forward vector
         */
        inline Vector3 worldForward() const;

        /**
         * \brief Computes the transform's right vector
         * \return The transform's right vector
         */
        inline Vector3 worldRight() const;

        /**
         * \brief Computes the transform's up vector
         * \return The transform's up vector
         */
        inline Vector3 worldUp() const;

        /**
         * \brief Computes the transform's back vector
         * \return The transform's back vector
         */
        inline Vector3 worldBack() const;

        /**
         * \brief Computes the transform's left vector
         * \return The transform's left vector
         */
        inline Vector3 worldLeft() const;

        /**
         * \brief Computes the transform's down vector
         * \return The transform's down vector
         */
        inline Vector3 worldDown() const;

        /**
         * \brief Gets the transform's current global position
         * \return The transform's global position
         */
        inline Vector3 getWorldPosition() const;

        /**
         * \brief Gets the transform's current global rotation
         * \return The transform's global rotation
         */
        inline Quaternion getWorldRotation() const;

        /**
         * \brief Gets a euler angles representation of the transform's current global rotation
         * \param rotationOrder The rotation application order
         * \return A euler angles representation of the transform's current global rotation
         */
        inline TVector3<Radian> getWorldEuler(ERotationOrder rotationOrder) const;

        /**
         * \brief Gets the transform's current global scale
         * \return The transform's global scale
         */
        inline Vector3 getWorldScale() const;

        /**
         * \brief Gets the transform's current global transformation matrix
         * \return The transform's global transformation matrix
         */
        inline Matrix4x4 getWorldMatrix() const;

        /**
         * \brief Sets the transform's current global position
         * \param position The transform's new global position
         * \return A reference to the current transform
         */
        inline Transform& setWorldPosition(const Vector3& position);

        /**
         * \brief Sets the transform's current global rotation
         * \param euler The transform's new global euler angles in degrees
         * \param rotationOrder The rotation application order
         * \return A reference to the current transform
         */
        inline Transform& setWorldEuler(const TVector3<Radian>& euler, ERotationOrder rotationOrder);

        /**
         * \brief Sets the transform's current global rotation
         * \param rotation The transform's new global euler angles in degrees
         * \return A reference to the current transform
         */
        inline Transform& setWorldRotation(const Quaternion& rotation);

        /**
         * \brief Sets the transform's current global rotation
         * \param scale The transform's new global scale
         * \return A reference to the current transform
         */
        inline Transform& setWorldScale(const Vector3& scale);

        /**
         * \brief Sets the transform's current global position, rotation and scale
         * \param position The transform's new global position
         * \param rotation The transform's new global rotation
         * \param scale The transform's new global scale
         * \return A reference to the current transform
         */
        inline Transform& setAllWorld(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

        /**
         * \brief Sets the transform's current world matrix
         * \param matrix The transform's new world matrix
         * \return A reference to the current transform
         */
        inline Transform& setWorldMatrix(const Matrix4x4& matrix);

        /**
         * \brief Adds the given vector to the transform's current global position
         * \param translation The translation vector to apply
         * \return A reference to the current transform
         */
        inline Transform& worldTranslate(const Vector3& translation);

        /**
         * \brief Adds the given euler angles to the transform's current global rotation
         * \param euler The rotation euler angles to apply
         * \param rotationOrder The rotation application order
         * \return A reference to the current transform
         */
        inline Transform& worldRotate(const TVector3<Radian>& euler, ERotationOrder rotationOrder);

        /**
         * \brief Adds the given vector to the transform's current global rotation
         * \param rotation The rotation vector to apply
         * \return A reference to the current transform
         */
        inline Transform& worldRotate(const Quaternion& rotation);

        /**
         * \brief Multiplies the transform's current global scale by the given vector
         * \param scale The scaling vector to apply
         * \return A reference to the current transform
         */
        inline Transform& worldScale(const Vector3& scale);

        /**
         * \brief Inverts the transform
         */
        inline void invert();

        /**
         * \brief Computes the inverse of the transform
         * \return The resulting inverse transform
         */
        [[nodiscard]] inline Transform inverse() const;

        /**
         * \brief Inverts the transform
         */
        inline void invertWorld();

        /**
         * \brief Computes the inverse of the transform
         * \return The resulting inverse transform
         */
        [[nodiscard]] inline Transform inverseWorld() const;

        static inline Transform interpolate(Transform from, const Transform& to, const float t);

        static inline Transform interpolateWorld(Transform from, const Transform& to, const float t);

        /**
         * \brief Generates a transformation matrix from the given position, rotation and scale
         * \param position The transform's position
         * \param rotation The transform's euler angles in degrees
         * \param scale The transform's scale
         * \return The generated transformation matrix
         */
        static inline Matrix4x4 generateMatrix(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

        /**
         * \brief Extracts the position, rotation and scale from the given transformation matrix
         * \param matrix The transformation matrix to decompose
         * \param position The vector in which the position should be extracted
         * \param rotation The quaternion in which the rotation should be extracted
         * \param scale The vector in which the scale should be extracted
         */
        static inline void decomposeMatrix(const Matrix4x4& matrix, Vector3& position, Quaternion& rotation, Vector3& scale);

    protected:
        /**
         * \brief Updates the transform's matrix
         */
        inline virtual void onChange();

        /**
        * \brief Handles parent notifications
        * \param notificationType The notification type
        * \param newParent The new parent after this event
        */
        inline virtual void notificationHandler(TransformNotifier::ENotificationType notificationType, Transform* newParent);

    private:
        Vector3    m_position;
        Quaternion m_rotation;
        Vector3    m_scale;

        Vector3    m_worldPosition;
        Quaternion m_worldRotation;
        Vector3    m_worldScale;

        Matrix4x4 m_matrix;
        Matrix4x4 m_worldMatrix;

        Transform* m_parent;

        TransformNotifier             m_notifier;
        TransformNotifier::ListenerId m_notificationHandlerId = 0;

        /**
         * \brief Updates the local transformation data based on the current global transform
         */
        inline void updateLocalMatrix();

        /**
         * \brief Updates the global transformation data based on the current local transform
         */
        inline void updateWorldMatrix();
    };
}

#include "Transform.inl"

#endif // !__LIBMATH__TRANSFORM_H__
