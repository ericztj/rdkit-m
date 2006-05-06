//  $Id: testTransforms.cpp 4955 2006-02-17 23:37:53Z glandrum $
// 
//   Copyright (C) 2005-2006 Rational Discovery LLC
//
//   @@ All Rights Reserved  @@
//

#include <RDGeneral/types.h>
#include <RDGeneral/Invariant.h>
#include <RDGeneral/utils.h>
#include "Transform2D.h"
#include "Transform3D.h"
#include "point.h"
#include <cstdlib>
#include <time.h>


using namespace RDGeom;
using namespace std;

double ptEq(const Point3D pt1, const Point3D pt2, double val = 1.e-8) {
  return ( (abs(pt1.x - pt2.x) < val) &&
           (abs(pt1.y - pt2.y) < val) &&
           (abs(pt1.z - pt2.z) < val) );
}

double ptEq(const Point2D pt1, const Point2D pt2, double val = 1.e-8) {
  return ( (abs(pt1.x - pt2.x) < val) &&
           (abs(pt1.y - pt2.y) < val));
}

double randNum(double x=5) {
  double res = (double)rand();
  res /= RAND_MAX;
  res *= x;
  return res;
}


void testPointOps3D() {
  Point3D pt0(1,0,0);
  Point3D pt1(0,1,0);
  Point3D pt2(-1,0,0);
  Point3D pt3(0,-1,0);

  TEST_ASSERT(abs(pt0.angleTo(pt0))<1e-4);
  TEST_ASSERT(abs(pt0.angleTo(pt1)-M_PI/2.)<1e-4);
  TEST_ASSERT(abs(pt0.angleTo(pt2)-M_PI)<1e-4);
  TEST_ASSERT(abs(pt0.angleTo(pt3)-M_PI/2.)<1e-4);

  TEST_ASSERT(abs(pt1.angleTo(pt0)-M_PI/2.)<1e-4);
  TEST_ASSERT(abs(pt1.angleTo(pt1))<1e-4);
  TEST_ASSERT(abs(pt1.angleTo(pt2)-M_PI/2.)<1e-4);
  TEST_ASSERT(abs(pt1.angleTo(pt3)-M_PI)<1e-4);

  TEST_ASSERT(abs(pt0.signedAngleTo(pt0))<1e-4);
  TEST_ASSERT(abs(pt0.signedAngleTo(pt1)-M_PI/2.)<1e-4);
  TEST_ASSERT(abs(pt0.signedAngleTo(pt2)-M_PI)<1e-4);
  TEST_ASSERT(abs(pt0.signedAngleTo(pt3)-3.*M_PI/2.)<1e-4);

  Point3D diffPt = pt0.directionVector(pt1);
  Point3D ref(-sqrt(2.)/2.,sqrt(2.)/2.,0);
  TEST_ASSERT(ptEq(diffPt,ref));
}
void testPointOps2D() {
  Point2D pt0(1,0);
  Point2D pt1(0,1);
  Point2D pt2(-1,0);
  Point2D pt3(0,-1);

  TEST_ASSERT(abs(pt0.angleTo(pt0))<1e-4);
  TEST_ASSERT(abs(pt0.angleTo(pt1)-M_PI/2.)<1e-4);
  TEST_ASSERT(abs(pt0.angleTo(pt2)-M_PI)<1e-4);
  TEST_ASSERT(abs(pt0.angleTo(pt3)-M_PI/2.)<1e-4);

  TEST_ASSERT(abs(pt1.angleTo(pt0)-M_PI/2.)<1e-4);
  TEST_ASSERT(abs(pt1.angleTo(pt1))<1e-4);
  TEST_ASSERT(abs(pt1.angleTo(pt2)-M_PI/2.)<1e-4);
  TEST_ASSERT(abs(pt1.angleTo(pt3)-M_PI)<1e-4);

  TEST_ASSERT(abs(pt0.signedAngleTo(pt0))<1e-4);
  TEST_ASSERT(abs(pt0.signedAngleTo(pt1)-M_PI/2.)<1e-4);
  TEST_ASSERT(abs(pt0.signedAngleTo(pt2)-M_PI)<1e-4);
  TEST_ASSERT(abs(pt0.signedAngleTo(pt3)-3.*M_PI/2.)<1e-4);

  Point2D diffPt = pt0.directionVector(pt1);
  Point2D ref(-sqrt(2.)/2.,sqrt(2.)/2.);
  TEST_ASSERT(ptEq(diffPt,ref));
}

