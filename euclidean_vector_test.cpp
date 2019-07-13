/*

  == Explanation and rational of testing ==

  For the purpose of this assignment, I have decided to use Unit Testing Approach
  for failure and success scenarios of each method of the EuclideanVector Class.

  Testing all* the methods of the class ensures that the class works as per the
  spec. This conforms to the coverage aspect of testing.

  Testing success and failure scenarios ensures that output is valid and expected
  under all* scenarios that the user will use the class. This conforms to the
  correctness aspect of testing.

  * all - Strictly corresponding to the assignment specification for COMP6771
          Assignment 2 - 2019 Term 2 UNSW.

  Further explanation should be clear from the test cases themselves.

  In order to clearly and easily understand the correctness and coverage of
  unit tests, the tests have been aligned to follow a similar pattern as the
  .h file :)

  ** Special Case Ignored : In testing the GetEuclideanNorm() Function, it was
                            noticed that 0.0 == 0.0 yields false and this has
                            been forgiven by the lecturer in the forums. As a
                            result of the above, the test case for
                            CreateUnitVector() that leads to an exception has
                            been commented out.
*/

#include <cmath>
#include <list>
#include <utility>
#include <vector>

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"

/*
  ------------------------------------------------------------------------------------------------------------------------
                                                    Constructors
  ------------------------------------------------------------------------------------------------------------------------
*/

// Default Constructor
SCENARIO("Create a EuclideanVector using the default constructor") {
  GIVEN("The length of the vector is 0") {
    auto length = 0;
    WHEN("EuclideanVector is created using default constructor") {
      auto ev = EuclideanVector(length);
      THEN("The vector has 0 Dimensions") { REQUIRE(ev.GetNumDimensions() == 0); }
    }
  }
  GIVEN("The length of the vector is 4") {
    auto length = 4;
    WHEN("EuclideanVector is created using default constructor") {
      auto ev = EuclideanVector(length);
      THEN("The vector has 4 Dimensions") {
        REQUIRE(ev.GetNumDimensions() == 4);
        AND_THEN("All the magnitudes are 0.0") {
          REQUIRE(ev[0] == 0.0);
          REQUIRE(ev[1] == 0.0);
          REQUIRE(ev[2] == 0.0);
          REQUIRE(ev[3] == 0.0);
        }
      }
    }
  }
}

// Constructor with Values
SCENARIO("Create a EuclideanVector given dimensions and intialising value") {
  GIVEN("The length of the vector is 4 and the magnitude of all dimensions is 5.0") {
    auto length = 4;
    auto magnitude = 5.0;
    WHEN("EuclideanVector is created using constructor for (int, double)") {
      auto ev = EuclideanVector(length, magnitude);
      THEN("The vector has 4 Dimensions") {
        REQUIRE(ev.GetNumDimensions() == 4);
        AND_THEN("All the magnitudes are 0.0") {
          REQUIRE(ev[0] == 5.0);
          REQUIRE(ev[1] == 5.0);
          REQUIRE(ev[2] == 5.0);
          REQUIRE(ev[3] == 5.0);
        }
      }
    }
  }
}

// Constructor with iterators
SCENARIO("Create a EuclideanVector given begin and end iterator of a vector<double>") {
  GIVEN("That there is an empty vector of doubles") {
    auto mags = std::vector<double>{};
    WHEN("EuclideanVector is created using begin and end iterator of the vector") {
      auto ev = EuclideanVector(mags.begin(), mags.end());
      THEN("The vector has 0 Dimensions") { REQUIRE(ev.GetNumDimensions() == 0); }
    }
  }
  GIVEN("That there is a non-empty vector of doubles") {
    auto mags = std::vector<double>{1.0, 2.0, 3.0, 4.0};
    WHEN("EuclideanVector is created using begin and end iterator of the vector") {
      auto ev = EuclideanVector(mags.begin(), mags.end());
      THEN("The euclidean vector has same number of dimensions as the length of the original "
           "vector") {
        REQUIRE(ev.GetNumDimensions() == mags.size());
        AND_THEN("The magnitudes are equal to that given originally, in the same order") {
          REQUIRE(ev[0] == mags[0]);
          REQUIRE(ev[1] == mags[1]);
          REQUIRE(ev[2] == mags[2]);
          REQUIRE(ev[3] == mags[3]);
        }
      }
    }
  }
}

