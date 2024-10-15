//=============================================================================
//
//   Exercise code for the lecture
//   "Introduction to Computer Graphics"
//   by Prof. Dr. Mario Botsch, Bielefeld University
//
//   Copyright (C) Computer Graphics Group, Bielefeld University.
//
//=============================================================================

//== INCLUDES =================================================================

#include "Mesh.h"
#include <fstream>
#include <string>
#include <stdexcept>
#include <limits>
#include <cmath>


//== IMPLEMENTATION ===========================================================


Mesh::Mesh(std::istream &is, const std::string &scenePath)
{
    std::string meshFile, mode;
    is >> meshFile;

    const char pathSep =
#ifdef _WIN32
                            '\\';
#else
                            '/';
#endif

    // load mesh from file
    read(scenePath.substr(0, scenePath.find_last_of(pathSep) + 1) + meshFile);

    is >> mode;
    if      (mode ==  "FLAT") draw_mode_ = FLAT;
    else if (mode == "PHONG") draw_mode_ = PHONG;
    else throw std::runtime_error("Invalid draw mode " + mode);

    is >> material;
}


//-----------------------------------------------------------------------------


bool Mesh::read(const std::string &_filename)
{
    // read a mesh in OFF format


    // open file
    std::ifstream ifs(_filename);
    if (!ifs)
    {
        std::cerr << "Can't open " << _filename << "\n";
        return false;
    }


    // read OFF header
    std::string s;
    unsigned int nV, nF, dummy, i;
    ifs >> s;
    if (s != "OFF")
    {
        std::cerr << "No OFF file\n";
        return false;
    }
    ifs >> nV >> nF >> dummy;
    std::cout << "\n  read " << _filename << ": " << nV << " vertices, " << nF << " triangles";


    // read vertices
    Vertex v;
    vertices_.clear();
    vertices_.reserve(nV);
    for (i=0; i<nV; ++i)
    {
        ifs >> v.position;
        vertices_.push_back(v);
    }


    // read triangles
    Triangle t;
    triangles_.clear();
    triangles_.reserve(nF);
    for (i=0; i<nF; ++i)
    {
        ifs >> dummy >> t.i0 >> t.i1 >> t.i2;
        triangles_.push_back(t);
    }


    // close file
    ifs.close();


    // compute face and vertex normals
    compute_normals();

    // compute bounding box
    compute_bounding_box();


    return true;
}


//-----------------------------------------------------------------------------

// Determine the weights by which to scale triangle (p0, p1, p2)'s normal when
// accumulating the vertex normals for vertices 0, 1, and 2.
// (Recall, vertex normals are a weighted average of their incident triangles'
// normals, and in our raytracer we'll use the incident angles as weights.)
// \param[in] p0, p1, p2    triangle vertex positions
// \param[out] w0, w1, w2    weights to be used for vertices 0, 1, and 2
void angleWeights(const vec3 &p0, const vec3 &p1, const vec3 &p2,
                  double &w0, double &w1, double &w2) {
    // compute angle weights
    const vec3 e01 = normalize(p1-p0);
    const vec3 e12 = normalize(p2-p1);
    const vec3 e20 = normalize(p0-p2);
    w0 = acos( std::max(-1.0, std::min(1.0, dot(e01, -e20) )));
    w1 = acos( std::max(-1.0, std::min(1.0, dot(e12, -e01) )));
    w2 = acos( std::max(-1.0, std::min(1.0, dot(e20, -e12) )));
}


//-----------------------------------------------------------------------------

