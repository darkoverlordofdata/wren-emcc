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