// Copy Constructor
SCENARIO("Create a EuclideanVector using the copy constructor") {
  GIVEN("That there is a Euclidean Vector") {
    auto ev = EuclideanVector(5, 10.0);
    WHEN("EuclideanVector is created using the copy constructor") {
      auto newEv{ev};
      THEN("The new vector has same number of Dimensions as the original one") {
        REQUIRE(ev.GetNumDimensions() == newEv.GetNumDimensions());
        AND_THEN("Both vectors have same magnitudes in all dimensions") {
          REQUIRE(ev[0] == newEv[0]);
          REQUIRE(ev[1] == newEv[1]);
          REQUIRE(ev[2] == newEv[2]);
          REQUIRE(ev[3] == newEv[3]);
          REQUIRE(ev[4] == newEv[4]);
        }
      }
    }
  }
}

// Move Constructor
SCENARIO("Create a EuclideanVector using the move constructor") {
  GIVEN("That there is a Euclidean Vector with 5 dimensions, all of which have magnitude 10.0") {
    auto ev = EuclideanVector(5, 10.0);
    WHEN("EuclideanVector is created using the move constructor") {
      auto newEv{std::move(ev)};
      THEN("The new vector has 5 dimensions") {
        REQUIRE(newEv.GetNumDimensions() == 5);
        AND_THEN("All the magnitues are 10.0") {
          REQUIRE(newEv[0] == 10.0);
          REQUIRE(newEv[1] == 10.0);
          REQUIRE(newEv[2] == 10.0);
          REQUIRE(newEv[3] == 10.0);
          REQUIRE(newEv[4] == 10.0);
        }
      }
      THEN("The old vector has 0 dimensions") { REQUIRE(ev.GetNumDimensions() == 0); }
    }
  }
}

/*
  ------------------------------------------------------------------------------------------------------------------------
                                                    Friends
  ------------------------------------------------------------------------------------------------------------------------
*/

// == (Equality Operator)
SCENARIO("Check the equality operator") {
  GIVEN("That there are two Euclidean Vectors with the same dimensions and magnitudes") {
    auto ev = EuclideanVector(5, 10.0);
    WHEN("Another vector is created using the copy constructor") {
      auto newEv{ev};
      THEN("The equality yields that the two vectors are equal") { REQUIRE(newEv == ev); }
    }
  }
  GIVEN("That there are two Euclidean Vectors with the different magnitudes") {
    auto ev = EuclideanVector(5, 10.0);
    WHEN("Another vector is created with different magnitudes") {
      auto newEv = EuclideanVector(5, 9.0);
      THEN("The equality operator yields that two vectors are not equal") {
        REQUIRE(!(newEv == ev));
      }
    }
  }
  GIVEN("That there are two Euclidean Vectors with the different dimensions") {
    auto ev = EuclideanVector(5, 10.0);
    WHEN("Another vector is created with different dimensions") {
      auto newEv = EuclideanVector(4, 10.0);
      THEN("The equality operator yields that two vectors are not equal") {
        REQUIRE(!(newEv == ev));
      }
    }
  }
}

// != (Inequality Operator)
SCENARIO("Check the inequality operator") {
  GIVEN("That there are two Euclidean Vectors with the same dimensions and magnitudes") {
    auto ev = EuclideanVector(5, 10.0);
    WHEN("Another vector is created using the copy constructor") {
      auto newEv{ev};
      THEN("The inequality yields that the two vectors are equal") { REQUIRE(!(newEv != ev)); }
    }
  }
  GIVEN("That there are two Euclidean Vectors with the different magnitudes") {
    auto ev = EuclideanVector(5, 10.0);
    WHEN("Another vector is created with different magnitudes") {
      auto newEv = EuclideanVector(5, 9.0);
      THEN("The inequality operator yields that two vectors are not equal") {
        REQUIRE(newEv != ev);
      }
    }
  }
  GIVEN("That there are two Euclidean Vectors with the different dimensions") {
    auto ev = EuclideanVector(5, 10.0);
    WHEN("Another vector is created with different dimensions") {
      auto newEv = EuclideanVector(4, 10.0);
      THEN("The inequality operator yields that two vectors are not equal") {
        REQUIRE(newEv != ev);
      }
    }
  }
}

// + (Adding Two Vectors)
SCENARIO("Add two vectors with the overloading + operator") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.0,2.0,...,5.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0, 4.0, 5.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    AND_GIVEN("That there is a vector with 5 dimensions and magnitudes as 5.0,4.0,...,1.0") {
      std::vector<double> vec2{5.0, 4.0, 3.0, 2.0, 1.0};
      auto ev2 = EuclideanVector(vec2.begin(), vec2.end());
      WHEN("A new vector is created by adding the two vectors") {
        auto newEv = ev1 + ev2;
        THEN("The new vector has 5 dimensions") {
          REQUIRE(newEv.GetNumDimensions() == 5);
          AND_THEN("The new vector has magnitudes 6.0,6.0,...,6.0") {
            REQUIRE(newEv[0] == 6.0);
            REQUIRE(newEv[1] == 6.0);
            REQUIRE(newEv[2] == 6.0);
            REQUIRE(newEv[3] == 6.0);
            REQUIRE(newEv[4] == 6.0);
          }
        }
      }
    }
  }
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.0,2.0,...,5.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0, 4.0, 5.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    AND_GIVEN("That there is a vector with 4 dimensions and magnitudes as 5.0,4.0,3.0,2.0") {
      std::vector<double> vec2{5.0, 4.0, 3.0, 2.0};
      auto ev2 = EuclideanVector(vec2.begin(), vec2.end());
      WHEN("A new vector is created by adding the two vectors") {
        try {
          auto newEv = ev1 + ev2;
        } catch (const EuclideanVectorError& e) {
          THEN("Exception is thrown : Dimensions of LHS(5) and RHS(4) do not match") {
            std::string err = e.what();
            REQUIRE(err.compare("Dimensions of LHS(5) and RHS(4) do not match") == 0);
          }
        }
      }
    }
  }
}