void Mesh::compute_normals()
{
    // compute triangle normals
    for (Triangle& t: triangles_)
    {
        const vec3& p0 = vertices_[t.i0].position;
        const vec3& p1 = vertices_[t.i1].position;
        const vec3& p2 = vertices_[t.i2].position;
        t.normal = normalize(cross(p1-p0, p2-p0));
    }

    // initialize vertex normals to zero
    for (Vertex& v: vertices_)
    {
        v.normal = vec3(0,0,0);
    }

    for (Triangle& t: triangles_)
    {
        //vertices_[t.i0].normal += angleWeights(t.i0, t.i1) * t.normal ;
        double w0, w1, w2;
        angleWeights(vertices_[t.i0].position, vertices_[t.i1].position, vertices_[t.i2].position, w0, w1, w2);
        vertices_[t.i0].normal += w0 * t.normal;
        vertices_[t.i1].normal += w1 * t.normal;
        vertices_[t.i2].normal += w2 * t.normal;
    }

    for (Vertex& v: vertices_)
    {
        v.normal = normalize(v.normal);
    }

    /** \todo
     * In some scenes (e.g the office scene) some objects should be flat
     * shaded (e.g. the desk) while other objects should be Phong shaded to appear
     * realistic (e.g. chairs). You have to implement the following:
     * - Compute vertex normals by averaging the normals of their incident triangles.
     * - Store the vertex normals in the Vertex::normal member variable.
     * - Weigh the normals by their triangles' angles.
     */
}


//-----------------------------------------------------------------------------


void Mesh::compute_bounding_box()
{
    bb_min_ = vec3(std::numeric_limits<double>::max());
    bb_max_ = vec3(std::numeric_limits<double>::lowest());

    for (Vertex v: vertices_)
    {
        bb_min_ = min(bb_min_, v.position);
        bb_max_ = max(bb_max_, v.position);
    }
}


//-----------------------------------------------------------------------------

double determinant3x3(std::vector<vec3> matrix) {
    double a = matrix[0][0], b = matrix[0][1], c = matrix[0][2];
    double d = matrix[1][0], e = matrix[1][1], f = matrix[1][2];
    double g = matrix[2][0], h = matrix[2][1], i = matrix[2][2];

    // Apply the determinant formula for 3x3 matrix
    return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}

