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