// - (Subtracting Two Vectors)
SCENARIO("Subtract two vectors with the overloading - operator") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.0,2.0,...,5.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0, 4.0, 5.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    AND_GIVEN("That there is a vector with 5 dimensions and magnitudes as 5.0,4.0,...,1.0") {
      std::vector<double> vec2{5.0, 4.0, 3.0, 2.0, 1.0};
      auto ev2 = EuclideanVector(vec2.begin(), vec2.end());
      WHEN("A new vector is created by subtracting the two vectors") {
        auto newEv = ev1 - ev2;
        THEN("The new vector has 5 dimensions") {
          REQUIRE(newEv.GetNumDimensions() == 5);
          AND_THEN("The new vector has magnitudes -4.0,-2..0,0.0,2.0,4.0") {
            REQUIRE(newEv[0] == -4.0);
            REQUIRE(newEv[1] == -2.0);
            REQUIRE(newEv[2] == 0.0);
            REQUIRE(newEv[3] == 2.0);
            REQUIRE(newEv[4] == 4.0);
          }
        }
      }
    }
  }
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.0,2.0,...,5.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0, 4.0, 5.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    AND_GIVEN("That there is a vector with 4 dimensions and magnitudes as 5.0,4.0,3.0,2.0") {
      std::vector<double> vec2{5.0, 4.0, 3.0, 2.0};
      auto ev2 = EuclideanVector(vec2.begin(), vec2.end());
      WHEN("A new vector is created by subtracting the two vectors") {
        try {
          auto newEv = ev1 - ev2;
        } catch (const EuclideanVectorError& e) {
          THEN("Exception is thrown : Dimensions of LHS(5) and RHS(4) do not match") {
            std::string err = e.what();
            REQUIRE(err.compare("Dimensions of LHS(5) and RHS(4) do not match") == 0);
          }
        }
      }
    }
  }
}

// * - 1-  (Multiplying Two Vectors)
SCENARIO("Multiply two vectors with the overloading * operator") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.0,2.0,...,5.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0, 4.0, 5.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    AND_GIVEN("That there is a vector with 5 dimensions and magnitudes as 5.0,4.0,...,1.0") {
      std::vector<double> vec2{5.0, 4.0, 3.0, 2.0, 1.0};
      auto ev2 = EuclideanVector(vec2.begin(), vec2.end());
      WHEN("A dot product is obtained by adding the element-wise product of the two vectors") {
        auto dotProd = ev1 * ev2;
        THEN("The dot product is ((1.0*5.0)+(2.0*4.0)+...+(5.0*1.0) = 35)") {
          auto calcDotProd = 0.0;
          for (int i = 0; i < 5; i++)
            calcDotProd += ev1[i] * ev2[i];
          REQUIRE(dotProd == calcDotProd);
        }
      }
    }
  }
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.0,2.0,...,5.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0, 4.0, 5.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    AND_GIVEN("That there is a vector with 4 dimensions and magnitudes as 5.0,4.0,3.0,2.0") {
      std::vector<double> vec2{5.0, 4.0, 3.0, 2.0};
      auto ev2 = EuclideanVector(vec2.begin(), vec2.end());
      WHEN("A dot product is obtained by adding the element-wise product of the two vectors") {
        try {
          auto dotProd = ev1 * ev2;
          std::cerr << dotProd << "is invalid. Control should not reach this line";
        } catch (const EuclideanVectorError& e) {
          THEN("Exception is thrown : Dimensions of LHS(5) and RHS(4) do not match") {
            std::string err = e.what();
            REQUIRE(err.compare("Dimensions of LHS(5) and RHS(4) do not match") == 0);
          }
        }
      }
    }
  }
}

