import "io" for Path
import "math" for Vec3, Mat

class Main {
    construct new() {
	    System.print("Hello world")
        System.print("======================================\n")
        var p = Path.new("~/GitHub/wren-emcc")

        System.print(p.ToString())
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


var fiber = Fiber.new {|param|
  System.print(param)
  var result = Fiber.yield()
  System.print(result)
}

fiber.call("First") //> First
fiber.call("Second") //> Second