bool Mesh::intersect_bounding_box(const Ray& _ray) const
{
    const vec3 x = normalize(vec3(1,0,0));
    const vec3 y = normalize(vec3(0,1,0));
    const vec3 z = normalize(vec3(0,0,1));

    const vec3 A = bb_min_;
    const vec3 G = bb_max_;
    const vec3 v = G - A;

    const vec3 e = dot(v,z) * z;
    const vec3 w = v - e;
    const vec3 d = dot(w,x) * x;
    const vec3 p = (A + w) - (A + d);

    const vec3 a = _ray.direction;
    const vec3 o = _ray.origin;

    const std::vector<vec3> mat_xz = {x, z, a};
    const std::vector<vec3> mat_yz = {y, z, a};
    const std::vector<vec3> mat_xy = {x, y, a};
    const vec3 sost_A = o - A;
    const vec3 sost_B = o - G;

    const double det_xz = determinant3x3(mat_xz);
    const double det_yz = determinant3x3(mat_yz);
    const double det_xy = determinant3x3(mat_xy);

    if (det_xz != 0)
    {
        // Planes 1 and 5

        //Plane 1:
        const double mu_1 = determinant3x3({sost_A,z,a}) / det_xz;
        const double lambda_1 = determinant3x3({x,sost_A,a}) / det_xz;
        const double t_1 = ((-1) * determinant3x3({x,z,sost_A})) / det_xz;

        if (0 <= mu_1 && mu_1 <= norm(d) && 0 <= lambda_1 && lambda_1 <= norm(e) && 0 <= t_1)
        {
            return true;
        }

        //Plane 5:
        const double mu_2 = determinant3x3({sost_B,z,a}) / det_xz;
        const double lambda_2 = determinant3x3({x,sost_B,a}) / det_xz;
        const double t_2 = ((-1) * determinant3x3({x,z,sost_B})) / det_xz;

        if (0 >= mu_2 && abs(mu_2) <= norm(d) && 0 >= lambda_2 && abs(lambda_2) <= norm(e) && 0 <= t_2)
        {
            return true;
        }

    } else if (det_yz != 0)
    {
        // Planes 2 and 6

        //Plane 2:
        const double mu_1 = determinant3x3({sost_A,z,a}) / det_yz;
        const double lambda_1 = determinant3x3({y,sost_A,a}) / det_yz;
        const double t_1 = ((-1) * determinant3x3({y,z,sost_A})) / det_yz;

        if (0 <= mu_1 && mu_1 <= norm(p) && 0 <= lambda_1 && lambda_1 <= norm(e) && 0 <= t_1)
        {
            return true;
        }

        //Plane 6:
        const double mu_2 = determinant3x3({sost_B,z,a}) / det_yz;
        const double lambda_2 = determinant3x3({y,sost_B,a}) / det_yz;
        const double t_2 = ((-1) * determinant3x3({y,z,sost_B})) / det_yz;

        if (0 >= mu_2 && abs(mu_2) <= norm(p) && 0 >= lambda_2 && abs(lambda_2) <= norm(e) && 0 <= t_2)
        {
            return true;
        }

    } else if (det_xy != 0)
    {
        // Planes 3 and 4

        //Plane 3:
        const double mu_1 = determinant3x3({sost_A,y,a}) / det_xy;
        const double lambda_1 = determinant3x3({x,sost_A,a}) / det_xy;
        const double t_1 = ((-1) * determinant3x3({x,y,sost_A})) / det_xy;

        if (0 <= mu_1 && mu_1 <= norm(d) && 0 <= lambda_1 && lambda_1 <= norm(p) && 0 <= t_1)
        {
            return true;
        }

        //Plane 4:
        const double mu_2 = determinant3x3({sost_B,y,a}) / det_xy;
        const double lambda_2 = determinant3x3({x,sost_B,a}) / det_xy;
        const double t_2 = ((-1) * determinant3x3({x,y,sost_B})) / det_xy;

        if (0 >= mu_2 && abs(mu_2) <= norm(d) && 0 >= lambda_2 && abs(lambda_2) <= norm(p) && 0 <= t_2)
        {
            return true;
        }

    }

    return false;

    /* Test this code 
    double tMinX = (bb_min_[0] - _ray.origin[0]) / _ray.direction[0];
    double tMinY = (bb_min_[1] - _ray.origin[1]) / _ray.direction[1];
    double tMinZ = (bb_min_[2] - _ray.origin[2]) / _ray.direction[2];
    double tMaxX = (bb_max_[0] - _ray.origin[0]) / _ray.direction[0];
    double tMaxY = (bb_max_[1] - _ray.origin[1]) / _ray.direction[1];
    double tMaxZ = (bb_max_[2] - _ray.origin[2]) / _ray.direction[2];

    tMinX = std::min(tMinX, tMaxX);
    tMinY = std::min(tMinY, tMaxY);
    tMinZ = std::min(tMinZ, tMaxZ);
    tMaxX = std::max(tMaxX, tMinX);
    tMaxY = std::max(tMaxY, tMinY);
    tMaxZ = std::max(tMaxZ, tMinZ);

    double tEnter = std::max(tMinX, tMinY, tMinZ);
    double tExit = std::min(tMaxX, tMaxY, tMaxZ);

    if (tEnter > tExit || tExit < 0) {
       return false;
    }
    return true;

    */


    /** \todo
    * Intersect the ray `_ray` with the axis-aligned bounding box of the mesh.
    * Note that the minimum and maximum point of the bounding box are stored
    * in the member variables `bb_min_` and `bb_max_`. Return whether the ray
    * intersects the bounding box.
    * This function is ued in `Mesh::intersect()` to avoid the intersection test
    * with all triangles of every mesh in the scene. The bounding boxes are computed
    * in `Mesh::compute_bounding_box()`.
    */
}


//-----------------------------------------------------------------------------