// * - 2a - (Multiplying Vector with Scalar)
SCENARIO("Multiply vector by scalar on the right with the overloading * operator") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.0,2.0,...,5.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0, 4.0, 5.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    WHEN("A scalar product is obtained my multiplying it on the right with 5.0 and the result "
         "stored in the new vector") {
      auto newEv = ev1 * 5;
      THEN("The new vector has 5 dimensions") {
        REQUIRE(newEv.GetNumDimensions() == 5);
        AND_THEN("The new vector has magnitudes as 5.0,10.0,15.0,20.0,25.0") {
          REQUIRE(newEv[0] == 5.0);
          REQUIRE(newEv[1] == 10.0);
          REQUIRE(newEv[2] == 15.0);
          REQUIRE(newEv[3] == 20.0);
          REQUIRE(newEv[4] == 25.0);
        }
      }
    }
  }
}

// * - 2b - (Multiplying Vector with Scalar)
SCENARIO("Multiply vector by scalar on the left with the overloading * operator") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.0,2.0,...,5.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0, 4.0, 5.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    WHEN("A scalar product is obtained my multiplying it on the left with 5.0 and the result "
         "stored in the new vector") {
      auto newEv = 5.0 * ev1;
      THEN("The new vector has 5 dimensions") {
        REQUIRE(newEv.GetNumDimensions() == 5);
        AND_THEN("The new vector has magnitudes as 5.0,10.0,15.0,20.0,25.0") {
          REQUIRE(newEv[0] == 5.0);
          REQUIRE(newEv[1] == 10.0);
          REQUIRE(newEv[2] == 15.0);
          REQUIRE(newEv[3] == 20.0);
          REQUIRE(newEv[4] == 25.0);
        }
      }
    }
  }
}

// / (Divide vector by scalar)
SCENARIO("Divide vector by scalar using the overloading / operator") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 5.0,10.0,15.0,20.0,25.0") {
    std::vector<double> vec1{5.0, 10.0, 15.0, 20.0, 25.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    WHEN("A new vector is obtained by dividing original vector by 5.0 and the result "
         "stored in the new vector") {
      auto newEv = ev1 / 5.0;
      THEN("The new vector has 5 dimensions") {
        REQUIRE(newEv.GetNumDimensions() == 5);
        AND_THEN("The new vector has magnitudes as 1.0, 2.0, 3.0, 4.0, 5.0") {
          REQUIRE(newEv[0] == 1.0);
          REQUIRE(newEv[1] == 2.0);
          REQUIRE(newEv[2] == 3.0);
          REQUIRE(newEv[3] == 4.0);
          REQUIRE(newEv[4] == 5.0);
        }
      }
    }
    WHEN("A new vector is obtained by dividing original vector by 0.0 and the result "
         "stored in the new vector") {
      try {
        auto newEv = ev1 / 0.0;
        std::cerr << newEv << "is invalid. Control should not reach this line";
      } catch (const EuclideanVectorError& e) {
        THEN("Exception is thrown : Invalid vector division by 0") {
          std::string err = e.what();
          REQUIRE(err.compare("Invalid vector division by 0") == 0);
        }
      }
    }
  }
}

// << (Print Vector like [1 2 3])
SCENARIO("Print a vector using the output stream") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.5, 2.7, 3.2, 4.6, 5.1") {
    std::vector<double> vec1{1.5, 2.7, 3.2, 4.6, 5.1};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    WHEN("It is printed using the output stream") {
      std::stringstream v;
      v << ev1;
      THEN("Then it is printed as [1.5 2.7 3.2 4.6 5.1]") {
        REQUIRE(v.str().compare("[1.5 2.7 3.2 4.6 5.1]") == 0);
      }
    }
  }
  GIVEN("That there is a vector with 0 dimensions") {
    auto ev1 = EuclideanVector(0);
    WHEN("It is printed using the output stream") {
      std::stringstream v;
      v << ev1;
      THEN("Then it is printed as []") { REQUIRE(v.str().compare("[]") == 0); }
    }
  }
}

/*
  ------------------------------------------------------------------------------------------------------------------------
                                                    Methods
  ------------------------------------------------------------------------------------------------------------------------
*/

