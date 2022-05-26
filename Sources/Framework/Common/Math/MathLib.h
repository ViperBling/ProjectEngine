#pragma once

#include "Eigen3/include/eigen3/Eigen/Dense"
#include "Eigen3/include/eigen3/Eigen/Geometry"

using namespace Eigen;

namespace ProjectEngine
{
    const float PI = 3.141592f;

    inline Matrix4f BuildViewLookat(const Vector3f& eye, const Vector3f& lookat, const Vector3f& up, bool leftHand) {
        Vector3f xAxis, yAxis, zAxis;
        float tmp1, tmp2, tmp3;

        if (leftHand) {
            zAxis = lookat - eye;
        } else {
            zAxis = eye - lookat;
        }

        zAxis.normalize();

        xAxis = up.cross(zAxis).normalized();

        yAxis = zAxis.cross(xAxis);

        tmp1 = -xAxis.dot(eye);
        tmp2 = -yAxis.dot(eye);
        tmp3 = -zAxis.dot(eye);

        Matrix4f tmp;
        tmp <<
            xAxis.x(), xAxis.y(), xAxis.z(), tmp1,
            yAxis.x(), yAxis.y(), yAxis.z(), tmp2,
            zAxis.x(), zAxis.y(), zAxis.z(), tmp3,
            0,         0,         0,         1.0f;

        return tmp;
    }

    inline Matrix4f BuildPerspectiveFov(const float fov, const float aspect, const float zn, const float zf, bool leftHand)
    {
        auto yscale = 1.0f / tanf(fov * 0.5f);
        auto xscale = yscale / aspect;

        Matrix4f tmp;
        if (leftHand) {
            tmp <<
                xscale, 0.0f,   0.0f,           0.0f,
                0.0f,   yscale, 0.0f,           0.0f,
                0.0f,   0.0f,   zf / (zf - zn), (-zn * zf) / (zf - zn),
                0.0f,   0.0f,   1.0f,           0.0f;
        } else {
            tmp <<
                xscale, 0.0f,   0.0f,           0.0f,
                0.0f,   yscale, 0.0f,           0.0f,
                0.0f,   0.0f,   zf / (zn - zf), (zn * zf) / (zn - zf),
                0.0f,   0.0f,   1.0f,           0.0f;
        }

        return tmp;
    }

    inline Matrix4f BuildOrtho(const float width, const float height, const float zn, const float zf, bool leftHand)
    {
        Matrix4f tmp;
        if (leftHand) {
            tmp <<
                2 / width, 0.0f,       0.0f,             0.0f,
                0.0f,      2 / height, 0.0f,             0.0f,
                0.0f,      0.0f,       1.0f / (zf - zn), -zn / (zf - zn),
                0.0f,      0.0f,       0.0f,             1.0f;
        } else {
            tmp <<
                2 / width, 0.0f,       0.0f,             0.0f,
                0.0f,      2 / height, 0.0f,             0.0f,
                0.0f,      0.0f,       1.0f / (zn - zf), zn / (zn - zf),
                0.0f,      0.0f,       0.0f,             1.0f;
        }

        return tmp;
    }

    inline Matrix4f BuildViewLookatRH(const Vector3f& eye, const Vector3f& lookat, const Vector3f& up)
    {
        return BuildViewLookat(eye, lookat, up, false);
    }

    inline Matrix4f BuildViewLookatLH(const Vector3f& eye, const Vector3f& lookat, const Vector3f& up)
    {
        return BuildViewLookat(eye, lookat, up, true);
    }

    inline Matrix4f BuildPerspectiveFovRH(const float fov, const float aspect, const float zn, const float zf)
    {
        return BuildPerspectiveFov(fov, aspect, zn, zf, false);
    }

    inline Matrix4f BuildPerspectiveFovLH(const float fov, const float aspect, const float zn, const float zf)
    {
        return BuildPerspectiveFov(fov, aspect, zn, zf, true);
    }

    inline Matrix4f BuildOrthoRH(const float width, const float height, const float zn, const float zf)
    {
        return BuildOrtho(width, height, zn, zf, false);
    }

    inline Matrix4f BuildOrthoLH(const float width, const float height, const float zn, const float zf)
    {
        return BuildOrtho(width, height, zn, zf, true);
    }
}
