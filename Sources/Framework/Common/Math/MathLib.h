#pragma once

#include "Eigen3/include/eigen3/Eigen/Dense"
#include "Eigen3/include/eigen3/Eigen/Geometry"

using namespace Eigen;

namespace ProjectEngine
{
    const float PI = 3.141592f;

<<<<<<< HEAD
//    typedef Eigen::Vector2f Vector2f;
//    typedef Eigen::Vector3f Vector3f;
//    typedef Eigen::Vector4f Vector4f;
//
//    typedef Eigen::Matrix4f Matrix4f;
//    typedef Eigen::Matrix3f Matrix3f;

    inline Matrix4f BuildViewLookatRH(const Vector3f& eye, const Vector3f& lookat, const Vector3f& up) {
        Vector3f xaxis, yaxis, zaxis;
        float tmp1, tmp2, tmp3;
        zaxis = eye - lookat;
        zaxis.normalize();

        xaxis = up.cross(zaxis);
        xaxis.normalize();

        yaxis = zaxis.cross(xaxis);

        tmp1 = -1 * xaxis.dot(eye);
        tmp2 = -1 * yaxis.dot(eye);
        tmp3 = -1 * zaxis.dot(eye);

        Matrix4f tmp;
        tmp <<
            xaxis.x(), xaxis.y(), xaxis.z(), tmp1,
                yaxis.x(), yaxis.y(), yaxis.z(), tmp2,
                zaxis.x(), zaxis.y(), zaxis.z(), tmp3,
                0, 0, 0, 1.0f;
        return tmp;
    }

    inline Matrix4f BuildViewLookatLH(const Vector3f& eye, const Vector3f& lookat, const Vector3f& up) {
        Vector3f xaxis, yaxis, zaxis;
        float tmp1, tmp2, tmp3;
        zaxis = lookat - eye;
        zaxis.normalize();

        xaxis = up.cross(zaxis);
        xaxis.normalize();

        yaxis = zaxis.cross(xaxis);

        tmp1 = -1 * xaxis.dot(eye);
        tmp2 = -1 * yaxis.dot(eye);
        tmp3 = -1 * zaxis.dot(eye);

        Matrix4f tmp;
        tmp <<
            xaxis.x(), xaxis.y(), xaxis.z(), tmp1,
                yaxis.x(), yaxis.y(), yaxis.z(), tmp2,
                zaxis.x(), zaxis.y(), zaxis.z(), tmp3,
                0, 0, 0, 1.0f;
        return tmp;
    }

    inline Matrix4f BuildPerspectiveFovRH(const float fov, const float aspect, const float zn, const float zf) {
=======
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
>>>>>>> remotes/origin/Branch_Rebase
        auto yscale = 1.0f / tanf(fov * 0.5f);
        auto xscale = yscale / aspect;

        Matrix4f tmp;
<<<<<<< HEAD
        tmp <<
            xscale, 0.0f, 0.0f, 0.0f,
                0.0f, yscale, 0.0f, 0.0f,
                0.0f, 0.0f, zf / (zn - zf), (zn * zf) / (zn - zf),
                0.0f, 0.0f, -1.0f, 0.0f;
=======
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
>>>>>>> remotes/origin/Branch_Rebase

        return tmp;
    }

<<<<<<< HEAD
    inline Matrix4f BuildPerspectiveFovLH(const float fov, const float aspect, const float zn, const float zf) {
        auto yscale = 1.0f / tanf(fov * 0.5f);
        auto xscale = yscale / aspect;

        Matrix4f tmp;
        tmp <<
            xscale, 0.0f, 0.0f, 0.0f,
                0.0f, yscale, 0.0f, 0.0f,
                0.0f, 0.0f, zf / (zf - zn), (-zn * zf) / (zf - zn),
                0.0f, 0.0f, 1.0f, 0.0f;
        return tmp;
    }

    inline Matrix4f BuildOrthoRH(const float width, const float height, const float zn, const float zf) {
        Matrix4f tmp;
        tmp <<
            2 / width, 0.0f, 0.0f, 0.0f,
                0.0f, 2 / height, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f / (zn - zf), zn / (zn - zf),
                0.0f, 0.0f, 0.0f, 1.0f;
        return tmp;
    }

    inline Matrix4f BuildOrthoLH(const float width, const float height, const float zn, const float zf) {
        Matrix4f tmp;
        tmp <<
            2 / width, 0.0f, 0.0f, 0.0f,
                0.0f, 2 / height, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f / (zf - zn), -zn / (zf - zn),
                0.0f, 0.0f, 0.0f, 1.0f;
        return tmp;
    }

    inline Matrix4f BuildTranslationMatrix(const Vector3f& offset) {
        Matrix4f tmp;
        tmp <<
            1.0f, 0.0f, 0.0f, offset.x(),
                0.0f, 1.0f, 0.0f, offset.y(),
                0.0f, 0.0f, 1.0f, offset.z(),
                0.0f, 0.0f, 0.0f, 1.0f;
        return tmp;
    }

    inline Matrix4f BuildScaleMatrix(const Vector3f& scale) {
        Matrix4f tmp;
        tmp <<
            scale.x(), 0.0f, 0.0f, 0.0f,
                0.0f, scale.y(), 0.0f, 0.0f,
                0.0f, 0.0f, scale.z(), 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f;
        return tmp;
    }

    inline Matrix4f BuildRotationMatrix(const Vector3f& axis, const float radio) {
        Matrix4f tmp;
        float c = cosf(radio), s = sinf(radio), one_minus_c = 1.0f - c;
        tmp << c + axis.x() * axis.x() * one_minus_c,
                axis.x() * axis.y() * one_minus_c - axis.z() * s,
                axis.x() * axis.z() * one_minus_c + axis.y() * s,
                0.0f,
                axis.x() * axis.y() * one_minus_c + axis.z() * s,
                c + axis.y() * axis.y() * one_minus_c,
                axis.y() * axis.z() * one_minus_c - axis.x() * s,
                0.0f,
                axis.x() * axis.z() * one_minus_c - axis.y() * s,
                axis.y() * axis.z() * one_minus_c + axis.x() * s,
                c + axis.z() * axis.z() * one_minus_c,
                0.0f,
                0.0f,
                0.0f,
                0.0f,
                1.0f;
        return tmp;
    }

    inline Matrix4f BuildRotationMatrix(const float rx, const float ry, const float rz) {

=======
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
>>>>>>> remotes/origin/Branch_Rebase
    }
}