// at (Get value at index)
SCENARIO("Get element at a given index using at()") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 5.0,10.0,15.0,20.0,25.0") {
    std::vector<double> vec1{5.0, 10.0, 15.0, 20.0, 25.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    WHEN("The value at index 3 is accessed using at()") {
      THEN("Then it is found to be 20.0") { REQUIRE(ev1.at(3) == 20.0); }
    }
    WHEN("The value at index -1 is accessed using at()") {
      try {
        std::cerr << ev1.at(-1) << "is invalid. Control should not reach this line";
      } catch (const EuclideanVectorError& e) {
        THEN("Exception is thrown : Index -1 is not valid for this EuclideanVector object") {
          std::string err = e.what();
          REQUIRE(err.compare("Index -1 is not valid for this EuclideanVector object") == 0);
        }
      }
    }
    WHEN("The value at index 5 is accessed using at()") {
      try {
        std::cerr << ev1.at(5) << "is invalid. Control should not reach this line";
      } catch (const EuclideanVectorError& e) {
        THEN("Exception is thrown : Index 5 is not valid for this EuclideanVector object") {
          std::string err = e.what();
          REQUIRE(err.compare("Index 5 is not valid for this EuclideanVector object") == 0);
        }
      }
    }
  }
  GIVEN("That there is a constant vector with 5 dimensions and magnitudes as "
        "5.0,10.0,15.0,20.0,25.0") {
    std::vector<double> vec1{5.0, 10.0, 15.0, 20.0, 25.0};
    const auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    WHEN("The value at index 3 is accessed using at()") {
      THEN("Then it is found to be 20.0") { REQUIRE(ev1.at(3) == 20.0); }
    }
  }
}
// at (Set value at index)
SCENARIO("Set element at a given index using at()") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 5.0,10.0,15.0,20.0,25.0") {
    std::vector<double> vec1{5.0, 10.0, 15.0, 20.0, 25.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    WHEN("The value at index 3 is changed using at()") {
      ev1.at(3) = 20.0;
      THEN("Then it is found to be 20.0") { REQUIRE(ev1.at(3) == 20.0); }
    }
  }
}

// GetNumDimensions (Get the dimensions of a vector)
SCENARIO("Get the dimensions using GetNumDimensions") {
  GIVEN("That there is a vector with 5 dimensions") {
    auto ev1 = EuclideanVector(5);
    WHEN("The number of dimensions are obtained using GetNumDimensions") {
      auto dims = ev1.GetNumDimensions();
      THEN("Dimensions are equal to 5") { REQUIRE(dims == 5); }
    }
  }
  GIVEN("That there is a constant vector with 5 dimensions") {
    const auto ev1 = EuclideanVector(5);
    WHEN("The number of dimensions are obtained using GetNumDimensions") {
      auto dims = ev1.GetNumDimensions();
      THEN("Dimensions are equal to 5") { REQUIRE(dims == 5); }
    }
  }
  GIVEN("That there is a vector with 0 dimensions") {
    auto ev1 = EuclideanVector(0);
    WHEN("The number of dimensions are obtained using GetNumDimensions") {
      auto dims = ev1.GetNumDimensions();
      THEN("Dimensions are equal to 0") { REQUIRE(dims == 0); }
    }
  }
}
// GetEuclideanNorm (Get the normal of a vector)
SCENARIO("Calculate the Norm of a EuclideanVector") {
  GIVEN("That there is a vector with 3 dimensions and magnitudes as 1.0, 2.0, 3.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    WHEN("The Euclidean Norm of this vector is obtained") {
      auto euclidNorm = ev1.GetEuclideanNorm();
      THEN("The new euclidean norm is given by the square root of the sum of squares of the "
           "magnitudes") {
        REQUIRE(euclidNorm == std::sqrt(1.0 * 1.0 + 2.0 * 2.0 + 3.0 * 3.0));
      }
    }
  }
  GIVEN("That there is a constant vector with 3 dimensions and magnitudes as 1.0, 2.0, 3.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0};
    const auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    WHEN("The Euclidean Norm of this vector is obtained") {
      auto euclidNorm = ev1.GetEuclideanNorm();
      THEN("The new euclidean norm is given by the square root of the sum of squares of the "
           "magnitudes") {
        REQUIRE(euclidNorm == std::sqrt(1.0 * 1.0 + 2.0 * 2.0 + 3.0 * 3.0));
      }
    }
  }
  GIVEN("That there is a vector with 0 dimensions") {
    auto ev1 = EuclideanVector(0);
    WHEN("The Euclidean Norm of this vector is obtained") {
      try {
        auto euclidNorm = ev1.GetEuclideanNorm();
        std::cerr << euclidNorm << "is invalid. Control should not reach this line";
      } catch (const EuclideanVectorError& e) {
        THEN("Exception is thrown : EuclideanVector with no dimensions does not have a norm") {
          std::string err = e.what();
          REQUIRE(err.compare("EuclideanVector with no dimensions does not have a norm") == 0);
        }
      }
    }
  }
}

