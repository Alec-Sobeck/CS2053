#pragma once

#include <glbinding/gl/nogl.h>
#include <glbinding/gl/types.h>

#include <glbinding/gl/bitfield.h>

#include <glbinding/SharedBitfield.hpp>

namespace gl11
{

// import bitfields to namespace
static const gl::ClientAttribMask GL_CLIENT_PIXEL_STORE_BIT = gl::ClientAttribMask::GL_CLIENT_PIXEL_STORE_BIT;
static const gl::AttribMask GL_CURRENT_BIT = gl::AttribMask::GL_CURRENT_BIT;
static const gl::ClientAttribMask GL_CLIENT_VERTEX_ARRAY_BIT = gl::ClientAttribMask::GL_CLIENT_VERTEX_ARRAY_BIT;
static const gl::AttribMask GL_POINT_BIT = gl::AttribMask::GL_POINT_BIT;
static const gl::AttribMask GL_LINE_BIT = gl::AttribMask::GL_LINE_BIT;
static const gl::AttribMask GL_POLYGON_BIT = gl::AttribMask::GL_POLYGON_BIT;
static const gl::AttribMask GL_POLYGON_STIPPLE_BIT = gl::AttribMask::GL_POLYGON_STIPPLE_BIT;
static const gl::AttribMask GL_PIXEL_MODE_BIT = gl::AttribMask::GL_PIXEL_MODE_BIT;
static const gl::AttribMask GL_LIGHTING_BIT = gl::AttribMask::GL_LIGHTING_BIT;
static const gl::AttribMask GL_FOG_BIT = gl::AttribMask::GL_FOG_BIT;
static const glbinding::SharedBitfield<gl::AttribMask, gl::ClearBufferMask> GL_DEPTH_BUFFER_BIT = gl::AttribMask::GL_DEPTH_BUFFER_BIT;
static const glbinding::SharedBitfield<gl::AttribMask, gl::ClearBufferMask> GL_ACCUM_BUFFER_BIT = gl::AttribMask::GL_ACCUM_BUFFER_BIT;
static const glbinding::SharedBitfield<gl::AttribMask, gl::ClearBufferMask> GL_STENCIL_BUFFER_BIT = gl::AttribMask::GL_STENCIL_BUFFER_BIT;
static const gl::AttribMask GL_VIEWPORT_BIT = gl::AttribMask::GL_VIEWPORT_BIT;
static const gl::AttribMask GL_TRANSFORM_BIT = gl::AttribMask::GL_TRANSFORM_BIT;
static const gl::AttribMask GL_ENABLE_BIT = gl::AttribMask::GL_ENABLE_BIT;
static const glbinding::SharedBitfield<gl::AttribMask, gl::ClearBufferMask> GL_COLOR_BUFFER_BIT = gl::AttribMask::GL_COLOR_BUFFER_BIT;
static const gl::AttribMask GL_HINT_BIT = gl::AttribMask::GL_HINT_BIT;
static const gl::AttribMask GL_EVAL_BIT = gl::AttribMask::GL_EVAL_BIT;
static const gl::AttribMask GL_LIST_BIT = gl::AttribMask::GL_LIST_BIT;
static const gl::AttribMask GL_TEXTURE_BIT = gl::AttribMask::GL_TEXTURE_BIT;
static const gl::AttribMask GL_SCISSOR_BIT = gl::AttribMask::GL_SCISSOR_BIT;
static const gl::AttribMask GL_ALL_ATTRIB_BITS = gl::AttribMask::GL_ALL_ATTRIB_BITS;
static const gl::ClientAttribMask GL_CLIENT_ALL_ATTRIB_BITS = gl::ClientAttribMask::GL_CLIENT_ALL_ATTRIB_BITS;

} // namespace gl11
