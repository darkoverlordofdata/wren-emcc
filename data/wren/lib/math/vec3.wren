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