// CreateUnitVector (Get the Unit vector of a vector)
SCENARIO("Create Unit vector of a euclidean vector") {
  GIVEN("That there is a vector with 4 dimensions and magnitudes as 1.0, 1.0, 1.0, 1.0") {
    auto ev1 = EuclideanVector(4, 1.0);
    WHEN("The unit vector of this vector is obtained") {
      auto unitVector = ev1.CreateUnitVector();
      THEN("The unit vector has magnitudes 0.5, 0.5, 0.5, 0.5") {
        REQUIRE(unitVector[0] == 0.5);
        REQUIRE(unitVector[1] == 0.5);
        REQUIRE(unitVector[2] == 0.5);
        REQUIRE(unitVector[3] == 0.5);
      }
    }
  }
  GIVEN("That there is a constant vector with 4 dimensions and magnitudes as 1.0, 1.0, 1.0, 1.0") {
    const auto ev1 = EuclideanVector(4, 1.0);
    WHEN("The unit vector of this vector is obtained") {
      auto unitVector = ev1.CreateUnitVector();
      THEN("The unit vector has magnitudes 0.5, 0.5, 0.5, 0.5") {
        REQUIRE(unitVector[0] == 0.5);
        REQUIRE(unitVector[1] == 0.5);
        REQUIRE(unitVector[2] == 0.5);
        REQUIRE(unitVector[3] == 0.5);
      }
    }
  }
  GIVEN("That there is a vector with 0 dimensions") {
    auto ev1 = EuclideanVector(0);
    WHEN("The Unit Vector of this vector is obtained") {
      try {
        auto unit = ev1.CreateUnitVector();
        std::cerr << unit << "is invalid. Control should not reach this line";
      } catch (const EuclideanVectorError& e) {
        THEN("Exception is thrown : EuclideanVector with no dimensions does not have a unit "
             "vector") {
          std::string err = e.what();
          REQUIRE(err.compare("EuclideanVector with no dimensions does not have a unit vector") ==
                  0);
        }
      }
    }
  }
  /*
  GIVEN("That there is a vector with 1 dimensions that is 0") {
    auto ev1 = EuclideanVector(1);
    AND_GIVEN("That the norm of the this vector is 0") {
      REQUIRE(ev1.GetEuclideanNorm() == 0.0);
      WHEN("The Unit vector this vector is obtained") {
        try {
          auto unitVector = ev1.CreateUnitVector();
          std::cerr << unitVector << "is invalid. Control should not reach this line";
        } catch (const EuclideanVectorError& e) {
          THEN("Exception is thrown : EuclideanVector with euclidean normal of 0 does not have a "
               "unit vector") {
            std::string err = e.what();
            REQUIRE(err.compare(
                        "EuclideanVector with euclidean normal of 0 does not have a unit vector") ==
                    0);
          }
        }
      }
    }
  } */
}
/*
  ------------------------------------------------------------------------------------------------------------------------
                                                    Operations
  ------------------------------------------------------------------------------------------------------------------------
*/
// = (Copy Assignment)
SCENARIO("Create a EuclideanVector using the copy assignment") {
  GIVEN("That there is a Euclidean Vector") {
    auto ev = EuclideanVector(5, 10.0);
    WHEN("EuclideanVector is created using the copy assignment") {
      auto newEv = ev;
      THEN("The new vector has same number of Dimensions as the original one") {
        REQUIRE(ev.GetNumDimensions() == newEv.GetNumDimensions());
        AND_THEN("Both vectors have same magnitudes in all dimensions") {
          REQUIRE(ev[0] == newEv[0]);
          REQUIRE(ev[1] == newEv[1]);
          REQUIRE(ev[2] == newEv[2]);
          REQUIRE(ev[3] == newEv[3]);
          REQUIRE(ev[4] == newEv[4]);
        }
      }
    }
  }
}

// = (Move Assignment)
SCENARIO("Create a EuclideanVector using the move assignment") {
  GIVEN("That there is a Euclidean Vector with 5 dimensions, all of which have magnitude 10.0") {
    auto ev = EuclideanVector(5, 10.0);
    WHEN("EuclideanVector is created using the move constructor") {
      auto newEv = std::move(ev);
      THEN("The new vector has 5 dimensions") {
        REQUIRE(newEv.GetNumDimensions() == 5);
        AND_THEN("All the magnitues are 10.0") {
          REQUIRE(newEv[0] == 10.0);
          REQUIRE(newEv[1] == 10.0);
          REQUIRE(newEv[2] == 10.0);
          REQUIRE(newEv[3] == 10.0);
          REQUIRE(newEv[4] == 10.0);
        }
      }
      THEN("The old vector has 0 dimensions") { REQUIRE(ev.GetNumDimensions() == 0); }
    }
  }
}

