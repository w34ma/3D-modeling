//
// IMPORTANT: fill in things below BEFORE submitting your solution
//
//-------------------------------------------------------------------------------------
// <course_id> CSIS0271_COMP3271 </course_id>
//
// <course_name> Computer Graphics <course_name>
//
// <student_name> XXX </student_name>
//
// <student_id> XXXXXXXXXX </student_id>
//
// <submission_date> 2015-XX-XX </submission_date>
//
// <notes_made_to_us> things you want us to know </notes_made_to_us>
//
// <assignment_description> refer to PDF file </assignment_description>
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//  cg_assignment_3.h
//
//  cg_assignment_3_template - template for COMP3271 Computer Graphics assignment 3
//
//  Instructor: Jack M. Wang
//
//  TA: Kan WU, ulmonkey1987@gmail.com
//
//  Department of Computer Science, The University of Hong Kong
//-------------------------------------------------------------------------------------

#ifndef CG_ASSIGNMENT_03_H_
#define CG_ASSIGNMENT_03_H_

// only windows platform supported for this assignment
#if defined(_WIN32)

    #include <windows.h>

    #include <GL/gl.h>
    #include <GL/glu.h>

    //#include <GL/glut.h>

#elif defined(__linux)

    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>

#elif defined(__APPLE__)

    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>

#endif

#include <iostream>
using std::cout;
using std::endl;

//-------------------------------------------------------------------------------------
// data type definition

// scaling direction (scaling along x, y, z axis)
enum enumScalingDirection
{
    SCALING_Y = 0, SCALING_Z, SCALING_X
};

// 3-component double-precision color (r, g, b: [0.0, 1.0])
class color3f
{
public:
    
    color3f(void): r_(0.0), g_(0.0), b_(0.0) {};
    
    color3f(const double r, const double g, const double b)
            : r_(r), g_(g), b_(b) {};
    
    double r_, g_, b_;
};

// 3d double-precision vector
class vect3f
{
public:
    
    vect3f(void): dx_(0), dy_(0), dz_(0) {};
    
    vect3f(const double dx, const double dy, const double dz): dx_(dx), dy_(dy), dz_(dz) {};
    
    vect3f(const vect3f& v): dx_(v.dx_), dy_(v.dy_), dz_(v.dz_) {};
    
    const vect3f operator -(const vect3f& v) const
    {
        return vect3f(dx_ - v.dx_, dy_ - v.dy_, dz_ - v.dz_);
    };

    const vect3f operator /(const double n) const
    {
        return vect3f(dx_ / n, dy_ / n, dz_ / n);
    };
    
    const vect3f operator *(const double n) const
    {
        return vect3f(dx_ * n, dy_ * n, dz_ * n);
    };
    
    double dx_, dy_, dz_;
};

// 2d double-precision points
class point2f
{
public:
    
    point2f(void): x_(0), y_(0) {};
    
    point2f(const double x, const double y): x_(x), y_(y) {};
    
    point2f(const point2f& p): x_(p.x_), y_(p.y_) {};
    
    double x_, y_;
};

// 3d double-precision point
class point3f
{
public:
    
    point3f(void): x_(0), y_(0), z_(0) {};
    
    point3f(const double x, const double y, const double z): x_(x), y_(y), z_(z) {};
    
    point3f(const point3f& p): x_(p.x_), y_(p.y_), z_(p.z_) {};
    
    const point3f operator +(const vect3f& v) const
    {
        return point3f(x_ + v.dx_, y_ + v.dy_, z_ + v.dz_);
    };
    
    const point3f operator -(const vect3f& v) const
    {
        return point3f(x_ - v.dx_, y_ - v.dy_, z_ - v.dz_);
    };

    double x_, y_, z_;
};