void test12D() {
  Point2D pt(1.0, 2.0);
  Transform2D trans;
  trans.TransformPoint(pt);

  CHECK_INVARIANT(abs(pt.x - 1.0) < 1.e-8, "");
  CHECK_INVARIANT(abs(pt.y - 2.0) < 1.e-8, "");
  
  Point2D ref1(randNum(), randNum());
  Point2D ref2(randNum(), randNum());

  std::cout << "ref1: " << ref1 << " ref2: " << ref2 << "\n";

  Point2D pt1(randNum(), randNum());
  Point2D pt2(randNum(), randNum());
  Point2D pt1o = pt1;
  Point2D pt2o = pt2;
  std::cout << "pt1: " << pt1 << " pt2: " << pt2 << "\n";

  Transform2D t2d;
  t2d.SetTransform(ref1, ref2, pt1, pt2);
  t2d.TransformPoint(pt1);
  t2d.TransformPoint(pt2);

  // make sure pt1 overlaps ref1
  Point2D dif1 = pt1 - ref1;
  CHECK_INVARIANT(abs(dif1.x) < 1.e-8, "");
  CHECK_INVARIANT(abs(dif1.y) < 1.e-8, "");

  // now check that the angle between the two vectors (ref2 - ref1) and
  // (pt2 - pt1) is zero
  Point2D rvec = ref2 - ref1;
  Point2D pvec = pt2 - pt1;
  rvec.normalize();
  pvec.normalize();
  double pdot = rvec.dotProduct(pvec);
  CHECK_INVARIANT(abs(pdot - 1.0) < 1.e-8, "");

  // compute the reverse transform and make sure we are basically getting the 
  // identity
  Transform2D tdi;
  tdi.SetTransform(pt1o, pt2o, pt1, pt2);
  tdi.TransformPoint(pt1);
  tdi.TransformPoint(pt2);
  
  
  CHECK_INVARIANT(ptEq(pt1, pt1o), "");
  CHECK_INVARIANT(ptEq(pt2, pt2o), "");

  // the following product should result in an identity matrix
  tdi *= t2d;
  
  tdi.TransformPoint(pt1);
  tdi.TransformPoint(pt2);
  
  CHECK_INVARIANT(ptEq(pt1, pt1o), "");
  CHECK_INVARIANT(ptEq(pt2, pt2o), "");

  Point2D npt1(1.0, 0.0);
  Point2D npt2(5.0, 0.0);
  Point2D opt1 = npt1;
  Point2D opt2(1.0, 4.0);
  Transform2D ntd;
  ntd.SetTransform(npt1, M_PI/2);
  ntd.TransformPoint(npt1);
  ntd.TransformPoint(npt2);
  
  CHECK_INVARIANT(ptEq(npt1, opt1), "");
  CHECK_INVARIANT(ptEq(npt2, opt2), "");

}

void test23D() {
  double PI = 3.1415926535897931;
  Point3D pt(1.0, 0.0, 0.0);
  Point3D tpt = pt;
  Transform3D trans;
  trans.SetRotation(PI/2., X_Axis);
  trans.TransformPoint(pt);
  CHECK_INVARIANT(ptEq(tpt, pt), "");
  
  Point pt2(0.0, 1.0, 0.0);
  Point tpt2(0.0, 0.0, 1.0);
  trans.TransformPoint(pt2);
  CHECK_INVARIANT(ptEq(tpt2, pt2), "");

  Point pt3(0.0, 0.0, 1.0);
  Point tpt3(0.0, -1.0, 0.0); 
  trans.TransformPoint(pt3);
  CHECK_INVARIANT(ptEq(tpt3, pt3), "");

  // rotate around y-axis
  Transform3D transy;
  transy.SetRotation(PI/2., Y_Axis);
  transy.TransformPoint(pt);
  Point tpt4(0.0, 0.0, -1.0);
  CHECK_INVARIANT(ptEq(tpt4, pt), "");

  Point pt5(0.0, 1.0, 0.0);
  Point tpt5(0.0, 1.0, 0.0);
  transy.TransformPoint(pt5);
  CHECK_INVARIANT(ptEq(tpt5, pt5), "");

  Point pt6(0.0, 0.0, 1.0);
  Point tpt6(1.0, 0.0, 0.0);
  transy.TransformPoint(pt6);
  CHECK_INVARIANT(ptEq(tpt6, pt6), "");

  // z-axis
  Transform3D transz;
  transz.SetRotation(PI/2., Z_Axis);
  Point pt7(1.0, 0.0, 0.0);
  Point tpt7(0.0, 1.0, 0.0);
  transz.TransformPoint(pt7);
  CHECK_INVARIANT(ptEq(tpt7, pt7), "");

  Point pt8(0.0, 1.0, 0.0);
  Point tpt8(-1.0, 0.0, 0.0);
  transz.TransformPoint(pt8);
  CHECK_INVARIANT(ptEq(tpt8, pt8), "");

  Point pt9(0.0, 0.0, 1.0);
  Point tpt9(0.0, 0.0, 1.0);
  transz.TransformPoint(pt9);
  CHECK_INVARIANT(ptEq(tpt9, pt9), "");

}

