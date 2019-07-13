// Created By : Rahil Agrawal

#include "assignments/ev/euclidean_vector.h"

#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm
#include <cassert>
#include <cmath>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Constructors

EuclideanVector::EuclideanVector(int i) : EuclideanVector::EuclideanVector(i, 0.0) {}

EuclideanVector::EuclideanVector(int i, double d) : vectorLength_{i} {
  magnitudes_ = std::make_unique<double[]>(i);
  for (int k = 0; k < i; k++)
    magnitudes_[k] = d;
}

EuclideanVector::EuclideanVector(std::vector<double>::const_iterator begin,
                                 std::vector<double>::const_iterator end) {
  vectorLength_ = end - begin;
  magnitudes_ = std::make_unique<double[]>(vectorLength_);
  std::copy(begin, end, magnitudes_.get());
}

EuclideanVector::EuclideanVector(const EuclideanVector& e) : vectorLength_{e.vectorLength_} {
  magnitudes_ = std::make_unique<double[]>(vectorLength_);
  std::copy(e.magnitudes_.get(), e.magnitudes_.get() + e.vectorLength_, magnitudes_.get());
}

EuclideanVector::EuclideanVector(EuclideanVector&& e)
  : magnitudes_{std::move(e.magnitudes_)}, vectorLength_{e.vectorLength_} {
  e.vectorLength_ = 0;
}

// Operations

EuclideanVector& EuclideanVector::operator=(const EuclideanVector& e) noexcept {
  vectorLength_ = e.vectorLength_;
  magnitudes_.release();
  magnitudes_ = std::make_unique<double[]>(vectorLength_);
  std::copy(e.magnitudes_.get(), e.magnitudes_.get() + e.vectorLength_, magnitudes_.get());
  return *this;
}

EuclideanVector& EuclideanVector::operator=(EuclideanVector&& e) noexcept {
  vectorLength_ = e.vectorLength_;
  e.vectorLength_ = 0;
  magnitudes_.release();
  magnitudes_ = std::move(e.magnitudes_);
  return *this;
}

double& EuclideanVector::operator[](const int index) noexcept {
  assert(index >= 0 && index < vectorLength_);

  return magnitudes_[index];
}

double EuclideanVector::operator[](const int index) const noexcept {
  assert(index >= 0 && index < vectorLength_);

  return magnitudes_[index];
}

EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& v) {
  if (vectorLength_ != v.vectorLength_) {
    std::ostringstream ss;
    ss << "Dimensions of LHS(" << vectorLength_ << ") and RHS(" << v.vectorLength_
       << ") do not match";
    throw EuclideanVectorError(ss.str());
  }

  for (int i = 0; i < vectorLength_; i++)
    magnitudes_[i] += v.magnitudes_[i];

  return *this;
}

EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& v) {
  if (vectorLength_ != v.vectorLength_) {
    std::ostringstream ss;
    ss << "Dimensions of LHS(" << vectorLength_ << ") and RHS(" << v.vectorLength_
       << ") do not match";
    throw EuclideanVectorError(ss.str());
  }

  for (int i = 0; i < vectorLength_; i++)
    magnitudes_[i] -= v.magnitudes_[i];

  return *this;
}

EuclideanVector& EuclideanVector::operator*=(const double d) noexcept {
  for (int i = 0; i < vectorLength_; i++)
    magnitudes_[i] *= d;

  return *this;
}

EuclideanVector& EuclideanVector::operator/=(const double d) {
  if (d == 0)
    throw EuclideanVectorError("Invalid vector division by 0");

  for (int i = 0; i < vectorLength_; i++)
    magnitudes_[i] /= d;

  return *this;
}

EuclideanVector::operator std::vector<double>() const noexcept {
  std::vector<double> mags;
  for (int i = 0; i < vectorLength_; i++)
    mags.push_back(magnitudes_[i]);

  return mags;
}

EuclideanVector::operator std::list<double>() const noexcept {
  std::list<double> mags;
  for (int i = 0; i < vectorLength_; i++)
    mags.push_back(magnitudes_[i]);

  return mags;
}

// Methods
double& EuclideanVector::at(int index) {
  if (index < 0 || index >= vectorLength_) {
    std::ostringstream ss;
    ss << "Index " << index << " is not valid for this EuclideanVector object";
    throw EuclideanVectorError(ss.str());
  }

  return magnitudes_[index];
}

double EuclideanVector::at(int index) const {
  if (index < 0 || index >= vectorLength_) {
    std::ostringstream ss;
    ss << "Index " << index << " is not valid for this EuclideanVector object";
    throw EuclideanVectorError(ss.str());
  }

  return magnitudes_[index];
}

int EuclideanVector::GetNumDimensions() const noexcept {
  return vectorLength_;
}
double EuclideanVector::GetEuclideanNorm() const {
  if (vectorLength_ == 0)
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a norm");

  double norm;
  for (int i = 0; i < vectorLength_; i++) {
    norm += pow(magnitudes_[i], 2);
  }

  return std::sqrt(norm);
}
EuclideanVector EuclideanVector::CreateUnitVector() const {
  if (GetNumDimensions() == 0)
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a unit vector");
  double norm = GetEuclideanNorm();
  if (norm == 0.0)
    throw EuclideanVectorError(
        "EuclideanVector with euclidean normal of 0 does not have a unit vector");

  std::vector<double> mags;
  for (int i = 0; i < vectorLength_; i++)
    mags.push_back(magnitudes_[i] / norm);

  return EuclideanVector(mags.begin(), mags.end());
}
