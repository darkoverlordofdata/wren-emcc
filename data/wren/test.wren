import "lib/io/path" for Path
import "lib/math/vec3" for Vec3

class Main {
    construct new() {
    }
    main() { 
	    System.print("Hello world again")
        System.print("======================================\n")
    }
    static helloWorld() { 

        return "Hola Mundo"

    }
    testly() {
        return "Hello World"
    }

    vectors() {
        var a = Vec3.new(1, 2, 3)
        var b = Vec3.new(4, 5, 6)

        var z = a.dot(b)
        return z
        // return 0

    }

    vectorx() {
        var a = Vec3.new(1, 2, 3)
        return a.z
        // return 0

    }
}

var test = Main.new()
var z = Mat.new()
z.identity()
System.print("%(z[0, 0]) %(z[0, 1]) %(z[0, 2]) %(z[0, 3])")
System.print("%(z[1, 0]) %(z[1, 1]) %(z[1, 2]) %(z[1, 3])")
System.print("%(z[2, 0]) %(z[2, 1]) %(z[2, 2]) %(z[2, 3])")
System.print("%(z[3, 0]) %(z[3, 1]) %(z[3, 2]) %(z[3, 3])")

// var a = Vec3.new(1, 2, 3)
// var b = Vec3.new(4, 5, 6)

// var z = a.dot(b)

