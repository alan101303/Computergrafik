//=============================================================================
//
//   Exercise code for the lecture "Introduction to Computer Graphics"
//     by Prof. Mario Botsch, Bielefeld University
//
//   Copyright (C) by Computer Graphics Group, Bielefeld University
//
//=============================================================================

#version 140
#extension GL_ARB_explicit_attrib_location : enable

//These things are n world coordinates, probably
layout (location = 0) in vec4 v_position; //World space position of the vertex
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 v_texcoord; //Coordinates to draw a texture on the face we want to render (for .frag)

out vec2 v2f_texcoord;
out vec3 v2f_normal;
out vec3 v2f_light;
out vec3 v2f_view;

//Uniforms are read only in both Vertex and Fragment Shader.
//This means: I don't have to calculate them here.
uniform mat4 modelview_projection_matrix;
uniform mat4 modelview_matrix;
uniform mat3 normal_matrix;
uniform vec4 light_position; //in eye space coordinates already



void main()
{
    /** \todo Setup all outgoing variables so that you can compute in the fragment shader
      the phong lighting. You will need to setup all the uniforms listed above, before you
      can start coding this shader.

      Hint: Compute the vertex position, normal and light_position in eye space.
      Hint: Write the final vertex position to gl_Position
    */

    //texcoordinate is hopefully already ok.
    v2f_texcoord = v_texcoord;

    //multiply v_normal with the matrix that is named normal, don't forget to normalize
    v2f_normal = normalize(normal_matrix * v_normal);

    //put the vector position in view coordinate to match light_position
    vec4 eye_v_position = normalize(modelview_matrix * v_position);

    //the view is at the origin of the system of reference of eye_v_position
    //multiply by -1 to get a vector that goes in the direction of the view
    //don't forget to normalize
    v2f_view = normalize(-eye_v_position).xyz;

    //find the vector that goes from the vector to the light source,
    //and normalize
    v2f_light = normalize(light_position - eye_v_position).xyz;

    //follow the hint
    gl_Position = normalize(modelview_projection_matrix * v_position);



}
