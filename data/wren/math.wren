/**
 * Native Vector2
 */
foreign class Vec2 {
  construct new( x, y ) {}

  foreign clamp(a, b)
  foreign dot( rhs )
  foreign length()
  foreign norm()
  foreign norm2()
  foreign normalize()

  // accessors
  foreign x
  foreign x=( rhs )
  foreign y
  foreign y=( rhs )
}



/**
 * Native Vector3
 */
foreign class Vec3 {
  construct new( x, y, z ) {}

  foreign clamp(a, b)
  foreign dot( rhs )
  foreign length()
  foreign norm()
  foreign norm2()
  foreign normalize()

  // accessors
  foreign x
  foreign x=( rhs )
  foreign y
  foreign y=( rhs )
  foreign z
  foreign z=( rhs )
}

/**
 * Native Vector4
 */
foreign class Vec4 {
  construct new( x, y, z, w ) {}

  foreign clamp(a, b)
  foreign dot( rhs )
  foreign length()
  foreign norm()
  foreign norm2()

  // accessors
  foreign x
  foreign x=( rhs )
  foreign y
  foreign y=( rhs )
  foreign z
  foreign z=( rhs )
  foreign w
  foreign w=( rhs )
}

/**
 * Native Matrix4x4
 */
foreign class Mat {
  construct new( ) {}

  foreign identity()
  foreign scale( rhs )
  foreign ortho( left, right, bottom, top, nearVal, farVal)
  foreign rotate( angle, vec)

  foreign [col, row]

}