//-------------------------------------------------------------------------------------
// TODO: draw handle for scaling the object
//
// INPUT: center_p: center position of the object
//        local_x_axis, local_y_axis, local_z_axis: local coordinate axis
//        
// OUTPUT: draw a handle that indicates its position and pointing direction
//
void draw_handle(const point3f& center_p, const vect3f& local_x_axis,
                 const vect3f& local_y_axis, const vect3f& local_z_axis)
{
    // PUT YOUR SOLUTION HERE
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    
    point3f p1(center_p.x_+ (2 * local_z_axis).dx_,center_p.x_+ (2 * local_z_axis).dx_,center_p.x_+ (2 * local_z_axis).dx_);
    point3f p2(center_p.x_+ (2 * local_z_axis).dx_,center_p.x_+ (2 * local_z_axis).dx_,center_p.x_+ (2 * local_z_axis).dx_);
    point3f p3(center_p.x_+ (2 * local_z_axis).dx_,center_p.x_+ (2 * local_z_axis).dx_,center_p.x_+ (2 * local_z_axis).dx_);
    point3f p4(center_p.x_+ (2 * local_z_axis).dx_,center_p.x_+ (2 * local_z_axis).dx_,center_p.x_+ (2 * local_z_axis).dx_);
    point3f p5(center_p.x_+ (2 * local_z_axis).dx_,center_p.x_+ (2 * local_z_axis).dx_,center_p.x_+ (2 * local_z_axis).dx_);

    glVertex3f(p1);
    glVertex3f(p2);
    glVertex3f(p3);
    
    glVertex3f(p1);
    glVertex3f(p2);
    glVertex3f(p5);
    
    glVertex3f(p1);
    glVertex3f(p4);
    glVertex3f(p5);
    
    glVertex3f(p1);
    glVertex3f(p3);
    glVertex3f(p4);
    glEnd();
    
    glBegin(GL_QUADS);

    glVertex3f(p2);
    glVertex3f(p3);
    glVertex3f(p4);
    glVertex3f(p5);
    glEnd();

    glPopMatrix();
}
//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------
// TODO: calculate the closest point on a line M:(m0+m*s) to another line R:(r0+r*t)
//
// INPUT: m0/r0: a point on the line M/R
//        m/r: the direction of the line M/R
//        
// OUTPUT: calculate a point on line M that is the closest to line R
//
point3f closest_point(const point3f& m0, const vect3f& m,
                      const point3f& r0, const vect3f& r)
{
    // PUT YOUR SOLUTION HERE
    //R go through viewpoint and Sstar
    //find the closest point on M:(m0+m*s)
    //v= m x r 叉积公式：u x v = { u2v3-v2u3 , u3v1-v3u1 , u1v2-u2v1 }
    
    vect3f V;
    V.dx_= m.dy_*r.dz_ - r.dy_*m.dz_;
    V.dy_= m.dz_*r.dx_ - r.dz_*m.dx_;
    V.dz_= m.dx_*r.dy_ - r.dx_*m.dy_;

    //N = r x V N is normal vector?
    vect3f N;
    N.dx_= r.dy_*V.dz_ - r.dy_*V.dz_;
    N.dy_= r.dz_*V.dx_ - r.dz_*V.dx_;
    N.dz_= r.dx_*V.dy_ - r.dx_*V.dy_;
    
    double vpt = m.dx_ * N.dx_ + m.dy_ * N.dy_ + m.dz_ * N.dz_;
    
    //viewpoint r0 and N define a plane Q and we want the intersection point of plan Q and line M
    double t = ((r0.x_ - m0.x_) * N.dx_ + (r0.y_ - m0.y_) * N.dy_ + (r0.z_ - m0.z_) * N.dz_) / vpt;
    
    return point3f(m0.x_ + m.dx_ * t, m0.y_ + m.dy_ * t, m0.z_ + m.dz_ * t);
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// TODO: rotate the object around its center position
//
// INPUT: obj_center: the center of the object
//        old_pos: previous mouse position, expressed in window coordinates
//        new_pos: current mouse position, expressed in window coordinates
//        
// OUTPUT: calculate the rotation matrix and store it in double rot[16]
//
void rotate(const point3f& obj_center, const point2f& old_pos, const point2f& new_pos,
            double rot[])
{
    // PUT YOUR SOLUTION HERE
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(obj_center.x_, obj_center.y_, obj_center.z_);
    vect3f n(0,0,1); // the vector pointing out to screen ?
    vect3f v(new_pos.x_ - old_pos.x_, new_pos.y_ - old_pos.y_, 0) // not sure if the last one is 0?
    //A = v x n rotate axis A
    vect3f A;
    A.dx_= v.dy_*n.dz_ - v.dy_*n.dz_;
    A.dy_= v.dz_*n.dx_ - v.dz_*n.dx_;
    A.dz_= v.dx_*n.dy_ - v.dx_*n.dy_;
    
    glRotatef(2 * sqrt(A.dx_ * A.dx_ + A.dy_ * A.dy_ + A.dz_ * A.dz_), A.dx_, A.dy_, A.dz_);//k = 2?
    
    glTranslatef(-obj_center.x_, -obj_center.y_, -obj_center.z_);
    float mat[16];
    glGetFloatv(GL_MODELVIEW_MATRIX,mat);
    rot = mat ;//rot is double and mat is float
    glPopMatrix();
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// TODO: translate the object along the direction <m1, m2>
//
// INPUT: m1/m2: the start/end point along the translating direction
//        old_pos: previous mouse position, expressed in world coordinates
//        new_pos: current mouse position, expressed in world coordinates
//        
// OUTPUT: calculate the translation matrix and store it in double translation[16]
//
void translate(const point3f m1, const point3f& m2, const point3f& view_p,
               const point3f& old_pos, const point3f& new_pos,
               double translation[])
{
    // PUT YOUR SOLUTION HERE
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    vect3f M(m1.x_ - m2.x_,m1.y_ - m2.y_,m1.z_ - m2.z_);//m1 - m2? or m2 -m1?
    vect3f Rstart(old_pos.x_ - view_p.x_,old_pos.y_ - view_p.y_,old_pos.z_ - view_p.z_);//old -view? or view - old?
    vect3f Rcurr(new_pos.x_ - view_p.x_,new_pos.y_ - view_p.y_,new_pos.z_ - view_p.z_);

    pint3f pcurr =closest_point(m1, M, new_pos, Rcurr);
    pint3f pstart =closest_point(m1, M, old_pos, Rstart);
    glTranslatef(pcurr.x_ - pstart.x_, pcurr.y_ - pstart.y_, pcurr.z_ - pstart.z_);
    // TODO: calculate the closest point on a line M:(m0+m*s) to another line R:(r0+r*t)
  
    float mat[16];
    glGetFloatv(GL_MODELVIEW_MATRIX,mat);
    translation = mat ;//rot is double and mat is float
    glPopMatrix();
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// TODO: scale the object along the direction <m1, m2>, with fixed point being m1
//
// INPUT: old_pos: previous mouse position, expressed in world coordinates
//        new_pos: current mouse position, expressed in world coordinates
//        view_p: viewpoint position
//        m1/m2: the start/end point along the translating direction
//        scale_dir: the flag that indicastes the axis of current scaling
//                   SCALING_Y(0), SCALING_Z(1), SCALING_X(2)
//        
// OUTPUT: calculate the scaling matrix and store it in double scaling[16]
//
void scale(const point3f& old_pos, const point3f& new_pos, const point3f& view_p,
           const point3f& m1, const point3f& m2, const int scale_dir,
           double scaling[])
{
    // PUT YOUR SOLUTION HERE
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(m1.x_, m1.y_, m1.z_);
    
    vect3f M(m1.x_ - m2.x_,m1.y_ - m2.y_,m1.z_ - m2.z_);//not sure m1 -m2 or m2 -m1
    vect3f Rstart(old_pos.x_ - view_p.x_,old_pos.y_ - view_p.y_,old_pos.z_ - view_p.z_);
    vect3f Rcurr(new_pos.x_ - view_p.x_,new_pos.y_ - view_p.y_,new_pos.z_ - view_p.z_);
    
    pint3f pcurr =closest_point(m1, M, new_pos, Rcurr);
    pint3f pstart =closest_point(m1, M, old_pos, Rstart);
    
    //all the scaling operatons are done along global axis
    float val1 =sqrt((pcurr - m1).x_ * (pcurr - m1).x_+(pcurr - m1).y_ * (pcurr - m1).y_+(pcurr - m1).z_ * (pcurr - m1).z_);
    float val2 =sqrt((pstart - m1).x_ * (pstart - m1).x_+(pstart - m1).y_ * (pstart - m1).y_+(pstart - m1).z_ * (pstart - m1).z_);
    float Svalue = val1/val2;
    
    if(scale_dir == 0){
        //Y-axis
        glScalef(1,1,Svalue);
    }else if(scale_dir == 1){
        //Z-axis
        glScalef(Svalue,1,1);
    }else if(scale_dir == 2){
        //X-axis
        glScalef(1,Svalue,1);
    }
    
    glTranslatef(-m1.x_, -m1.y_, -m1.z_);
    
    float mat[16];
    glGetFloatv(GL_MODELVIEW_MATRIX,mat);
    scaling = mat ;//scaling is double and mat is float
    glPopMatrix();
}
//-------------------------------------------------------------------------------------

#endif // !CG_ASSIGNMENT_03_H_
