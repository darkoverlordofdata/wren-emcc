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

// var a = Vec3.new(1, 2, 3)
// var b = Vec3.new(4, 5, 6)

// var z = a.dot(b)