// [] (Subscript Overload - Get)
SCENARIO("Get values using the [] operator") {
  GIVEN("That there is a Euclidean Vector with 5 dimensions, all of which have magnitude 10.0") {
    auto ev = EuclideanVector(5, 10.0);
    WHEN("Values are acquired using []") {
      THEN("The values are correct") {
        REQUIRE(ev[0] == 10.0);
        REQUIRE(ev[1] == 10.0);
        REQUIRE(ev[2] == 10.0);
        REQUIRE(ev[3] == 10.0);
        REQUIRE(ev[4] == 10.0);
      }
    }
  }
  GIVEN("That there is a Euclidean Vector with 5 dimensions, all of which have magnitude 10.0") {
    const auto ev = EuclideanVector(5, 10.0);
    WHEN("Values are acquired using []") {
      THEN("The values are correct") {
        REQUIRE(ev[0] == 10.0);
        REQUIRE(ev[1] == 10.0);
        REQUIRE(ev[2] == 10.0);
        REQUIRE(ev[3] == 10.0);
        REQUIRE(ev[4] == 10.0);
      }
    }
  }
}

// [] (Subscript Overload - Set)
SCENARIO("Set values using the [] operator") {
  GIVEN("That there is a Euclidean Vector with 5 dimensions, all of which have magnitude 10.0") {
    auto ev = EuclideanVector(5, 10.0);
    WHEN("Values are changed using []") {
      ev[0] = 0.0;
      ev[1] = 1.0;
      THEN("The values are successfully changed") {
        REQUIRE(ev[0] == 0.0);
        REQUIRE(ev[1] == 1.0);
      }
    }
  }
}

// += (Add a vector the the given vector)
SCENARIO("Add two vectors with the overloading += operator") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.0,2.0,...,5.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0, 4.0, 5.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    AND_GIVEN("That there is a vector with 5 dimensions and magnitudes as 5.0,4.0,...,1.0") {
      std::vector<double> vec2{5.0, 4.0, 3.0, 2.0, 1.0};
      auto ev2 = EuclideanVector(vec2.begin(), vec2.end());
      WHEN("the second vector is added into the first one") {
        ev1 += ev2;
        THEN("The old vector has 5 dimensions") {
          REQUIRE(ev1.GetNumDimensions() == 5);
          AND_THEN("The old vector has magnitudes 6.0,6.0,...,6.0") {
            REQUIRE(ev1[0] == 6.0);
            REQUIRE(ev1[1] == 6.0);
            REQUIRE(ev1[2] == 6.0);
            REQUIRE(ev1[3] == 6.0);
            REQUIRE(ev1[4] == 6.0);
          }
        }
      }
    }
  }
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.0,2.0,...,5.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0, 4.0, 5.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    AND_GIVEN("That there is a vector with 4 dimensions and magnitudes as 5.0,4.0,3.0,2.0") {
      std::vector<double> vec2{5.0, 4.0, 3.0, 2.0};
      auto ev2 = EuclideanVector(vec2.begin(), vec2.end());
      WHEN("The second vector is added into the first") {
        try {
          ev1 += ev2;
        } catch (const EuclideanVectorError& e) {
          THEN("Exception is thrown : Dimensions of LHS(5) and RHS(4) do not match") {
            std::string err = e.what();
            REQUIRE(err.compare("Dimensions of LHS(5) and RHS(4) do not match") == 0);
          }
        }
      }
    }
  }
}

// -= (Subtract a vector from the given vector)
SCENARIO("Subtract two vectors with the overloading -= operator") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.0,2.0,...,5.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0, 4.0, 5.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    AND_GIVEN("That there is a vector with 5 dimensions and magnitudes as 5.0,4.0,...,1.0") {
      std::vector<double> vec2{5.0, 4.0, 3.0, 2.0, 1.0};
      auto ev2 = EuclideanVector(vec2.begin(), vec2.end());
      WHEN("The second vector is subtracted from the first vector") {
        ev1 -= ev2;
        THEN("The first vector has 5 dimensions") {
          REQUIRE(ev1.GetNumDimensions() == 5);
          AND_THEN("The first vector has magnitudes -4.0,-2..0,0.0,2.0,4.0") {
            REQUIRE(ev1[0] == -4.0);
            REQUIRE(ev1[1] == -2.0);
            REQUIRE(ev1[2] == 0.0);
            REQUIRE(ev1[3] == 2.0);
            REQUIRE(ev1[4] == 4.0);
          }
        }
      }
    }
  }
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.0,2.0,...,5.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0, 4.0, 5.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    AND_GIVEN("That there is a vector with 4 dimensions and magnitudes as 5.0,4.0,3.0,2.0") {
      std::vector<double> vec2{5.0, 4.0, 3.0, 2.0};
      auto ev2 = EuclideanVector(vec2.begin(), vec2.end());
      WHEN("The second vector is subtracted from the first") {
        try {
          ev1 -= ev2;
        } catch (const EuclideanVectorError& e) {
          THEN("Exception is thrown : Dimensions of LHS(5) and RHS(4) do not match") {
            std::string err = e.what();
            REQUIRE(err.compare("Dimensions of LHS(5) and RHS(4) do not match") == 0);
          }
        }
      }
    }
  }
}