void test3MatMultiply() {
  double PI = 3.1415926535897931;
  // start with line on the axis starting at 1.0, 
  // transform it into a line on z-axis starting at 3.0
  Point pt1(1.0, 0.0, 0.0);
  Point pt2(2.0, 0.0, 0.0);
  
  std::cout << "Pt1: " << pt1 << " Pt2: " << pt2 << "\n";
  std::cout << "-Pt1: " << (-pt1) << "\n";
  // move to orgin
  Transform3D t1;
  t1.SetTranslation(-pt1);

  Point tp1 = pt1;
  Point tp2 = pt1;
  t1.TransformPoint(tp1);
  t1.TransformPoint(tp2);
  std::cout << "tp1: " << tp1 << " tp2: " << tp2 << "\n";

  // rotation around origin 
  Transform3D t2;
  t2.SetRotation(-PI/2.0, Y_Axis);

  t2.TransformPoint(tp1);
  t2.TransformPoint(tp2);
  std::cout << "tp1: " << tp1 << " tp2: " << tp2 << "\n";

  // move on z-axis
  Transform3D t3;
  Point npt1(0.0, 0.0, 3.0);
  t3.SetTranslation(npt1);
  Point npt2(0.0, 0.0, 4.0);

  t3.TransformPoint(tp1);
  t3.TransformPoint(tp2);
  std::cout << "tp1: " << tp1 << " tp2: " << tp2 << "\n";

  std::cout << "npt1: " << npt1 << " npt2: " << npt2 << "\n";

  // combine the transform;
  
  Transform3D t4 = t3*t2*t1;
  t2 *= t1;
  t3 *= t2;

  Point opt1 = pt1;
  Point opt2 = pt2;

  t3.TransformPoint(pt1);
  t3.TransformPoint(pt2);
  std::cout << "Pt1: " << pt1 << " Pt2: " << pt2 << "\n";
  // check the transformed points align with the new points on z-axis
  CHECK_INVARIANT(ptEq(pt1, npt1), "");
  CHECK_INVARIANT(ptEq(pt2, npt2), "");

  t4.TransformPoint(opt1);
  t4.TransformPoint(opt2);
  CHECK_INVARIANT(ptEq(opt1, npt1), "");
  CHECK_INVARIANT(ptEq(opt2, npt2), "");
}

void testFromQuaternion() {
  double qt[4];
  qt[0] = cos(RDKit::PI/6);
  qt[1] = -sin(RDKit::PI/6);
  qt[2] = 0.0;
  qt[3] = 0.0;
  Transform3D trans;
  trans.SetRotationFromQuaternion(qt);

  Transform3D ntrans;
  ntrans.SetRotation(RDKit::PI/3, Point3D(1.0, 0.0, 0.0));

  unsigned int i,j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      CHECK_INVARIANT(RDKit::feq(trans.getVal(i,j), ntrans.getVal(i,j)), "");
    }
  } 

}

  
int main() {
  srand(time(NULL));

  std::cout << "****************************************\n";
  std::cout << "testPointOps3D\n";
  testPointOps3D();

  std::cout << "****************************************\n";
  std::cout << "testPointOps2D\n";
  testPointOps2D();

  std::cout << "****************************************\n";
  std::cout << "test12D\n";
  test12D();

  std::cout << "****************************************\n";
  std::cout << "test23D\n";
  test23D();

  std::cout << "****************************************\n";
  std::cout << "test3MatMultiply\n";
  test3MatMultiply();
  
  std::cout << "****************************************\n";
  std::cout << "testFromQuaternion\n";
  testFromQuaternion();
  std::cout << "****************************************\n";
  return 0;
}