bool Mesh::intersect(const Ray& _ray,
                     vec3&      _intersection_point,
                     vec3&      _intersection_normal,
                     double&    _intersection_t ) const
{
    // check bounding box intersection
    if (!intersect_bounding_box(_ray))
    {
        return false;
    }

    vec3   p, n;
    double t;

    _intersection_t = NO_INTERSECTION;

    // for each triangle
    for (const Triangle& triangle : triangles_)
    {
        // does ray intersect triangle?
        if (intersect_triangle(triangle, _ray, p, n, t))
        {
            // is intersection closer than previous intersections?
            if (t < _intersection_t)
            {
                // store data of this intersection
                _intersection_t      = t;
                _intersection_point  = p;
                _intersection_normal = n;
            }
        }
    }

    return (_intersection_t != NO_INTERSECTION);
}


//-----------------------------------------------------------------------------

bool
Mesh::
intersect_triangle(const Triangle&  _triangle,
                   const Ray&       _ray,
                   vec3&            _intersection_point,
                   vec3&            _intersection_normal,
                   double&          _intersection_t) const
{
    //Get the vertices of the given triangle:
    const vec3& p0 = vertices_[_triangle.i0].position;
    const vec3& p1 = vertices_[_triangle.i1].position;
    const vec3& p2 = vertices_[_triangle.i2].position;

    //A triangle can be represented through this formula: x = 1*U + a*A + b*B
    // U is the origin of the triangle, A and B are the two vectors that indicate the other two Vertices starting from U
    // 0 <= a,b <= 1
    //To find the intersection with a ray: o + td = 1*U + a*A + b*B
    //This is the same as: o - U = a*A + b*B - td
    //Seen as a matrix: o - U = (A,B,d) * (a,b,t)^T

    // o - U
    const vec3 b = _ray.origin - p2;

    // a
    const vec3 alphaPart = p0 - p2;

    // b
    const vec3 betaPart = p1 - p2;

    // -d
    const vec3 tPart = _ray.direction * (-1);

    //Matrix (A,B,d)
    const std::vector<vec3> A = { alphaPart, betaPart, tPart};

    //Cramer's Rule applied:
    const double detA = determinant3x3(A);
    // a
    const double alpha = determinant3x3({b, betaPart, tPart}) / detA;
    // b
    const double beta = determinant3x3({alphaPart, b, tPart}) / detA;
    // t
    const double t = determinant3x3({alphaPart, betaPart, b}) / detA;

    // a and b must be positive. Here gamma doesn't refer to the other formula seen in the lesson.
    // gamma is used to check whether a and b are smaller-equal 1 or not
    const double gamma = 1 - alpha - beta;
    if (t < 0 || alpha < 0 || beta < 0 || gamma < 0) {
        return false;
    }

    //Saves the things that we need:
    _intersection_t = t;
    _intersection_point = _ray(_intersection_t);

    //Returns the right _intersection_normal according to the draw_mode_
    if (draw_mode_ == FLAT) {
        _intersection_normal = normalize(_triangle.normal);
    } else {
        _intersection_normal = normalize(
            alpha * vertices_[_triangle.i0].normal + beta * vertices_[_triangle.i1].normal + gamma * vertices_[_triangle
                .i2].normal);
    }

    return true;
    /** \todo
    * - intersect _ray with _triangle
    * - store intersection point in `_intersection_point`
    * - store ray parameter in `_intersection_t`
    * - store normal at intersection point in `_intersection_normal`.
    * - Depending on the member variable `draw_mode_`, use either the triangle
    *  normal (`Triangle::normal`) or interpolate the vertex normals (`Vertex::normal`).
    * - return `true` if there is an intersection with t > 0 (in front of the viewer)
    *
    * Hint: Rearrange `ray.origin + t*ray.dir = a*p0 + b*p1 + (1-a-b)*p2` to obtain a solvable
    * system for a, b and t.
    *
    * Refer to [Cramer's Rule](https://en.wikipedia.org/wiki/Cramer%27s_rule) to easily solve it.
     */

    return false;
}


//=============================================================================