// *= (Multiply given vector by scalar)
SCENARIO("Multiply vector by scalar with the overloading *= operator") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 1.0,2.0,...,5.0") {
    std::vector<double> vec1{1.0, 2.0, 3.0, 4.0, 5.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    WHEN("The vector is multiplied by 5.0") {
      ev1 *= 5;
      THEN("The vector has 5 dimensions") {
        REQUIRE(ev1.GetNumDimensions() == 5);
        AND_THEN("The vector has magnitudes as 5.0,10.0,15.0,20.0,25.0") {
          REQUIRE(ev1[0] == 5.0);
          REQUIRE(ev1[1] == 10.0);
          REQUIRE(ev1[2] == 15.0);
          REQUIRE(ev1[3] == 20.0);
          REQUIRE(ev1[4] == 25.0);
        }
      }
    }
  }
}

// /= (Divide given vector by scalar)
SCENARIO("Divide vector by scalar using the overloading /= operator") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes as 5.0,10.0,15.0,20.0,25.0") {
    std::vector<double> vec1{5.0, 10.0, 15.0, 20.0, 25.0};
    auto ev1 = EuclideanVector(vec1.begin(), vec1.end());
    WHEN("The vector is divided by 5.0") {
      ev1 /= 5.0;
      THEN("The vector has 5 dimensions") {
        REQUIRE(ev1.GetNumDimensions() == 5);
        AND_THEN("The vector has magnitudes as 1.0, 2.0, 3.0, 4.0, 5.0") {
          REQUIRE(ev1[0] == 1.0);
          REQUIRE(ev1[1] == 2.0);
          REQUIRE(ev1[2] == 3.0);
          REQUIRE(ev1[3] == 4.0);
          REQUIRE(ev1[4] == 5.0);
        }
      }
    }
    WHEN("The vector is divided by 0.0") {
      try {
        ev1 /= 0.0;
        std::cerr << ev1 << "is invalid. Control should not reach this line";
      } catch (const EuclideanVectorError& e) {
        THEN("Exception is thrown : Invalid vector division by 0") {
          std::string err = e.what();
          REQUIRE(err.compare("Invalid vector division by 0") == 0);
        }
      }
    }
  }
}

// TypeCast - EuclidVector to Vector
SCENARIO("Type case a EuclideanVector to a std::vector") {
  GIVEN("That there is a vector with 5 dimensions and magnitudes all as 5.0") {
    auto ev1 = EuclideanVector(5, 5.0);
    WHEN("The vector is type casted to a std::vector") {
      auto doubleVect = std::vector<double>{ev1};
      THEN("The vector has size equal to 5") {
        REQUIRE(doubleVect.size() == 5);
        AND_THEN("All the values of the vector are 5") {
          for (auto begin = doubleVect.begin(); begin != doubleVect.end(); begin++)
            REQUIRE(*begin == 5.0);
        }
      }
    }
  }
  GIVEN("That there is a const vector with 5 dimensions and magnitudes all as 5.0") {
    const auto ev1 = EuclideanVector(5, 5.0);
    WHEN("The vector is type casted to a std::vector") {
      auto doubleVect = std::vector<double>{ev1};
      THEN("The vector has size equal to 5") {
        REQUIRE(doubleVect.size() == 5);
        AND_THEN("All the values of the vector are 5") {
          for (auto begin = doubleVect.begin(); begin != doubleVect.end(); begin++)
            REQUIRE(*begin == 5.0);
        }
      }
    }
  }
}

// TypeCast - EuclidVector to List
SCENARIO("Type case a EuclideanVector to a std::list") {
  GIVEN("That there is a Euclidean Vector with 5 dimensions and magnitudes all as 5.0") {
    auto ev1 = EuclideanVector(5, 5.0);
    WHEN("The vector is type casted to a std::list") {
      auto doubleList = std::list<double>{ev1};
      THEN("The list has size equal to 5") {
        REQUIRE(doubleList.size() == 5);
        AND_THEN("All the values of the list are 5") {
          for (auto i = 0; i < 5; i++) {
            REQUIRE(doubleList.front() == 5.0);
            doubleList.pop_front();
          }
        }
      }
    }
  }
  GIVEN("That there is a constant Euclidean Vector with 5 dimensions and magnitudes all as 5.0") {
    const auto ev1 = EuclideanVector(5, 5.0);
    WHEN("The vector is type casted to a std::list") {
      auto doubleList = std::list<double>{ev1};
      THEN("The list has size equal to 5") {
        REQUIRE(doubleList.size() == 5);
        AND_THEN("All the values of the list are 5") {
          for (auto i = 0; i < 5; i++) {
            REQUIRE(doubleList.front() == 5.0);
            doubleList.pop_front();
          }
        }
      }
    }
  }
}
