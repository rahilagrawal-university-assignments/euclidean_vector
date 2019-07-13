// Created By : Rahil Agrawal

#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <exception>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {
 public:
  // Constructors
  explicit EuclideanVector(int);
  EuclideanVector(int, double);
  EuclideanVector(std::vector<double>::const_iterator, std::vector<double>::const_iterator);
  EuclideanVector(const EuclideanVector&);
  // Move Constructor will reduce the number of dimensions of the given vector to 0
  EuclideanVector(EuclideanVector&&);

  // Friends

  friend bool operator==(const EuclideanVector& u, const EuclideanVector& v) noexcept {
    if (u.vectorLength_ != v.vectorLength_)
      return false;
    for (int i = 0; i < u.vectorLength_; i++) {
      if (u.magnitudes_[i] != v.magnitudes_[i])
        return false;
    }
    return true;
  }

  friend bool operator!=(const EuclideanVector& u, const EuclideanVector& v) noexcept {
    return !(operator==(u, v));
  }

  friend EuclideanVector operator+(const EuclideanVector& u, const EuclideanVector& v) {
    if (u.vectorLength_ != v.vectorLength_) {
      std::ostringstream ss;
      ss << "Dimensions of LHS(" << u.vectorLength_ << ") and RHS(" << v.vectorLength_
         << ") do not match";
      throw EuclideanVectorError(ss.str());
    }

    std::vector<double> mags;
    for (int i = 0; i < u.vectorLength_; i++)
      mags.push_back(u.magnitudes_[i] + v.magnitudes_[i]);

    return EuclideanVector(mags.begin(), mags.end());
  }

  friend EuclideanVector operator-(const EuclideanVector& u, const EuclideanVector& v) {
    if (u.vectorLength_ != v.vectorLength_) {
      std::ostringstream ss;
      ss << "Dimensions of LHS(" << u.vectorLength_ << ") and RHS(" << v.vectorLength_
         << ") do not match";
      throw EuclideanVectorError(ss.str());
    }

    std::vector<double> mags;
    for (int i = 0; i < u.vectorLength_; i++)
      mags.push_back(u.magnitudes_[i] - v.magnitudes_[i]);

    return EuclideanVector(mags.begin(), mags.end());
  }

  friend double operator*(const EuclideanVector& u, const EuclideanVector& v) {
    if (u.vectorLength_ != v.vectorLength_) {
      std::ostringstream ss;
      ss << "Dimensions of LHS(" << u.vectorLength_ << ") and RHS(" << v.vectorLength_
         << ") do not match";
      throw EuclideanVectorError(ss.str());
    }

    double dotProd;
    for (int i = 0; i < u.vectorLength_; i++)
      dotProd += u.magnitudes_[i] * v.magnitudes_[i];

    return dotProd;
  }

  friend EuclideanVector operator*(const EuclideanVector& u, const double d) noexcept {
    std::vector<double> mags;
    for (int i = 0; i < u.vectorLength_; i++)
      mags.push_back(u.magnitudes_[i] * d);

    return EuclideanVector(mags.begin(), mags.end());
  }

  friend EuclideanVector operator*(double d, const EuclideanVector& u) noexcept {
    return operator*(u, d);
  }

  friend EuclideanVector operator/(const EuclideanVector& u, const double d) {
    if (d == 0)
      throw EuclideanVectorError("Invalid vector division by 0");

    std::vector<double> mags;
    for (int i = 0; i < u.vectorLength_; i++)
      mags.push_back(u.magnitudes_[i] / d);

    return EuclideanVector(mags.begin(), mags.end());
  }

  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) noexcept {
    os << "[";
    if (!(v.vectorLength_ == 0)) {
      for (auto i = 0; i < v.vectorLength_ - 1; i++)
        os << v.magnitudes_[i] << " ";
      os << v.magnitudes_[v.vectorLength_ - 1];
    }
    os << "]";
    return os;
  }

  // Operations
  EuclideanVector& operator=(const EuclideanVector&) noexcept;
  // Move Assignment will reduce the number of dimensions of the given vector to 0
  EuclideanVector& operator=(EuclideanVector&&) noexcept;
  double& operator[](const int) noexcept;
  double operator[](const int) const noexcept;
  EuclideanVector& operator+=(const EuclideanVector&);
  EuclideanVector& operator-=(const EuclideanVector&);
  EuclideanVector& operator*=(const double) noexcept;
  EuclideanVector& operator/=(const double);
  explicit operator std::vector<double>() const noexcept;
  explicit operator std::list<double>() const noexcept;

  // Methods
  double& at(int);
  double at(int) const;
  int GetNumDimensions() const noexcept;
  double GetEuclideanNorm() const;
  EuclideanVector CreateUnitVector() const;

  // Destructor
  ~EuclideanVector() = default;

 private:
  std::unique_ptr<double[]> magnitudes_;
  int vectorLength_;
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
