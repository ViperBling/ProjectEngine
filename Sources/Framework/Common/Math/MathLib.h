#pragma once

#include "Eigen3/include/eigen3/Eigen/Dense"
#include "Eigen3/include/eigen3/Eigen/Geometry"

using namespace Eigen;

namespace ProjectEngine
{
    const float PI = 3.141592f;

//    typedef Eigen::Vector2f Vector2f;
//    typedef Eigen::Vector3f Vector3f;
//    typedef Eigen::Vector4f Vector4f;
//
//    typedef Eigen::Matrix4f Matrix4f;
//    typedef Eigen::Matrix3f Matrix3f;

    inline Matrix4f BuildViewLookatRH(const Vector3f& eye, const Vector3f& lookAt, const Vector3f& up)
    {
        Vector3f xAxis, yAxis, zAxis;
        float tmp1, tmp2, tmp3;
        zAxis = eye - lookAt;
        zAxis.normalize();

        xAxis = up.cross(zAxis);
        xAxis.normalize();

        yAxis = zAxis.cross(xAxis);

        tmp1 = -1 * xAxis.dot(eye);
        tmp2 = -1 * yAxis.dot(eye);
        tmp3 = -1 * zAxis.dot(eye);

        Matrix4f ret;
        ret <<
            xAxis.x(), xAxis.y(), xAxis.z(), tmp1,
            yAxis.x(), yAxis.y(), yAxis.z(), tmp2,
            zAxis.x(), zAxis.y(), zAxis.z(), tmp3,
            0, 0, 0, 1.0f;
        return ret;
    }

    inline Matrix4f BuildViewLookatLH(const Vector3f& eye, const Vector3f& lookAt, const Vector3f& up)
    {
        Vector3f xAxis, yAxis, zAxis;
        float tmp1, tmp2, tmp3;
        zAxis = lookAt - eye;
        zAxis.normalize();

        xAxis = up.cross(zAxis);
        xAxis.normalize();

        yAxis = zAxis.cross(xAxis);

        tmp1 = -1 * xAxis.dot(eye);
        tmp2 = -1 * yAxis.dot(eye);
        tmp3 = -1 * zAxis.dot(eye);

        Matrix4f ret;
        ret <<
            xAxis.x(), xAxis.y(), xAxis.z(), tmp1,
            yAxis.x(), yAxis.y(), yAxis.z(), tmp2,
            zAxis.x(), zAxis.y(), zAxis.z(), tmp3,
            0, 0, 0, 1.0f;
        return ret;
    }

    inline Matrix4f BuildPerspectiveFovRH(const float fov, const float aspect, const float zN, const float zF)
    {
        float yScale = 1.f / tanf(fov * 0.5f);
        float xScale = yScale / aspect;

        Matrix4f result;
        result <<
            xScale, 0.0f, 0.0f, 0.0f,
            0.0f, yScale, 0.0f, 0.0f,
            0.0f, 0.0f, zF / (zN - zF), (zN * zF) / (zN - zF),
            0.0f, 0.0f, -1.0f, 0.0f;

        return result;
    }

    inline Matrix4f BuildPerspectiveFovLH(const float fov, const float aspect, const float zN, const float zF)
    {
        float yScale = 1.f / tanf(fov * 0.5f);
        float xScale = yScale / aspect;

        Matrix4f result;
        result <<
               xScale, 0.0f, 0.0f, 0.0f,
                0.0f, yScale, 0.0f, 0.0f,
                0.0f, 0.0f, zF / (zF - zN), (-zN * zF) / (zF - zN),
                0.0f, 0.0f, 1.0f, 0.0f;

        return result;
    }

    inline Matrix4f BuildOrthoRH(const float width, const float height, const float zN, const float zF)
    {
        Matrix4f result;
        result <<
            2 / width, 0.0f, 0.0f, 0.0f,
                0.0f, 2 / height, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f / (zN - zF), zN / (zN - zF),
                0.0f, 0.0f, 0.0f, 1.0f;
        return result;
    }

    inline Matrix4f BuildOrthoLH(const float width, const float height, const float zN, const float zF)
    {
        Matrix4f result;
        result <<
            2 / width, 0.0f, 0.0f, 0.0f,
                0.0f, 2 / height, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f / (zF - zN), -zN / (zF - zN),
                0.0f, 0.0f, 0.0f, 1.0f;
        return result;
    }
}
